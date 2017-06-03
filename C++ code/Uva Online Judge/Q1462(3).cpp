#include<cstdio>
#include<vector>
#include<cassert>
#include<string>
using namespace std;
struct Trie
{
	vector<int>ch[26],flow;
	vector<string>tmp;
	int sz;
	void clear()
	{
		for(int i=0;i<26;i++)ch[i].clear();
		flow.clear();
		Expand();
		sz=1;
		tmp.clear(),tmp.push_back(string(""));
	}
	void Expand(){for(int i=0;i<26;i++)ch[i].push_back(0);flow.push_back(0);tmp.push_back("-1");}
	int GetNxt(const int u,const int c)
	{
		if(ch[c][u])return ch[c][u];
		Expand();
		return ch[c][u]=sz++;
	}
	void Insert(char *str)
	{
		int u=0;
		string s;
		for(int i=0;str[i];i++)flow[u]++,u=GetNxt(u,str[i]-'a'),s.push_back(str[i]),tmp[u]=s;
		flow[u]++;
	}
	vector<bool>vis;
	int GetCnt(const char *c,const int edth)
	{
		vis.resize(flow.size());
		for(int i=0;i<vis.size();i++)vis[i]=false;
		Dfs(0,c,edth);
		return GetCnt(0);
	}
	int GetCnt(const int u)
	{
		if(vis[u])return flow[u];
		int ans=0;
		for(int i=0;i<26;i++)if(ch[i][u])ans+=GetCnt(ch[i][u]);
		return ans;
	}
	void Dfs(const int u,const char *c,const int edth)
	{
		if(vis[u])return;
		if((*c)=='\0')
		{
			printf("reach(%s)\n",tmp[u].c_str());
			vis[u]=true;
			return;
		}
		assert((*c)>='a'&&(*c)<='z');
		if(ch[(*c)-'a'][u])Dfs(ch[(*c)-'a'][u],c+1,edth);
		if(!edth)return;
		if((*(c+1))!=(*c))Dfs(u,c+1,edth-1);//delete a alphabet
		for(int i=0;i<26;i++)if(ch[i][u]&&'a'+i!=(*c))
		{
			Dfs(ch[i][u],c+1,edth-1);//change a alphabet
			Dfs(ch[i][u],c,edth-1);//add a alphabet
		}
	}
}TRIE;
int N,M;
int main()
{
	freopen("in.txt","r",stdin);
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
