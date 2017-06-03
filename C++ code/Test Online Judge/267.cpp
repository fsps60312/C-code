#include<cstdio>
#include<cassert>
#include<map>
#include<vector>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
struct Trie
{
	vector<map<char,int> >CH;
	vector<int>SZ;
	void clear(){CH.clear(),SZ.clear();Expand();}
	void Expand(){CH.push_back(map<char,int>()),SZ.push_back(0);}
	int GetNxt(const int u,const char c)
	{
		const auto it=CH[u].find(c);
		if(it==CH[u].end())
		{
			const int sz=CH.size();
			Expand();
			return CH[u][c]=sz;
		}
		else return it->second;
	}
	void Insert(char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)SZ[u]++,u=GetNxt(u,str[i]);
		SZ[u]++;
	}
	int Query(char *str)
	{
		int ans=0,u=0;
		for(int i=0;str[i];i++)
		{
			u=CH[u][str[i]];
			ans++;
			if(SZ[u]==1)return ans;
		}
		return ans;
	}
}TRIE;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcase;scanf(1,"%d",&testcase);
	while(testcase--)
	{
		scanf(1,"%d",&N);
		TRIE.clear();
		int ans=0;
		for(int i=0;i<N;i++)
		{
			static char tmp[1000001];
			scanf(1,"%s",tmp);
			TRIE.Insert(tmp);
			ans+=TRIE.Query(tmp);
		}
		static int kase=1;
		printf("Case #%d: %d\n",kase++,ans);
	}
	scanf(-1,"%d",&testcase);
	return 0;
}
