#include<cpu_power_cal.h>

#define CLUSTER_NUM			4

float cluster_power[CLUSTER_NUM];
char buffer[80];

// dvfs_table
struct cluster_dvfs{
	struct dvfs_table cluster1[3];
	struct dvfs_table cluster2[5];
	struct dvfs_table cluster3[5];
	struct dvfs_table fcm[5];
}whalek_dvfs={
	      {{1000000, 700000},{1125000, 750000},{1250000, 800000}},
	      {{1488000, 800000},{1616000, 850000},{1744000, 900000},{1872000, 950000},{2000000, 1000000}},
	      {{1432000, 800000},{1574000, 850000},{1716000, 900000},{1858000, 950000},{2000000, 1000000}},
	      {{1072000, 800000},{1179000, 850000},{1286000, 900000},{1393000, 950000},{1500000, 1000000}}
};

// thermal model
struct cluster_group{
	char *name;
	signed int cpu_n;
	float clutser_temp;
	float arry_tn[CLUSTER_RX_LEN];
	struct cluster_rx cluster_Rx_group[CLUSTER_RX_LEN];
	
}cluster_group_mem[CLUSTER_GROUP_LEN]={
			{"SOC", -1, 0.0, {0.0, 0.0, 0.0},
			{{{4.358, 4.337, 4.364, 4.418, 4.465, 4.292, 4.300, 4.371, 6.630, 0.610420}},
			 {{7.133, 6.645, 6.282, 5.887, 5.603, 7.042, 6.491, 6.061, 8.670, 0.017805}},
			{{7.188, 7.151, 7.127, 7.103, 7.085, 7.212, 7.164, 7.129, 7.428, 0.005420}}}},
			{"Little1", 0, 0.0, {0.0, 0.0, 0.0},
			{{{5.005, 6.086, 7.045, 7.350, 7.073, 16.220, 11.128, 8.491, 4.055, 0.997899}},
			 {{7.815, 8.338, 8.625, 8.638, 8.503, 10.238, 9.476, 8.914, 7.502, 0.031315}},
			{{7.275, 7.364, 7.424, 7.436, 7.418, 7.864, 7.644, 7.512, 7.259, 0.000708}}}},
			{"Little2", 1, 0.0, {0.0, 0.0, 0.0},
			{{{4.692, 5.665, 7.009, 8.471, 9.010, 10.651, 17.464, 13.514, 4.016, 0.996740}},
			 {{7.398, 8.083, 8.543, 8.838, 8.892, 9.393, 10.343, 9.634, 6.893, 0.032136}},
			{{7.227, 7.330, 7.416, 7.480, 7.497, 7.623, 7.900, 7.687, 7.194, 0.000717}}}}, 
			{"Little3", 2, 0.0, {0.0, 0.0, 0.0},
			{{{4.614, 5.538, 7.063, 9.408, 11.497, 8.390, 13.099, 21.744, 4.066, 0.989938}},
			 {{7.174, 7.953, 8.496, 8.957, 9.267, 8.896, 9.580, 10.618, 6.478, 0.034786}},
			{{7.202, 7.312, 7.408, 7.503, 7.575, 7.507, 7.672, 7.972, 7.154, 0.000742}}}},
			{"Ananke1", 3, 0.0, {0.0, 0.0, 0.0},
			{{{9.867, 17.912, 12.205, 8.235, 6.710, 6.159, 5.746, 5.602, 4.059, 0.996238}},
			{{9.208, 10.371, 9.559,	8.821, 8.362, 8.358, 8.120, 7.979, 7.068, 0.031944}},
			{{7.482, 7.789, 7.581, 7.432, 7.356, 7.359, 7.327, 7.308, 7.173, 0.000707}}}},
			{"Ananke2", 4, 0.0, {0.0, 0.0, 0.0},
			{{{7.012, 12.213, 18.196, 12.524, 9.550, 7.037, 7.004, 7.043, 4.037, 0.995896}},
			 {{8.603, 9.559, 10.449, 9.523, 8.953, 8.616, 8.540, 8.484, 6.756, 0.032573}},
			{{7.374, 7.581, 7.830, 7.589, 7.471, 7.415, 7.407, 7.399, 7.149, 0.000715 }}}},
			{"Ananke3", 5, 0.0, {0.0, 0.0, 0.0},
			{{{5.368, 8.016, 12.504, 19.954, 16.194, 7.316, 8.515, 9.614, 4.091, 0.993339}},
			 {{7.925, 8.768, 9.511, 10.555, 9.794, 8.617, 8.837, 8.979, 6.301, 0.033154}},
			 {{7.276, 7.424, 7.588, 7.869 , 7.663, 7.426, 7.475 , 7.504 , 7.115, 0.000722}}}}, 
			{"Ananke4", 6, 0.0, {0.0, 0.0, 0.0},
			{{{4.875, 6.634, 9.690, 15.765, 25.094, 7.023, 8.914, 11.582, 4.145, 0.981408}},
			 {{7.483, 8.339, 8.974, 9.744 , 10.861, 8.483, 8.865 , 9.265, 6.003, 0.036018}},
			{{7.222, 7.354, 7.477, 7.651 , 7.952 , 7.408, 7.486 , 7.571, 7.094, 0.000748}}}},
			{"prometheus", 7, 0.0, {0.0, 0.0, 0.0},
			{{{14.657, 10.125, 6.978, 5.442, 4.905, 5.041, 4.722, 4.633, 4.177, 0.967003}},
			 {{9.943, 9.236, 8.581, 7.953, 7.483, 7.823, 7.422, 7.178, 7.453, 0.027778659}},
			 {{7.648, 7.487, 7.369, 7.277, 7.219, 7.265, 7.219, 7.192, 7.206, 0.000662661}}}},
};

