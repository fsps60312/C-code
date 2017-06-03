#include<cstdio>
#include<cassert>
using namespace std;
int N;
void Solve(const int l,const int r)
{
	if(l==r){printf("Answer %d\n",r);fflush(stdout);return;}
	const int cnt=(r-l+1+2)/3;
	printf("Test");
	for(int i=0;i<cnt;i++)printf(" %d",l+i);
	for(int i=0;i<cnt;i++)printf(" %d",r-i);
	puts("");
	fflush(stdout);
	for(int i=0;i<1000000;i++);
	int a;scanf("%d",&a);
	switch(a)
	{
		case -1:Solve(r-cnt+1,r);return;
		case 0:Solve(l+cnt,r-cnt);return;
		case 1:Solve(l,l+cnt-1);return;
		default:assert(0);break;
	}
}
int main()
{
//	assert(0);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		Solve(1,N);
	}
	return 0;
}
