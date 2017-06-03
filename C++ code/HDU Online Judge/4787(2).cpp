#include<cstdio>
#include<cassert>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>
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
	vector<vector<int> >ET,PARENT;
	vector<int>DEPTH;
	vector<pair<int,int> >SEGS;
	int N;
	void Clear(const int _N)
	{
		N=_N;
		ET.clear();
		ET.resize(N),PARENT.resize(N),DEPTH.resize(N);
		SEGS.resize(N);
	}
	void Build(const int u,const int parent,const int depth,int &tick)
	{
		DEPTH[u]=depth;
		PARENT[u].clear();
		if(parent!=-1)
		{
			for(int i=0,cur=parent;;cur=PARENT[cur][i++])
			{
				PARENT[u].push_back(cur);
				if((1<<i)>DEPTH[cur])break;
			}
		}
		SEGS[u].first=tick;
		for(int i=0;i<(int)ET[u].size();i++)Build(ET[u][i],u,depth+1,tick);
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
		for(int i=0,dis=DEPTH[a]-DEPTH[b];(1<<i)<=dis;i++)if(dis&(1<<i))a=PARENT[a][i];
		assert(DEPTH[a]==DEPTH[b]);
		if(a==b)return a;
		for(int i=30;i>=0;i--)if((1<<i)<=DEPTH[a]&&PARENT[a][i]!=PARENT[b][i])
		{
			a=PARENT[a][i],b=PARENT[b][i];
		}
		assert(PARENT[a][0]==PARENT[b][0]);
		return PARENT[a][0];
	}
	void AddCount(const int u,const int count){SEG_TREE.Modify(1,0,N-1,SEGS[u].first,SEGS[u].second,count);}
	int QueryCount(const int u){return SEG_TREE.Query(1,0,N-1,SEGS[u].second);}
}*TREE_FOR_SORT;
bool Cmp(const int a,const int b){return TREE_FOR_SORT->SEGS[a].second<TREE_FOR_SORT->SEGS[b].second;}
struct AC_Automaton
{
	vector<int>CH[2],COUNT;
	int N;
	void Clear()
	{
		for(int i=0;i<2;i++)CH[i].clear();
		COUNT.clear();
		N=0;Extend();
	}
	void Extend()
	{
		for(int i=0;i<2;i++)CH[i].push_back(0);
		COUNT.push_back(0);
		N++;
	}
	int GetNxt(const int u,const int c)
	{
		if(CH[c][u])return CH[c][u];
		Extend();return CH[c][u]=N-1;
	}
	void Insert(const char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)u=GetNxt(u,str[i]-'0');
//		COUNT[u]++;
		COUNT[u]=1;
	}
	vector<int>FAIL;
	SquashedTree TREE;
	void Build()
	{
		FAIL.resize(N);
		FAIL[0]=0;
		queue<int>q;
		for(int i=0;i<2;i++)if(CH[i][0])q.push(CH[i][0]),FAIL[CH[i][0]]=0;
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			for(int i=0;i<2;i++)if(CH[i][u])
			{
				int &f=FAIL[CH[i][u]]=FAIL[u];
				while(f&&CH[i][f]==0)f=FAIL[f];
				f=CH[i][f];
				q.push(CH[i][u]);
			}
		}
		TREE.Clear(N);
		for(int i=1;i<N;i++)TREE.ET[FAIL[i]].push_back(i);
		TREE.Build();
		for(int i=0;i<N;i++)if(COUNT[i])TREE.AddCount(i,COUNT[i]);
	}
	int Query(const char *str)
	{
		int u=0;
		vector<int>vis_nodes;
		for(int i=0;str[i];i++)
		{
			const int c=str[i]-'0';
			while(u&&CH[c][u]==0)u=FAIL[u];
			u=CH[c][u];
			vis_nodes.push_back(u);
		}
		sort(vis_nodes.begin(),vis_nodes.end(),
			[this](const int a,const int b)->bool{return TREE.SEGS[a].second<TREE.SEGS[b].second;});
		int ans=0;
		for(int i=0;i<(int)vis_nodes.size();i++)
		{
			if(i)ans-=TREE.QueryCount(TREE.QueryLCA(vis_nodes[i-1],vis_nodes[i]));
			ans+=TREE.QueryCount(vis_nodes[i]);
		}
		return ans;
	}
};
struct AC_Bit
{
	AC_Automaton ACS[100001];
	string STRS[100001];
	int N;
	void Clear(){N=0;}
	void AddString(const char *str)
	{
		N++;
		STRS[N]=str;
		ACS[N].Clear();
		for(int i=N-(N&(-N))+1;i<=N;i++)ACS[N].Insert(str);
		ACS[N].Build();
	}
	int Query(const char *str)
	{
		int ans=0;
		for(int i=N;i;i-=i&(-i))ans+=ACS[i].Query(str);
		return ans;
	}
}BIT;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	for(int n;testcount--;)
	{
		scanf("%d",&n);
		BIT.Clear();
		static int kase=1;
		printf("Case #%d:\n",kase++);
		int ans=0;
		for(char type;n--;)
		{
			type=getchar();
			static char str0[5000001],str1[5000001];
			switch(type)
			{
				case'+':
				{
					scanf("%s",str0);
					int len=-1;while(str0[++len]);
					for(int i=0;i<len;i++)str1[i]=str0[(i+ans)%len];
					str1[len]='\0';
					BIT.AddString(str1);
				}break;
				case'?':
				{
					scanf("%s",str0);
					int len=-1;while(str0[++len]);
					for(int i=0;i<len;i++)str1[i]=str0[(i+ans)%len];
					str1[len]='\0';
					printf("%d\n",ans=BIT.Query(str1));
				}break;
				default:n++;break;
			}
		}
	}
	return 0;
}
