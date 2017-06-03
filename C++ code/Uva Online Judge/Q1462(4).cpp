#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
struct Trie
{
	vector<int>ch[26],flow;
	vector<int>tag,vis;
	int kase;
	int sz;
	void clear()
	{
		for(int i=0;i<26;i++)ch[i].clear();
		flow.clear(),tag.clear(),vis.clear();
		kase=0;
		Expand();
		sz=1;
	}
	void Expand(){for(int i=0;i<26;i++)ch[i].push_back(0);flow.push_back(0),tag.push_back(0),vis.push_back(0);}
	int GetNxt(const int u,const int c)
	{
		if(ch[c][u])return ch[c][u];
		Expand();
		return ch[c][u]=sz++;
	}
	void Insert(char *str)
	{
		assert(kase==0);
		int u=0;
		for(int i=0;str[i];i++)flow[u]++,u=GetNxt(u,str[i]-'a');
		flow[u]++;
	}
	int GetCnt(const char *c,const int edth)
	{
		kase++;
		Dfs(0,c,edth);
		return GetCnt(0);
	}
	int GetCnt(const int u)
	{
		if(vis[u]!=kase)return 0;
		if(tag[u]==kase)return flow[u];
		int ans=0;
		for(int i=0;i<26;i++)if(ch[i][u])ans+=GetCnt(ch[i][u]);
		return ans;
	}
	void Dfs(const int u,const char *c,const int edth)
	{
		if(tag[u]==kase)return;
		vis[u]=kase;
		if((*c)=='\0')
		{
			tag[u]=kase;
			return;
		}
		assert((*c)>='a'&&(*c)<='z');
		if(ch[(*c)-'a'][u])Dfs(ch[(*c)-'a'][u],c+1,edth);
		if(!edth)return;
		Dfs(u,c+1,edth-1);//delete a alphabet
		for(int i=0;i<26;i++)if(ch[i][u])
		{
			Dfs(ch[i][u],c+1,edth-1);//change a alphabet
			Dfs(ch[i][u],c,edth-1);//add a alphabet
		}
	}
}TRIE;
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		TRIE.clear();
		for(int i=0;i<N;i++)
		{
			static char str[11];scanf("%s",str);
			TRIE.Insert(str);
		}
		scanf("%d",&M);
		while(M--)
		{
			static char str[11];
			static int edth;
			scanf("%s%d",str,&edth);
			printf("%d\n",TRIE.GetCnt(str,edth));
		}
	}
	return 0;
}
