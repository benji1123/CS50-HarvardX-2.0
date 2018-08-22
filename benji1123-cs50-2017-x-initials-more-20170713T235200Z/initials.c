#include <cs50.h>
#include <stdio.h>
#include <string.h>
void initials(string name);

/* ben li
2017 July 11*/

int main(void)
{
    
    //prompt user for name
    string s = get_string();
    
    //generate initials
    initials(s);
    
}

void initials(string name)
{
    //check if first character is letter
    if(name[0] != (char) 32)
    {
        printf("%c",name[0]);//print first initial
    }
    
    //generate rest of initials by iterating through & checking remainder of input
    for(int i = 1; i < strlen(name)-1; i++)
    {
        if(name[i] == (char)32) //if the current char is ' ', print the next char if it is not
        {
            if(name[i+1] != (char)32)
            {
                printf("%c", name[i+1]);//print initial
            }
        }
    }
    printf("\n");
}