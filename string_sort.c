#include<stdio.h>
#include<string.h>

int main()
{
    printf("Input a string:\n");
    char str[21];
    gets(str);
    char *p = str;
    char mid;
    int i = strlen(str),n = 1,k = 1;
    while( *p )
    {
        for( ;n < i;n++ )
        {
            if( *p > str[n] )
            {
                mid = *p;
                *p = str[n];
                str[n] = mid;
            }
        }
        k++;
        n = k;
        p++;
    }
    puts(str);
    return 0;
}