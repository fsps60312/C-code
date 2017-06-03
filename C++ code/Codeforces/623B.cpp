#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=1LL<<62;
void getmin(LL &a,const LL b){if(b<a)a=b;}
int N;
LL A,B,S[1000000];
LL Solve(const LL g,const bool type)
{
	if(g==1LL)return INF;
	int l=0;
	for(;l<N&&S[l]%g==0;l++);
	if(l==N)return 0;
	int r=N-1;
	for(;S[r]%g==0;r--);
	LL ans=A*(r-l+1);
	if(type)return ans;
	if((S[l]+1)%g==0||(S[l]-1)%g==0)
	{
		const int backup=l;
		l++;
		for(;l<N&&S[l]%g==0;l++);
		if(l==N)getmin(ans,B);
		else getmin(ans,B+A*(r-l+1));
		l=backup;
	}
	if((S[r]+1)%g==0||(S[r]-1)%g==0)
	{
		r--;
		for(;r>=0&&S[r]%g==0;r--);
		if(r==-1)getmin(ans,B);
		else getmin(ans,B+A*(r-l+1));
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%lld%lld",&N,&A,&B)==3)
	{
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		LL ans=INF;
		for(int i=1;i*i<=S[0];i++)if(S[0]%i==0)getmin(ans,min(Solve(i,false),Solve(S[0]/i,false)));
		for(int i=1;i*i<=S[N-1];i++)if(S[N-1]%i==0)getmin(ans,min(Solve(i,false),Solve(S[N-1]/i,false)));
		S[0]++;
		for(int i=1;i*i<=S[0];i++)if(S[0]%i==0)getmin(ans,min(Solve(i,true),Solve(S[0]/i,true))+B);
		S[0]-=2;
		for(int i=1;i*i<=S[0];i++)if(S[0]%i==0)getmin(ans,min(Solve(i,true),Solve(S[0]/i,true))+B);
		S[0]++;
		S[N-1]++;
		for(int i=1;i*i<=S[N-1];i++)if(S[N-1]%i==0)getmin(ans,min(Solve(i,true),Solve(S[N-1]/i,true))+B);
		S[N-1]-=2;
		for(int i=1;i*i<=S[N-1];i++)if(S[N-1]%i==0)getmin(ans,min(Solve(i,true),Solve(S[N-1]/i,true))+B);
		S[N-1]++;
		printf("%lld\n",ans);
	}
}
