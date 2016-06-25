//
//  main.c
//  algorithm
//
//  Created by Qiu Tao on 6/25/16.
//  Copyright © 2016 Qiu Tao. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sort.h"

#define ARR_LEN 2000000
#define RAN_DEF 20000000
//#define UT_DEBUG

int main(int argc, char *argv[]) {
    
    int i = 0;
    int arr[ARR_LEN];
    time_t t_begin, t_end;
    
    printf("[sort test]\n");
#ifdef UT_DEBUG
    printf("[original array]\n");
#endif
    
   // seed for random numbers
    srand( (unsigned)time( NULL ) );
    for (i = 0; i < ARR_LEN; i++) {
        // generates numbers that between 0 and ARR_LEN - 1
        arr[i] = rand() % RAN_DEF;
        
#ifdef UT_DEBUG
        printf("%d ", arr[i]);
#endif
        
    }
    
    printf("\n->arr[0]=%d...arr[%d]=%d\n", arr[0], ARR_LEN - 1, arr[ARR_LEN - 1]);
    
    printf("\n--------sort begins------->\n");
    
    // time before sort
    time(&t_begin);
    
    // sort
    quick_sort(arr, 0, ARR_LEN - 1);
    //selection_sort(arr, ARR_LEN );
    //insertion_sort(arr, ARR_LEN );
    //bubble_sort(arr, ARR_LEN);
    
    // time after sort
    time(&t_end);
    
    // time passed
    double seconds = difftime(t_end, t_begin);
    printf("+++Time: %fs\n", seconds);
    
    printf("<--------sort ends--------\n\n");

#ifdef UT_DEBUG
    printf("[sortted array dump]\n");
    for (i = 0; i < ARR_LEN; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
#endif
    
    printf("->arr[0]=%d...arr[%d]=%d\n", arr[0], ARR_LEN - 1, arr[ARR_LEN - 1]);
    
}
