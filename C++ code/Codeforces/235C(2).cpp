#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
#include<stack>
#include<algorithm>
using namespace std;
bool IncludeSegment(const pair<int,int>&a,const pair<int,int>&b){return a.first<=b.first&&b.second<=a.second;}
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
	void Add(const int id,const int l,const int r,const int loc)
	{
		SUM[id]++;
		if(l<r)
		{
			const int mid=(l+r)/2;
			if(loc<=mid)Add(id*2,l,mid,loc);
			else Add(id*2+1,mid+1,r,loc);
		}
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
	void Clear(const int _N){N=_N;ET.clear();ET.resize(N),SEGS.resize(N);}
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
	const pair<int,int>&Segment(const int u){return SEGS[u];}
	void AddSize(const int u){SEG_TREE.Add(1,0,N-1,SEGS[u].second);}
	int QuerySize(const int u){return SEG_TREE.Query(1,0,N-1,SEGS[u].first,SEGS[u].second);}
};
struct SuffixAutomaton
{
	vector<int>EDGE[26],GREEN,MAX_LEN;
	vector<vector<int> >VIS_NODES;
	int SIZE;
	void Clear()
	{
		for(int i=0;i<26;i++)EDGE[i].clear();
		GREEN.clear(),MAX_LEN.clear();
		VIS_NODES.clear();
		SIZE=0;
		NewNode(0);
	}
	int NewNode(const int max_len)
	{
		for(int i=0;i<26;i++)EDGE[i].push_back(0);
		GREEN.push_back(0),MAX_LEN.push_back(max_len);
		return SIZE++;
	}
	int Split(int cur,const int c)
	{
		const int pg=EDGE[c][cur];
		assert(MAX_LEN[pg]>MAX_LEN[cur]+1);
		const int wish=NewNode(MAX_LEN[cur]+1);
		for(;cur&&EDGE[c][cur]==pg;cur=GREEN[cur])EDGE[c][cur]=wish;
		for(int i=0;i<26;i++)EDGE[i][wish]=EDGE[i][pg];
		GREEN[wish]=GREEN[pg];
		GREEN[pg]=wish;
		return wish;
	}
	void Insert(const char *str)
	{
		int last=0,n=-1;while(str[++n]);
		vector<int>vis_nodes;
		for(int i=0;i<n*2-1;i++)
		{
			const int c=str[i%n]-'a';
			if(!EDGE[c][last])
			{
				int cur=last;
				last=NewNode(MAX_LEN[cur]+1);
				for(;cur&&!EDGE[c][cur];cur=GREEN[cur])EDGE[c][cur]=last;
				if(!EDGE[c][cur])EDGE[c][cur]=last;
				else
				{
					const int pg=EDGE[c][cur];
					if(MAX_LEN[pg]==MAX_LEN[cur]+1)GREEN[last]=pg;
					else GREEN[last]=Split(cur,c);
				}
			}
			else
			{
				const int pl=EDGE[c][last];
				if(MAX_LEN[pl]==MAX_LEN[last]+1)last=pl;
				else last=Split(last,c);
			}
			assert(MAX_LEN[last]==i+1);
			if(MAX_LEN[last]>=n)vis_nodes.push_back(last);
		}
		VIS_NODES.push_back(vis_nodes);
	}
	void TryMatch(const char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)
		{
			const int c=str[i]-'a';
			while(u&&!EDGE[c][u])u=GREEN[u];
			if(EDGE[c][u])
			{
				if(MAX_LEN[EDGE[c][u]]==MAX_LEN[u]+1)u=EDGE[c][u];
				else u=Split(u,c);
			}
		}
	}
	SquashedTree TREE;
	void BuildTrees()
	{
		TREE.Clear(SIZE);
		for(int i=1;i<SIZE;i++)TREE.ET[GREEN[i]].push_back(i);
		TREE.Build();
	}
	vector<pair<int,int> >TRACE;
	void Match(const char *str)
	{
		TRACE.clear();
		int u=0;
		for(int i=0;str[i];i++)
		{
			const int c=str[i]-'a';
			while(u&&!EDGE[c][u])u=GREEN[u];
			u=EDGE[c][u];
			TREE.AddSize(u);
		}
	}
	int Query(const int queryindex)
	{
		sort(VIS_NODES[queryindex].begin(),VIS_NODES[queryindex].end(),
			[this](const int a,const int b)->bool{return TREE.Segment(a).second<TREE.Segment(b).second;});
		stack<int>changes;
		int ans=0;
		for(const int u:VIS_NODES[queryindex])
		{
			while(!changes.empty()&&IncludeSegment(TREE.Segment(u),TREE.Segment(changes.top())))
			{
				ans-=TREE.QuerySize(changes.top()),changes.pop();
			}
			ans+=TREE.QuerySize(u),changes.push(u);
		}
		return ans;
	}
}SAM;
char S[1000001];
int N;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%s",S)==1)
	{
		scanf("%d",&N);
		SAM.Clear();
		for(int i=0;i<N;i++)
		{
			static char str[1000001];
			scanf("%s",str);
			SAM.Insert(str);
		}
		SAM.TryMatch(S);
		SAM.BuildTrees();
		SAM.Match(S);
		for(int i=0;i<N;i++)printf("%d\n",SAM.Query(i));
	}
	return 0;
}
