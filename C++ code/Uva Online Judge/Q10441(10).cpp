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
void dfs(int u)
{
	set<Edge>::iterator it;
	string s;
	int to;
	while(TO[u].size())
	{
		it=TO[u].begin();
		s=(*it).s;
		to=(*it).to;
		TO[u].erase(*it);
		dfs(to);
		ANS.push_back(s);
		N--;
	}
}
bool solve()
{
	int cnt=0;
	for(int i=0;i<26;i++)
	{
		if(CNT[i]&1)if(++cnt>2)return false;
		if(abs((int)TO[i].size()*2-CNT[i])>1)return false;
	}
	if(cnt==0)
	{
		for(int i=0;i<26;i++)
		{
			if(CNT[i])
			{
				dfs(i);
				return !N;
			}
		}
		termin("all zero\n");
	}
	for(int i=0;i<26;i++)
	{
		if(TO[i].size()*2==CNT[i]+1)
		{
			dfs(i);
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
			for(int i=ANS.size()-1;i>=0;i--)
			{
				printf("%s%c",ANS[i].c_str(),i?'.':'\n');
			}
		}
		else puts("***");
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
