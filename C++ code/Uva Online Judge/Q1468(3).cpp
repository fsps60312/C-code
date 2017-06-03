#include<cstdio>
#define max(x,y) (x>y?x:y)
#define min(x,y) (x<y?x:y)
#define abs(x) (x>=0?x:-(x))
void getmin(int &a,int b){if(b<a)a=b;}
int T,M,N,H[60000];
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
	H[P1.x]=H[P2.x]=0;
	if(P1.x>P2.x)
	{
		Point p=P1;
		P1=P2,P2=p;
	}
	for(int i=P1.x+1;i<P2.x;i++)H[i]=60000;
	if(N==2)return (M+1)*(M+1);
	for(int i=2;i<N;i++)
	{
		scanf("%d%d",&P.x,&P.y);
		getmin(H[P.x],abs(P1.y-P.y));
	}
	for(int x=P1.x,h=H[x];x<P2.x;x++,h++)
	{
		getmin(h,H[x]);
		getmin(H[x],h);
	}
	for(int x=P2.x,h=H[x];x>P1.x;x--,h++)
	{
		getmin(h,H[x]);
		getmin(H[x],h);
	}
	int ans=0;
	for(int x=P1.x+1,v;x<P2.x;x++)
	{
		//printf(" %d",H[x]);
		v=min(P1.y+H[x]-1,M-1)-max(P1.y-H[x]+1,0)+1;
		if(v<=0)continue;
		ans+=v;
	}//printf("\n");
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&M,&N);
		printf("%d\n",solve());
	}
	return 0;
}
