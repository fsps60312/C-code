#include<cstdio>
#include<map>
#include<string>
#include<vector>
using namespace std;
struct Trie
{
	vector<map<string,int> >ch;
	void clear(){ch.clear();ch.push_back(map<string,int>());}
	int GetNxt(const int u,const string &s)
	{
		auto it=ch[u].find(s);
		if(it!=ch[u].end())return it->second;
		const int sz=ch.size();
		ch.push_back(map<string,int>());
		return ch[u][s]=sz;
	}
	void Insert(char *tmp)
	{
		int len=-1;while(tmp[++len])if(tmp[len]=='\\')tmp[len]='\0';
		int u=0;
		string str;
		for(int i=0;i<=len;i++)
		{
			if(tmp[i])str.push_back(tmp[i]);
			else u=GetNxt(u,str),str.clear();
		}
	}
	void Print(const int u,const int dep)const
	{
		for(const auto &it:ch[u])
		{
			for(int i=0;i<dep;i++)putchar(' ');
			printf("%s\n",it.first.c_str());
			Print(it.second,dep+1);
		}
	}
}TRIE;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		TRIE.clear();
		for(int i=0;i<N;i++)
		{
			static char tmp[81];scanf("%s",tmp);
			TRIE.Insert(tmp);
		}
		TRIE.Print(0,0);
		puts("");
	}
	return 0;
}
