#include<cstdio>
#include<cassert>
using namespace std;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;
	scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		int ans=0,sum=0;
		for(int i=0,a,b;i<N;i++)
		{
			scanf("%d%d",&a,&b);
			sum+=a;
			if(sum%2==1)ans^=b;
		}
		puts(ans!=0?"A-Mi-Ba":"B-Mi-Ba");
	}
	return 0;
}
