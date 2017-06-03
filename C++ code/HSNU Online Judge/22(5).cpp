#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL T,A,B,D;
vector<LL>P;
LL OPE[50001];
LL GetFactor(LL n)
{
	int ans=0L;
	for(LL i=0L,cnt=0L;P[i]*P[i]<=n;i++,cnt=0L)
	{
		while(n%P[i]==0L)cnt++,n/=P[i];
		if(cnt>1L)return 0L;
		else if(cnt)ans++;
	}
	if(n>1L)ans++;
	return ans&1L?-1L:1L;
}
void BuildP()
{
	P.push_back(2L),P.push_back(3L);
	for(LL i=2L,j;;i++)
	{
		P.push_back(P[i-1L]);
		do
		{
			P[i]+=2L;
			for(j=0L;P[j]*P[j]<=P[i]&&P[i]%P[j];j++);
		}while(P[i]%P[j]==0L);
		if(P[i]*P[i]>50000L)break;
	}
}
void BuildExc()
{
	OPE[1]=0L;
	for(LL n=2L;n<=50000L;n++)OPE[n]=OPE[n-1]+GetFactor(n);
}
int main()
{
	BuildP();
	BuildExc();
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld",&A,&B,&D);
		A/=D,B/=D;
		LL ans=A*B;
		for(LL n=2L,r,limit=min(A,B);n<=limit;n=++r)
		{
			r=min(limit,min(A/(A/n),B/(B/n)));
			ans+=(A/n)*(B/n)*(OPE[r]-OPE[n-1L]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
