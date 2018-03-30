#!/usr/bin/env Python
# coding=utf-8
import re ;
import datetime ;
import sys

#Pending_Wakeup_Sources="Pending Wakeup Sources"
#failed_power_down = "alarmtimer device failed to power down"
#noirq_suspend_alarmtimer_device="noirq suspend of alarmtimer device failed"
# Syncing_filesystems = "Syncing filesystems"
# Freezing_user_space_processes = "Freezing user space processes"
# Suspending_console = "Suspending console"
# Disabling_non_boot_CPU = "Disabling non-boot CPUs"
# cpu0_enter_sprd_pm_deepsleep = "cpu0, enter sprd_pm_deepsleep"
# Enabling_non_boot_CPUs = "Enabling non-boot CPUs"
# Restarting_tasks = "Restarting tasks"

failed_to_suspend_list = []
failed_to_suspend_list_not_suspend = []
hold_lock_list = []
suspend_entry_list = []
suspend_exit_list = []
suspend_entry_exit_list =[]
suspend_exit_entry_list =[]
wake_up_by_list = []
dirty_and_writeback_data_list = []
dirty_and_writeback_data_list_time = []
entry_suspend_time = "\d{2}-\d{2} \d{2}:\d{2}:\d{2}.\d*]"
can_not_suspend_flag = 0
failed_suspend_device_dic = {}
wake_up_by_mbox_dic1 = {}
wake_up_by_mbox_dic2 = {}
time_start = ""
time_end = ""
start_flag = 0
kernel_log_file = sys.argv[1]
log_result_file = sys.argv[2]

def cal_time(entry_list,exit_list,flag):
    for (entry_suspend, exit_suspend) in zip ( entry_list, exit_list ):
        entry_time = ''.join ( re.findall ( entry_suspend_time, entry_suspend ) ).replace ( "]", "" )
        exit_time = ''.join ( re.findall ( entry_suspend_time, exit_suspend ) ).replace ( "]", "" )
        entry_time_ms = datetime.datetime.strptime (entry_time, '%m-%d %H:%M:%S.%f')
        exit_time_ms = datetime.datetime.strptime ( exit_time, '%m-%d %H:%M:%S.%f' )

        if(flag==0):
            # 进入 suspend 到退出 suspend
            suspend_entry_exit_list.append((exit_time_ms - entry_time_ms).total_seconds())
        else:
            # 前一次退出 suspend 到当次进入 suspend
            suspend_exit_entry_list.append((entry_time_ms - exit_time_ms).total_seconds())

file_log = open (kernel_log_file, "rt", encoding="UTF-8", errors='ignore' ) ;
while True:
    content = file_log.readline () ;
    if not content:
        break ;
    #针对log的总时长
    if(len(re.findall(entry_suspend_time, content ))):
        if(start_flag==0):
            time_start = ''.join(re.findall(entry_suspend_time, content )).replace("]","")
            start_flag = 1
        else:
            time_end = ''.join(re.findall(entry_suspend_time, content )).replace("]","")

    # 针对suspend被打断
    if((content.find ( "active wakeup source" ) != -1)):
        can_not_suspend_flag = 1
        active_wakeup = content
    if (content.find ( "failed to suspend: error" ) != -1):
        can_not_suspend_flag = 2
        failed_dvice = content
    if (content.find ( "Some devices failed to suspend, or early wake event detected" ) != -1):
        if(can_not_suspend_flag==2):
            failed_dvice = ''.join ( re.findall ( "PM: Device .*", failed_dvice )).replace("PM: ", "")
            failed_to_suspend_list.append(failed_dvice)
        elif(can_not_suspend_flag==1):
            failed_to_suspend_list_not_suspend.append(active_wakeup)
            active_wakeup = ''.join ( re.findall ("active wakeup source: .*", active_wakeup ) )
            failed_to_suspend_list.append ( active_wakeup)

    # 针对持锁无法suspend
    if(content.find ("active wakeup source" ) != -1):
        hold_lock_list.append ( content)

    #针对entry suspend和exit suspend的时间
    if (content.find ( "suspend entry" ) != -1):
        suspend_entry_list.append(content)
    if (content.find ( "suspend exit" ) != -1):
        suspend_exit_list.append(content)

    # 针对唤醒源
    if ((content.find ( "wake up by" ) != -1) or (content.find ( "wakeup by" ) != -1)):
         wakeup_type= ''.join(re.findall ( "] c0 .*", content)).replace("] c0 ","")
         wake_up_by_list.append(wakeup_type)

    # 同步文件size过大
    if(re.findall ("dirty and writeback data is \d* kB", content )):
        size = int(''.join(re.findall ( "is \d*", content)).replace("is ", ""))
        dirty_and_writeback_data_list.append ( size)
        dirty_and_writeback_data_list_time.append(content)
file_log.close () ;

