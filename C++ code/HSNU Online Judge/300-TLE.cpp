#include<cstdio>
#include<cassert>
#include<vector>
#include<queue>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
int N,M,A[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&A[i]),A[i]--;
		int ans=0;
		for(int s=0;s<(1<<N);s++)
		{
			bool found=false;
			for(int i=0;i<N;i++)if((s&(1<<i))&&(s&(1<<A[i]))){found=true;break;}
			if(!found)ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
