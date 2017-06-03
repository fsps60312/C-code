#include<cstdio>
#include<cstdlib>
#include<algorithm>
#define LL long long
const LL INF=1LL<<62;
using namespace std;
LL T,N,D,H[100],XN,X[20000],DP[100][20000];//money cost when move stone i to height j
void getmin(LL &a,LL b){if(b<a)a=b;}
LL mabs(LL a){return a>=0?a:-a;}
struct Point{LL x,y;};
void termin(){int a[10];for(int i=0;;i--)a[i]=100;}
struct MaxQueue
{
	Point v[20000];
	LL l,r;
	void clear(){l=0,r=-1;}
	void push(LL x,LL p)
	{
		while(r>=l&&x<=v[r].x)r--;
		r++;
		v[r]=(Point){x,p};
	}
	void pop(LL p)
	{
		while(l<=r&&p>X[v[l].y])l++;
	}
	Point front(){if(r<l)termin();return v[l];}
	LL back(){if(r<l&&r!=-1)termin();return r<l?-1:v[r].y;}
}MQ;
void get_X()
{
	LL k=0;
	for(LL i=0;i<N;i++)
	{
		for(LL j=-N+1;j<N;j++)
		{
			X[k++]=H[i]+j*D;
		}
	}
	sort(X,X+k);
	XN=1;
	for(LL i=1;i<k;i++)
	{
		if(X[i-1]==X[i])continue;
		X[XN++]=X[i];
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&N,&D);
		for(LL i=0;i<N;i++)
		{
			scanf("%lld",&H[i]);
		}
        if(mabs(H[N-1]-H[0])>D*(N-1))
        {
        	printf("impossible\n");
        	continue;
		}
		get_X();
//		for(LL x=0;x<XN;x++)printf("%5d",X[x]);printf("\n");
		for(LL x=0;x<XN;x++)
		{
			DP[0][x]=X[x]==H[0]?0:INF;
//			printf("%5d",DP[0][x]==INF?-1:DP[0][x]);
		}
//		puts("");
		for(LL i=1;i<N;i++)
		{
			MQ.clear();
			for(LL x=0;x<XN;x++)
			{
				for(LL j=MQ.back()+1;j<XN&&X[j]<=X[x]+D;j++)MQ.push(DP[i-1][j],j);
				MQ.pop(X[x]-D);
				LL &dp=DP[i][x];
				Point p=MQ.front();
				if(p.x==INF)
				{
					dp=INF;
					continue;
				}
				else
				{
					dp=p.x+mabs(H[i]-X[x]);
				}
			}
//			for(LL x=0;x<XN;x++)
//			{
//				printf("%5d",DP[i][x]==INF?-1:DP[i][x]);
//			}printf("\n");
		}
//		for(LL h=0;h<N;h++)
//		{
//		}
		LL ans=INF;
		for(LL i=0;i<XN;i++)
		{
			if(X[i]==H[N-1])
			{
				ans=DP[N-1][i];
				break;
			}
		}
		if(ans==INF)printf("impossible\n");
		else printf("%lld\n",ans);
	}
	return 0;
}