with open (log_result_file, "wt", encoding="UTF-8", errors='ignore' ) as file_result:
    # 显示log总时长
    time_space = (datetime.datetime.strptime ( time_end, '%m-%d %H:%M:%S.%f' )-
                  datetime.datetime.strptime ( time_start, '%m-%d %H:%M:%S.%f' )).total_seconds()
    total_time_hour = int(time_space//3600)
    total_time_min = int((time_space-total_time_hour*3600)//60)
    total_time_secound = int((time_space-total_time_hour*3600-total_time_min*60)//1)
    total_time_mesl = int(((time_space-total_time_hour * 3600 - total_time_min * 60 - total_time_secound) * 1000)//1)
    if (total_time_hour < 10):
        resume_hour = '0' + str ( total_time_hour )
    if (total_time_min < 10):
        resume_left_minute = '0' + str ( total_time_min )
    if (total_time_secound):
        resume_left_secound = '0' + str ( total_time_secound )
    file_result.write ( "log total time:  " + str ( total_time_hour ) + ':' + str ( total_time_min ) + ':' + str (
        total_time_secound ) + '.' + str ( total_time_mesl ) + '\n' )


    if(len(suspend_entry_list) or len(suspend_exit_list)):
        cal_time(suspend_entry_list,suspend_exit_list,0) # suspend的时间
        secound_suspend_entry_list = list(suspend_entry_list)
        secound_suspend_exit_list = list(suspend_exit_list)
        secound_suspend_entry_list.pop ( 0 )
        secound_suspend_exit_list.pop ()
        cal_time ( secound_suspend_entry_list, secound_suspend_exit_list ,1) # resume的总时间

        file_result.write ( "\nsuspend entry: 系统开始走suspend流程\n" )
        file_result.write ( "suspend exit:  系统开始走resume流程\n" )

        suspend_hour = int((sum(suspend_entry_exit_list))//3600)
        suspend_left_minute =int(((sum(suspend_entry_exit_list))-suspend_hour*3600)//60)
        suspend_left_secound = int(((sum(suspend_entry_exit_list))-suspend_hour*3600-suspend_left_minute*60)//1)
        suspend_left_msel = int(((((sum(suspend_entry_exit_list))-suspend_hour*3600-suspend_left_minute*60) - suspend_left_secound)*1000)//1)
        if(suspend_hour<10):
            resume_hour = '0'+str(suspend_hour)
        if(suspend_left_minute<10):
            resume_left_minute =  '0'+str(suspend_left_minute)
        if(suspend_left_secound):
            resume_left_secound = '0'+str(suspend_left_secound)
        file_result.write("suspend total time: "+str(suspend_hour)+':'+str(suspend_left_minute)+':'+str(suspend_left_secound)+'.'+str(suspend_left_msel)+'\n')

        resume_hour = int((sum(suspend_exit_entry_list))//3600)
        resume_left_minute =int(((sum(suspend_exit_entry_list))-resume_hour*3600)//60)
        resume_left_secound = int(((sum(suspend_exit_entry_list))-resume_hour*3600-resume_left_minute*60)//1)
        resume_left_msel = int(((((sum(suspend_exit_entry_list))-resume_hour*3600-resume_left_minute*60) - resume_left_secound)*1000)//1)
        if(resume_hour<10):
            resume_hour = '0'+str(resume_hour)
        if(resume_left_minute<10):
            resume_left_minute =  '0'+str(resume_left_minute)
        if(resume_left_secound):
            resume_left_secound = '0'+str(resume_left_secound)
        file_result.write("resume total time:  "+str(resume_hour)+':'+str(resume_left_minute)+':'+str(resume_left_secound)+'.'+str(resume_left_msel)+'\n')

    if (len ( wake_up_by_list )):
        file_result.write ( "\n系统待机后被唤醒（rtc、ana、mbox、gpio)\n" )
        wake_up_by_set = set(wake_up_by_list)
        for x in wake_up_by_set:
            if(x.find("mbox: wake up by")!=-1 ):
                wake_up_by_mbox_dic1[x] = wake_up_by_list.count(x)
            elif(x.find("wake up by mbox")!=-1):
                wake_up_by_mbox_dic2[x] = wake_up_by_list.count ( x )
            else:
                file_result.write ( "%-100s"%x+str(wake_up_by_list.count(x))+'\n' )
        for key1, key2 in zip(wake_up_by_mbox_dic1,wake_up_by_mbox_dic2):
            if(wake_up_by_mbox_dic1[key1] == wake_up_by_mbox_dic2[key2]):
                file_result.write("%-100s" % key2 + str(wake_up_by_mbox_dic2[key2])+ '\n')


    if (len ( failed_to_suspend_list )):
        file_result.write ( "\nsleep过程被打断\n" )
        failed_to_suspend_set = set(failed_to_suspend_list)
        file_result.write("1、early wake event detected\n")
        for x in  failed_to_suspend_set:
            if(x.find("failed to suspend: error")!=-1):
                failed_suspend_device_dic[x] = failed_to_suspend_list.count ( x )
            else:
                file_result.write ( "%-100s" % x + str ( failed_to_suspend_list.count ( x ))+'\n')
        file_result.write("2、Some devices failed to suspend\n")
        for key in failed_suspend_device_dic:
            file_result.write ( "%-100s" % key + str(failed_suspend_device_dic[key])+ '\n' )


    if (len ( hold_lock_list )):
        file_result.write ( "\n持锁导致无法进入suspend\n" )
        list_result_not_suspend = [l for l in hold_lock_list if l not in failed_to_suspend_list_not_suspend]
        list_result = []
        for x in  list(list_result_not_suspend):
            list_result.append(''.join(re.findall("active wakeup source: .*",x)))
        for x in set(list_result):
            file_result.write ( "%-100s" % x + str ( list_result.count ( x ) ) + '\n' )

    if (len ( dirty_and_writeback_data_list )):
            file_result.write ( "\n回写数据过大，导致同步文件失败\n" )
            file_result.write("total times:"+str(len(dirty_and_writeback_data_list))+'\n')
            file_result.write(dirty_and_writeback_data_list_time[
                                  dirty_and_writeback_data_list.index(min(dirty_and_writeback_data_list))])
            file_result.write ( dirty_and_writeback_data_list_time[
                                    dirty_and_writeback_data_list.index ( max ( dirty_and_writeback_data_list ) )] )

file_result.close () ;

