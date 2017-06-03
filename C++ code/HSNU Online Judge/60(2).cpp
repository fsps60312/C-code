#include<cstdio>
#include<algorithm>
#include<cassert>
using namespace std;
unsigned long long MX[64],MN[64];
long long N;
int ANS[64];
bool Dfs(const bool &posi,const unsigned long long &n,const int &dep)
{
//	printf("%d:(%d,%llu)(%llu,%llu)\n",dep,posi,n,MN[dep],MX[dep]);
	if(dep==-1)return n==0LLU;
	if(posi){if(n>MX[dep])return false;}
	else{if(n>MN[dep])return false;}
	ANS[dep]=0;
	if(Dfs(posi,n,dep-1))return true;
	ANS[dep]=1;
	bool tposi=((dep&1)==0);
	if(tposi!=posi)return Dfs(posi,n+(1LLU<<dep),dep-1);
	else
	{
		if(n==(1LLU<<dep))return Dfs(true,0LLU,dep-1);
		else if(n>(1LLU<<dep))return Dfs(posi,n-(1LLU<<dep),dep-1);
		else return Dfs(posi^true,(1LLU<<dep)-n,dep-1);
	}
}
void Verify()
{
	long long now=1LL,ans=0LL;
	for(int i=0;i<64;i++,now*=-2LL)
	{
		if(ANS[i]==1)ans+=now;
	}
	assert(ans==N);
}
int main()
{
//	freopen("out.txt","w",stdout);
//	for(int i=-1000000;i<=1000000;i++)printf("%d\n",i);return 0;
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	MX[0]=1LLU,MN[0]=0LLU;
	for(int i=1;i<64;i++)
	{
		MX[i]=MX[i-1],MN[i]=MN[i-1];
		if(i&1)MN[i]+=1LLU<<i;
		else MX[i]+=1LLU<<i;
	}
//	for(int i=0;i<64;i++)printf("(%llu,%llu)\n",MN[i],MX[i]);
	while(scanf("%lld",&N)==1)
	{
		assert(Dfs(N>=0,N>=0?N:-N,63));
		bool print1=false;
		for(int i=63;i>=0;i--)
		{
			if(ANS[i]==1){printf("1");print1=true;}
			else if(ANS[i]==0){if(print1)printf("0");}
			else assert(0);
		}
		if(!print1)puts("0");
		else puts("");
		Verify();
	}
	return 0;
}
