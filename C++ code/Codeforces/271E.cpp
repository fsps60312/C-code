#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
int Gcd(const int a,const int b){return b==0?a:Gcd(b,a%b);}
int N,M,A[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		int g=A[0]-1;
		for(int i=1;i<N;i++)g=Gcd(g,A[i]-1);
		while(g%2==0)g/=2;
		vector<int>fs;
		for(int i=1;i*i<=g;i++)if(g%i==0)fs.push_back(i),fs.push_back(g/i);
		sort(fs.begin(),fs.end()),fs.resize(unique(fs.begin(),fs.end())-fs.begin());
		LL ans=0LL;
		for(const int f:fs)
		{
//			printf("f=%d\n",f);
			for(int p=0;;p++)
			{
				const LL gap=f*(1LL<<p);
				if(M-gap<1LL)break;
				const LL amx=M-gap;
//				printf("gap=%lld,cnt=%lld\n",gap,amx);
				ans+=amx;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
