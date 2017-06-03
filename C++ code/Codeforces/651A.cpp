#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int A,B;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&A,&B)==2)
	{
		int ans=0;
		for(;A>0&&B>0;)
		{
			if(A>B)swap(A,B);
			B-=2,A+=1;
			if(B<0)break;
			ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
