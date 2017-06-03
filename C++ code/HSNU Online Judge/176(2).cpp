#include<cstdio>
#include<vector>
using namespace std;
int S[1000],SUM,HALF;
vector<int>ITEM;
vector<bool>DP;
int main()
{
	SUM=0;
	for(int i=0;i<7;i++)
	{
		scanf("%d",&S[i]);
		if(S[i]>42)S[i]=(S[i]-42)%2+42;
		SUM+=(i+1)*S[i];
	}
	HALF=SUM/2;
	ITEM.clear();
	for(int i=0;i<7;i++)for(int j=0;j<S[i];j++)ITEM.push_back(i+1);
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
