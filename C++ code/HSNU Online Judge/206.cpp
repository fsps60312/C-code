#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
int N,M;
LL DP[3][1<<12];
LL ANS[12][12];
vector<int>V[3];
bool PutV(const int &s,const int &r,const int &c,int &t)
{
	t=s+(1<<c);
	return true;
}
bool PutH(const int &s,const int &r,const int &c,int &t)
{
	if(s&(1<<(c+1))||c+1>=M)return false;
	t=s;
	return true;
}
void Push(const int &d,const int &t,const int &dp)
{
	if(DP[d][t]==0LL)V[d].push_back(t);
	DP[d][t]+=dp;
}
void Dfs(int r,int c,const int &d)
{
//	printf("M=%d,r=%d,c=%d,V[%d].size()=%d\n",M,r,c,d,V[d].size());
	for(int &s:V[d])
	{
		LL &dp=DP[d][s];
		static int t;
		if(s&(1<<c)){Push((d+1)%3,t=s-(1<<c),dp);continue;}
		if(PutV(s,r,c,t))Push((d+1)%3,t,dp);
		if(PutH(s,r,c,t))Push((d+2)%3,t,dp);
		dp=0LL;
	}
	V[d].clear();
	if(++c==M)
	{
		ANS[r][M-1]=ANS[M-1][r]=DP[(d+1)%3][0];
		c-=M,r++;
	}
	if(r==M)return;
	Dfs(r,c,(d+1)%3);
}
int main()
{
//	freopen("out.txt","w",stdout);
	for(int i=0;i<(1<<12);i++)DP[0][i]=DP[1][i]=DP[2][i]=0LL;
	for(M=1;M<=12;M++)
	{
		for(int i=0;i<3;i++)
		{
			for(int s:V[i])DP[i][s]=0LL;
			V[i].clear();
		}
		V[0].push_back(0);
		DP[0][0]=1LL;
		Dfs(0,0,0);
	}
//	return 0;
	while(scanf("%d%d",&N,&M)==2)
	{
		printf("%lld\n",ANS[--N][--M]);
	}
	return 0;
}
