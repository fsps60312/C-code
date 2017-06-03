#include<cstdio>
#define max(x,y) (x>y?x:y)
#define abs(x) ((x)>=0?(x):-(x))
void getmin(int &a,int b){if(b<a)a=b;}
int T,M,N;
struct Point
{
	int x,y;
	int operator-(Point a)const
	{
		int ans=abs(x-a.x)+abs(y-a.y);
//		printf(" %d(%d %d,%d,%d %d,%d)",ans,abs(x-a.x),x,a.x,abs(y-a.y),y,a.y);
		return ans;
	}
}P1,P2,P;
int calarea(int r)
{
	int ans=1;
	for(int i=1;i<r;i++)ans+=i*4;
	return ans;
}
int solve()
{
	int max1=2147483647,max2=2147483647;
	scanf("%d%d%d%d",&P1.x,&P1.y,&P2.x,&P2.y);
	for(int i=2;i<N;i++)
	{
		scanf("%d%d",&P.x,&P.y);
		//printf("%d:%d %d\n",i,P-P1,P-P2);
		getmin(max1,P-P1);
		getmin(max2,P-P2);
//		printf("\n");
	}
	if(max1==2147483647)return (M+1)*(M+1);
	printf("%d %d\n",max1,max2);
	return calarea(max1)+calarea(max2);
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
