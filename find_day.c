#include<stdio.h>
#include<string.h>

int main()
{
   char week[7][11] =  {{"Sunday"},{"Monday"},{"Tuesday"},{"Wednesday"},{"Thursday"},\
   {"Friday"},{"Saturday"} };
   printf("Please enter a string:\n");
   char str[11];
   gets( str );
   char *p = str;
   int j = 0,i = 0,flag = 0;
   for( ;i<7;i++ )
   {
       if( week[i][j] == '\0' )
       {
           flag = 1;
           printf("%s is %d\n",str,i);
           break;
       }
       if( *p == week[i][j] )
       {
           p++;
           j++;
           i--;
           continue;
       }
       j = 0;
       p = str;
   }
   if( !flag )
    {
        printf("Not found!\n");
    }
    return 0;
}