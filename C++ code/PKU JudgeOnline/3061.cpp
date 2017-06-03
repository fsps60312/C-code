#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
typedef long long LL;
int N;
LL BOUND,S[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%lld",&N,&BOUND);
		for(int i=0;i<N;i++)scanf("%lld",&S[i]);
		LL sum=0LL;
		int ans=INF;
		for(int l=0,r=-1;l<N;l++)
		{
			while(r+1<N&&sum<BOUND)sum+=S[++r];
			if(sum<BOUND)break;
			if(r-l+1<ans)ans=r-l+1;
			sum-=S[l];
		}
		if(ans==INF)ans=0;
		printf("%d\n",ans);
	}
	return 0;
}
