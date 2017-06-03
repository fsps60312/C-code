#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<stack> 
using namespace std;
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
	SegTree SEG_TREE;
	int N;
	void Clear(const int _N){N=_N;ET.clear();ET.resize(N),SEGS.resize(N);}
	void Build(const int u,int &tick)
	{
		SEGS[u].first=tick;
		for(const int nxt:ET[u])Build(nxt,tick);
		SEGS[u].second=tick++;
	}
	void Build()
	{
		int tick=0;
		Build(0,tick);
		assert(tick==N);
		SEG_TREE.Build(1,0,N-1);
	}
	void AddTag(const int u)
	{
		SEG_TREE.Add(1,0,N-1,SEGS[u].second);
	}
	int CountTags(const int u)
	{
		return SEG_TREE.Query(1,0,N-1,SEGS[u].first,SEGS[u].second);
	}
};
struct SuffixAutomaton
{
	vector<int>EDGE[26],GREEN,MAX_LEN;
	int N;
	void Clear()
	{
		for(int i=0;i<26;i++)EDGE[i].clear();
		GREEN.clear(),MAX_LEN.clear();
		N=0;
		NewNode(0);
	}
	int NewNode(const int max_len)
	{
		for(int i=0;i<26;i++)EDGE[i].push_back(0);
		GREEN.push_back(-1),MAX_LEN.push_back(max_len);
		return N++;
	}
	int Split(int cur,const int c)
	{
		const int wish=NewNode(MAX_LEN[cur]+1),pg=EDGE[c][cur];
		assert(MAX_LEN[pg]>MAX_LEN[cur]+1);
		for(;cur!=-1&&EDGE[c][cur]==pg;cur=GREEN[cur])EDGE[c][cur]=wish;
		for(int i=0;i<26;i++)EDGE[i][wish]=EDGE[i][pg];
		GREEN[wish]=GREEN[pg];
		GREEN[pg]=wish;
		return wish;
	}
	int Extend(const int u,const int c)
	{
		const int last=NewNode(MAX_LEN[u]+1);
		int cur=u;
		for(;cur!=-1&&!EDGE[c][cur];cur=GREEN[cur])EDGE[c][cur]=last;
		if(cur==-1)GREEN[last]=0;
		else
		{
			const int pg=EDGE[c][cur];
			if(MAX_LEN[pg]==MAX_LEN[cur]+1)GREEN[last]=pg;
			else
			{
				const int tmp=Split(cur,c);
				GREEN[last]=tmp;
			}
		}
		assert(GREEN[last]!=-1);
		return last;
	}
	SquashedTree TREE;
	void Build(const char *str)
	{
		Clear();
		vector<int>vis_nodes;
		for(int i=0,u=0;str[i];i++)vis_nodes.push_back(u=Extend(u,str[i]-'a'));
		TREE.Clear(N);
		for(int i=1;i<N;i++)TREE.ET[GREEN[i]].push_back(i);
		TREE.Build();
		for(const int u:vis_nodes)TREE.AddTag(u);
	}
	int Match(const char *str,const int n)
	{
		vector<int>vis_nodes;
		for(int i=0,u=0,len=0;str[i];i++)
		{
			const int c=str[i]-'a';
			while(u&&!EDGE[c][u])u=GREEN[u],len=MAX_LEN[u];
			if(EDGE[c][u])len++,u=EDGE[c][u];
			if(len>=n)vis_nodes.push_back(u);
		}
		sort(vis_nodes.begin(),vis_nodes.end(),
			[this](const int a,const int b)->bool{return TREE.SEGS[a].second<TREE.SEGS[b].second;});
		stack<int>stk;
		for(const int u:vis_nodes)
		{
			while(!stk.empty()&&ContainsSegment(TREE.SEGS[u],TREE.SEGS[stk.top()]))stk.pop();
			stk.push(u);
		}
		int ans=0;
		while(!stk.empty())ans+=TREE.CountTags(stk.top()),stk.pop();
		return ans;
	}
}SAM;
char S[2000000];
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s",S)==1)
	{
		SAM.Build(S);
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			scanf("%s",S);
			int len=-1;while(S[++len]);
			for(int i=0;i<len-1;i++)S[len+i]=S[i];
			S[len*2-1]='\0';
			printf("%d\n",SAM.Match(S,len));
		}
	}
	return 0;
}
