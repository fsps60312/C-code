#include<cstdio>
#include<cassert>
using namespace std;
int N,MOD;
int DP[1000000][3],H[1000000];
int main()
{
	scanf("%d%d",&N,&MOD);
	for(int i=0;i<N;i++)for(int h=0;h<3;h++)DP[i][h]=0;
	for(int h=0;h<3;h++)DP[N-1][h]=1;
	for(int i=N-2;i>=0;i--)
	{
		for(int h=0;h<3;h++)
		{
			int &dp=DP[i][h];
			if(h>0)(dp+=DP[i+1][h-1])%=MOD;
			if(h+1<3)(dp+=DP[i+1][h+1])%=MOD;
		}
	}
	static char s[1000001];
	scanf("%s",s);
	int hmx=-3,hmn=3;
	for(int i=0,h=0;i<N;i++)
	{
		if(s[i]=='P')h++;
		else if(s[i]=='L')h--;
		else assert(0);
		H[i]=h;
		if(h>hmx)hmx=h;
		if(h<hmn)hmn=h;
	}
	int ans=0;
	for(int initial=0;initial<3;initial++)
	{
		if(initial+hmn<0||initial+hmx>=3)continue;
		int ta=0;
		for(int i=0;i<N;i++)for(int j=0;j<initial+H[i];j++)(ta+=DP[i][j])%=MOD;
		(ans+=ta)%=MOD;
	}
	if(mx==1&&mn==0&&);
	ans++;
	printf("%d\n",(ans%MOD+MOD)%MOD);
	return 0;
}
