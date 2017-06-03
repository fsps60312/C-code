#include<cstdio>
#include<cassert>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
const int INF=2147483647;
struct Trie
{
	vector<int>CH[4],CHSZ,END;
	int SZ;
	void Clear()
	{
		for(int i=0;i<4;i++)CH[i].clear();
		CHSZ.clear(),END.clear();
		SZ=0;
		Expand();
	}
	void Expand()
	{
		for(int i=0;i<4;i++)CH[i].push_back(0);
		CHSZ.push_back(0);
		END.push_back(0);
		++SZ;
	}
	int Id(const char c)const
	{
		switch(c)
		{
			case'A':return 0;
			case'G':return 1;
			case'C':return 2;
			case'U':return 3;
			default:assert(0);return -1;
		}
	}
	int GetNxt(const int u,const int c)
	{
		if(CH[c][u])return CH[c][u];
		Expand();
		return CH[c][u]=SZ-1;
	}
	int Insert(const char *str)
	{
		int u=0;
		for(int i=0;str[i];i++)
		{
			++CHSZ[u];
			u=GetNxt(u,Id(str[i]));
		}
		++CHSZ[u],++END[u];
		return u;
	}
	int GetLoc(const char *str)const
	{
		int u=0;
		for(int i=0;str[i];i++)
		{
			const int c=Id(str[i]);
			if(!(u=CH[c][u]))return -1;
		}
		return u;
	}
	vector<int>LEFT,RIGT;
	void Dfs(const int u,int &tick)
	{
		LEFT[u]=tick;
		for(int i=0;i<4;i++)if(CH[i][u])Dfs(CH[i][u],tick);
		RIGT[u]=tick++;
	}
	void Build()
	{
		LEFT.resize(SZ),RIGT.resize(SZ);
		int tick=0;
		Dfs(0,tick);
		assert(tick==SZ);
	}
	char rId(const int i)const
	{
		static char data[4]={'A','G','C','U'};
		return data[i];
	}
	void DfsOutput(const int u,string &now,vector<string>&ans)const
	{
		for(int i=0;i<END[u];i++)ans.push_back(now);
		for(int i=0;i<4;i++)if(CH[i][u])
		{
			now.push_back(rId(i));
			DfsOutput(CH[i][u],now,ans);
			now.pop_back();
		}
	}
	void SortStrings(vector<string>&s)const
	{
		multimap<int,string>ans;
		for(int i=0;i<(int)s.size();i++)
		{
			ans.insert(make_pair(RIGT[]))
		}
		ans.clear();
	}
};
struct QueryType
{
	string qs;
	int loc,*ans;
	QueryType(){}
	QueryType(const string &_qs,const int _loc,int *_ans):qs(_qs),loc(_loc),ans(_ans){}
};
bool operator<(const QueryType &a,const QueryType &b){return a.loc<b.loc;}
int N,M;
int ANS[100000*2];
vector<string>S,P,Q;
Trie TRIE;
vector<QueryType>QUERY;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		S.clear();
		TRIE.Clear();
		for(int i=0;i<N;i++)
		{
			static char str[100001];
			scanf("%s",str);
			S.push_back(str);
			TRIE.Insert(str);
		}
		TRIE.SortStrings(S);
		for(const string s:S)puts(s.c_str());
		TRIE.Build();
		P.clear(),Q.clear();
		QUERY.clear();
		for(int i=0;i<M;i++)
		{
			static char pstr[100001],qstr[100001];
			scanf("%s%s",pstr,qstr);
			P.push_back(pstr),Q.push_back(qstr);
			const int loc=TRIE.GetLoc(pstr);
			if(loc!=-1)
			{
				QUERY.push_back(QueryType(qstr,TRIE.LEFT[loc]-1,&ANS[i*2]));
				QUERY.push_back(QueryType(qstr,TRIE.RIGT[loc],&ANS[i*2+1]));
			}
		}
		for(int i=0;i<M*2;i++)ANS[i]=0;
		sort(QUERY.begin(),QUERY.end());
		reverse(QUERY.begin(),QUERY.end());
		while(QUERY.back().loc==-1)QUERY.pop_back();
		reverse(QUERY.begin(),QUERY.end());
		assert((int)S.size()==N);
		static Trie suf;
		suf.Clear();
		for(int i=0,j=0,pre_u=0;;i++)
		{
			const int u=(i<N?TRIE.GetLoc(S[i].c_str()):INF);
			assert(pre_u<=u);
			pre_u=u;
			for(;j<(int)QUERY.size()&&QUERY[j].loc<u;j++)
			{
				const int loc=suf.GetLoc(QUERY[j].qs.c_str());
				if(loc!=-1)*QUERY[j].ans+=suf.CHSZ[loc];
			}
			if(i==N)break;
			reverse(S[i].begin(),S[i].end());
			suf.Insert(S[i].c_str());
		}
		for(int i=0;i<M;i++)printf("%d-%d\n",ANS[i*2+1],ANS[i*2]);
	}
	return 0;
}
