#include<cstdio>
#include<vector>
using namespace std;
int S[7],SUM,HALF;
vector<int>ITEM;
vector<bool>DP;
int main()
{
	SUM=0;
	for(int i=0;i<7;i++)scanf("%d",&S[i]),SUM+=(i+1)*S[i];
	HALF=SUM/2;
	ITEM.clear();
	for(int w=0;w<7;w++)
	{
		int remain=S[w];
		for(int i=0;(1<<i)<=remain;i++)
		{
			ITEM.push_back((w+1)*(1<<i));
			remain-=1<<i;
		}
		if(remain)ITEM.push_back((w+1)*remain);
	}
	DP.clear();DP.resize(HALF+1,false);
	DP[0]=true;
	for(const int v:ITEM)
	{
		for(int i=HALF;i-v>=0;i--)DP[i]=DP[i]|DP[i-v];
	}
	for(int i=HALF;i>=0;i--)if(DP[i])
	{
		printf("%d\n",(SUM-i)-i);
		break;
	}
	return 0;
}
