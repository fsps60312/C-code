#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
char S[100001],LINE[10001];
int N;
struct Trie
{
	vector<int>e[26];
	vector<vector<int> >v;
	vector<int>f;
	vector<int>tag;
	vector<int>cnt;
	void Clear()
	{
		for(int i=0;i<26;i++)e[i].clear();
		v.clear(),f.clear(),tag.clear(),cnt.clear();
		Push();
	}
	int Push()
	{
		int sz=v.size();
		for(int i=0;i<26;i++)e[i].push_back(0);
		v.push_back(vector<int>());
		f.push_back(0);
		tag.push_back(0);
		return sz;
	}
	int GetNxt(int c,int u)
	{
		if(e[c][u]==0)
		{
			int sz=Push();
			return e[c][u]=sz;
		}
		return e[c][u];
	}
	void Insert(char *s)
	{
		int u=0;
		for(int i=0;s[i];i++)u=GetNxt(s[i]-'a',u);
		v[u].push_back(cnt.size()),tag[u]=1;
		cnt.push_back(0);
	}
	void GetFail()
	{
		f[0]=0;
		queue<int>q;
		for(int i=0;i<26;i++)
		{
			int &u=e[i][0];
			if(u==0)continue;
			q.push(u);
			f[u]=0;
		}
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=0;i<26;i++)
			{
				int &o=e[i][u];
				if(o==0)continue;
				f[o]=f[u];
				while(f[o]&&e[i][f[o]]==0)f[o]=f[f[o]];
				f[o]=e[i][f[o]];
				tag[o]|=tag[f[o]];
				q.push(o);
			}
		}
//		for(int i=0;i<f.size();i++)printf("f[%d]=%d\n",i,f[i]);
	}
	void Match(char *s)
	{
		int u=0;
		for(int i=0;s[i];i++)
		{
			while(u&&e[s[i]-'a'][u]==0)u=f[u];
			u=e[s[i]-'a'][u];
//			printf("u=%d\n",u);
			for(int j=u;tag[j];j=f[j])
			{
//				printf("tag[%d]=%d\n",j,tag[j]);
				for(int k=0;k<v[j].size();k++)cnt[v[j][k]]++;
			}
		}
	}
	void printans()
	{
		for(int i=0;i<cnt.size();i++)printf("%d\n",cnt[i]);
	}
}TRIE;
int main()
{
	scanf("%s%d",S,&N);
	TRIE.Clear();
	for(int i=0;i<N;i++)
	{
		scanf("%s",LINE);
//		puts("a");
		TRIE.Insert(LINE);
//		puts("b");
	}
	TRIE.GetFail();
	TRIE.Match(S);
	TRIE.printans();
	return 0;
}
