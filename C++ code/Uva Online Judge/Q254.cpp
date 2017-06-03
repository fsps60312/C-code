#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
//typedef unsigned long long LL;
typedef __int128 LL;
LL GetInt128()
{
	char c=getchar();
	while(c<'0'||'9'<c)c=getchar();
	LL ans=0;
	while('0'<=c&&c<='9')ans=ans*10+(c-'0'),c=getchar();
	return ans;
}
LL Require(const int radius)
{
	LL ans=1;
	ans<<=radius;
	return --ans;
}
vector<int>ANS[3];
void Move(const int radius,const int from,const int to,const LL step)
{
//	printf("%d %d %d %llu\n",radius,from,to,step);
	if(radius==1)
	{
		if(step==0)ANS[from].push_back(1);
		else if(step==1)ANS[to].push_back(1);
		else assert(0);
		return;
	}
	const LL mid=Require(radius-1);
	if(step<=mid)
	{
		ANS[from].push_back(radius);
		Move(radius-1,from,3-from-to,step);
	}
	else
	{
		ANS[to].push_back(radius);
		Move(radius-1,3-from-to,to,step-mid-1);
	}
}
int N;
LL M;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		M=GetInt128();
		if(N==0&&M==0)break;
//		printf("%d %llu\n",N,M);
		for(int i=0;i<3;i++)ANS[i].clear();
		Move(N,0,N&1?1:2,M);
		printf("%u %u %u\n",ANS[0].size(),ANS[1].size(),ANS[2].size());
	}
	return 0;
}
