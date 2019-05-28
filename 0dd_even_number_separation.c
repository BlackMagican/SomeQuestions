#include<stdio.h>
#include<stdlib.h>


void Seperate(int a[], int n); //数组a[]存放用户输入的n个整数
void pri(int n,int number[]);

int main()
{
    int n;
    int *a;
    printf("Input n:");
    scanf("%d",&n);
    a = (int*)malloc(n*sizeof(int));
    printf("Input numbers:");
    for( int i = 0;i<n;i++ )
    {
        scanf("%d",&a[i]);
    }
    Seperate( a,n );
    return 0;
}

void Seperate( int a[],int n )
{
    int even[50];
    int odd[50];
    int *p = a,i = 0,j = 0;
    while( (i+j)<n )
    {
        if( (*p)%2 == 0 )
        {
            even[i] = *p;
            i++; 
        }else{
            odd[j] = *p;
            j++;
        }
        p++;
    }
    pri( j,odd );
    printf("\n");
    pri( i,even );
}

void pri(int n,int number[])
{
    for( int x = 0;x<n;x++ )
    {
        if( x == 0 )
        {
            printf("%d",number[x]);
        }else{
            printf(",%d",number[x]);
        }
    }
}