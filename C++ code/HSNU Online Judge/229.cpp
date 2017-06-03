#include<cstdio>
#include<queue>
#include<vector>
using namespace std;
const int INF=2147483647;
int N,K;
struct Cable
{
	int l,r,cost;
	Cable(){}
	Cable(const int &_l,const int &_r,const int &c):l(_l),r(_r),cost(c){}
	bool operator<(const Cable &c){return cost>c.cost;}
};
int S[100000],IL[99999],IR[99999],COST[99999],CL[99999],CR[99999];
priority_queue<Cable>CABLE;
void GetCABLE()
{
	while(!CABLE.empty())CABLE.pop();
	for(int i=0;i<N;i++)
	{
		scanf("%d",&S[i]);
		if(i)
		{
			COST[i-1]=S[i]-S[i-1];
			IL[i-1]=i-1,IR[i-1]=i;
			if(i-1>0)CL[i-1]=COST[i-2],CR[i-2]=COST[i-1];
		}
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d%d",&N,&K);
	for(int i=1;i<N;i++)
	{
		
	}
	return 0;
}
