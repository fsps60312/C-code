#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL BASE=103,MOD=2147483647;
LL PS[1000001],POW[1000001];
int N,Z[1000000];
char S[1000001];
int Solve()
{
	Z[0]=0;
	int len=0;
	for(int i=1,mx=0;i<N;i++)
	{
		if(mx+Z[mx]-1>=i)Z[i]=min(mx+Z[mx]-1-i+1,Z[i-mx]);
		else Z[i]=0;
		while(S[Z[i]]==S[i+Z[i]])Z[i]++;
		if(i+Z[i]>mx+Z[mx])mx=i;
		if(Z[i]<=N/2&&i+Z[i]-1==N-1){len=Z[i];break;}
	}
	PS[0]=0,POW[0]=1;
	for(int i=1;i<=N;i++)PS[i]=(PS[i-1]*BASE+(S[i-1]-'a'))%MOD,POW[i]=POW[i-1]*BASE%MOD;
	if(len>=N/2)return N/2;
	int mx=0;
	for(int i=1;len+i<=N/2;i++)
	{
		if(((PS[len+i]-PS[len]*POW[i])%MOD+MOD)%MOD==((PS[N-len]-PS[N-len-i]*POW[i])%MOD+MOD)%MOD)mx=i;
	}
	return len+mx;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%s",&N,S);
//	puts(S);
	printf("%d\n",Solve());
	return 0;
}
