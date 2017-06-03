#include<cstdio>
#include<cassert>
#include<queue>
#include<vector>
#include<string>
#include<stack>
#include<algorithm>
using namespace std;
typedef long long LL;
bool ContainsSegment(const pair<int,int>&a,const pair<int,int>&b)
{
	return a.first<=b.first&&b.second<=a.second;
}
struct SegTree
{
	vector<int>SUM;
	void Build(const int id,const int l,const int r)
	{
		while((int)SUM.size()<=id)SUM.push_back(0);
		SUM[id]=0;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Modify(const int id,const int l,const int r,const int loc,const int val)
	{
		SUM[id]+=val;
		if(l==r)return;
		const int mid=(l+r)/2;
		if(loc<=mid)return Modify(id*2,l,mid,loc,val);
		else return Modify(id*2+1,mid+1,r,loc,val);
	}
	int Query(const int id,const int l,const int r,const int bl,const int br)
	{
		if(r<bl||br<l)return 0;
		if(bl<=l&&r<=br)return SUM[id];
		const int mid=(l+r)/2;
		return Query(id*2,l,mid,bl,br)+Query(id*2+1,mid+1,r,bl,br);
	}
};
struct SquashedTree
{
	vector<vector<int> >ET;
	vector<pair<int,int> >SEGS;
	int N;
	void Clear(const int _N)
	{
		N=_N;
		ET.clear();
		ET.resize(N),SEGS.resize(N);
	}
	void Build(const int u,int &tick)
	{
		SEGS[u].first=tick;
		for(const int nxt:ET[u])Build(nxt,tick);
		SEGS[u].second=tick++; 
	}
	SegTree SEG_TREE;
	void Build()
	{
		int tick=0;
		Build(0,tick);
		assert(tick==N);
		SEG_TREE.Build(1,0,N-1);
	}
	void AddCount(const int u,const int count)
	{
		SEG_TREE.Modify(1,0,N-1,SEGS[u].second,count);
	}
	int QueryCounts(const int u)
	{
//		printf("segment=(%d,%d)\n",SEGS[u].first,SEGS[u].second);
		return SEG_TREE.Query(1,0,N-1,SEGS[u].first,SEGS[u].second);
	}
};
struct AC_Automaton
{
	vector<int>CH[26],COUNT;
	int N;
	void Clear()
	{
		for(int i=0;i<26;i++)CH[i].clear();
		COUNT.clear();
		N=0;
		Expand();
	}
	void Expand()
	{
		for(int i=0;i<26;i++)CH[i].push_back(0);
		COUNT.push_back(0);
		N++;
	}
	int GetNxt(const int u,const int c)
	{
		if(CH[c][u])return CH[c][u];
		Expand();return CH[c][u]=N-1;
	}
	void Insert(const char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)u=GetNxt(u,str[i]-'a');
		COUNT[u]++;
	}
	vector<int>FAIL;
	SquashedTree TREE;
	void BuildFail()
	{
		FAIL.resize(N);
		FAIL[0]=0;
		queue<int>q;
		for(int i=0;i<26;i++)if(CH[i][0])FAIL[CH[i][0]]=0,q.push(CH[i][0]);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			for(int i=0;i<26;i++)if(CH[i][u])
			{
				int &f=FAIL[CH[i][u]]=FAIL[u];
				while(f&&!CH[i][f])f=FAIL[f];
				f=CH[i][f];
				q.push(CH[i][u]);
			}
		}
		TREE.Clear(N);
		for(int i=1;i<N;i++)TREE.ET[FAIL[i]].push_back(i);
		TREE.Build();
		for(int i=0;i<N;i++)if(COUNT[i])TREE.AddCount(i,COUNT[i]);
	}
	LL CountCalleds(const char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)
		{
			const int c=str[i]-'a';
			if(!CH[c][u])return 0LL;
			u=CH[c][u];
		}
		return TREE.QueryCounts(u);
	}
};
struct AC_Bit
{
	AC_Automaton ACS[200001];
	string STRS[200001];
	int N;
	void Clear(){N=0;}
	void Add(const char *str)
	{
		N++;
		STRS[N]=str;
		ACS[N].Clear();
		for(int i=N-(N&(-N))+1;i<=N;i++)ACS[N].Insert(STRS[i].c_str());
		ACS[N].BuildFail();
	}
	LL Query(int i,const char *str)
	{
//		printf("Query(%d,%s)\n",i,str);
		LL ans=0LL;
		for(;i;i-=(i&(-i)))ans+=ACS[i].CountCalleds(str);
		return ans;
	}
	LL Query(const int l,const int r,const int k)
	{
		return Query(r,STRS[k].c_str())-Query(l-1,STRS[k].c_str());
	}
}AC_BIT;
int N;
int main()
{
	freopen("in.txt","r",stdin);
	int querycount;
	scanf("%d%d",&N,&querycount);
	AC_BIT.Clear();
	for(int i=0;i<N;i++)
	{
		static char str[200001];
		scanf("%s",str);
		AC_BIT.Add(str);
	}
	for(int l,r,k;querycount--;)
	{
		scanf("%d%d%d",&l,&r,&k);
		printf("%lld\n",AC_BIT.Query(l,r,k));
	}
	return 0;
}
