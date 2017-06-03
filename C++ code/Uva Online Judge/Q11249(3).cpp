#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int T,K,Q,A,B,SG[100001];
void buildSG()
{
	for(int i=0;i<=100000;i++)SG[i]=-1;
	SG[1]=K+2;
	SG[K+2]=1;
	int pre=1;
	for(int i=2;i<=100000;i++)
	{
		if(SG[i]!=-1)continue;
		int v=(SG[pre]-pre)+K+i+1;
		if(v>100000)break;
		SG[i]=v;//SG[i]-i>SG[pre]-pre+K
		SG[v]=i;
		pre=i;
	}
}
bool solve()
{
	if(A>B)swap(A,B);
	return SG[A]!=B;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&K,&Q);
		buildSG();
		while(Q--)
		{
			scanf("%d%d",&A,&B);
			printf(solve()?"WINNING\n":"LOSING\n");
		}
		puts("");
	}
	return 0;
}