// power model
struct power_modle{
	float v_base;
	
	float p_dyperghz;
	float p_leak_base;
	
    float t_scale_a;
    float t_scale_b;
    float t_scale_c;
    float t_scale_d;
   
    float v_scale_e;
    float v_scale_f;
    float v_scale_g;
    float v_scale_h;
}cpu_power_modle[CLUSTER_NUM]={
	{0.8, 34.75, 2.908, 0.0000825, -0.011700, 0.608000, -8.185000, -0.115000, 1.027000, 0.577000, -0.060000},
	{0.8, 57.0, 1.714, 0.0000825, -0.011700, 0.608000, -8.185000, -0.115000, 1.027000, 0.577000, -0.060000},
	{0.8, 73.5, 4.258, 0.0000825, -0.011700, 0.608000, -8.185000, -0.115000, 1.027000, 0.577000, -0.060000},
	{0.8, 275.0, 8.309, 0.0000825, -0.011700, 0.608000, -8.185000, -0.115000, 1.027000, 0.577000, -0.060000}
};


// thermal model
int deal_arry_p(int *arry_p, int n)
{
	int p_key = 0;
	int temp_key = 0;
	if(n<90){
		p_key = n/71;
		arry_p[p_key] = (p_key==0)?1:0;
	}else if(n<MAX_N){
		p_key = (n-90)/100+1;
		temp_key = n-n/100*100;      
		arry_p[p_key] = ((temp_key>=61)&&(temp_key<=90))?0:1;
	}
	return arry_p[p_key]?p_key:0;
}

float cal_txn(int n, float *arry_Rx,float *tn_1)
{
	float arithmetic = 0.0;
	float t1n = 0.0;
	int arry_p_index = 0;
	if(n==0){
		return t1n;
	}
	int arry_p[CLUSTER_GROUP_LEN] = {0,0,0,0,0,0,0,0,0};
	arry_p_index = deal_arry_p(arry_p, n);
	arithmetic = arry_p[arry_p_index]*arry_Rx[arry_p_index];
	t1n = arithmetic*arry_Rx[CLUSTER_GROUP_LEN]+(1-arry_Rx[CLUSTER_GROUP_LEN])*(*tn_1);
	*tn_1 = t1n;
	return t1n;
}

