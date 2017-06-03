#include<cstdio>
#include<vector>
#include<map>
#include<stack>
#include<queue>
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
		for(;s[idx]==' '||s[idx]=='\t';idx++);//there are tabs!
		switch(s[idx])
		{
			case'd':type=0;break;
			case'p':type=1;break;
			case'i':type=2;break;
			case'j':type=3;break;
			default:type=4;break;
		}
		if(type<=1)return;
		for(;!(s[idx]==' '||s[idx]=='\t');idx++);
		for(;s[idx]==' '||s[idx]=='\t';idx++);
		a=0;
		for(;s[idx]&&!(s[idx]==' '||s[idx]=='\t');idx++)a=a*10+s[idx]-'0';
		if(type<=3)return;
		for(;s[idx]==' '||s[idx]=='\t';idx++);
		b=0;
		for(;s[idx]&&!(s[idx]==' '||s[idx]=='\t');idx++)b=b*10+s[idx]-'0';
	}
}CMD[100001];
bool EmptyStr(char *s){for(;*s==' '||*s=='\t';s++);return !*s;}
int N,LOOP[100001],DP[100001];
bool VIS[100001];
int max(int a,int b){return a>b?a:b;}
int Dfs(int u)
{
	if(u==N+1)return -1;
	if(DP[u]!=-1)return DP[u];
	if(VIS[u])return -1;
	VIS[u]=true;
	if(LOOP[u]!=u)
	{
		int l=LOOP[u];
		LOOP[u]=u,VIS[u]=false;
		int v1=Dfs(u);
		if(v1==-1)return -1;
		v1*=CMD[l].b;
		int v2=Dfs(l+1);
		if(v2==-1)return -1;
		LOOP[u]=l,VIS[u]=false;
		return v1+v2;
	}
	int ans;
	switch(CMD[u].type)
	{//die,pass,ifgo,jump,loop
		case 0:ans=1;break;
		case 1:
		{
			int v=Dfs(u+1);
			if(v==-1)return -1;
			ans=1+v;
		}break;
		case 2:
		{
			int v1=Dfs(u+1);
			if(v1==-1)return -1;
			int v2=Dfs(CMD[u].a);
			if(v2==-1)return -1;
			ans=1+max(v1,v2);
		}break;
		case 3:
		{
			int v=Dfs(CMD[u].a);
			if(v==-1)return -1;
			ans=1+v;
		}break;
		default:ans=1;break;
	}
	VIS[u]=false;
	return DP[u]=ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(gets(LINE)&&!EmptyStr(LINE))
	{
		N=0;
		do
		{
			N++;
			VIS[N]=false;
			DP[N]=-1;
			CMD[N].scan(LINE);
			LOOP[N]=N;
			if(CMD[N].type==4)LOOP[CMD[N].a]=N;
		}while(gets(LINE)&&!EmptyStr(LINE));
		int ans=Dfs(1);
		if(ans==-1)printf("infinity\n");
		else printf("%d\n",ans);
	}
	return 0;
}
