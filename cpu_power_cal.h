#include<stdio.h>
#include<string.h>
#include <stdarg.h>
#include <unistd.h>

#define LOG_NDEBUG 	1
#define LOG_TAG 	"cpu_power_cal"
#include "utils/Log.h"

#define FREQ_HEX	1000000
#define VDD_HEX		1000
#define TEMP_HEX	1000
#define V_BASE		0.8

#define P_DYNBASE_LIT	57.0
#define P_LEAKBASE_LIT	1.714

#define P_DYNBASE_MID	73.5
#define P_LEAKBASE_MID	4.258

#define P_DYNBASE_BIG	275.0
#define P_LEAKBASE_BIG	8.309

#define P_DYNBASE_FCM	34.75
#define P_LEAKBASE_FCM	2.908

#define TSCAL_A		0.0000825
#define TSCAL_B		-0.011700
#define TSCAL_C		0.608000
#define TSCAL_D		-8.185000

#define VSCAL_A		-0.115000
#define VSCAL_B		1.027000
#define VSCAL_C		0.577000
#define VSCAL_D		-0.060000

#define CPU_THERMAL_PATH	"/sys/class/thermal/thermal_zone0/temp"
#define CPU_CORE			"cpu"
#define CPU_VDD_PATH		"/sys/cpu_power/cluster" 
#define VDD_FCM_FREQ		"/sys/devices/system/cpu/cpu6/cpufreq/scaling_cur_freq"
#define CPU_FCM_FREQ		"/sys/devices/system/cpu/cpu7/cpufreq/scaling_cur_freq"
#define CPU_OFFLINE_PATH	"/sys/devices/system/cpu/offline"

#define CORE_NUM			4
#define CLUSTER_RX_LEN		3 // for each clutser rx is 3
#define CLUSTER_GROUP_LEN	9 
#define MAX_N				861

struct dvfs_table{
	unsigned long int freq;
	unsigned long int vdd;
};

struct cluster_rx{
	float arry_rx[CLUSTER_GROUP_LEN+1];// add taux
};




