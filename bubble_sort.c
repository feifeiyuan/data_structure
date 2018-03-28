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

int arry_int[] = {51416,
51463,51463,
51487,
51562,
51506,
51606,
51566,
51625,
51613,
51646,
51900,
51887,
51975,
51906,
51908,
51875,
51896,
51873,
51925,
51962,
51981,
51950,
52045,
51954,
52036,
51960,
52062,
52037,
52068,
52012,
52054,
52025,
52040,
52026,
52062,
52200,
52093,
52225,
52079,
52179,
52150,
52173,
52262,
52187,
52268,
52250,
52245,
52225,
52226,
52243,
52387,
52212,
52262,
52256,
52283,
52262,
52290,
52276,
52200,
52400,
52318,
52375,
52333,
52366,
52350,
52376,
52525,
52312,
52468,
52343,
52441,
52383,
52430,
52366,
52325,
52400,
52281,
52350,
52275,
52370,
52313,
52370,
52325,
52425,
52406,
52393,
52475,
52441,
52453,
52440,
52537,
52575,
52475,
52462,
52500,
52420,
52520,
52433,
52587,
52612,
52618,
52675,
52583,
52675,
52610,
52680,
52562,
52600,
52637,
52631,
52654,
52695,
52673,
52716,
52700,
52800,
52743,
52775,
52729,
52733,
52720,
52723,
52900,
52662,
52806,
52681,
52808,
52700,
52846,
52733,
52812,
52875,
52831,
52937,
52850,
52908,
52846,
52886,
52837,
52787,
52931,
52850,
52941,
52854,
52940,
52860,
52862,
53037,
52931,
53012,
52941,
52975,
52956,
52936,
52937,
52975,
52918,
52950,
52908,
52970,
52936,
52963,
52987,
52962,
53018,
52975,
53016,
52950,
53020,
52943,
52862,
52987,
52912,
52987,
52950,
52987,
53016,
53013,
53025,
53062,
53050,
53043,
53087,
53112,
53116,
53103,
53175,
53137,
53193,
53162,
53225,
53233,
53246,
53273,
53400,
51487,
51562,
51506,
51606,
51566,
51625,
51613,
51646,
51900,
51887,
51975,
51906,
51908,
51875,
51896,
51873,
51925,
51962,
51981,
51950,
52045,
51954,
52036,
51960,
52062,
52037,
52068,
52012,
52054,
52025,
52040,
52026,
52062,
52200,
52093,
52225,
52079,
52179,
52150,
52173,
52262,
52187,
52268,
52250,
52245,
52225,
52226,
52243,
52387,
52212,
52262,
52256,
52283,
52262,
52290,
52276,
52200,
52400,
52318,
52375,
52333,
52366,
52350,
52376,
52525,
52312,
52468,
52343,
52441,
52383,
52430,
52366,
52325,
52400,
52281,
52350,
52275,
52370,
52313,
52370,
52325,
52425,
52406,
52393,
52475,
52441,
52453,
52440,
52537,
52575,
52475,
52462,
52500,
52420,
52520,
52433,
52587,
52612,
52618,
52675,
52583,
52675,
52610,
52680,
52562,
52600,
52637,
52631,
52654,
52695,
52673,
52716,
52700,
52800,
52743,
52775,
52729,
52733,
52720,
52723,
52900,
52662,
52806,
52681,
52808,
52700,
52846,
52733,
52812,
52875,
52831,
52937,
52850,
52908,
52846,
52886,
52837,
52787,
52931,
52850,
52941,
52854,
52940,
52860,
52862,
53037,
52931,
53012,
52941,
52975,
52956,
52936,
52937,
52975,
52918,
52950,
52908,
52970,
52936,
52963,
52987,
52962,
53018,
52975,
53016,
52950,
53020,
52943,
52862,
52987,
52912,
52987,
52950,
52987,
53016,
53013,
53025,
53062,
53050,
53043,
53087,
53112,
53116,
53103,
53175,
53137,
53193,
53162,
53225,
53233,
53246,
53273,
53400,
53337};

int main(void)
{
    clock_t c_start, c_end;
    c_start = clock();
    int i = 0;
    int j = 0;
    int temp = 0;
    int k = 80;
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
# if 1
        if(i==k){
            max_k = arry_int[i];
            break;
        }
#endif

    }

// for debug code
#if 0
    for(i=0; i<len; i++){
        printf("arry_int[%d] is %d\n", i, arry_int[len-i]);
    }
#endif

    c_end = clock();
    double space_time = c_end - c_start;
    //printf("the max_k is %d\n", max_k); //for loop once break
    printf("the max_k is %d\n", max_k); // for loop complete
    printf("space time is %.f us\n", space_time);

}
