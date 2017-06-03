#include<cstdio>
#include<algorithm>
using namespace std;
int N;
struct Line
{
	int l,r;
	bool operator<(const Line &a)const{return l<a.l;}
}LINE[50000];
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d%d",&LINE[i].l,&LINE[i].r);
	sort(LINE,LINE+N);
	printf("%d ",LINE[0].l);
	int r=LINE[0].r;
	for(int i=1;i<N;i++)
	{
		if(LINE[i].l>r)printf("%d\n%d ",r,LINE[i].l),r=LINE[i].r;
		else r=max(r,LINE[i].r);
	}
	printf("%d\n",r);
	return 0;
}
