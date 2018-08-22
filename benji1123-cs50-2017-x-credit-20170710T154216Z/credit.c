#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


int main(void)
{
    printf("enter card number: ");
    double c = get_double();
    double b = c;
    
    double sum = 0; //sum of odd digits
    double sum2 = 0; //sum of even digits
    double total;
    
    int i=1;
    while(true)
    {
        //even digits
        if((i%2) == 0)
        {
            int n =(int) 2*floor(fmod(b,10));
            double a = (double) n;
            
            //digit 1
            double dig1 = floor(fmod(a,10));
            sum2+=dig1;
            
            a=a/10;
            //digit 2 (if applicable)
            if(fmod(a,10) != dig1)
            {
                sum2+=floor(fmod(a,10));
            }
        }
        
        //odd digits 
        else if((i%2) != 0)
        {
            sum += floor(fmod(b,10));
        }
        
        //prep for next iteration
        i++;
        if(fmod(b,10)==b){ break; }
        b=b/10;
        
    }
    
    
    //check last digit of total
    total = sum + sum2;
    if(fmod(total,10) == 0)
    {
        printf("\nLuhn's Algorithm verified!");
    }
    else
    {
        printf("error\n");
    }
    

    //CARD TYPE
    bool amex = false;
    bool mcard = false;
    bool visa = false;
    double l = floor (log10 (fabs (c))) + 1; //card # length


    //Check Amex
    if( l == 15.0 )
    {
        if(floor(fmod(c/pow(10,14),10))==3.0)
        {
            if(floor(fmod(c/pow(10,13),10)) == 4 || floor(fmod(c/pow(10,13),10)) == 7)
            {
                printf("\nverified!\n");
                printf("AMEX\n");
                amex = true;
            }
        }
    }
    
    
    //Check Mastercard
    if( l == 16.0)
    {
        if(floor(fmod(c/pow(10,15),10))==5.0)
        {
                if(floor(fmod(c/pow(10,14),10)) > 0 && floor(fmod(c/pow(10,14),10)) < 6)
            {
                printf("\nverified!\n");
                printf("MASTERCARD\n");
                mcard = true;
            }
        }
    }
    
    
    //Check VISA
    if( l == 13.0 || l == 16.0)
    {
        if( floor(fmod(c/pow(10,15),10))==4.0 || floor(fmod(c/pow(10,12),10))==4.0 )
        {
            printf("\nverified!\n");
            printf("VISA\n");
            visa = true;
        }
    }
    
    if(amex == false && mcard == false && visa == false)
    {
        printf("INVALID\n");
    }
}