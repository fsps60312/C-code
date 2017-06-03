#include<cstdio>
int T,N;
double A,B,C,V,ANS;
void getmax(int a){if(a>ANS)ANS=a;}
double getvalue(double x){return A*x*x+B*x+C;}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        ANS=-5000000.0-5000.0;
        while(N--)
        {
            scanf("%lf%lf%lf",&A,&B,&C);
            //A(x+B/2A)^2
            if(A!=0.0)
            {
                V=-B/A*0.5;
                if(V>0.0&&V<1000.0)getmax(getvalue(V));
            }
            getmax(C);
            getmax(getvalue(1000.0));
        }
        printf("%.4f\n",ANS);
    }
    return 0;
}
