#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
int T,K,Q,A,B,MX,SG[199999];
bool solve()
{
//1,k+2
//2,2k+4
	if(A>B)swap(A,B);
	int d=B-A;
	if(d<=K)return true;
	if(d==K+1)return A!=1;
	if(d%(K+1)==0)return A!=d/(K+1);
	
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&K,&Q);
		SG[0]=MX=0;
		while(Q--)
		{
			scanf("%d%d",&A,&B);
			printf(solve()?"WINNING\n":"LOSING\n");
		}
		puts("");
	}
	return 0;
}
