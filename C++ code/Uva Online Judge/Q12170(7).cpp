#include<cstdio>
#include<cstdlib>
#include<algorithm>
const int INF=1<<30;
using namespace std;
int T,N,D,H[100],XN,X[20000],DP[100][20000];//money cost when move stone i to height j
void getmin(int &a,int b){if(b<a)a=b;}
int abs(int a){return a>=0?a:-a;}
struct Point{int x,y;};
struct MaxQueue
{
	Point v[20000];
	int l,r;
	void clear(){l=0,r=-1;}
	void push(int x,int p)
	{
		while(r>=l&&x<=v[r].x)r--;
		r++;
		v[r]=(Point){x,p};
	}
	void pop(int p)
	{
		while(l<=r&&p>X[v[l].y])l++;
	}
	Point front(){return v[l];}
	int back(){return r<l?-1:v[r].y;}
}MQ;
void get_X()
{
	int k=0;
	for(int i=0;i<N;i++)
	{
		for(int j=-N+1;j<N;j++)
		{
			X[k++]=H[i]+j*D;
		}
	}
	sort(X,X+k);
	XN=1;
	for(int i=1;i<k;i++)
	{
		if(X[i-1]==X[i])continue;
		X[XN++]=X[i];
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&D);
		for(int i=0;i<N;i++)
		{
			scanf("%d",&H[i]);
		}
		get_X();
//		for(int x=0;x<XN;x++)printf("%5d",X[x]);printf("\n");
		for(int x=0;x<XN;x++)
		{
			DP[0][x]=X[x]==H[0]?0:INF;
//			printf("%5d",DP[0][x]==INF?-1:DP[0][x]);
		}
//		puts("");
		for(int i=1;i<N;i++)
		{
			MQ.clear();
			for(int x=0;x<XN;x++)
			{
				MQ.pop(X[x]-D);
				for(int j=MQ.back()+1;j<XN&&X[j]<=X[x]+D;j++)MQ.push(DP[i-1][j],j);
				int &dp=DP[i][x];
				Point p=MQ.front();
				if(p.x==INF)
				{
					dp=INF;
					continue;
				}
				else
				{
					dp=p.x+abs(H[i]-X[x]);
				}
			}
//			for(int x=0;x<XN;x++)
//			{
//				printf("%5d",DP[i][x]==INF?-1:DP[i][x]);
//			}printf("\n");
		}
//		for(int h=0;h<N;h++)
//		{
//		}
		int ans=INF;
		for(int i=0;i<XN;i++)
		{
			if(X[i]==H[N-1])
			{
				ans=DP[N-1][i];
				break;
			}
		}
		if(ans==INF)printf("impossible\n");
		else printf("%d\n",ans);
	}
	return 0;
}
