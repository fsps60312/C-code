#include<cstdio>
#include<cassert>
#include<vector>
#include<string>
#include<map>
using namespace std;
typedef long long LL;
bool ContainsSegment(const pair<int,int>&a,const pair<int,int>&b)
{
	return a.first<=b.first&&b.second<=a.second;
}
struct Bit
{
	vector<LL>DATA;
	int N;
	void Clear(const int _N){N=_N;DATA.clear(),DATA.resize(N+1,0LL);}
	void Modify(int i,const LL &val){i++;for(;i<=N;i+=(i&(-i)))DATA[i]+=val;}
	LL Query(int i){i++;LL ans=0LL;for(;i;i-=(i&(-i)))ans+=DATA[i];return ans;}
	LL Query(const int l,const int r){return Query(r)-Query(l-1);}
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
	Bit BIT;
	void Build()
	{
		int tick=0;
		Build(0,tick);
		assert(tick==N);
		vector<vector<int> >().swap(ET);//release memory
		BIT.Clear(N);
	}
	void AddCount(const int u,const int count)
	{
		BIT.Modify(SEGS[u].second,count);
	}
	LL QueryCounts(const int u)
	{
		return BIT.Query(SEGS[u].first,SEGS[u].second);
	}
};
struct SuffixAutomaton 
{
	vector<int>HEAD,NEXT,NODE_ID;
	vector<char>ALPHABET;
	vector<int>GREEN,MAX_LEN,COUNT;
	int N,NSZ;
	void Clear()
	{
		HEAD.clear(),NEXT.clear(),ALPHABET.clear(),NODE_ID.clear();
		GREEN.clear(),MAX_LEN.clear(),COUNT.clear();
		N=NSZ=0;
		NewNode(0);
	}
	void NewNode(const int max_len)
	{
		HEAD.push_back(-1);
		GREEN.push_back(-1),MAX_LEN.push_back(max_len),COUNT.push_back(0);
		N++;
	}
	void ExtendNext(const char c,const int next,const int node_id)
	{
		NEXT.push_back(next),ALPHABET.push_back(c),NODE_ID.push_back(node_id);
		NSZ++;
	}
	int GetChild(const int u,const char c)
	{
		for(int cur=HEAD[u];cur!=-1;cur=NEXT[cur])if(ALPHABET[cur]==c)return NODE_ID[cur];
		return 0;
	}
	void AddChild(const int u,const int c,const int node_id)
	{
		ExtendNext(c,HEAD[u],node_id);
		HEAD[u]=NSZ-1;
	}
	void SetChild(const int u,const char c,const int node_id)
	{
		for(int cur=HEAD[u];cur!=-1;cur=NEXT[cur])if(ALPHABET[cur]==c)
		{
			NODE_ID[cur]=node_id;return;
		}
		AddChild(u,c,node_id);
	}
	void Split(int cur,const int c,const int pg)
	{
		NewNode(MAX_LEN[cur]+1);
		const int wish=N-1;
		for(;cur!=-1&&GetChild(cur,c)==pg;cur=GREEN[cur])SetChild(cur,c,wish);
		for(cur=HEAD[pg];cur!=-1;cur=NEXT[cur])AddChild(wish,ALPHABET[cur],NODE_ID[cur]);
		GREEN[wish]=GREEN[pg];
		GREEN[pg]=wish;
	}
	void Extend(int &last,const char c)
	{
		int trywalk=GetChild(last,c);
		if(!trywalk)
		{
			int cur=last;NewNode(MAX_LEN[cur]+1),last=N-1;
			for(;cur!=-1&&!GetChild(cur,c);cur=GREEN[cur])AddChild(cur,c,last);
			if(cur==-1)GREEN[last]=0;
			else
			{
				const int pg=GetChild(cur,c);
				if(MAX_LEN[pg]==MAX_LEN[cur]+1)GREEN[last]=pg;
				else Split(cur,c,pg),GREEN[last]=N-1;
			}
		}
		else
		{
			if(MAX_LEN[trywalk]>MAX_LEN[last]+1)Split(last,c,trywalk),trywalk=N-1;
			assert(MAX_LEN[trywalk]==MAX_LEN[last]+1);
			last=trywalk;
		}
	}
	void Insert(const char *str)
	{
		int last=0;
		for(int i=0;str[i];i++)Extend(last,str[i]),COUNT[last]++;
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
			u=GetChild(u,str[i]);
			if(!u)return 0LL;
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
		ANS[N].clear();
		STRS[N]=str;
		SAMS[N].Clear();
		for(int i=N-(N&(-N))+1;i<=N;i++)SAMS[N].Insert(STRS[i].c_str());
		SAMS[N].BuildTree();
	}
	map<int,LL>ANS[200001];
	LL GetAnswer(const int i,const int v)
	{
		const auto it=ANS[i].find(v);
		if(it!=ANS[i].end())return it->second;
		return ANS[i][v]=SAMS[i].CountCalleds(STRS[v].c_str());
	}
	LL Query(int i,const int v)
	{
		LL ans=0LL;
		for(;i;i-=(i&(-i)))ans+=GetAnswer(i,v);
		return ans;
	}
	LL Query(const int l,const int r,const int k)
	{
		return Query(r,k)-Query(l-1,k);
	}
}SAM_BIT;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
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
		printf("%I64d\n",SAM_BIT.Query(l,r,k));
	}
	return 0;
}
