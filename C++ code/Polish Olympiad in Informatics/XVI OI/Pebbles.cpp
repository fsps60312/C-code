#include<cstdio>
#include<cassert>
using namespace std;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		int sg=0;
		for(int i=0,v,pre=0;i<N;i++)
		{
			scanf("%d",&v);
			if((N-i)%2==1)sg^=v-pre;
			pre=v;
		}
		puts(sg==0?"NIE":"TAK");
	}
	return 0;
}
