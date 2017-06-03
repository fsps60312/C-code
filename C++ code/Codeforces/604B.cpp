#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int N,K,S[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		int a=0;
		while(N>=0&&N<K*2)
		{
			--N,--K;
			a=max(a,S[N]);
		}
		for(int l=0,r=N-1;l<r;++l,--r)a=max(a,S[l]+S[r]);
		printf("%d\n",a);
	}
	return 0;
}
