#include<cstdio>
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
#define abs(x) (x>=0?x:-(x))
void getmin(int &a,int b){if(b<a)a=b;}
int T,M,N;
struct Point
{
	int x,y;
	int operator-(Point a)const
	{
		int ans=abs(x-a.x)+abs(y-a.y);
		return ans;
	}
}P1,P2,P;
int solve()
{
	scanf("%d%d%d%d",&P1.x,&P1.y,&P2.x,&P2.y);
	if(P1.x>P2.x)
	{
		Point p=P1;
		P1=P2,P2=p;
	}
	int max1=P2.x-P1.x,max2=max1;
	if(N==2)return (M+1)*(M+1);
	for(int i=2;i<N;i++)
	{
		scanf("%d%d",&P.x,&P.y);
		getmin(max1,P-P1);
		getmin(max2,P-P2);
	}
	printf("mx1=%d,mx2=%d\n%d-%d\n",max1,max2,P1.x,P2.x);
	int ans=0;
	for(int x=P1.x+1,v;x<P2.x;x++)
	{
		v=max(min(x-P1.x,P1.x+max1-x),min(x-(P2.x-max2),P2.x-x))*2-1;
		if(v>0)ans+=v;
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&M,&N);
		printf("%d\n",solve());
	}
	return 0;
}
