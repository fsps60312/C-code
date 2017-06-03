#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
int N;
LL K,SUM[2001][2001];
LL Sum(const int x1,const int y1,const int x2,const int y2){return SUM[y2][x2]-SUM[y1-1][x2]-SUM[y2][x1-1]+SUM[y1-1][x1-1];}
bool Solve(const int row,const int *upon,int &x1,int &y1,int &x2,int &y2)
{
	static int left[2002],rigt[2002];
	vector<int>stk;
	stk.clear(),stk.push_back(0);
	for(int i=1;i<=N;i++)
	{
		while(upon[stk.back()]<=upon[i])stk.pop_back();
		left[i]=stk.back();
		stk.push_back(i);
	}
	stk.clear(),stk.push_back(N+1);
	for(int i=N;i>=1;i--)
	{
		while(upon[stk.back()]<=upon[i])stk.pop_back();
		rigt[i]=stk.back();
		stk.push_back(i);
	}
	for(int i=1;i<=N;i++)
	{
//		printf("upon[%d]=%d,left=%d,rigt=%d\n",i,upon[i],left[i],rigt[i]);
		const int h=upon[i]+1;
		if(h<=N&&Sum(left[i]+1,h,rigt[i]-1,row)>=K)
		{
			x1=left[i]+1,y1=h,x2=rigt[i]-1,y2=row;
			while(Sum(x1,y1,x2,y2)>2*K)
			{
//				printf("(%d,%d,%d,%d)=%lld\n",x1,y1,x2,y2,Sum(x1,y1,x2,y2));
					 if(Sum(x1+1,y1,x2,y2)>=K)++x1;
				else if(Sum(x1,y1+1,x2,y2)>=K)++y1;
				else if(Sum(x1,y1,x2-1,y2)>=K)--x2;
				else if(Sum(x1,y1,x2,y2-1)>=K)--y2;
				else assert(0);
			}
			return true;
		}
	}
	return false;
}
int UPON[2001][2002];
bool Solve(int &ans_x1,int &ans_y1,int &ans_x2,int &ans_y2)
{
	const int inf=2147483647;
	for(int i=1;i<=N;i++)
	{
		UPON[i][0]=UPON[i][N+1]=inf;
		if(Solve(i,UPON[i],ans_x1,ans_y1,ans_x2,ans_y2))return true;
	}
	return false;
}
void Initialize()
{
	for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)
	{
		UPON[i][j]=(SUM[i][j]>2*K?i:(i==1?0:UPON[i-1][j]));
	}
	for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)SUM[i][j]+=SUM[i-1][j]+SUM[i][j-1]-SUM[i-1][j-1];
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%lld%d",&K,&N)==2)
	{
		for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)scanf("%lld",&SUM[i][j]);
		Initialize();
		int ans_x1,ans_y1,ans_x2,ans_y2;
		if(!Solve(ans_x1,ans_y1,ans_x2,ans_y2))puts("NIE");
		else printf("%d %d %d %d\n",ans_x1,ans_y1,ans_x2,ans_y2);
	}
	return 0;
}
