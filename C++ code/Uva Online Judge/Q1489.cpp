#include<cstdio>
#include<map>
#define LL long long
using namespace std;
const LL MOD=1000000003;
int N,K,V[50];
map<int,LL> SET;
int main()
{
	while(scanf("%d%d",&N,&K)==2&&(N||K))
	{
		for(int i=0;i<N;i++)scanf("%d",V+i);
		int hn=N/2;
		for(int s=(1<<hn)-1,v=0,i;s>=0;s--,v=0)
		{
			for(i=0;i<N;i++)if(s&(1<<i))v^=V[i];
			if(SET.find(v)==SET.end())SET[v]=1LL;
			else SET[v]++;
		}
		LL ans=0LL;
		for(int s=(1<<(N-hn))-1,v=K,i;s>=0;s--,v=K)
		{
			for(i=0;i<N;i++)if(s&(1<<i))v^=V[i+hn];
			if(SET.find(v)!=SET.end())
			{
				ans+=SET[v];
				ans%=MOD;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
