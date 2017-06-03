#include<cstdio>
#include<vector>
#include<queue>
#include<map>
using namespace std;
const int MAXN=4000000;
char S[100001],LINE[100001];
int N;
struct Trie
{
	vector<map<int,int> >e;
	vector<vector<int> >v;
	vector<int>f;
	vector<int>tag;
	vector<int>cnt;
	vector<int>ans;
	void Clear()
	{
		e.clear();
		v.clear(),f.clear(),tag.clear(),cnt.clear(),ans.clear();
		e.reserve(MAXN);
		v.reserve(MAXN),f.reserve(MAXN),tag.reserve(MAXN),cnt.reserve(MAXN),ans.reserve(MAXN);
		Push();
	}
	int Push()
	{
		static int sz;sz=v.size();
		e.push_back(map<int,int>());
		v.push_back(vector<int>());
		f.push_back(0);
		tag.push_back(0);
		cnt.push_back(0);
		return sz;
	}
	int GetNxt(int c,int u)
	{
		if(e[u].find(c)==e[u].end())
		{
			static int sz;sz=Push();
			return e[u][c]=sz;
		}
		return e[u][c];
	}
	void Insert(char *s)
	{
		int u=0;
		for(int i=0;s[i];i++)u=GetNxt(s[i]-'a',u);
		v[u].push_back(ans.size()),tag[u]=1;
		ans.push_back(0);
	}
	void GetFail(vector<int>&s)
	{
		f[0]=0;
		static queue<int>q;
		s.clear();
		s.push_back(0);
		for(auto i:e[0])
		{
			int &u=i.second;
			q.push(u);
			s.push_back(u);
			f[u]=0;
		}
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(auto i:e[u])
			{
				int &o=i.second;
				int &ff=f[o]=f[u];
				while(ff&&e[ff].find(i.first)==e[ff].end())ff=f[ff];
				ff=(e[ff].find(i.first)==e[ff].end()?0:e[ff][i.first]);
				tag[o]|=tag[ff];
				q.push(o);
				s.push_back(o);
			}
		}
	}
	void Match(char *s)
	{
		int u=0;
		for(int i=0,c;s[i];i++)
		{
			c=s[i]-'a';
			while(u&&e[u].find(c)==e[u].end())u=f[u];
			u=(e[u].find(c)==e[u].end()?0:e[u][c]);
			cnt[u]++;
		}
	}
	void printans(const vector<int>&s)
	{
		for(int _i=s.size()-1;_i>=0;_i--)
		{
			const int &i=s[_i];
			if(tag[i])
			{
				cnt[f[i]]+=cnt[i];
				static int k;
				for(k=0;k<v[i].size();k++)ans[v[i][k]]+=cnt[i];
			}
		}
		for(int i=0;i<ans.size();i++)printf("%d\n",ans[i]);
	}
}TRIE;
int main()
{
//	freopen("in.txt","r",stdin);
	static vector<int>s;
	s.reserve(MAXN);
	while(scanf("%s%d",S,&N)==2)
	{
		TRIE.Clear();
		for(int i=0;i<N;i++)
		{
			scanf("%s",LINE);
			TRIE.Insert(LINE);
		}
		TRIE.GetFail(s);
		TRIE.Match(S);
		TRIE.printans(s);
	}
	return 0;
}
