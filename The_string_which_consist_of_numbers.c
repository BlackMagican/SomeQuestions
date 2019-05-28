#include<stdio.h>
#include<ctype.h>

int IsAllDigit(char p[])
{
    int flag = 1;
    char *ptr = p;
    while( *ptr )
    {
        if( !isalpha( *ptr ) )
        {
            ptr++;
        }else{
            flag = 0;
            break;
        }
    } 
    return flag;
}


int main()
{
    printf("Please input a string:\n");
    char str[21];
    gets(str);
    if( IsAllDigit(str) )
    {
        printf("The string is digit string.");
    }else{
        printf("The string is not digit string.");
    }
    return 0;

}