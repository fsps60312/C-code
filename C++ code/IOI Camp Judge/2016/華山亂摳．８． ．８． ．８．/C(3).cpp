#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int A[4],PRE[4][1000000],VIS[4][1000000],KASE=0;
vector<int>S[4];
int Solve(const int dep,const int mod)
{
	int ans;
	if(dep==3)ans=A[dep];
	else
	{
		vector<int>&nxto=S[dep];
		nxto.clear();
		nxto.push_back(1LL);
		int *pre=PRE[dep],*vis=VIS[dep];
//		for(int i=0;i<mod;i++)pre[i]=-1;
		KASE++;
		pre[1]=0,vis[1]=KASE;
		for(int i=1;;i++)
		{
			const int v=(long long)nxto[i-1]*A[dep]%mod;
			nxto.push_back(v);
			if(vis[v]!=KASE)pre[v]=-1,vis[v]=KASE;
			if(pre[v]!=-1)
			{
				ans=Solve(dep+1,i-pre[v]);
				break;
			}
			else pre[v]=i;
		}
	}
	if(dep==0)return ans;
	const vector<int>&offset=S[dep-1];
	if(ans<(int)offset.size())return offset[ans];
	const int v=((ans-(int)offset.size())/mod+1LL)*mod;
	assert((int)offset.size()-mod<=ans-v&&ans-v<(int)offset.size());
	return offset[ans-v];
}
int main()
{
	for(int i=0;i<4;i++)for(int j=0;j<1000000;j++)VIS[i][j]=0;
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		for(int i=0;i<4;i++)scanf("%d",&A[i]);
		int m;scanf("%d",&m);
		printf("%d\n",Solve(0,m));
	}
	return 0;
}
