#include<cstdio>
#include<cassert>
#include<vector>
#include<string>
#include<set>
#include<map>
#include<algorithm>
using namespace std;
const int INF=2147483647;
struct Trie
{
	vector<int>CH[26],COUNT;
	vector<set<string> >NAMES;
	int SZ;
	void Clear()
	{
		for(int i=0;i<26;i++)CH[i].clear();
		COUNT.clear(),NAMES.clear(),SZ=0;
		Expand();
	}
	void Expand()
	{
		for(int i=0;i<26;i++)CH[i].push_back(0);
		COUNT.push_back(0),NAMES.push_back(set<string>());
		SZ++;
	}
	int GetNxt(const int u,const int c)
	{
		if(CH[c][u])return CH[c][u];
		Expand();return CH[c][u]=SZ-1;
	}
	void Insert(const char *str,string name)
	{
		int u=0;
		for(int i=0;str[i];i++)u=GetNxt(u,str[i]-'a');
		COUNT[u]++,NAMES[u].insert(name);
	}
	vector<pair<int,string> >ANS;
	void Dfs(const int u,string &now,const int n)
	{
		if((int)NAMES[u].size()==n)
		{
			ANS.push_back(make_pair(-COUNT[u],now));
		}
		for(int i=0;i<26;i++)if(CH[i][u])
		{
			now.push_back('a'+i);
			Dfs(CH[i][u],now,n);
			now.pop_back();
		}
	}
	void PrintAnswers(const int n)
	{
		ANS.clear();
		string now="";
		Dfs(0,now,n);
		if(ANS.empty())puts("ALL CLEAR");
		else
		{
			sort(ANS.begin(),ANS.end());
			for(const auto &p:ANS)puts(p.second.c_str());
		}
		
	}
}TRIE;
char S[2000003];
int N;
bool IsChar(const char a){return a!=' '&&a!='\n';}
void Read(char *a,char *b)
{
	while(!IsChar(*a))a++;
	while(IsChar(*a))*(b++)=*(a++);
	*b='\0';
}
int main()
{
//	freopen("in.txt","r",stdin);
	fgets(S,INF,stdin);
	sscanf(S,"%d",&N);
	set<string>all_names;
	TRIE.Clear();
	for(int i=0;i<N;i++)
	{
		fgets(S,INF,stdin);
		static char name[21];
//		sscanf(S,"%s",name);
		Read(S,name);
		all_names.insert(name);
		for(int j=0;S[j]!='\n'&&S[j];j++)if(S[j]==' ')
		{
			static char word[2000001];
//			sscanf(S+j,"%s",word);
			Read(S+j,word);
			TRIE.Insert(word,name);
		}
	}
	TRIE.PrintAnswers(all_names.size());
	return 0;
}
