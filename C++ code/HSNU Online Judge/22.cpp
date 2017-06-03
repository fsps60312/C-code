#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL T,A,B,D;
vector<LL>P,F;
inline void GetFactor(LL n)
{
	static LL i,cnt;
	F.clear();
	for(i=0L,cnt=0L;P[i]*P[i]<=n;i++,cnt=0L)
	{
		while(n%P[i]==0L)cnt++,n/=P[i];
		if(cnt)F.push_back(P[i]);
	}
	if(n>1L)F.push_back(n);
}
inline int CntBit(int a)
{
	a=((a&0xaaaaaaaa)>>1)+(a&0x55555555);
	a=((a&0xcccccccc)>>2)+(a&0x33333333);
	a=((a&0xf0f0f0f0)>>4)+(a&0x0f0f0f0f);
	a=((a&0xff00ff00)>>8)+(a&0x00ff00ff);
	a=((a&0xffff0000)>>16)+(a&0x0000ffff);
	return a;
}
inline LL Mul(const int &s,const LL &sz)
{
	static LL k,ans;
	ans=1L;
	for(k=0L;k<sz;k++)if(s&(1<<k))ans*=F[k];
	return ans;
}
inline LL Solve()
{
	static LL ans,sz;
	static int s,limit;
	ans=0L,sz=F.size();
	for(s=1,limit=1L<<sz;s<limit;s++)
	{
		if(CntBit(s)&1L)ans+=B/Mul(s,sz);
		else ans-=B/Mul(s,sz);
	}
	return B-ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	P.push_back(2L),P.push_back(3L);
	for(LL i=2L,j;;i++)
	{
		P.push_back(P[i-1L]);
		do
		{
			P[i]+=2L;
			for(j=0L;P[j]*P[j]<=P[i]&&P[i]%P[j];j++);
		}while(!P[i]%P[j]);
		if(P[i]*P[i]>50000L)break;
	}
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld%lld",&A,&B,&D);
		A/=D,B/=D;
		if(A>B)swap(A,B);
		LL ans=B;
		for(LL n=2L;n<=A;n++)
		{
			GetFactor(n);
			ans+=Solve();
		}
		printf("%lld\n",ans);
	}
	return 0;
}
