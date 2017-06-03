#include<cstdio>
#define abs(x) (x>=0?x:-(x))
int T,C,N,DP[100001];
void getmin(int &a,int b){if(b<a)a=b;}
struct Point
{
	int x,y,w;
}P[100001];
int Dis(int i,int j){return abs(P[i].x-P[j].x)+abs(P[i].y-P[j].y);}
int Dis(int i){return abs(P[i].x)+abs(P[i].y);}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&C,&N);
		DP[0]=DP[1]=0;
		for(int i=1;i<=N;i++)DP[i]=1000000000;
		for(int i=1;i<=N;i++)scanf("%d%d%d",&P[i].x,&P[i].y,&P[i].w);
		for(int i=1;i<=N;i++)
		{
			for(int j=i,c=P[i].w,dis=DP[i-1]+Dis(i);j<=N&&c<=C;dis+=Dis(j,j+1),j++,c+=P[j].w)
			{
				if(j>i&&DP[j-1]+Dis(j)<=dis)break;
				getmin(DP[j],dis+Dis(j));
			}
		}
		printf("%d\n",DP[N]);
	}
	return 0;
}
