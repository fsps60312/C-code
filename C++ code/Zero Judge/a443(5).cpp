#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,S[1000000];
bool Solve()
{
	if(N==1)return S[0]==0;
	sort(S,S+N,greater<int>());
	if(S[0]>=N||S[N-1]<=0)return false;
	
	assert(0);
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
