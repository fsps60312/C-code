#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
int Id(const vector<int>&s,const int v)
{
	const auto &it=lower_bound(s.begin(),s.end(),v);
	assert(it!=s.end());
	return (int)(it-s.begin());
}
struct DisjointSets
{
	int S[1000];
	void Clear(const int N){for(int i=0;i<N;i++)S[i]=i;}
	int Find(const int a){return S[a]==a?a:(S[a]=Find(S[a]));}
	bool Merge(int a,int b){return (a=Find(a))==(b=Find(b))?false:(S[a]=b,true);}
}DJ;
int N,M,T;
bool TERMINAL[200];
vector<pair<int,int> >ET[200];
vector<vector<int> >S;
void GetAllSuffixes(const int u,vector<int>&now)
{
	if(TERMINAL[u])
	{
//		for(const int v:now)printf(" %d",v);puts("");
		vector<int>v=now;
		reverse(v.begin(),v.end());
		S.push_back(v);
	}
	for(const auto &nxt:ET[u])
	{
		now.push_back(nxt.second);
		GetAllSuffixes(nxt.first,now);
		now.pop_back();
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("suffix.in","r",stdin);
	freopen("suffix.out","w",stdout);
	while(scanf("%d%d%d",&N,&M,&T)==3)
	{
		for(int i=0;i<N;i++)TERMINAL[i]=false,ET[i].clear();
		for(int i=0,v;i<T;i++)scanf("%d",&v),TERMINAL[--v]=true;
		for(int i=0,a,b;i<M;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			ET[a].push_back(make_pair(b,i));
		}
		S.clear();
		{vector<int>now;GetAllSuffixes(0,now);}
		DJ.Clear(M);
		int mx=0;
		for(int i=0;i<(int)S.size();i++)
		{
			if(S[i].size()>S[mx].size())mx=i;
			for(int j=0;j<(int)S.size();j++)if(i!=j)
			{
				const vector<int>&a=S[i],&b=S[j];
				assert(a.size()!=b.size());
				for(int k=0;k<(int)a.size()&&k<(int)b.size();k++)DJ.Merge(a[k],b[k]);
			}
		}
		vector<int>w;
		for(int i=0;i<M;i++)w.push_back(DJ.Find(i));
		sort(w.begin(),w.end()),w.resize(unique(w.begin(),w.end())-w.begin());
		printf("%d %d\n",(int)S[mx].size(),(int)w.size());
		reverse(S[mx].begin(),S[mx].end());
		for(int i=0;i<(int)S[mx].size();i++)
		{
			if(i)putchar(' ');
			printf("%d",Id(w,DJ.Find(S[mx][i]))+1);
		}
		puts("");
		for(int i=0;i<M;i++)
		{
			if(i)putchar(' ');
			printf("%d",Id(w,DJ.Find(i))+1);
		}
		puts("");
		assert(S[mx].size()+1==S.size());
	}
	return 0;
}
