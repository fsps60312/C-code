#include<cstdio>
#include<cassert>
using namespace std;
const int INF=2147483647;
void getmax(int &a,const int b){if(b>a)a=b;}
int N,S[100000];
int Solve1()
{
	int now=0,ans=-INF;
	for(int i=0;i<N;i++)
	{
		if(now<0)now=0;
		now+=S[i];
		getmax(ans,now);
	}
	return ans;
}
int Solve2()
{
	int ans=0,mx=-INF;
	bool vis=false;
	for(int i=0;i<N;i++)
	{
		if(S[i]>0)ans+=S[i],vis=true;
		getmax(mx,S[i]);
	}
	if(!vis)ans+=mx;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		printf("%d %d\n",Solve1(),Solve2());
	}
	return 0;
}
