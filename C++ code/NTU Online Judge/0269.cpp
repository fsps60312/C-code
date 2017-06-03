#include<cstdio>
#include<cassert>
#include<string>
#include<vector>
using namespace std;
void getmax(int &a,const int b){if(a<b)a=b;}
struct Trie
{
	struct Node
	{
		vector<string>S[26][26];
	};
	vector<Node>S;
	vector<int>CH[26];
	int SZ;
	void Expand()
	{
		S.push_back(Node());
		for(int i=0;i<26;i++)CH[i].push_back(0);
		++SZ;
	}
	void Clear()
	{
		S.clear();
		for(int i=0;i<26;i++)CH[i].clear();
		SZ=0;
		Expand();
	}
	int GetNxt(const int u,const int c)
	{
		if(CH[c][u])return CH[c][u];
		Expand();
		return CH[c][u]=SZ-1;
	}
	void Insert(const char *str)
	{
		int u=0,i;
		for(i=0;str[i];i++)u=GetNxt(u,str[i]-'a');
		S[u].S[str[0]-'a'][str[i-1]-'a'].push_back(str);
	}
	void Check(const int n,const char *str,int *ans)
	{
		int u=0;
		for(int i=0;i<n;i++)
		{
			const int c=str[i]-'a';
			if(!CH[u][c])return;
			u=CH[u][c];
			if(!S[u].S[str[0]-'a'][c].empty())ans[i]=u;
		}
	}
}TRIE;
char S[1001];
int N;
int ANS[1000][1000];
int DP[1000];
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%s",S);
		scanf("%d",&N);
		TRIE.Clear();
		for(int i=0;i<N;i++)
		{
			static char str[101];
			scanf("%s",str);
			TRIE.Insert(str);
		}
		for(int start=0;start<N;start++)
		{
			for(int i=start;i<N;i++)ANS[start][i]=-1;
			TRIE.Check(N-start,S+start,ANS[start]+start);
		}
		for(int i=0;i<N;i++)DP[i]=-1;
		for(int i=0;i<N;i++)getmax(DP[i],ANS[0][i]);
		for()
	}
	return 0;
}
