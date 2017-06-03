#include<cstdio>
#include<cassert>
#include<cmath>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
struct DjSet
{
	vector<int>data,elements;
	void Clear(const vector<int>&_elements)
	{
		elements.clear();
		for(const int i:_elements)elements.push_back(i);
		vector<int>&e=elements;
		sort(e.begin(),e.end()),e.resize(unique(e.begin(),e.end())-e.begin());
		data.resize(elements.size());
		for(int i=0;i<(int)data.size();i++)data[i]=i;
	}
	bool Contains(const int v)
	{
		const auto it=lower_bound(elements.begin(),elements.end(),v);
		return it!=elements.end()&&(*it)==v;
	}
	int Id(const int v)
	{
		const auto it=lower_bound(elements.begin(),elements.end(),v);
		assert(it!=elements.end()&&(*it)==v);
		return it-elements.begin();
	}
	int FindBase(const int a){return data[a]==a?a:(data[a]=FindBase(data[a]));}
	int Find(const int a){return FindBase(Id(a));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;data[a]=b;return true;}
	void OutputAllPairs(map<pair<int,int>,int>&ans)
	{
		vector<vector<int> >s;s.resize(data.size());
		for(int i=0;i<(int)data.size();i++)s[FindBase(i)].push_back(i);
		for(const vector<int>&v:s)
		{
			for(int i=0;i<(int)v.size();i++)for(int j=i+1;j<(int)v.size();j++)
			{
				ans[make_pair(elements[v[i]],elements[v[j]])]++;
				ans[make_pair(elements[v[j]],elements[v[i]])]++;
			}
		}
	}
};
vector<DjSet>BIG_COLORS;
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
vector<Edge>EDGE[100000];
int N,M;
map<pair<int,int>,int>ANS;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<M;i++)EDGE[i].clear();
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c),c--;
			EDGE[c].push_back(Edge(a,b));
		}
		const int sq_m=sqrt(M);
		ANS.clear(),BIG_COLORS.clear();
		for(int i=0;i<M;i++)if(!EDGE[i].empty())
		{
			static DjSet dj;
			vector<int>elements;
			for(const Edge &e:EDGE[i])elements.push_back(e.a),elements.push_back(e.b);
			dj.Clear(elements);
			for(const Edge &e:EDGE[i])dj.Merge(e.a,e.b);
			if((int)EDGE[i].size()<=sq_m)dj.OutputAllPairs(ANS);
			else BIG_COLORS.push_back(dj);
		}
		int querycount;scanf("%d",&querycount);
		for(int a,b;querycount--;)
		{
			scanf("%d%d",&a,&b);
			int ans=0;
			if(true)
			{
				const auto it=ANS.find(make_pair(a,b));
				if(it!=ANS.end())ans+=it->second;
			}
			for(DjSet &dj:BIG_COLORS)if(dj.Contains(a)&&dj.Contains(b)&&dj.Find(a)==dj.Find(b))ans++;
			printf("%d\n",ans);
		}
	}
	return 0;
}
