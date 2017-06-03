#include<cstdio>
#include<algorithm>
using namespace std;
int N,Q,S[50000];
int MN[17][50000],MX[17][50000];
int main()
{
	scanf("%d%d",&N,&Q);
	for(int i=0;i<N;i++)scanf("%d",&S[i]),MN[0][i]=MX[0][i]=S[i];
	for(int d=1;(1<<d)<=N;d++)
	{
		for(int i=0;i+(1<<d)<=N;i++)
		{
			MN[d][i]=min(MN[d-1][i],MN[d-1][i+(1<<(d-1))]);
			MX[d][i]=max(MX[d-1][i],MX[d-1][i+(1<<(d-1))]);
		}
	}
	while(Q--)
	{
		static int a,b;scanf("%d%d",&a,&b),a--,b--;
		if(a>b)swap(a,b);
		for(int d=16;d>=0;d--)if((1<<d)<=b-a+1)
		{
			const int l=a,r=b-(1<<d)+1;
			printf("%d\n",max(MX[d][l],MX[d][r])-min(MN[d][l],MN[d][r]));
			break;
		}
	}
	return 0;
}
