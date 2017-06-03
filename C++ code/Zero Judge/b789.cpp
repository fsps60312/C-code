#include<cstdio>
#include<cassert>
using namespace std;
int N,S[1000000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	static int ans[1000000];
	int len=0;
	for(int i=0;i<N;i++)
	{
		int l=0,r=len;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(S[i]>ans[mid])l=mid+1;
			else r=mid;
		}
		if(r==len)++len;
		ans[r]=S[i];
	}
	printf("%d\n",len);
	return 0;
}
