#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,P,Q,X,Y,SUM[1000001],LEFT_MN[1000001],RIGT_MN[1000001];
char S[1000002];
int Adjust(const int move)
{
	const int loc=N-move;
	const int left_low=P+(RIGT_MN[loc]-SUM[loc]),rigt_low=Q+(LEFT_MN[loc]-SUM[loc]);
	int ans=0,dif=(Q-(SUM[loc]-SUM[0]))-(P+(SUM[N]-SUM[loc]));
	if(left_low<0)
	{
		const int action=(abs(left_low)+1)/2;
		ans+=action,dif-=action*2;
	}
	if(rigt_low<0)
	{
		const int action=(abs(rigt_low)+1)/2;
		ans+=action,dif+=action*2;
	}
	assert(dif%2==0);
	return ans+=abs(dif/2);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d%d",&N,&P,&Q,&X,&Y)==5)
	{
		scanf("%s",S+1);
		SUM[0]=0;
		for(int i=1;i<=N;i++)SUM[i]=SUM[i-1]+(S[i]=='-'?-1:1);
		LEFT_MN[0]=SUM[0];
		for(int i=1;i<=N;i++)LEFT_MN[i]=min(LEFT_MN[i-1],SUM[i]);
		RIGT_MN[N]=SUM[N];
		for(int i=N-1;i>=0;i--)RIGT_MN[i]=min(RIGT_MN[i+1],SUM[i]);
		assert((P+SUM[N]-Q)%2==0);
		int ans=INF;
		for(int move=0;move<N;move++)ans=min(ans,Adjust(move)*X+move*Y);
		printf("%d\n",ans);
	}
	return 0;
}
