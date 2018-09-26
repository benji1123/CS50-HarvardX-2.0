#include <cs50.h>
#include <stdio.h>

int Bottles(int i);
int main(void)
{
    printf("minutes: ");
    int min = get_int();
    printf("Bottles: %i\n", Bottles(min));
    
}

int Bottles(int i)
{
    return i*12;
}