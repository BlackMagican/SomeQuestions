#include<stdio.h>
#include<math.h>

int Isprime( long int n )
{
    int i  =2,flag = 1;
    for( ;i <= sqrt(n);i++ )
        {
            if( n%i == 0)
            {
                flag = 0;
                break;
            }
        }
    return flag;
}


void Prime( long int n,long int max)
{
    int count = 0;
    while( n < max )
    {
        if( Isprime(n) )
        {
            if( Isprime(n+2) )
            {
                printf("(%ld,%ld)\n",n,n+2);
                n+=2;
                count++;
            }else{
                n++;
            }
        }else{
            n++;
        }
    }
    printf("total=%d\n",count);
}


int main()
{
    long int n1,n2;
    printf("please input c,d(c>2):\n");
    scanf("%ld,%ld",&n1,&n2);
    Prime( n1+1,n2-1 );
    return 0;
}