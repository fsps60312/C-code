#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,C,S[1000000];
bool Solve(int time)
{
	int cur=N-1;
	while(cur>=0)
	{
		const int available=time-S[cur]-C+1;
		if(available<=0)return false;
		cur-=available;
		time-=(available-1)+C+(available-1);
	}
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&C)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		for(int i=1,now=S[0];i<N;now=S[i++])
		{
			if(++now>S[i])S[i]=now;
		}
		int l=0,r=INF;
		while(l<r)
		{
			const int mid=l+(r-l)/2;
			if(Solve(mid))r=mid;
			else l=mid+1;
		}
		printf("%lld\n",(long long)r+C);
	}
	return 0;
}
