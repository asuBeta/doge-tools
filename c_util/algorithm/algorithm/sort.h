//
//  sort.h
//  algorithm
//
//  Created by Qiu Tao on 6/25/16.
//  Copyright © 2016 Qiu Tao. All rights reserved.
//

#ifndef sort_h
#define sort_h

#define SWAP(X,Y) (X)^=(Y);(Y)^=(X);(X)^=(Y)

extern void quick_sort(int *arr, int left, int right);
extern void selection_sort(int *arr, int num);
extern void insertion_sort(int *arr, int num);
extern void bubble_sort(int *arr, int num);

#endif /* sort_h */
