�÷�:
��cmd��ִ������
python ***\deal_kernel_log.py ***\kernel_log�ļ� ***\���ɽ���ļ���


ʾ��˵��
log��ʱ��������Ϊץȡ��62:25:40.456��log
log total time:  62:25:40.456													

suspend entry: ϵͳ��ʼ��suspend����
suspend exit:  ϵͳ��ʼ��resume����
suspend total time: 57:19:25.554    (suspend����ʱ�䣬��57:19:25.554����suspend״̬)
resume total time:  05:03:53.67    (resume����ʱ�䣬��05:03:53.67����resume״̬)

ϵͳ�����󱻻��ѣ�rtc��ana��mbox��gpio)
��Ӧ�Ļ���Դ											    ����Դ��Ӧ�Ļ��Ѵ���
wakeup by INTC2 !! mask:0x00000020 raw:0xe0000020 en:0x00080038                                     1410
wake up by ana                                                                                      586
wakeup by INTC1 !! mask:0x00000040 raw:0x00000040 en:0x36af4ce8                                     586
wake up by mbox_tar_ap                                                                              1410

sleep���̱����
1��early wake event detected (sleeep���̱���ϵ�ԭ��Ϊ����wake event)				    ����ÿ��wake event�Ĵ���
active wakeup source: [timerfd]                                                                     1
active wakeup source: NETLINK                                                                       7
active wakeup source: rtc_irq                                                                       5
active wakeup source: psensor timeout wakelock                                                      1
active wakeup source: smsg-5-7                                                                      25
2��Some devices failed to suspend(sleeep���̱���ϵ�ԭ��Ϊ�豸suspendʧ��)			    �����豸suspendʧ�ܵĴ���
Device alarmtimer failed to suspend: error -16                                                      68

���������޷�����suspend
��Ӧ���ֵ���											    ���������ֵĴ���
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

��д���ݹ��󣬵���ͬ���ļ�ʧ��
total times:382  ���ܹ�ͬ���ļ�ʧ�ܵĴ�����
382[02-02 23:30:02.213] <6>[ 1993.005836] c0 PM: dirty and writeback data is 132 kB, it's too much for sys_sync, try again!  (��Сsize:132kb)
952[02-02 23:10:05.452] <6>[ 1977.372960] c0 PM: dirty and writeback data is 1172 kB, it's too much for sys_sync, try again! (���size:1172kb)






