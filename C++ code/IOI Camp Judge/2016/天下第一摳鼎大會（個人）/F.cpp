#include<cstdio>
#include<cassert>
using namespace std;
int N,M,IN[100000];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)IN[i]=0;
		for(int a,b,i=0;i<M;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			IN[b]++;
		}
		int ans=0;
		for(int i=0;i<N;i++)if(IN[i]==0)ans++;
		printf("%d\n",ans);
	}
	return 0;
}
