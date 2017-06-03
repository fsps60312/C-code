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
		puts(N%2!=0?"tsan":"hao");
	}
	return 0;
}
