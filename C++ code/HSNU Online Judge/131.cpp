#include<cstdio>
#include<cassert>
#include<algorithm>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
int N,C,FENCE[100000];
bool Solve(const int dis)
{
	int cnt=C-1,cur=0;
	while(cnt--)
	{
		int l=cur+1,r=N;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(FENCE[mid]-FENCE[cur]>=dis)r=mid;
			else l=mid+1;
		}
		if((cur=r)==N)return false;
	}
	return true;
}
int main()
{
	scanf(2,"%d%d",&N,&C);
	for(int i=0;i<N;i++)scanf(1,"%d",&FENCE[i]);
	sort(FENCE,FENCE+N);
	int l=0,r=1000000000;
	while(l<r)
	{
		const int mid=(l+r+1)/2;
		if(Solve(mid))l=mid;
		else r=mid-1;
	}
	assert(Solve(r));
	printf("%d\n",r);
	return 0;
}
