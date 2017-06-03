#include<cstdio>
#include<vector>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Trie
{
	vector<map<char,int> >CH;
	vector<int>LEN;
	void clear(){CH.clear(),LEN.clear();Expand();}
	void Expand(){CH.push_back(map<char,int>()),LEN.push_back(0);}
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
	void Insert(char *s)
	{
		int u=0,i=0;
		for(;s[i];i++)u=GetNxt(u,s[i]);
		LEN[u]=i;
	}
	vector<int>FAIL;
	void GetFail()
	{
		FAIL.clear(),FAIL.resize(CH.size(),0);
		queue<int>q;
		for(const auto &it:CH[0])q.push(it.second);
		while(!q.empty())
		{
			const int u=q.front();q.pop();
			for(const auto &it:CH[u])
			{
				const int nxt=it.second;
				int f=FAIL[u];
				while(f&&CH[f].find(it.first)==CH[f].end())f=FAIL[f];
				const auto result=CH[f].find(it.first);
				FAIL[nxt]=(result==CH[f].end()?0:result->second);
				getmax(LEN[nxt],LEN[FAIL[nxt]]);
				q.push(nxt);
			}
		}
	}
	struct Segment
	{
		int l,r;
		Segment(){}
		Segment(const int _l,const int _r):l(_l),r(_r){}
		bool operator<(const Segment &s)const{return l<s.l;}
	};
	int Solve(const char *str)
	{
		vector<Segment>segs;
		int u=0;
		for(int i=0;str[i];i++)
		{
			auto it=CH[u].find(str[i]);
			while(u&&it==CH[u].end())it=CH[u=FAIL[u]].find(str[i]);
			if(it!=CH[u].end())
			{
				u=it->second;
				if(LEN[u])segs.push_back(Segment(i-LEN[u]+1,i+1));
			}
		}
		sort(segs.begin(),segs.end());
		int ans=0,cur=0;
		for(Segment &seg:segs)
		{
			if(cur<seg.l)cur=seg.l;
			if(cur<seg.r)ans+=seg.r-cur,cur=seg.r;
		}
		return ans;
	}
}TRIE;
int N;
char S[300001];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%s",&N,S)==2)
	{
		TRIE.clear();
		if(true)
		{
			int m;
			char *tmp=new char[5001];
			scanf("%d",&m);
			while(m--)scanf("%s",tmp),TRIE.Insert(tmp);
			delete[]tmp;
		}
		TRIE.GetFail();
		printf("%d\n",N-TRIE.Solve(S));
		break;
	}
	return 0;
}
