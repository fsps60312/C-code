#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Item
{
	int c,a,b;
	bool operator<(const Item &i)const{return a<i.a;}
}ITEM[1000];
struct Plan
{
	int m,k,s,id;
	bool operator<(const Plan &p)const{return m<p.m;}
}PLAN[1000000];
int N,P,DP[100001];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d%d%d",&ITEM[i].c,&ITEM[i].a,&ITEM[i].b);
	sort(ITEM,ITEM+N);
	scanf("%d",&P);
	for(int i=0;i<P;i++)scanf("%d%d%d",&PLAN[i].m,&PLAN[i].k,&PLAN[i].s),PLAN[i].id=i;
	sort(PLAN,PLAN+P);
	for(int i=0;i<=100000;i++)DP[i]=-INF;
	DP[0]=INF;
	bool *ans=new bool[P];
	for(int i=0,j=0;i<P;i++)
	{
		const Plan &p=PLAN[i];
		for(;j<N&&ITEM[j].a<=p.m;j++)
		{
			const Item &it=ITEM[j];
			for(int k=100000;k>=it.c;k--)
			{
				getmax(DP[k],min(DP[k-it.c],it.b));
			}
//			printf("ITEM[%d].a=%d\n",j,ITEM[j].a);
		}
//		printf("PLAN[%d].m=%d\n",i,PLAN[i].m);
//		printf("%d<%d\n",p.m+p.s,DP[p.k]);
		ans[p.id]=(p.m+p.s<DP[p.k]);
	}
	for(int i=0;i<P;i++)puts(ans[i]?"TAK":"NIE");
	delete[]ans;
	return 0;
}
