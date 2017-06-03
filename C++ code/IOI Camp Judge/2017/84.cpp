#include<cstdio>
#include<cassert>
using namespace std;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		static int n,cnt[100000];
		scanf("%d",&n);
		for(int i=0;i<n;i++)cnt[i]=0;
		for(int i=0,a,b;i<n-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			++cnt[a],++cnt[b];
		}
		int ans=0;
		for(int i=0;i<n;i++)if(cnt[i]==1)++ans;
		if(ans==n)--ans;
		printf("%d\n",ans);
	}
	return 0;
}
