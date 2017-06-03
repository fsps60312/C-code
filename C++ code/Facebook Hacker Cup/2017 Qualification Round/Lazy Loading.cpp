#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		int n;
		scanf("%d",&n);
		int *w=new int[n];
		for(int i=0;i<n;i++)scanf("%d",&w[i]);
		sort(w,w+n);
		int l=0,r=n-1,ans=0;
		while(r>=l)
		{
			l+=(50-1)/w[r];
			r--;
			if(l>r+1)break;
			ans++;
		}
		delete[]w;
		static int kase=0;
		printf("Case #%d: %d\n",++kase,ans);
	}
	return 0;
}
