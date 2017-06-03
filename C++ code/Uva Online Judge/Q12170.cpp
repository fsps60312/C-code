#include<cstdio>
#include<cstdlib>
#include<algorithm>
const int INF=1<<30;
using namespace std;
int T,N,D,H[100],XN,X[20000],DP[100][20000];//money cost when move stone i to height j
void getmin(int &a,int b){if(b<a)a=b;}
int abs(int a){return a>=0?a:-a;}
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
int get_DP(int h,int x)//moving stone h to height x
{
	int &ans=DP[h][x];
	if(ans!=-1)return ans;
	if(h==0)return H[h]==X[x]?0:INF;
	ans=INF;
	for(int i=0;i<XN;i++)
	{
		if(H[h]-X[i]>D)continue;
		if(X[i]-H[h]>D)break;
		getmin(ans,get_DP(h-1,i)+abs(H[h]-X[x]));
	}
	return ans;
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
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<XN;j++)
			{
				DP[i][j]=-1;
			}
		}
		int ans=INF;
		for(int i=0;i<XN;i++)getmin(ans,get_DP(N-1,i));
		if(ans==INF)printf("impossible\n");
		else printf("%d\n",ans);
	}
	return 0;
}
