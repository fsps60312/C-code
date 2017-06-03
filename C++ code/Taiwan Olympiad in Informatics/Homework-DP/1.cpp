#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
struct Box
{
	int a,b,c;
	Box(){}
	Box(int _a,int _b,int _c)
	{
		int s[3]={_a,_b,_c};
		sort(s,s+3);
		a=s[0],b=s[1],c=s[2];
	}
	bool operator<(const Box &o)const
	{
		if(a!=o.a)return a<o.a;
		if(b!=o.b)return b<o.b;
		if(c!=o.c)return c<o.c;
		return false;
	}
	bool operator>(const Box &o)const{return a>o.a&&b>o.b&&c>o.c;}
}S[1001];
int DP[1001];
void getmax(int &a,const int b){if(b>a)a=b;}
int N;
int main()
{
	scanf("%d",&N);
	S[0].a=S[0].b=S[0].c;
	for(int i=1,a,b,c;i<=N;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		S[i]=Box(a,b,c);
	}
	sort(S+1,S+N+1);
	DP[0]=0;
	int ans=0;
	for(int i=1;i<=N;i++)
	{
//		printf("(%d,%d,%d)\n",S[i].a,S[i].b,S[i].c);
		DP[i]=0;
		for(int j=0;j<i;j++)
		{
			if(S[i]>S[j])getmax(DP[i],DP[j]+1);
		}
		getmax(ans,DP[i]);
	}
	printf("%d\n",ans);
}
