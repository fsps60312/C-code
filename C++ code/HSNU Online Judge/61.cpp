#include<cstdio>
#include<algorithm>
using namespace std;
int N,S[100000];
int Solve()
{
	if(N==1)return S[0];
	sort(S,S+N);
	int ans=0;
	while(N>=4)
	{
		ans+=S[1];//go
		ans+=S[0];//back
		ans+=S[N-1];//go
		ans+=S[1];//back
		N-=2;
	}
	if(N==2)ans+=S[1];
	else
	{
		ans+=S[2];//go
		ans+=S[0];//back
		ans+=S[1];//go
	}
	return ans;
}
int main()
{
//	freopen("in.txt","w",stdout);printf("100000\n");for(int i=0;i<100000;i++)printf(" 1000");puts("");return 0;
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		printf("%d\n",Solve());
//		break;
	}
	return 0;
}
