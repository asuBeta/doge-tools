//
//  main.c
//  algorithm
//
//  Created by Qiu Tao on 6/25/16.
//  Copyright © 2016 Qiu Tao. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "sort.h"

#define ARR_LEN 20000000
#define RAN_DEF 200000000
//#define UT_DEBUG

static void get_sysdt(char *date){
    
    struct timeval tv;
    
    struct tm *p_date = NULL;
    struct timezone *p_tz = NULL;
    
    memset(&tv, 0x00, sizeof(struct timeval));
    gettimeofday(&tv, p_tz);
    
    time_t result = tv.tv_sec;
    
    if (result){
        // the date is based on local timezone
        p_date = localtime(&result);
        if (p_date){
            // foramt util second
            strftime(date, 14, "%Y%m%d%H%M%S",p_date);
            // append millsecond to the date string, at the positon of second
            sprintf(date + 14, "%03d", tv.tv_usec/1000);
        }
    }
    
}

int main(int argc, char *argv[]) {
    
    int i = 0;
    int arr[ARR_LEN];
    char timestamp[17 + 1];
    
    memset(timestamp, 0x00, sizeof(timestamp));
    
    printf("###sort test###\n");
    
   // seed for random numbers
    srand( (unsigned)time( NULL ) );
    for (i = 0; i < ARR_LEN; i++) {
        // generates numbers that between 0 and RAN_DEF - 1
        arr[i] = rand() % RAN_DEF;
    }
    
#ifdef UT_DEBUG
    printf("[original array dump]\n");
    for (i = 0; i < ARR_LEN; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
#endif
    
    printf("->arr[0]=%d,...,arr[%d]=%d\n", arr[0], ARR_LEN - 1, arr[ARR_LEN - 1]);
    
    
    // time before sort
    get_sysdt(timestamp);
    printf("[%s]sort begins...\n", timestamp);
    
    // sort
    quick_sort(arr, 0, ARR_LEN - 1);
    //selection_sort(arr, ARR_LEN );
    //insertion_sort(arr, ARR_LEN );
    //bubble_sort(arr, ARR_LEN);
    
    // time after sort
    get_sysdt(timestamp);
    
    printf("[%s]sort ends...\n", timestamp);

#ifdef UT_DEBUG
    printf("[sortted array dump]\n");
    for (i = 0; i < ARR_LEN; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
#endif
    
    printf("->arr[0]=%d,...,arr[%d]=%d\n", arr[0], ARR_LEN - 1, arr[ARR_LEN - 1]);
    
}

