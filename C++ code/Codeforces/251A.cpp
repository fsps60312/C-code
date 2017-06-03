#include<cstdio>
#include<cassert>
using namespace std;
typedef long long LL;
int N,D,S[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&D)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		LL ans=0LL;
		for(int l=0,r=-1;l<N;l++)
		{
			while(r+1<N&&S[r+1]-S[l]<=D)r++;
			ans+=(LL)(r-l)*(r-l-1LL)/2LL;
		}
		printf("%I64d\n",ans);
	}
	return 0;
}
