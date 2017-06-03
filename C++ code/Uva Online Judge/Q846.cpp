#include<cstdio>
#include<cassert>
using namespace std;
int Solve(int dis)
{
	for(int i=1,ans=0;;i++)
	{
		if(dis<=0)return ans;
		dis-=i,ans++;
		if(dis<=0)return ans;
		dis-=i,ans++;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	int t;scanf("%d",&t);
	for(int x,y;t--;)
	{
		scanf("%d%d",&x,&y);
		printf("%d\n",Solve(y-x));
	}
	return 0;
}
