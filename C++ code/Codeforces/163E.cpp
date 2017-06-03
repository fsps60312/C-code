#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
struct SegTree
{
	vector<int>S;
	void Build(const int id,const int l,const int r)
	{
		while((int)S.size()<=id)S.push_back(0);
		S[id]=0;
		if(l<r)
		{
			const int mid=(l+r)/2;
			Build(id*2,l,mid),Build(id*2+1,mid+1,r);
		}
	}
	void Modify(const int id,const int l,const int r,const int bl,const int br,const int val)
	{
		if(r<bl||br<l)return;
		if(bl<=l&&r<=br){S[id]+=val;return;}
		const int mid=(l+r)/2;
		Modify(id*2,l,mid,bl,br,val),Modify(id*2+1,mid+1,r,bl,br,val);
	}
	int Query(const int id,const int l,const int r,const int loc)
	{
		if(l==r)return S[id];
		const int mid=(l+r)/2;
		if(loc<=mid)return S[id]+Query(id*2,l,mid,loc);
		else return S[id]+Query(id*2+1,mid+1,r,loc);
	}
};
struct SquashedTree
{
	SegTree SEG_TREE;
	vector<vector<int> >ET;
	vector<pair<int,int> >SEGMENTS;
	int N;
	void Clear(const int _N){N=_N;ET.clear();ET.resize(N),SEGMENTS.resize(N);}
	void Build(const int u,int &tick)
	{
		SEGMENTS[u].first=tick;
		for(const int nxt:ET[u])Build(nxt,tick);
		SEGMENTS[u].second=tick++;
	}
	void Build()
	{
		int tick=0;
		Build(0,tick);
		assert(tick==N);
		SEG_TREE.Build(1,0,N-1);
	}
	void ModifyNode(const int u,const int val)
	{
		SEG_TREE.Modify(1,0,N-1,SEGMENTS[u].first,SEGMENTS[u].second,val);
	}
	int QueryParentsSum(const int u)
	{
		return SEG_TREE.Query(1,0,N-1,SEGMENTS[u].second);
	}
};
struct AC_Automaton
{
	vector<int>CH[26],CITIZENS;
	vector<bool>INCLUDED;
	int SZ;
	void Clear()
	{
		for(int i=0;i<26;i++)CH[i].clear();
		CITIZENS.clear(),INCLUDED.clear();
		SZ=0;
		Expand();
	}
	void Expand()
	{
		for(int i=0;i<26;i++)CH[i].push_back(0);
		SZ++;
	}
	int GetNxt(const int u,const int c)
	{
		if(CH[c][u])return CH[c][u];
		Expand();
		return CH[c][u]=SZ-1;
	}
	void Insert(const char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)u=GetNxt(u,str[i]-'a');
		CITIZENS.push_back(u);
		INCLUDED.push_back(false);
	}
	vector<int>FAIL;
	SquashedTree TREE;
	void BuildFail()
	{
		FAIL.resize(SZ);
		TREE.Clear(SZ);
		FAIL[0]=0;
		queue<int>q;
		for(int i=0;i<26;i++)if(CH[i][0])FAIL[CH[i][0]]=0,q.push(CH[i][0]),TREE.ET[0].push_back(CH[i][0]);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			for(int i=0;i<26;i++)if(CH[i][u])
			{
				int &f=FAIL[CH[i][u]]=FAIL[u];
				while(f&&CH[i][f]==0)f=FAIL[f];
				f=CH[i][f];
				q.push(CH[i][u]),TREE.ET[f].push_back(CH[i][u]);
			}
		}
		TREE.Build();
		for(int i=0;i<(int)CITIZENS.size();i++)ModifyCitizen(i,1);
	}
	void ModifyCitizen(const int id,const int val)
	{
		if(val==1){if(INCLUDED[id])return;INCLUDED[id]=true;}
		else if(val==-1){if(!INCLUDED[id])return;INCLUDED[id]=false;}
		else assert(0);
		TREE.ModifyNode(CITIZENS[id],val);
	}
	long long ReadText(const char *str)
	{
		long long ans=0LL;
		int u=0;
		for(int i=0;str[i];i++)
		{
			const int c=str[i]-'a';
			while(u&&CH[c][u]==0)u=FAIL[u];
			u=CH[c][u];
			ans+=TREE.QueryParentsSum(u);
		}
		return ans;
	}
}AC;
int N;
char S[1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	int querycount;scanf("%d%d",&querycount,&N);
	AC.Clear();
	for(int i=0;i<N;i++)
	{
		scanf("%s",S);
		AC.Insert(S);
	}
	AC.BuildFail();
	for(char type;querycount--;)
	{
		index_reinput:;
		type=getchar();
		switch(type)
		{
			case'+':
			{
				int id;scanf("%d",&id),id--;
				AC.ModifyCitizen(id,1);
			}break;
			case'-':
			{
				int id;scanf("%d",&id),id--;
				AC.ModifyCitizen(id,-1);
			}break;
			case'?':
			{
				scanf("%s",S);
				printf("%lld\n",AC.ReadText(S));
			}break;
			default:goto index_reinput;
		}
	}
	return 0;
}
