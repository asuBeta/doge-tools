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
#include <stdarg.h>

#include "sort.h"

#define ARR_LEN 200000
#define RAN_DEF 2000000
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

// print function for debug. equals to "[timestamp]" + printf
static void debug_print(char *fmt, ...)
{
    va_list args;
    char timestamp[17 + 1];
    
    memset(timestamp, 0x00, sizeof(timestamp));
    
    get_sysdt(timestamp);
    printf("[%s]", timestamp);
    
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
}


int main(int argc, char *argv[]) {
    
    int i = 0;
    int arr[ARR_LEN];
    
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
    debug_print("sort begins...\n");
    
    // sort
    quick_sort(arr, 0, ARR_LEN - 1);
    //selection_sort(arr, ARR_LEN );
    //insertion_sort(arr, ARR_LEN );
    //bubble_sort(arr, ARR_LEN);
    
    // time after sort
    debug_print("sort ends...\n");

#ifdef UT_DEBUG
    printf("[sortted array dump]\n");
    for (i = 0; i < ARR_LEN; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
#endif
    
    printf("->arr[0]=%d,...,arr[%d]=%d\n", arr[0], ARR_LEN - 1, arr[ARR_LEN - 1]);
    
}

