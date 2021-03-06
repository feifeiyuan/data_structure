/*************************************************************************
	> File Name: bubble_sort.c
	> Author: 
	> Mail: 
	> Created Time: Wed 28 Mar 2018 01:10:50 PM CST
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

#define LOOP_BREAK      0
#define LOOP_COMPLETE   1

int arry_int[] = {51416,563,51463,51487,51562,51506,51606,
				  51566,51625,51613,51646,51900,51887,51975,
				  51906,51908,51875,51896,51873,51925,51962,
				  51981,51950,52045,51954,52036,51960,52062,
				  52037,52068,52012,52054,52025,52040,52026,
				  };

int main(void)
{
    clock_t c_start, c_end;
    c_start = clock();
    int i = 0;
    int j = 0;
    int temp = 0;
    int k = 8;
    int max_k = 0;
    int len = sizeof(arry_int)/sizeof(arry_int[0]);
    for(i=0; i<len; i++){
        for(j=i;j<len-i;j++){
            if(arry_int[i]<arry_int[j]){
                temp = arry_int[i];
                arry_int[i] = arry_int[j];
                arry_int[j] = temp;
            }
        }


// for loop once break
# if LOOP_BREAK
        if(i==k){
            max_k = arry_int[i-1];
            break;
        }
#endif

    }

    c_end = clock();
    double space_time = c_end - c_start;

#if LOOP_BREAK
    printf("the max_k is %d\n", max_k); //for loop once break
#endif

#if LOOP_COMPLETE
    printf("the max_k is %d\n", arry_int[k-1]); // for loop complete
#endif

    printf("space time is %.f us\n", space_time);

}
