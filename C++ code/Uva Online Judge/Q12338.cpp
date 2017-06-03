#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
int T,N,Q;
struct Trie
{
	vector<int>ch[26];
	int sz;
	void clear(){for(int i=0;i<26;i++)ch[i].clear();sz=0;Expand();}
	void Expand(){for(int i=0;i<26;i++)ch[i].push_back(0);sz++;}
	int GetNxt(const int u,const int c)
	{
		if(ch[c][u]!=0)return ch[c][u];
		Expand();
		return ch[c][u]=sz-1;
	}
	int Insert(char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)assert(str[i]>='a'&&str[i]<='z'),u=GetNxt(u,str[i]-'a');
		return u;
	}
	vector<vector<int> >father;
	vector<int>depth;
	void BuildFa(const int u,const int fa,const int dep)
	{
		if(!u)return;
		depth[u]=dep;
		father[u].clear();
		father[u].push_back(fa);
		for(int i=0,now=fa;i<(int)father[now].size();i++)father[u].push_back(now=father[now][i]);
		for(int i=0;i<26;i++)BuildFa(ch[i][u],u,dep+1);
	}
	void BuildFa()
	{
		father.resize(sz);
		depth.resize(sz);
		father[0].clear(),depth[0]=0;
		for(int i=0;i<26;i++)BuildFa(ch[i][0],0,1);
	}
	int GetDepOfLCA(int a,int b)
	{
		if(depth[a]<depth[b])swap(a,b);
		for(int i=30,s=depth[a]-depth[b];i>=0;i--)if(s&(1<<i))a=father[a][i];
		assert(depth[a]==depth[b]);
		if(a==b)return depth[a];
		for(int i=30;i>=0;i--)if(i<(int)father[a].size()&&i<(int)father[b].size()&&father[a][i]!=father[b][i])a=father[a][i],b=father[b][i];
		assert(a!=b);
		assert(depth[a]==depth[b]);
		assert(depth[a]>0);
		return depth[a]-1;
	}
}TRIE;
vector<int>LEAF;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		TRIE.clear(),LEAF.clear();
		for(int i=0;i<N;i++)
		{
			static char tmp[10001];
			scanf("%s",tmp);
			LEAF.push_back(TRIE.Insert(tmp));
		}
		TRIE.BuildFa();
		static int kase=1;
		printf("Case %d:\n",kase++);
		scanf("%d",&Q);
		while(Q--)
		{
			static int a,b;scanf("%d%d",&a,&b);
			printf("%d\n",TRIE.GetDepOfLCA(LEAF[--a],LEAF[--b]));
		}
	}
	return 0;
}
