//
//  w9099s01.c
//  testc
//
//  Created by Qiu Tao on 3/25/16.
//  Copyright © 2016 Qiu Tao. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

#include "w9099s01.h"


/**
* <p>Remove the spaces in the LEFT side of a string.</p>
*/

void w9099s01_ltrim(char *str){
    
    char *tmp = NULL;
    
    tmp = str;
    
    // do nothing when empty string comes
    if (tmp == NULL || strlen(tmp) == 0)
        return;
    
    while (*tmp == 0x20)
        tmp++;
    
    sprintf(str, "%s", tmp);
}


/**
* <p>Remove the spaces in the RIGHT side of a string.</p>
*/

void w9099s01_rtrim(char *str){
    
    unsigned long i_loop = 0;
    
    // do nothing when empty string comes
    if (str == NULL || strlen(str) == 0)
        return;
    
    for(i_loop = strlen(str); i_loop > 0; i_loop--){
        if(str[i_loop - 1] == 0x20)
            str[i_loop - 1] = 0x00;
        else
            break;
    }
}


/**
* <p>Remove the space in both left and right sides of a string,
* <p>excpet those inside.<p>
*/

void w9099s01_trim(char *str){
    
    // remove the spaces in the left side
    w9099s01_ltrim(str);
    
    // remove the spaces in the right side
    w9099s01_rtrim(str);
}



/**
* <p>A function for high precision multiplication of two float numbers.</p>
* <li>input: two strings of float numbers, eg, 999.9999</li>
* <li>output: the multiplication result of inputs in long doule type</li>
*/

long double w9099s01_flt_mltply(char* num1, char* num2){
    
    // variable declares
    long double ld_x1y1 = 0.0;
    long double ld_x1y2 = 0.0;
    long double ld_x2y1 = 0.0;
    long double ld_x2y2 = 0.0;
    
    char *x1 = NULL;
    char *x2 = NULL;
    char *y1 = NULL;
    char *y2 = NULL;
    
    long long ll_x1 = 0;
    long long ll_x2 = 0;
    long long ll_y1 = 0;
    long long ll_y2 = 0;
    
    unsigned int i_pos_x = 0;
    unsigned int i_pos_y = 0;
    
    x1 = strtok(num1, DOT);     // integer part of number1
    x2 = strtok(NULL, DOT);     // decimal part of number1
    y1 = strtok(num2, DOT);     // integer part of number2
    y2 = strtok(NULL, DOT);     // decimal part of number1
    
    ll_x1 = atoll(x1);
    ll_x2 = atoll(x2);
    ll_y1 = atoll(y1);
    ll_y2 = atoll(y2);
    
    // obtain the decimal place
    i_pos_x = (unsigned int)strlen(x2);
    i_pos_y = (unsigned int)strlen(y2);
    
    // because x1.x2 * y1.y2 = (x1 + x2/10^m) * (y1 + y2/10^n)
    // = x1y1 + x1y2/10^n + x2y1/10^m + x2y2/10^(m+n)
    ld_x1y1 = (long double)(ll_x1 * ll_y1);
    ld_x1y2 = (long double)(ll_x1 * ll_y2) / (long double)pow(10, i_pos_y);
    ld_x2y1 = (long double)(ll_x2 * ll_y1) / (long double)pow(10, i_pos_x);
    ld_x2y2 = (long double)(ll_x2 * ll_y2) / (long double)pow(10, i_pos_x + i_pos_y);
    
    
    return ld_x1y1 + ld_x1y2 + ld_x2y1 + ld_x2y2;
}

