#include<stdio.h>
#define expression(x) ((x)*(x)*(x)-(x)-1)

double count( float mid)
{
    mid = expression(mid);
    return mid;
}

int main()
{
    float a,b,ans,mid;
    scanf( "%f,%f",&a,&b );
    while( 1 )
    {
        mid = ( a+b )/2.0;
        ans = count( mid );
        if( ans <= 0.000001 && ans >= 0 )
        {
            ans = mid;
            break;
        }
        if( ans > 0)
        {
            b = mid;
        }else{
            a = mid;
        }
    }
    printf( "x=%6.2f\n",ans );
    return 0;
}