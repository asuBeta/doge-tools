//
//  sort.c
//  algorithm
//
//  Created by Qiu Tao on 6/25/16.
//  Copyright © 2016 Qiu Tao. All rights reserved.
//


#include "sort.h"

static int med3(int x, int y, int z)
{
    if (x < y) {
        if (y < z) return y;
        else if (z < x) return x;
        else return z;
    } else {
        if (z < y) return y;
        else if (x < z) return x;
        else return z;
    }
}

void quick_sort(int *arr, int left, int right)
{
    if (left < right) {
        int i = left, j = right;
        int pivot = med3(arr[i], arr[i + (j - i) / 2], arr[j]); // i + j overflow is possible
        
        while (1) {
            while (arr[i] < pivot) i++;
            while (pivot < arr[j]) j--;
            if (i >= j) break;
            SWAP(arr[i], arr[j]);
            i++;
            j--;
        }
        
        quick_sort(arr, left, i - 1);
        quick_sort(arr, j + 1, right);
        
    }
}

void selection_sort(int *arr, int num)
{
    int i, j;
    
    for (j = 0; j < num - 1; j++) {
        
        // assume the min is the first element
        int min = j;
        
        for (i = j + 1; i < num; i++) {
            if (arr[i] < arr[min]) {
                // update the index of min
                min = i;
            }
        }
        
        // min was changed? then swap
        if (min != j) SWAP(arr[j], arr[min]);
    }
    
}

void insertion_sort(int *arr, int num)
{
    int i, j;
    int temp;
    
    for (i = 1; i < num; i++) {
        temp = arr[i];
        
        for (j = i - 1; j >= 0 && arr[j] > temp; j--) { // if j = -1, j >= 0 is false
            arr[j + 1] = arr[j];
        }
        // put arr[i] in the right position
        arr[j + 1] = temp;
    }
}

void bubble_sort(int *arr, int num)
{
    int i, j;
    int swap = 0; // swap action flag
    
    for (i = 0; i < num - 1; i++) {
        
        swap = 0;
        for (j = num - 1; j >= i; j--) {
            if (arr[j] < arr[j - 1]) {
                SWAP(arr[j - 1], arr[j]);
                swap = 1;
            }
        }
        
        // if not swapped this time, the array is already in order
        if (!swap) return;
    }
}