// write data to node
int store_cur_data(float power_total, char *store_file_path){
	FILE *fp_store_data = NULL;
	if((fp_store_data=fopen(store_file_path,"w"))==NULL){
		ALOGD("can not open the file:%s\n", store_file_path);
		return -1;
	}
	fprintf(fp_store_data, "%.3f\n", power_total);
	fclose(fp_store_data);
	fp_store_data = NULL;
	return 0;
}

// read data from node
long int get_cur_data(char *get_file_path) {
	FILE *fp_get_data = NULL;
	long int cur_data = 0;
	
	if((fp_get_data=fopen(get_file_path,"r"))==NULL){
		ALOGD("can not open the file:%s\n", get_file_path);
		return -1;
	}
	fscanf(fp_get_data,"%ld",&cur_data);
	fclose(fp_get_data);
	fp_get_data = NULL;
	return cur_data;
}


// match freq to vdd 
float find_vdd(struct dvfs_table *cluster, int len, unsigned long cur_freq_int){
	int i = 0;
	for(i=0;i<len;i++){
		if(cluster[i].freq == cur_freq_int ){
				return cluster[i].vdd;
		}
	}
	return 0;
}

float match_freq_to_vdd(unsigned long cur_freq_int, int cluster){
	unsigned long cpu_vdd = 0;
	switch(cluster){
		case 1://cluster1
			cpu_vdd = find_vdd(whalek_dvfs.cluster1,sizeof(whalek_dvfs.cluster1)/sizeof(whalek_dvfs.cluster1[0]),cur_freq_int);
			break;
		case 2://cluster2
			cpu_vdd = find_vdd(whalek_dvfs.cluster2,sizeof(whalek_dvfs.cluster2)/sizeof(whalek_dvfs.cluster2[0]),cur_freq_int);
			break;
		case 3://cluster3
			cpu_vdd = find_vdd(whalek_dvfs.cluster3,sizeof(whalek_dvfs.cluster3)/sizeof(whalek_dvfs.cluster3[0]),cur_freq_int);
			break;
		case 4:// fcm
			cpu_vdd = find_vdd(whalek_dvfs.fcm,sizeof(whalek_dvfs.fcm)/sizeof(whalek_dvfs.fcm[0]),cur_freq_int);
			break;
		default:
			break;
	}
	return cpu_vdd/1000000;
}

// cal power for each core
float cal_each_core_power(signed int cpu_n, float cpu_temp){
	float cpu_power = 0.0;
	unsigned long cpu_freq = 0;
	char ch_cpu_n[10] = {cpu_n +'0'};
	char cpu_cur_freq[100] = "/sys/devices/system/cpu/cpu";
	float cpu_vdd = 0.0;
	float p_dyn = 0.0;
	float p_leak = 0.0;
	float t_scale = 0.0;
	float v_scale = 0.0;
	int index = 0;
	strcat(cpu_cur_freq, ch_cpu_n);
	strcat(cpu_cur_freq, "/cpufreq/scaling_cur_freq");
	switch(cpu_n){
		case 0:
		case 1:
		case 2:
			index = 0;
			cpu_freq = get_cur_data(cpu_cur_freq);
			break;
		case 3:
		case 4:
		case 5:
		case 6:
			index = 1;
			cpu_freq = get_cur_data(cpu_cur_freq);
			break;
		case 7:
			index = 2;
			cpu_freq = get_cur_data(cpu_cur_freq);
			break;
		case 8:
			index = 2;
			cpu_freq = 1000000; 
			break;
	}
	cpu_vdd = match_freq_to_vdd(cpu_freq, index+1);
	p_dyn = cpu_power_modle[index].p_dyperghz*cpu_freq*cpu_vdd*cpu_vdd/(cpu_power_modle[index].v_base*cpu_power_modle[index].v_base);
	t_scale = cpu_power_modle[index].t_scale_a*cpu_temp*cpu_temp*cpu_temp+cpu_power_modle[index].t_scale_b*cpu_temp*cpu_temp+cpu_power_modle[index].t_scale_c*cpu_temp+cpu_power_modle[index].t_scale_d;
	v_scale = cpu_power_modle[index].v_scale_e*cpu_vdd*cpu_vdd*cpu_vdd + cpu_power_modle[index].v_scale_f*cpu_vdd*cpu_vdd + cpu_power_modle[index].v_scale_g*cpu_vdd+cpu_power_modle[index].v_scale_h;
	p_leak = cpu_power_modle[index].p_leak_base*t_scale*v_scale;
	cpu_power = p_dyn + p_leak;
	return cpu_power;
}


