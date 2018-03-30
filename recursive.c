#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define CLUSTER_RX_LEN		3 // for each clutser rx is 3
#define CLUSTER_GROUP_LEN	9 
#define MAX_N				861

struct cluster_rx{
	float arry_rx[CLUSTER_GROUP_LEN+1];// add taux
};

struct cluster_group{
	char *name;
	float clutser_temp;
	struct cluster_rx cluster_Rx_group[CLUSTER_RX_LEN];
	float arry_tn[CLUSTER_RX_LEN];
}cluster_group_mem[CLUSTER_GROUP_LEN]=
		{"prometheus",0.0,
			{{14.657, 10.125, 6.978, 5.442, 4.905, 5.041, 4.722, 4.633, 4.177, 0.967003},
			 {9.943, 9.236, 8.581, 7.953, 7.483, 7.823, 7.422, 7.178, 7.453, 0.027778659},
			 {7.648, 7.487, 7.369, 7.277, 7.219, 7.265, 7.219, 7.192, 7.206,0.000662661}},
			 {0.0, 0.0, 0.0},
		"Ananke1",0.0,
			{{9.867, 17.912, 12.205, 8.235, 6.710, 6.159, 5.746, 5.602, 4.059, 0.996238},
			 {9.208, 10.371, 9.559,	8.821, 8.362, 8.358, 8.120, 7.979, 7.068, 0.031944},
			 {7.482, 7.789, 7.581, 7.432, 7.356, 7.359, 7.327, 7.308, 7.173, 0.000707}},
			 {0.0, 0.0, 0.0},
		"Ananke2",0.0,
			{{7.012, 12.213, 18.196, 12.524, 9.550, 7.037, 7.004, 7.043, 4.037, 0.995896},
			 {8.603, 9.559, 10.449, 9.523, 8.953, 8.616, 8.540, 8.484, 6.756, 0.032573},
			 {7.374, 7.581, 7.830, 7.589, 7.471, 7.415, 7.407, 7.399, 7.149, 0.000715 }},
			 {0.0, 0.0, 0.0},
		"Ananke3",0.0,
			{{5.368, 8.016, 12.504, 19.954, 16.194, 7.316, 8.515, 9.614, 4.091, 0.993339 },
			 {7.925, 8.768, 9.511, 10.555, 9.794, 8.617, 8.837, 8.979, 6.301, 0.033154},
			 {7.276, 7.424, 7.588, 7.869 , 7.663, 7.426, 7.475 , 7.504 , 7.115, 0.000722}},
			 {0.0, 0.0, 0.0},
		"Ananke4",0.0,
			{{4.875, 6.634, 9.690, 15.765, 25.094, 7.023, 8.914, 11.582, 4.145, 0.981408},
			 {7.483, 8.339, 8.974, 9.744 , 10.861, 8.483, 8.865 , 9.265, 6.003, 0.036018},
			 {7.222, 7.354, 7.477, 7.651 , 7.952 , 7.408, 7.486 , 7.571, 7.094, 0.000748}},
			 {0.0, 0.0, 0.0},
		"Little1",0.0,
			{{5.005, 6.086, 7.045, 7.350, 7.073, 16.220, 11.128, 8.491, 4.055, 0.997899},
			 {7.815, 8.338, 8.625, 8.638, 8.503, 10.238, 9.476, 8.914, 7.502, 0.031315},
			 {7.275, 7.364, 7.424, 7.436, 7.418, 7.864, 7.644, 7.512, 7.259, 0.000708}},
			 {0.0, 0.0, 0.0},
		"Little2",0.0,
			{{4.692, 5.665, 7.009, 8.471, 9.010, 10.651, 17.464, 13.514, 4.016, 0.996740},
			 {7.398, 8.083, 8.543, 8.838, 8.892, 9.393, 10.343, 9.634, 6.893, 0.032136},
			 {7.227, 7.330, 7.416, 7.480, 7.497, 7.623, 7.900, 7.687, 7.194, 0.000717}},
			 {0.0, 0.0, 0.0},
		"Little3",0.0,
			{{4.614, 5.538, 7.063, 9.408, 11.497, 8.390, 13.099, 21.744, 4.066, 0.989938},
			 {7.174, 7.953, 8.496, 8.957, 9.267, 8.896, 9.580, 10.618, 6.478, 0.034786},
			 {7.202, 7.312, 7.408, 7.503, 7.575, 7.507, 7.672, 7.972, 7.154, 0.000742}},
			 {0.0, 0.0, 0.0},
		"SOC",0.0,
			{{4.358, 4.337, 4.364, 4.418, 4.465, 4.292, 4.300, 4.371, 6.630, 0.610420},
			 {7.133, 6.645, 6.282, 5.887, 5.603, 7.042, 6.491, 6.061, 8.670, 0.017805},
			 {7.188, 7.151, 7.127, 7.103, 7.085, 7.212, 7.164, 7.129, 7.428, 0.005420}},
			 {0.0, 0.0, 0.0},
};

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


int main()
{
	clock_t c_start, c_end;
	c_start = clock();
	float ret = 0.0;
	double space_time;
	int i = 0;
	int j = 0; 
	int start_index = 0;
	int n = 0;
	float arry_temp[CLUSTER_GROUP_LEN] ={0};

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
			//arry_temp[i] = cluster_group_mem[i].clutser_temp;
			//printf("cluster_group_mem[%d] thm is %f\n",i,cluster_group_mem[i].clutser_temp);
			cluster_group_mem[i].clutser_temp = 0.0;
		}
		c_end = clock();
		space_time = c_end - c_start;
		printf("space time is %.f us\n", space_time);
		printf("space time is %.f ms\n", space_time/1000);
		sleep(0.1);
		//printf("\n");
	}
	
	for(i=0; i<CLUSTER_GROUP_LEN; i++){
		printf("cluster_group_mem[%d] thm is %f\n",i,arry_temp[i]);
	}

#if 0
	c_end = clock();
	space_time = c_end - c_start;
	printf("space time is %.f us\n", space_time);
	printf("space time is %.f ms\n", space_time/1000);
#endif

	return 0;
}
