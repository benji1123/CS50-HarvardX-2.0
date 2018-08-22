#include <cs50.h>
#include <stdio.h>
#include <crypt.h>
#include <string.h>
#define _XOPEN_SOURCE
#include <unistd.h>
void brute(string hashpas, string salt);

int main(int argc, string argv[])
{
 
    //user must input two CL arguments, or else program terminates
    if(argc != 2)
    {
        printf("ERROR!, user failed to input two CL arguments\n");
        return 1;
    }
    printf("\n\n...please wait....\n\n\ninput is: %s\n",argv[1]);
    
    //get SALT: first two characters of hashed password
    char arr[3] = {argv[1][0], argv[1][1], '\0'};
    string salt = arr;
    printf("salt is: %s\n", salt);
    
    //brute force
    brute(argv[1], salt);
}



//BRUTE FORCE
void brute(string hashpas, string salt)
{
    printf("\n\n...please wait....\n\n\n");
    //all possible characters within password
    char c[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char testPass[5] = {'\0','\0','\0','\0', '\0'}; 
    

    //compare all possible 1-4 character passwords to true-password

    //CHAR 1
    for(int i=0; i<53; i++) 
    {
        testPass[0] = c[i];
        if(strcmp(crypt(testPass, salt),hashpas) == 0 )
        {
            printf("CRACKED!\nPASSWORD IS: %s\n", testPass);
            return;
        }
        
        //CHAR 2
        for(int j=0; j<53; j++) //char 2
        {
            
            testPass[0] = c[i];
            testPass[1] = c[j];
            if(strcmp(crypt(testPass, salt),hashpas) == 0)
            {
                printf("CRACKED!\nPASSWORD IS: %s\n", testPass);
                return;
            }
            
            //CHAR 
            for(int k=0; k<53; k++) //char 3
            {
                
                testPass[0] = c[i];
                testPass[1] = c[j];
                testPass[2] = c[k];
                if(strcmp(crypt(testPass, salt),hashpas) == 0 )
                {
                    printf("CRACKED!\nPASSWORD IS: %s\n", testPass);
                    return;
                }
            
                //CHAR 4
                for(int l=0; l<53; l++) //char 4
                {
                    //build password
                    testPass[0] = c[i];
                    testPass[1] = c[j];
                    testPass[2] = c[k];
                    testPass[3] = c[l];
                    if(strcmp(crypt(testPass, salt),hashpas) == 0 )
                    {
                        printf("CRACKED!\nPASSWORD IS: %s\n", testPass);
                        return;
                    }
                }
                
            }
        }
    }
    printf("sorry no luck!\n");
}

