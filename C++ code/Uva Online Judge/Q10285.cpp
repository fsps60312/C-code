#include<cstdio>
#include<queue>
using namespace std;
char NAME[1000000];
int T,R,C,H[101][101],DP[102][102];
struct Pq
{
	int r,c,v;
	bool operator<(Pq a)const{return v>a.v;}
};
void getmax(int &a,int b){if(b>a)a=b;}
int solve()
{
	priority_queue<Pq> pq;
	for(int r=1;r<=R;r++)
		for(int c=1;c<=C;c++)
			pq.push((Pq){r,c,H[r][c]});
	int ans=0;
	while(!pq.empty())
	{
		Pq u=pq.top();pq.pop();
		int &r=u.r,&c=u.c,&a=DP[r][c];
		getmax(a,DP[r+1][c]+1);
		getmax(a,DP[r-1][c]+1);
		getmax(a,DP[r][c+1]+1);
		getmax(a,DP[r][c-1]+1);
		getmax(ans,a);
	}
	return ans;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s%d%d",NAME,&R,&C);
		for(int r=1;r<=R;r++)
			for(int c=1;c<=C;c++)
				scanf("%d",&H[r][c]);
		for(int r=0;r<=R+1;r++)
			for(int c=0;r<=C+1;c++)
				DP[r][c]=0;
		printf("%s: %d\n",NAME,solve());
	}
	return 0;
}
