#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL T,A,B,D;
vector<LL>P;
vector<LL>EXC,OPE;
void GetFactor(const LL &nn)
{
//LL nn=n;
//vector<LL>f;
	static LL n;n=nn;
	int ans=0L;
	for(LL i=0L,cnt=0L;P[i]*P[i]<=n;i++,cnt=0L)
	{
		while(n%P[i]==0L)cnt++,n/=P[i];
		if(cnt>1L)return;
		else if(cnt)ans++;
	}
	if(n>1L)ans++;
//if(n>1L)f.push_back(n);
//printf("%lld:",nn);for(int i=0;i<f.size();i++)printf(" %lld",f[i]);puts("");
//system("pause");
	EXC.push_back(nn);
	OPE.push_back(ans&1L?-1L:1L);
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
	for(LL n=2L;n<=50000L;n++)GetFactor(n);
	EXC.push_back(50001L);
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
		for(LL i=0L;EXC[i]<=min(A,B);i++)
		{
			LL &v=EXC[i];
//			printf("%lld:%lld\n",v,OPE[i]);
			ans+=(A/v)*(B/v)*OPE[i];
		}
		printf("%lld\n",ans);
	}
	return 0;
}
