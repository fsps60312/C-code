#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
using namespace std;
void getmax(int &a,int b){if(b>a)a=b;}
char LINE[81];
struct Command
{
	int type;//die,pass,ifgo,jump,loop
	int a,b;
	void scan(char *s)
	{
		int idx=0;
		for(;s[idx]==' ';idx++);
		switch(s[idx])
		{
			case'd':type=0;break;
			case'p':type=1;break;
			case'i':type=2;break;
			case'j':type=3;break;
			case'l':type=4;break;
			default:assert(0);
		}
		if(type<=1)return;
		for(;s[idx]!=' ';idx++);
		for(;s[idx]==' ';idx++);
		a=0;
		for(;s[idx]!=' ';idx++){assert(s[idx]>='0'&&s[idx]<='9');a=a*10+s[idx]-'0';}
		if(type<=3)return;
		for(;s[idx]==' ';idx++);
		b=0;
		for(;s[idx]!=' ';idx++){assert(s[idx]>='0'&&s[idx]<='9');b=b*10+s[idx]-'0';}
	}
}CMD[100000];
bool EmptyStr(char *s){for(;*s==' ';s++);return !*s;}
int N,JUMP[100000],COST[100000];
struct Edge
{
	int to,cost;
	Edge(){}
	Edge(int to,int cost):to(to),cost(cost){}
};
vector<vector<Edge> >AD;
map<int,int>IDX,RI;
vector<int>DP;
int GetIdx(int v)
{
	if(IDX.find(v)==IDX.end())
	{
		static int sz;sz=IDX.size();
		AD.push_back(vector<int>());
		DP.push_back(0);
		RI[sz]=v;
		return IDX[v]=sz;
	}
	return IDX[v];
}
int MaxCost(int u)
{
	if(u==IDX.size())return 0;
	if(DP[u])return DP[u];
	DP[u]=-1;
	int ans=0;
	for(int i=0;i<AD[u].size();i++)
	{
		Edge &e=AD[u][i];
		int v=MaxCost(e.to);
		if(v==-1)return -1;
		getmax(ans,v+e.cost);
	}
	return DP[u]=ans;
}
void BuildTree(int up,int down)
{
	AD.clear(),IDX.clear(),RI.clear(),DP.clear();
	for(int i=up;i<=down;)
	{
		int cost=0;
		int j=i;
		while(j<=down&&JUMP[j]!=j)cost+=COST[j],j=JUMP[j];
		if(j==i)cost++,j++;
		switch()
		i=j;
	}
}
void Solve()
{
	for(int i=0;i<N;i++)
	{
		if(CMD[i].type!=4)continue;
		int &a=CMD[i].a,&b=CMD[i].b;
		BuildTree(a,i-1);
		COST[a]*=b;
	}
	BuildTree(0,N-1);
}
int main()
{
	freopen("in.txt","r",stdin);
	while(gets(LINE))
	{
		for(N=0;gets(LINE)&&!EmptyStr(LINE);N++)
		{
			JUMP[i]=i;
//			puts(LINE);
			CMD[i].scan(LINE);
//			printf("type=%d a=%d b=%d\n",CMD[i].type,CMD[i].a,CMD[i].b);
		}
		Solve();
	}
	return 0;
}
