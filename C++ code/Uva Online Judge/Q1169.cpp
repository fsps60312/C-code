#include<cstdio>
#define abs(x) (x>=0?x:-(x))
int T,C,N,DP[100000];
void getmin(int &a,int b){if(b<a)a=b;}
struct Point
{
	int x,y,w;
}P[100000];
int Dis(int i,int j){return abs(P[i].x-P[j].x)-abs(P[i].y-P[j].y);}
int Dis(int i){return abs(P[i].x)+abs(P[i].y);}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&C,&N);
		DP[0]=0;
		for(int i=1;i<N;i++)DP[i]=1000000000;
		for(int i=0;i<N;i++)scanf("%d%d%d",&P[i].x,&P[i].y,&P[i].w);
		for(int i=0;i<N;i++)
		{
			for(int j=i,c=P[j].w,dis=DP[j]+Dis(j);j<N&&c<=C;dis+=Dis(j,j+1),j++,c+=P[j].w)
			{
				if(j>i&&DP[j]+Dis(j)<=dis)break;
				getmin(DP[j],dis+Dis(j));
			}
		}
		printf("%d\n",DP[N-1]);
	}
	return 0;
}
