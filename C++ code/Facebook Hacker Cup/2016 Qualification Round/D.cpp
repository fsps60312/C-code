#include<cstdio>
#include<cassert>
#include<map>
#include<vector>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
struct Edge
{
	int nxt,cost;
	Edge(){}
	Edge(const int _n,const int _c):nxt(_n),cost(_c){}
};
vector<vector<Edge> >ET;
vector<int>WORD;
int NewVertex()
{
	const int ans=ET.size();
	ET.push_back(vector<Edge>());
	WORD.push_back(0);
	return ans;
}
struct Trie
{
	vector<map<char,int> >CH;
	vector<int>CNT;
	void clear(){CH.clear(),CNT.clear();Expand();}
	void Expand(){CH.push_back(map<char,int>()),CNT.push_back(0);}
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
		for(int i=0;str[i];i++)u=GetNxt(u,str[i]);
		CNT[u]++;
	}
	void BuildGraph(const int u,const int gu,const int cost)
	{
		assert(gu<(int)ET.size());
		if((int)CH[u].size()==0)
		{
			const int now=NewVertex();
			ET[gu].push_back(Edge(now,cost));
			WORD[now]+=CNT[u];
		}
		else if((int)CH[u].size()==1&&CNT[u]==0)BuildGraph(CH[u].begin()->second,gu,cost+1);
		else
		{
			const int now=NewVertex();
			ET[gu].push_back(Edge(now,cost));
			WORD[now]+=CNT[u];
			for(const auto &it:CH[u])BuildGraph(it.second,now,1);
		}
	}
}TRIE;
int N,K;
int main()
{
	freopen("in.txt","r",stdin);
	int testcase;scanf(1,"%d",&testcase);
	while(testcase--)
	{
		scanf(2,"%d%d",&N,&K);
		TRIE.clear();
		for(int i=0;i<N;i++)
		{
			static char tmp[100001];scanf(1,"%s",tmp);
			TRIE.Insert(tmp);
		}
		ET.clear(),WORD.clear();
		TRIE.BuildGraph(0,NewVertex(),0);
		for(int u=0;u<(int)ET.size();u++)
		{
			printf("u=%d,word=%d\n",u,WORD[u]);
			for(const Edge &e:ET[u])printf("(%d,%d)\n",e.nxt,e.cost);
		}
	}
	scanf(-1,"%d",&testcase);
	return 0;
}
