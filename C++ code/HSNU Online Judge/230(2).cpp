#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,C;
struct Child
{
	vector<int>f,l;
	Child(){}
	Child(int *fa,const int &fsz,int *la,const int &lsz)
	{
		f.clear(),l.clear();
		for(int i=0;i<fsz;i++)f.push_back(fa[i]);
		for(int i=0;i<lsz;i++)l.push_back(la[i]);
	}
};
vector<Child>CH[10000];
int HAPPY[10000][1<<5];
int DP[10001][1<<4][1<<4];
inline bool Happy(const Child &ch,const int &s)
{
	const vector<int>&l=ch.l,&f=ch.f;
	for(int i=0;i<l.size();i++)if(s&(1<<(l[i])))return true;
	for(int i=0;i<f.size();i++)if(!(s&(1<<(f[i]))))return true;
	return false;
}
void BuildHAPPY()
{
	for(int i=0;i<N;i++)
	{
		for(int s=0;s<(1<<5);s++)
		{
			int &happy=HAPPY[i][s]=0;
			for(int j=0;j<CH[i].size();j++)if(Happy(CH[i][j],s))happy++;
		}
	}
}
void getmax(int &a,const int &b){if(b>a)a=b;}
int Solve()
{
	const int four=(1<<4)-1;
	for(int i=0;i<(1<<4);i++)for(int j=0;j<(1<<4);j++)DP[0][i][j]=-INF;
	for(int s=0;s<(1<<4);s++)DP[0][s][s]=0;
	for(int i=0;i<N;i++)
	{
		for(int s=0;s<(1<<4);s++)for(int u=0;u<(1<<4);u++)DP[i+1][s][u]=-INF;
		for(int s=0;s<(1<<4);s++)
		{
			for(int u=0;u<(1<<4);u++)
			{
				int &dp=DP[i][s][u];
				if(dp==-INF)continue;
				int now;
				now=u+(0<<4);
				getmax(DP[i+1][s][now>>1],dp+HAPPY[i][now]);
				now=u+(1<<4);
				getmax(DP[i+1][s][now>>1],dp+HAPPY[i][now]);
			}
		}
	}
	int ans=-INF;
	for(int s=0;s<(1<<4);s++)getmax(ans,DP[N][s][s]);
	return ans;
}
int main()
{
//	freopen("out.txt","r",stdin);
	while(scanf("%d%d",&N,&C)==2)
	{
		for(int i=0;i<N;i++)CH[i].clear();
		for(int i=0;i<C;i++)
		{
			static int e,fsz,lsz,fa[5],la[5];
			scanf("%d%d%d",&e,&fsz,&lsz);
			for(int i=0;i<fsz;i++)
			{
				scanf("%d",&fa[i]);
				fa[i]-=e;
				if(fa[i]<0)fa[i]+=N;
				assert(fa[i]>=0&&fa[i]<=4);
			}
			for(int i=0;i<lsz;i++)
			{
				scanf("%d",&la[i]);
				la[i]-=e;
				if(la[i]<0)la[i]+=N;
				assert(la[i]>=0&&la[i]<=4);
			}
			CH[--e].push_back(Child(fa,fsz,la,lsz));
		}
		BuildHAPPY();
		int ans=Solve();
		printf("%d\n",ans);
	}
	return 0;
}
/*
14 5
2 1 2 4 2 6
3 1 1 6 4
6 1 2 9 6 8
8 1 1 9 12
12 3 0 12 13 2
*/
