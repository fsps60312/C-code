#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
struct Bulb
{
	int V,K,C,L;
}BULB[1000];
int SUM[1000],ANS[1000];
bool cmp_BULB(Bulb a,Bulb b)
{
	return a.V<b.V;
}
void getmin(int &a,int b){if(b<a)a=b;}
int N;
int main()
{
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)
		{
			Bulb &b=BULB[i];
			scanf("%d%d%d%d",&b.V,&b.K,&b.C,&b.L);
		}
		sort(BULB,BULB+N,cmp_BULB);
		SUM[0]=BULB[0].L,ANS[0]=BULB[0].K+BULB[0].C*BULB[0].L;
		for(int i=1;i<1000;i++)
		{
			SUM[i]=SUM[i-1]+BULB[i].L;
			ANS[i]=SUM[i]*BULB[i].C+BULB[i].K;
			for(int j=0;j<i;j++)getmin(ANS[i],ANS[j]+(SUM[i]-SUM[j])*BULB[i].C+BULB[i].K);
		}
		printf("%d\n",ANS[N-1]);
	}
	return 0;
}
