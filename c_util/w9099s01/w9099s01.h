//
//  w9099s01.h
//
//  Created by Qiu Tao on 3/25/16.
//  Copyright © 2016 Qiu Tao. All rights reserved.
//

#ifndef w9099s01_h
#define w9099s01_h


// macro definitons
#define W9099S01_SWAP(x,y) \
        (x) = (x)^(y);\
        (y) = (x)^(y);\
        (x) = (x)^(y);                  // swap two numbers


// const definitons
#define SYSERR          -1              // system error
#define DATE_LEN_14    14               // date length of yyyymmddhhmmss
#define DOT             "."             // a dot


// extern function declarations
extern void w9099s01_sysdt(char *date);

extern void w9099s01_add_times(char *new_dt, const char* old_dt, int second);

extern void w9099s01_ltrim(char *str);

extern void w9099s01_rtrim(char *str);

extern void w9099s01_trim(char *str);

extern long double w9099s01_flt_mltply(char* str1, char* str2);


#endif /* w9099s01_h */
