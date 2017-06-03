#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>
#include<cassert>
#include<set>
#define termin(x,...) {printf(x,##__VA_ARGS__);assert(0);}
using namespace std;
string null="";
int N,T,CNT[26];
char LINE[21];
vector<string>ANS;
struct Edge
{
	int to;
	string s;
	Edge(){}
	Edge(int to,string s):to(to),s(s){}
	bool operator<(Edge a)const{return s<a.s;}
};
set<Edge>TO[26];
void dfs(int u,int fa,string &s)
{
	if(fa!=-1)
	{
		ANS.push_back(s);
		CNT[fa]--,CNT[u]--,N--;
		if(!N)return;
	}
	for(set<Edge>::iterator it=TO[u].begin();it!=TO[u].end();it++)
	{
		string s=(*it).s;
		int to=(*it).to;
		if(N>1&&!TO[to].size())continue;
		TO[u].erase(*it);
		dfs(to,u,s);
		break;
	}
}
bool solve()
{
	int cnt=0;
	for(int i=0;i<26;i++)
	{
		if(CNT[i]&1)cnt++;
	}
	if(cnt>2)return false;
	if(cnt==0)
	{
		for(int i=0;i<26;i++)
		{
			if(CNT[i])
			{
				dfs(i,-1,null);
				return !N;
			}
		}
		termin("all zero\n");
	}
	for(int i=0;i<26;i++)
	{
		if(TO[i].size()*2==CNT[i]+1)
		{
			dfs(i,-1,null);
			return !N;
		}
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<26;i++)
		{
			TO[i].clear();
			CNT[i]=0;
		}
		for(int i=0,c1,c2;i<N;i++)
		{
			scanf("%s",LINE);
			c1=LINE[0]-'a',c2=-1;
			while(LINE[++c2]);c2=LINE[--c2]-'a';
			TO[c1].insert(Edge(c2,LINE));
			CNT[c1]++,CNT[c2]++;
		}
		ANS.clear();
		if(solve())
		{
		}
		else puts("***");
			for(int i=0,limit=ANS.size()-1;i<=limit;i++)
			{
				printf("%s%c",ANS[i].c_str(),i==limit?'\n':'.');
			}
	}
}
/*
1
10
aaba
bbaababbbabbab
a
ababbabbaaaa
babbbaaaabbaababb
baabbabb
babbbabaabaab
baababaaa
baaabbbabaababb
bbbabbaaaaabaab
*/
