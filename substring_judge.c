#include<stdio.h>
#include<string.h>

int IsSubString(char a[], char b[]);

int main()
{
    char str1[81];
    char str2[80];
    printf("Input the first string:");
    gets(str1);
    printf("Input the second string:");
    gets(str2);
    if( IsSubString( str1,str2 ) )
    {
        printf( "Yes\n");
    }else{
        printf("No\n");
    }
    return 0;
}

int IsSubString(char a[], char b[])
{
    int flag = 1;
    char *p = a;
    char *pe = b;
    while(1)
    {
        if( *pe == '\0')
        {
            break;
        }
        if( *p == '\0' )
        {
            flag = 0;
            break;
        }
        if( *p == *pe )
        {
            p++;
            pe++;
        }else{
            p++;
        }
    }
    return flag;
}