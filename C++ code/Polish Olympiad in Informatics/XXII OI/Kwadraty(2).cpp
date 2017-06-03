#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
using namespace std;
typedef long long LL;
const int MXN=14*(14+1)*(2*14+1)/6,INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
LL Sum(const LL n){return n*(n+1LL)*(2LL*n+1LL)/6LL;}
set<int>INFS;
int K[MXN+1],GOOD[MXN+1];
void BuildINFS()
{
	for(int i=0;i<=MXN;i++)K[i]=INF,GOOD[i]=0;
	K[0]=0;
	for(int n=1;n*n<=MXN;n++)
	{
		for(int i=MXN-n*n;i>=0;i--)if(K[i]!=INF)
		{
			getmin(K[i+n*n],n);
		}
	}
	INFS.clear();
	for(int i=0;i<=MXN;i++)if(K[i]==INF)INFS.insert(i);
	for(int i=MXN-1,mn=K[MXN];i>=0;i--)
	{
		if(K[i]>mn)GOOD[i]=1;
		getmin(mn,K[i]);
	}
	for(int i=1;i<=MXN;i++)GOOD[i]+=GOOD[i-1];
}
LL N,M;
int main()
{
	BuildINFS();
//	for(const int v:INFS)printf("%d ",v);puts("");
//	freopen("in.txt","r",stdin);
	while(scanf("%lld",&N)==1)
	{
		int k;
		LL good;
		if(N<=MXN)k=K[N],good=GOOD[N];
		else
		{
			good=GOOD[MXN];
			for(M=15;Sum(M)<N;M++)
			{
				good+=INFS.size();
			}
			for(set<int>::iterator it=INFS.begin();it!=INFS.end();++it)
			{
				if(Sum(M)-(*it)<=N)good++;
			}
			if(INFS.find(Sum(M)-N)!=INFS.end())k=M+1LL;
			else k=M;
		}
		if(k==INF)putchar('-');
		else printf("%d",k);
		putchar(' ');
		printf("%lld\n",good);
	}
	return 0;
}
