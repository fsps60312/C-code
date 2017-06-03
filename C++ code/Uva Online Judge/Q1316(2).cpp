#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int N,DJSET[10000],ANS;
void getmax(int &a,int b){if(b>a)a=b;}
struct Prod
{
	int p,d;
	Prod(int a,int b):p(a),d(b){}
	Prod(){}
}PROD[10000];
bool cmpsort(Prod a,Prod b)
{
	return a.p>b.p;
}
int findDJ(int a)
{
	return DJSET[a]==a?a:(DJSET[a]=findDJ(DJSET[a]));
}
bool insrt(int d,int p)
{
	int i=findDJ(d);
	if(i==0)return false;
	ANS+=p;
	DJSET[i]=i-1;
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		int md=0;
		for(int i=0;i<N;i++)
		{
			scanf("%d%d",&PROD[i].p,&PROD[i].d);
			getmax(md,PROD[i].d);
		}
		sort(PROD,PROD+N,cmpsort);
		for(int i=0;i<=md;i++)DJSET[i]=i;
		ANS=0;
		for(int i=0;i<N;i++)
		{
			insrt(PROD[i].d,PROD[i].p);
		}
		printf("%d\n",ANS);
	}
	return 0;
}
