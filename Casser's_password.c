#include<stdio.h>
#include<string.h>

void Caesar(char c[])
{
    char *ptr = c;
    while( *ptr )
    {
        switch(*ptr)
        {
            case 'x':
                *ptr = 'a';
                break;
            case 'y':
                *ptr = 'b';
                break;
            case 'z':
                *ptr = 'c';
                break;
            default:
                *ptr+=3;
                break;
        }
        ptr++;
    }
    puts(c);
}

int main()
{
    char password[101];
    printf("Input a string:");
    gets( password );
    char *p = password;
    Caesar(p);
    return 0;
}
