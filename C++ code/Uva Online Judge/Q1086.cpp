#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int B,M;
struct Vote
{
	struct Bse
	{
		int b,v;
		Bse(){}
		Bse(int b,int v):b(b),v(v){}
		int idx(){return b*2+v;}
//		bool operator<(const Bse &a)const{return b<a.b;}
	};
	vector<Bse>bse;
	void canf()
	{
		bse.clear();
		static int k;
		scanf("%d",&k);
		while(k--)
		{
			static char yn[2];
			static int v;
			scanf("%d%s",&v,yn);
			bse.push_back(Bse(--v,yn[0]=='y'?1:0));
		}
	}
	const int size(){return bse.size();}
	Bse operator[](int i){return bse[i];}
};
vector<Vote>VOTE;
bool VIS[200];
vector<int>TO[200];
vector<int>STK;
bool dfs(int u)
{
	if(VIS[u^1])return false;
	if(VIS[u])return true;
	VIS[u]=true;
	STK.push_back(u);
	for(int i=0;i<TO[u].size();i++)
	{
		int &j=TO[u][i];
		if(!dfs(j))return false;
	}
	return true;
}
bool solve()
{
	for(int i=0;i<B*2;i+=2)
	{
		if(VIS[i]||VIS[i^1])continue;
		if(!TO[i].size()&&!TO[i^1].size())continue;
		int ti=i;
		if(!TO[ti].size())ti^=1;
		STK.clear();
		bool d1=dfs(ti)
		if(!dfs(ti))
		{
			for(int j=0;j<STK.size();j++)VIS[STK[j]]=false;
			if(!dfs(ti^1))return false;
		}
	}
	return true;
}
int main()
{
	while(scanf("%d%d",&B,&M)==2&&(B||M))
	{
		for(int i=0;i<B*2;i++)
		{
			VIS[i]=false;
			TO[i].clear();
		}
		VOTE.clear();
		for(int i=0;i<M;i++)
		{
			static Vote v;
			v.canf();
			VOTE.push_back(v);
		}
		for(int i=0;i<M;i++)
		{
			Vote &v=VOTE[i];
			if(v.size()<=2)
			{
				for(int j=0;j<v.size();j++)
				{
					VIS[v[j].idx()]=true;
				}
			}
			else
			{
				for(int j=0;j<v.size();j++)
				{
					int idx=v[j].idx()^1;
					for(int k=0;k<v.size();k++)
					{
						if(k==j)continue;
						TO[idx].push_back(v[k].idx());
					}
				}
			}
		}
		static int kase=1;
		printf("Case %d: ",kase++);
		if(solve())
		{
			static char ans[101];
			for(int i=0;i<B;i++)
			{
				if(!VIS[i*2]&&!VIS[i*2+1])ans[i]='?';
				else if(VIS[i*2])ans[i]='n';
				else ans[i]='y';
			}
			ans[B]=0;
			puts(ans);
		}
		else puts("impossible");
	}
	return 0;
}
