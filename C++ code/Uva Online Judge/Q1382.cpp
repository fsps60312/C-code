#include<cstdio>
#include<algorithm>
using namespace std;
int N;
struct Star
{
	int x,y;
}S[100];
void getmax(int &a,int b){if(b>a)a=b;}
int solve()
{
	int ans=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			int &x1=S[i].x,&x2=S[j].x,&y1=S[i].y,&y2=S[j].y,ta=0;
			for(int k=0;k<N;k++)
			{
				int &x=S[k].x,&y=S[k].y;
				if(x==x1||x==x2||y==y1||y==y2)ta++;
			}
			getmax(ans,ta);
		}
	}
	return ans;
}
int main()
{
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)scanf("%d%d",&S[i].x,&S[i].y);
		printf("Case %d: %d\n",kase++,solve());
	}
	return 0;
}
