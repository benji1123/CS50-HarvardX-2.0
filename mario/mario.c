#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h;
    while(true)
    {
        printf("input a height that is between or equal to 0 and 23: ");
        h = get_int();
        
        if(h>-1 && h <24)
        {
            break;
        }
        else
        {
            continue;
        }
    }
    


    for(int i=1; i<h; i++) //each iteration = one row 
    {
        for(int s=0; s<h-i; s++) { printf(" "); } //INDENTATION
        
        for(int c=0; c < i; c++) { printf("#"); } //BLOCK1
        printf("  ");                              //CENTER
        
        for(int c=0; c < i; c++) { printf("#"); } //BLOCK2
        printf("\n");                             
    }
}

