#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<stack>
#include<queue>
using namespace std;
void massert(bool valid){if(valid)return;while(1)printf("E");}
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
			case'D':
			case'd':type=0;break;
			case'P':
			case'p':type=1;break;
			case'I':
			case'i':type=2;break;
			case'J':
			case'j':type=3;break;
			case'L':
			case'l':type=4;break;
			default:
			{
				massert(0);
			}
		}
		if(type<=1)return;
		for(;!(s[idx]==' '||s[idx]=='\t');idx++);
		for(;s[idx]==' '||s[idx]=='\t';idx++);
		a=0;
		for(;s[idx]&&!(s[idx]==' '||s[idx]=='\t');idx++){assert(s[idx]>='0'&&s[idx]<='9');a=a*10+s[idx]-'0';}
		if(type<=3)return;
		for(;s[idx]==' '||s[idx]=='\t';idx++);
		b=0;
		for(;s[idx]&&!(s[idx]==' '||s[idx]=='\t');idx++){assert(s[idx]>='0'&&s[idx]<='9');b=b*10+s[idx]-'0';}
	}
}CMD[100001];
bool EmptyStr(char *s){for(;*s==' '||*s=='\t';s++);return !*s;}
int N,LOOP[100001],DP[100001];
bool VIS[100001];
int max(int a,int b){return a>b?a:b;}
int Dfs(int u)
{
//	printf("u=%d\n",u);
	assert(u>=1&&u<=N+1);
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
		assert(CMD[l].type==4);
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
		case 4:ans=1;break;
		default:assert(0);
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
//			puts(LINE);
			CMD[N].scan(LINE);
//			printf("i=%d: type=%d a=%d b=%d\n",N,CMD[N].type,CMD[N].a,CMD[N].b);
			LOOP[N]=N;
			if(CMD[N].type==4)
			{
				int &a=CMD[N].a;
				assert(a<N);
				LOOP[a]=N;
			}
		}while(gets(LINE)&&!EmptyStr(LINE));
		for(int i=1;i<=N;i++)
		{
			switch(CMD[i].type)
			{//die,pass,ifgo,jump,loop
				case 0:break;
				case 1:break;
				case 2:assert(CMD[i].a>=1&&CMD[i].a<=N);break;
				case 3:assert(CMD[i].a>=1&&CMD[i].a<=N);break;
				case 4:assert(CMD[i].a>=1&&CMD[i].a<=N);break;
				default:assert(0);
			}
		}
//		printf("N=%d\n",N);
		int ans=Dfs(1);
		if(ans==-1)printf("infinity\n");
		else printf("%d\n",ans);
	}
	return 0;
}
//2 3 5 4 5 2 3 5 4 5...
