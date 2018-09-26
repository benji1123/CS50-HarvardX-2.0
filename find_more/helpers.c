/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int min = 0, max = n-1; //set default bounds for binary search in values[]
    int mid; //the index-value being readily compared to "value"
    
    while(min <= max) //search is unsuccesful if "min" exceeds "max"
    {
        mid = min + (max-min)/2; 
        
        //VALUE FOUND
        if(values[mid] == value)
        {
            printf("\n\nNEEDLE AT HAYSTACK[%i]", mid);
            return true;
        }
        else if(values[mid+1]==value)
        {
            printf("\n\nNEEDLE AT HAYSTACK[%i]", mid+1);
            return true;
        }
        else if(values[mid-1]==value)
        {
            printf("\n\nNEEDLE AT HAYSTACK[%i]", mid-1);
            return true;
        }
        
        //VALUE NOT FOUND YET
        else if(values[mid]<value) //re-establish the low point
        {
            min=mid+1;
        }
        else //re-establish the high point
        {
            max=mid-1;
        }
    }
    if(min>max) //search has failed if "min" exceeds "max"
    {
        return false;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    //INITIALIZE an ARRAY WITH COUNT OF APPEARING ELEMENTS WITHIN HAYSTACK[] (Inventory)
    int count_arr[65536]; //generatable # range: 0 --> 65536 
    for(int i=0; i<n; i++) 
    {
        count_arr[i] = 0; //default all count-values to zero
    }
    
    for(int i=0; i<n; i++) //take inventory of values[] elements
    {
        count_arr[values[i]]++;
    }


    //SORT HAYSTACK[] with COUNTING SORT
    int hay_index=0; //index being altered within values[]
    for(int i=0; i<n; i++) //iterate through count_arr[] and transfer elements to values[] one by one in order
    {
        if(count_arr[i] > 0) //the current 'i' value occurs and must be put in values[]
        {
            for(int quantity = count_arr[i]; quantity > 0; quantity--) //repeat for every original occurence of 'i'
            {
                values[hay_index] = i; //replace values[x] with ordered value
                hay_index++; //jump to next element in values[]
            }
        }
    }
    return; //exit void() function
}
