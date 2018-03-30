用法:
在cmd行执行命令
python ***\deal_kernel_log.py ***\kernel_log文件 ***\生成结果文件名


示例说明
log总时长，以下为抓取了62:25:40.456的log
log total time:  62:25:40.456													

suspend entry: 系统开始走suspend流程
suspend exit:  系统开始走resume流程
suspend total time: 57:19:25.554    (suspend的总时间，有57:19:25.554处于suspend状态)
resume total time:  05:03:53.67    (resume的总时间，有05:03:53.67处于resume状态)

系统待机后被唤醒（rtc、ana、mbox、gpio)
对应的唤醒源											    唤醒源对应的唤醒次数
wakeup by INTC2 !! mask:0x00000020 raw:0xe0000020 en:0x00080038                                     1410
wake up by ana                                                                                      586
wakeup by INTC1 !! mask:0x00000040 raw:0x00000040 en:0x36af4ce8                                     586
wake up by mbox_tar_ap                                                                              1410

sleep过程被打断
1、early wake event detected (sleeep过程被打断的原因为发现wake event)				    具体每个wake event的次数
active wakeup source: [timerfd]                                                                     1
active wakeup source: NETLINK                                                                       7
active wakeup source: rtc_irq                                                                       5
active wakeup source: psensor timeout wakelock                                                      1
active wakeup source: smsg-5-7                                                                      25
2、Some devices failed to suspend(sleeep过程被打断的原因为设备suspend失败)			    具体设备suspend失败的次数
Device alarmtimer failed to suspend: error -16                                                      68

持锁导致无法进入suspend
对应所持的锁											    所持锁出现的次数
active wakeup source: PowerManagerService.WakeLocks                                                 3
active wakeup source: eventpoll                                                                     1686
active wakeup source: [timerfd]                                                                     1
active wakeup source: NETLINK                                                                       183
active wakeup source: sbuf-5-4-1-rx                                                                 5
active wakeup source: sbuf-5-6-1-rx                                                                 2
active wakeup source: alarmtimer                                                                    6
active wakeup source: KeyEvents                                                                     3
active wakeup source: psensor timeout wakelock                                                      9
active wakeup source: pub_int_handle_wakelock                                                       11
active wakeup source: sdiom_rx_wakelock                                                             13
active wakeup source: smsg-5-7                                                                      67
active wakeup source: sprdwl_keep_wakelock                                                          1

回写数据过大，导致同步文件失败
total times:382  （总共同步文件失败的次数）
382[02-02 23:30:02.213] <6>[ 1993.005836] c0 PM: dirty and writeback data is 132 kB, it's too much for sys_sync, try again!  (最小size:132kb)
952[02-02 23:10:05.452] <6>[ 1977.372960] c0 PM: dirty and writeback data is 1172 kB, it's too much for sys_sync, try again! (最大size:1172kb)






