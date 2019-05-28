#include<stdio.h>
#include<math.h>
#define N 10

double determinant( double A[N][N],int n);
void create_sub( double A[N][N],double subA[N][N],int n,int line,int row);

int main()
{
    int n;
    double ans;
    double A[N][N];
    printf("Please input:\n");
    scanf("%d",&n);            //阶数
    for( int i = 0;i<n;i++ )   //获取矩阵
    {
        for( int j =0;j<n;j++ )
        {
            scanf("%lf",&A[i][j] );
        }
    }
    ans = determinant( A,n );
    printf("The answer is %f",ans);
    return 0;
}

double determinant( double A[N][N],int n)
{
    double answer,sub_answer;
    double subA[N][N];
    int j = 0;
    if( n == 1 )
    {
        answer = A[0][0];
        return answer;
    }else if( n == 2 )
    {
        answer = A[0][0]*A[1][1]-A[1][0]*A[0][1];
        return answer;
    }else{
        for(int line = 0;line<n;line++ )
        {
            create_sub( A,subA,n,line,j );
            sub_answer = determinant( subA,n-1 );
            answer += A[0][line]*pow(-1,(line+j))*sub_answer;
        }
        
    }
    return answer;
}

void create_sub( double A[N][N],double subA[][N],int n,int line,int row)
{
    int i = 0,j = 0,subi = 0,subj = 0;
    for( ;j<n;j++)
    {
        if( j == row )
        {
            continue;
        }
        for( i = 0;i<n;i++ )
        {
            if(i == line )
            {
                continue;
            }else{
                subA[subj][subi] = A[j][i];
                subi++;
            }     
        }
        subj++;
    }
}