int get_bigcore_status(){
	FILE *fp_get_data = NULL;
    char cur_data[20];
    char *big_core = "7";
	int ret = 0;

    if((fp_get_data=fopen(CPU_OFFLINE_PATH,"r"))==NULL){
		ALOGD("can not open the file\n");
         return -1;
    }
    fscanf(fp_get_data,"%s",cur_data);
    if(strstr(cur_data, big_core)){
		ret = 1;
    }
    fclose(fp_get_data);
    fp_get_data = NULL;
	return ret;
}

int vspf(char *fmt,...){
        va_list ap;
        int cnt;
        memset(buffer,0,80);
        va_start(ap,fmt);
        cnt = vsprintf(buffer, fmt, ap);
        va_end(ap);
        return(cnt);
}

int cal_cpu_power(char * cpu, char *vdd, int cluster){
	char freq_path[100] = "/sys/devices/system/cpu/";
	char vdd_path[100] = "/sys/kernel/debug/sprd-regulator/";
	float p_dyn = 0.0;
	float p_leakage = 0.0;
	float cur_vdd = 0.0;
	long int cur_freq_int = 0;
	float cur_freq = 0.0;

	strcat(freq_path,cpu);
	strcat(freq_path,"/cpufreq/scaling_cur_freq");
	strcat(vdd_path,vdd);
	strcat(vdd_path,"/voltage");
	
	if (cluster == 3){
		cur_freq_int = get_cur_data(VDD_FCM_FREQ);
		cur_vdd = match_freq_to_vdd(cur_freq_int,2);
		if(get_bigcore_status()==1){
			cur_freq = 768000/FREQ_HEX;
		}else{
			cur_freq = get_cur_data(CPU_FCM_FREQ)*0.75/FREQ_HEX;
		}
	}else{
		cur_freq_int = get_cur_data(freq_path);
		cur_vdd = match_freq_to_vdd(cur_freq_int,cluster);
		cur_freq = cur_freq_int/FREQ_HEX;
	}
	
	ALOGD("freq is %.3f\n", cur_freq);
		
	//float cur_vdd = get_cur_data(vdd_path)/VDD_HEX;
	ALOGD("vdd is %.3f\n", cur_vdd);
	
	float cur_temp = 85;//get_cur_data(CPU_THERMAL_PATH)/TEMP_HEX;	
	ALOGD("cpu_temp is %.3f\n", cur_temp);
	
	float t_scale = TSCAL_A*cur_temp*cur_temp*cur_temp + TSCAL_B*cur_temp*cur_temp + TSCAL_C*cur_temp + TSCAL_D;
	float v_scale = VSCAL_A*cur_vdd*cur_vdd*cur_vdd + VSCAL_B*cur_vdd*cur_vdd + VSCAL_C*cur_vdd + VSCAL_D;
	
	ALOGD("t_scale is %.3f\n", t_scale);
	ALOGD("v_scale is %.3f\n", v_scale);

	switch (cluster){
		case 0:
			p_dyn = P_DYNBASE_LIT*cur_freq*cur_vdd*cur_vdd/V_BASE/V_BASE;
			p_leakage = t_scale*v_scale*P_LEAKBASE_LIT;
			ALOGD("p_dyn is %.3f p_leakage is %.3f, cluster is %d\n", p_dyn, p_leakage, cluster);
			break;
		case 1:
			p_dyn = P_DYNBASE_MID*cur_freq*cur_vdd*cur_vdd/V_BASE/V_BASE;
			p_leakage = t_scale*v_scale*P_LEAKBASE_MID;
			ALOGD("p_dyn is %.3f p_leakage is %.3f cluster is %d\n", p_dyn, p_leakage, cluster);
			break;
		case 2:
			p_dyn = P_DYNBASE_BIG*cur_freq*cur_vdd*cur_vdd/V_BASE/V_BASE;
			p_leakage = t_scale*v_scale*P_LEAKBASE_BIG;
			ALOGD("p_dyn is %.3f p_leakage is %.3f cluster is %d\n", p_dyn, p_leakage, cluster);
			break;
		default:
			p_dyn = P_DYNBASE_FCM*cur_freq*cur_vdd*cur_vdd/V_BASE/V_BASE;
			p_leakage = t_scale*v_scale*P_LEAKBASE_FCM;
			ALOGD("p_dyn is %.3f p_leakage is %.3f cluster is %d\n", p_dyn, p_leakage, cluster);
			break;
	}	

	float p_total = p_leakage + p_dyn;
	cluster_power[cluster] += p_total;
	ALOGD("cluster_power[%d] is %.3f\n", cluster, cluster_power[cluster]);
	return 0;
}



