#include<cstdio>
#include<cassert>
using namespace std;
int main()
{
//	freopen("in.txt","r",stdin);
	for(int n,k;scanf("%d%d",&n,&k)==2;)
	{
		int ans=0,t=60*4;
		t-=k;
		for(int i=1;i<=n;i++)
		{
			if(5*i>t)break;
			t-=5*i;
			ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
