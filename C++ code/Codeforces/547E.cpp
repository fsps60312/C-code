#include<cstdio>
#include<cassert>
#include<queue>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;
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
	void Modify(const int id,const int l,const int r,const int bl,const int br,const int val)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){SUM[id]+=val;return;}
		const int mid=(l+r)/2;
		Modify(id*2,l,mid,bl,br,val),Modify(id*2+1,mid+1,r,bl,br,val);
	}
	int Query(const int id,const int l,const int r,const int loc)
	{
		if(l==r)return SUM[id];
		const int mid=(l+r)/2;
		if(loc<=mid)return SUM[id]+Query(id*2,l,mid,loc);
		else return SUM[id]+Query(id*2+1,mid+1,r,loc);
	}
};
struct SquashedTree
{
	vector<vector<int> >ET,PARENT;
	vector<pair<int,int> >SEGS;
	vector<int>DEPTH;
	int N;
	void Clear(const int _N)
	{
		N=_N;
		ET.clear(),PARENT.clear();
		ET.resize(N),PARENT.resize(N),SEGS.resize(N),DEPTH.resize(N);
	}
	void Build(const int u,const int parent,const int depth,int &tick)
	{
		DEPTH[u]=depth;
		PARENT[u].clear();
		if(parent!=-1)
		{
			for(int cur=parent,i=0;;cur=PARENT[cur][i++])
			{
				PARENT[u].push_back(cur);
				if(i>=(int)PARENT[cur].size())break;
			}
		}
		SEGS[u].first=tick;
		for(const int nxt:ET[u])Build(nxt,u,depth+1,tick);
		SEGS[u].second=tick++; 
	}
	SegTree SEG_TREE;
	void Build()
	{
		int tick=0;
		Build(0,-1,0,tick);
		assert(tick==N);
		SEG_TREE.Build(1,0,N-1);
	}
	int QueryLCA(int a,int b)
	{
		if(DEPTH[a]<DEPTH[b])swap(a,b);
		for(int dis=DEPTH[a]-DEPTH[b],i=0;(1<<i)<=dis;i++)if(dis&(1<<i))a=PARENT[a][i];
		assert(DEPTH[a]==DEPTH[b]);
		if(a==b)return a;
		for(int i=30;i>=0;i--)if((1<<i)<DEPTH[a]&&PARENT[a][i]!=PARENT[b][i])
		{
			a=PARENT[a][i],b=PARENT[b][i];
		}
		assert(PARENT[a][0]==PARENT[b][0]);
		return PARENT[a][0];
	}
	void AddCount(const int u,const int count)
	{
		SEG_TREE.Modify(1,0,N-1,SEGS[u].first,SEGS[u].second,count);
	}
	int QueryCounts(const int u)
	{
		return SEG_TREE.Query(1,0,N-1,SEGS[u].second);
	}
};
struct AC_Automaton
{
	vector<int>CH[26],COUNT;
	vector<bool>IS_END;
	int N;
	void Clear()
	{
		for(int i=0;i<26;i++)CH[i].clear();
		COUNT.clear(),IS_END.clear();
		N=0;
		Expand();
	}
	void Expand()
	{
		for(int i=0;i<26;i++)CH[i].push_back(0);
		COUNT.push_back(0),IS_END.push_back(false);
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
		COUNT[u]++,IS_END[u]=true;
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
				if(IS_END[f])IS_END[CH[i][u]]=true;
				q.push(CH[i][u]);
			}
		}
		TREE.Clear(N);
		for(int i=1;i<N;i++)TREE.ET[FAIL[i]].push_back(i);
		TREE.Build();
		for(int i=0;i<N;i++)if(COUNT[i])TREE.AddCount(i,COUNT[i]);
	}
	int CountCalls(const char *str)
	{
		
	}
};
struct AC_Bit
{
	
}BIT;
int main()
{
	freopen("in.txt","r",stdin);
	assert(0);
	return 0;
}
