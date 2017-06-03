#include<cstdio>
#include<vector>
#include<string>
#include<algorithm>
#include<cassert>
#define termin(x,...) {printf(x,##__VA_ARGS__);assert(0);}
using namespace std;
string null=string("");
int N,T,CNT[26],OUT[26];
char LINE[21];
vector<string>ANS;
struct Edge
{
	int to;
	string s;
	Edge(){}
	Edge(int to,string s):to(to),s(s){}
	bool operator<(Edge a)const{return s>a.s;}
};
vector<Edge>TO[26];
void dfs(int u,int fa,string &s)
{
	if(fa!=-1)
	{
		ANS.push_back(s);
		CNT[fa]--,CNT[u]--,OUT[fa]--,N--;
		if(!N)return;
	}
	for(int i=(int)TO[u].size()-1;i>=0;i--)
	{
		Edge &e=TO[u][i];
		string s=e.s;
		int to=e.to;
		TO[u].pop_back();
		dfs(to,u,s);
		break;
	}
}
bool solve()
{
	int cnt=0;
	for(int i=0;i<26;i++)
	{
		sort(TO[i].begin(),TO[i].end());
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
		if((CNT[i]&1)&&OUT[i])
		{
			dfs(i,-1,null);
			return !N;
		}
	}
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<26;i++)
		{
			TO[i].clear();
			CNT[i]=0,OUT[i]=0;
		}
		for(int i=0,c1,c2;i<N;i++)
		{
			scanf("%s",LINE);
			c1=LINE[0]-'a',c2=-1;
			while(LINE[++c2]);c2=LINE[--c2]-'a';
			TO[c1].push_back(Edge(c2,LINE));
			CNT[c1]++,CNT[c2]++,OUT[c1]++;
		}
		ANS.clear();
		if(solve())
		{
			for(int i=0,limit=ANS.size()-1;i<=limit;i++)
			{
				printf("%s%c",ANS[i].c_str(),i==limit?'\n':'.');
			}
		}
		else puts("***");
	}
}
