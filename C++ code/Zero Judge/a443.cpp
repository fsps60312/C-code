#include<cstdio>
#include<cassert>
#include<algorithm>
#include<functional>
using namespace std;
int N,S[1000000],CNT[1000000];
bool Solve()
{
	sort(S,S+N,greater<int>());
	if(N<=S[0]||S[N-1]<=0)return false;
	for(int i=1;i<N;i++)CNT[i]=0;
	for(int i=0;i<N;i++)++CNT[S[i]];
	for(int i=N-2;i>=1;i--)CNT[i]+=CNT[i+1];
	int vertex=0;
	for(int h=N-1;h>=1;h--)
	{
		assert(CNT[h]-vertex>=0);
		while(CNT[h]-vertex)
		{
			vertex++;
			int remain=h;
			for(int i=h;remain&&i>=1;i--)
			{
				const int v=min(remain,CNT[i]-vertex);
				assert(v>=0);
				CNT[i]-=v,remain-=v;
			}
			if(remain)return false;
		}
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N!=0)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		puts(Solve()?"Possible":"Not possible");
	}
	return 0;
}
