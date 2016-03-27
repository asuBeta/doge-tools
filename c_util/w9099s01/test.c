#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "w9099s01.h"

// gcc test.c -L. -lw9099s01 -o test

int main(){
    
    char str1[20];
    char str2[20];
    long double result = 0;
//    long double ld_x = 0.0;
//    long double ld_y = 0.0;
    
    printf("input str1: ");
    scanf("%s", str1);
    
    printf("input str2: ");
    scanf("%s", str2);
    
//    ld_x = atof(str1);
//    ld_y = atof(str2);
    
    result = flt_mltply(str1, str2);
    printf("###result = %.18Lf\n", result);
//    printf("###result2 = %.18Lf\n", ld_x * ld_y);
    
    return 0;
}