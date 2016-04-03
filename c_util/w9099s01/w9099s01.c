//
//  w9099s01.c
//
//  Created by Qiu Tao on 3/25/16.
//  Copyright © 2016 Qiu Tao. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include <sys/time.h>

#include "w9099s01.h"


/**
* <p>Get system time with precison of millsecond</p>
* <p>date format: yyyymmddHHMMSSsss(length of 17 + 1)</p>
*/

void w9099s01_sysdt(char *date){
    
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
            strftime(date, DATE_LEN_14, "%Y%m%d%H%M%S",p_date);
            // append millsecond to the date string, at the positon of second
            sprintf(date + DATE_LEN_14, "%03d", tv.tv_usec/1000);
        }
    }

}


/**
* <p>Add seconds to or subtract seconds from given time.</p>
* <p>char *new_dt: new time after operation.</p>
* <p>const char* old_dt: old time for operation.</p>
* <p><b>time format(I/O):yyyymmddHHMMSS (length of 14 + 1)</b></p>
* <p>int second: seconds to add or subtract. Positive for adding,
*    and negative for subtracting.</p>
*/

void w9099s01_add_times(char *new_dt, const char* old_dt, int second){
    
    struct tm s_old_dt;
    struct tm *p_new_dt = NULL;
    
    time_t total_secs = 0;
    memset(&s_old_dt, 0x00, sizeof(s_old_dt));

    
    strptime(old_dt, "%Y%m%d%H%M%S", &s_old_dt);
    
    total_secs = mktime(&s_old_dt);
    
    if (total_secs) {
        total_secs += second;
        p_new_dt = localtime(&total_secs);
        if (p_new_dt){
            // foramt util second
            strftime(new_dt, DATE_LEN_14, "%Y%m%d%H%M%S",p_new_dt);
        }
    }
    
}


/**
* <p>Remove the spaces in the LEFT side of a string.</p>
*/

void w9099s01_ltrim(char *str){
    
    char *tmp = NULL;
    
    tmp = str;
    
    // do nothing when an empty string comes
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
    
    size_t i_loop = 0;
    
    // do nothing when an empty string comes
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
* <li>parameters: two strings of float numbers, eg, 999.9999</li>
* <li>return: the multiplication result of inputs in long doule type</li>
*/

long double w9099s01_flt_mltply(char* num1, char* num2){
    
    // declare variables
    int sgn_flg = 1;    // sign flag for result
    
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
    
    // mutiply the sign flag with -1 if argument is negative
    if (num1[0] == '-') sgn_flg *= -1;
    if (num2[0] == '-') sgn_flg *= -1;
    
    x1 = strtok(num1, DOT);     // integer part of number1
    x2 = strtok(NULL, DOT);     // decimal part of number1
    y1 = strtok(num2, DOT);     // integer part of number2
    y2 = strtok(NULL, DOT);     // decimal part of number1
    
    ll_x1 = llabs(atoll(x1));
    ll_x2 = atoll(x2);
    ll_y1 = llabs(atoll(y1));
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
    

    return (ld_x1y1 + ld_x1y2 + ld_x2y1 + ld_x2y2) * sgn_flg;
}

