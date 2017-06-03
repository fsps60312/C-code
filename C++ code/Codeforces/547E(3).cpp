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
struct SuffixAutomaton 
{
	vector<int>EDGE[26],GREEN,MAX_LEN,COUNT;
	int N;
	void Clear()
	{
		for(int i=0;i<26;i++)EDGE[i].clear();
		GREEN.clear(),MAX_LEN.clear(),COUNT.clear();
		N=0;
		NewNode(0);
	}
	void NewNode(const int max_len)
	{
		for(int i=0;i<26;i++)EDGE[i].push_back(0);
		GREEN.push_back(-1),MAX_LEN.push_back(max_len),COUNT.push_back(0);
		N++;
	}
	void Split(int cur,const int c)
	{
		const int pg=EDGE[c][cur];
		NewNode(MAX_LEN[cur]+1);
		const int wish=N-1;
		for(;cur!=-1&&EDGE[c][cur]==pg;cur=GREEN[cur])EDGE[c][cur]=wish;
		for(int i=0;i<26;i++)EDGE[i][wish]=EDGE[i][cur];
		GREEN[wish]=GREEN[cur];
		GREEN[cur]=wish;
	}
	void Extend(int &last,const int c)
	{
		if(!EDGE[c][last])
		{
			int cur=last;NewNode(MAX_LEN[cur]+1),last=N-1;
			for(;cur!=-1&&!EDGE[c][cur];cur=GREEN[cur])EDGE[c][cur]=last;
			if(cur==-1)GREEN[last]=0;
			else
			{
				const int pg=EDGE[c][cur];
				if(MAX_LEN[pg]==MAX_LEN[cur]+1)GREEN[last]=pg;
				else Split(cur,c),GREEN[last]=N-1;
			}
		}
		else
		{
			if(MAX_LEN[EDGE[c][last]]>MAX_LEN[last]+1)Split(last,c);
			else assert(MAX_LEN[EDGE[c][last]]==MAX_LEN[last]+1);
			last=EDGE[c][last];
		}
	}
	void Insert(const char *str)
	{
		int last=0;
		for(int i=0;str[i];i++)Extend(last,str[i]-'a'),COUNT[last]++;
	}
	SquashedTree TREE;
	void BuildTree()
	{
		TREE.Clear(N);
		for(int i=1;i<N;i++)TREE.ET[GREEN[i]].push_back(i);
		TREE.Build();
		for(int i=0;i<N;i++)if(COUNT[i])TREE.AddCount(i,COUNT[i]);
	}
	LL CountCalleds(const char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)
		{
			const int c=str[i]-'a';
			if(!EDGE[c][u])return 0LL;
			u=EDGE[c][u];
		}
		return TREE.QueryCounts(u);
	}
};
struct SAM_Bit
{
	SuffixAutomaton SAMS[200001];
	string STRS[200001];
	int N;
	void Clear(){N=0;}
	void Add(const char *str)
	{
		N++;
		STRS[N]=str;
		SAMS[N].Clear();
		for(int i=N-(N&(-N))+1;i<=N;i++)SAMS[N].Insert(STRS[i].c_str());
		SAMS[N].BuildTree();
	}
	LL Query(int i,const char *str)
	{
//		printf("Query(%d,%s)\n",i,str);
		LL ans=0LL;
		for(;i;i-=(i&(-i)))ans+=SAMS[i].CountCalleds(str);
		return ans;
	}
	LL Query(const int l,const int r,const int k)
	{
		return Query(r,STRS[k].c_str())-Query(l-1,STRS[k].c_str());
	}
}SAM_BIT;
int N;
int main()
{
	freopen("in.txt","r",stdin);
	int querycount;
	scanf("%d%d",&N,&querycount);
	SAM_BIT.Clear();
	for(int i=0;i<N;i++)
	{
		static char str[200001];
		scanf("%s",str);
		SAM_BIT.Add(str);
	}
	for(int l,r,k;querycount--;)
	{
		scanf("%d%d%d",&l,&r,&k);
		printf("%lld\n",SAM_BIT.Query(l,r,k));
	}
	return 0;
}