int main(){
	
#if 0
	char cpu_power_path[100];
	char cpu_core[20];
	while (1) {
		memset(cluster_power, 0, sizeof(cluster_power));
		for(int i=0; i<8; i++){
			strcpy(cpu_core, CPU_CORE);
		    vspf("%d", i);
			strcat(cpu_core, buffer);
			if( i<3){
				cal_cpu_power(cpu_core, "vddarm0", 0);
			}else if( i>=3 && i<7 ){
				cal_cpu_power(cpu_core, "vddarm1", 1);
			}else if( i==7 ){
				cal_cpu_power(cpu_core, "vddarm2", 2);
			}
		}
		cal_cpu_power(cpu_core, "vddarm1", 3);	
	
		for(int j=0; j<CLUSTER_NUM; j++){
			strcpy(cpu_power_path, CPU_VDD_PATH);
			vspf("%d", j);
			strcat(cpu_power_path, buffer);
			strcat(cpu_power_path, "_power");
			store_cur_data(cluster_power[j], cpu_power_path);
			if(j==3){
				store_cur_data(cluster_power[j], "/sys/cpu_power/fcm_power");
			}
			ALOGD("cluster_power[%d]: %.3f\n", j, cluster_power[j]);	
		}
		sleep(1);
	}
#endif
	
	clock_t c_start, c_end;
	c_start = clock();
	
#if 0
	float ret = 0.0;
#endif

	double space_time;
	int i = 0;
	int j = 0; 
	int start_index = 0;
	int n = 0;
	
	while(1){
		c_start = clock();
		n = n<MAX_N?start_index++:MAX_N;
		//printf("n is %d\n",n);
		for(i=0;i<CLUSTER_GROUP_LEN;i++){
			//printf("cluster_group_mem[%d] name is %s\n",i,cluster_group_mem[i].name);
			for(j=0;j<CLUSTER_RX_LEN;j++){
				//cluster_group_mem[i].arry_tn[j] = cal_txn(n, cluster_group_mem[i].cluster_Rx_group[j].arry_rx);	
				//printf("i is %d, r%d is %f\n", i, j,cluster_group_mem[i].arry_tn[j]);
				cluster_group_mem[i].clutser_temp += cal_txn(n, cluster_group_mem[i].cluster_Rx_group[j].arry_rx, &cluster_group_mem[i].arry_tn[j]);
				//printf("i is %d, r%d is %f\n", i, j,cluster_group_mem[i].arry_tn[j]);
			}
			cluster_group_mem[i].clutser_temp +=25;
			cal_each_core_power(cluster_group_mem[i].cpu_n,cluster_group_mem[i].clutser_temp);
			//arry_temp[i] = cluster_group_mem[i].clutser_temp;
			//printf("cluster_group_mem[%d] thm is %f\n",i,cluster_group_mem[i].clutser_temp);
			cluster_group_mem[i].clutser_temp = 0.0;
		}
		//c_end = clock();
		//space_time = c_end - c_start;
		//printf("space time1 is %.f us\n", space_time);
		usleep(1000000);
		c_end = clock();
		space_time = c_end - c_start;
		//printf("space time is %f us\n", space_time);
	}

	return 0;
}
