#include<stdio.h>
#include<math.h>

int count(double n,double *p)
{
    int number = 1,i;
    double result = 0.0;
    for( ;number <= 1000;number++ )
    {
        i = number;
        result = 0.0;
        for( ;i <= 2*number;i++ )
        {
            result += sqrt(i);
        }
        if( result >= n )
        {
            break;
        }
    }
    *p = result;
    if( n == 0.0 )
    {
        number = 0;
    }
    return number;
}


int main()
{
    double n,result;
    double *p = &result;
    int m;
    printf("Input n:\n");
    scanf("%lf",&n);
    m = count(n,p);
    printf("Result:m>=%d\n",m);
    printf("s=%.2f\n",*p);
    return 0;
}