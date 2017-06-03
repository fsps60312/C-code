#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
typedef long long LL;
struct Matrix
{
	LL s[2][2];
	Matrix operator*(const Matrix &a)const
	{
		Matrix ans;
		for(int i=0;i<2;i++)for(int j=0;j<2;j++)
		{
			LL &v=ans.s[i][j]=0;
			for(int k=0;k<2;k++)(v+=s[i][k]*a.s[k][j])%=mod;
		}
	}
};
LL Get(LL p)
{
	Matrix a;
	a.s[0][0]=0LL;
	a.s[0][1]=a.s[1][1]=a.s[1][0]=1LL;
	Matrix ans;
	ans.s[0][0]=ans.s[1][1]=1LL;
	ans.s[1][0]=ans.s[0][1]=0LL;
	for(;p;p>>=1)
	{
		if(p&1LL)ans=ans*a;
		a=a*a;
	}
	return ans.s[1][0];
}
vector<int>F;
struct Node
{
	int p;
	LL cycle,id;
	LL val;
	vector<Node*>ch;
	Node(const int _p,const LL _cycle,const LL _id,const LL _val):p(_p),cycle(_cycle),id(_id),val(_val){}
	void Expand()
	{
		LL mod=1LL;
		for(int i=0;i<p;i++)mod*=10LL;
		map<pair<LL,LL>,LL>vis;
		for(int i=0;;i++)
		{
			const pair<LL,LL>&p=make_pair(Get(cycle*i+id-1LL)%mod,Get(cycle*i+id)%mod);
			if(vis.find(p)!=vis.end())
			{
				const LL &nxtcyc=vis[p];
				for(const auto p:vis)
				{
					ch.push_back(new Node(p+1,nxtcyc,p.second,p.first.second));
				}
				break;
			}
			else vis[p]=i*cycle+id;
		}
	}
};
LL Dfs(const int dep,const LL cycle,const LL id)
{
	LL mod=1LL;
	for(int i=0;i<dep;i++)mod*=10LL;
	map<pair<LL,LL>,LL>vis;
	LL ans=INF;
	for(int i=0;;i++)
	{
		const pair<LL,LL>&p=make_pair(Get(cycle*i+id-1LL,mod),Get(cycle*i+id,mod));
		if(vis.find(p)!=vis.end())
		{
			const LL &nxtcyc=vis[p];
			for(const auto p:vis)
			{
				if(dep==13)getmin(ans,p.second);
				else getmin(ans,Dfs(dep+1,nxtcyc,p.second));
			}
			break;
		}
		else vis[p]=i*cycle+id;
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	for(LL f;scanf("%lld",&f)==1;)
	{
		F.clear();
		for(;f;f/=10LL)F.push_back(f%10LL);
		vector<int,vector<make_pair<int,int> > >s;
		CH.clear();
	}
	return 0;
}
