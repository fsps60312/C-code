#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int MOD=1000000007;
int N;
char S[5001];
int DP[5000][5000],SUM[5000][5001];
int SA[5000];
void BuildSA()
{
	static int tmp[3][5000];
	int *x=tmp[0],*y=tmp[1],*c=tmp[2];
	int p=256;
	for(int i=0;i<p;i++)c[i]=0;
	for(int i=0;i<N;i++)c[x[i]=S[i]]++;
	for(int i=1;i<p;i++)c[i]+=c[i-1];
	for(int i=N-1;i>=0;i--)SA[--c[x[i]]]=i;//loc i, rank x[i]
	for(int move=1;move<=N;move<<=1)//rank r, loc SA[r]
	{
		int cnt=0;
		for(int i=N-move;i<N;i++)y[cnt++]=i;
		for(int i=0;i<N;i++)if(SA[i]>=move)y[cnt++]=SA[i]-move;
		for(int i=0;i<p;i++)c[i]=0;
		for(int i=0;i<N;i++)c[x[i]]++;
		for(int i=1;i<p;i++)c[i]+=c[i-1];
		for(int i=N-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];//rank r, loc y[i]
		swap(x,y);
		p=0;
		x[SA[0]]=p++;
		for(int i=1;i<N;i++)
		{
			if(y[SA[i-1]]!=y[SA[i]])x[SA[i]]=p++;
			else if((SA[i-1]+move<N)!=(SA[i]+move<N))x[SA[i]]=p++;
			else if(SA[i-1]+move>=N&&SA[i]+move>=N)x[SA[i]]=p-1;
			else x[SA[i]]=(y[SA[i-1]+move]==y[SA[i]+move]?p-1:p++);
		}
		assert(p<=N);
		if(p==N)break;
	}
}
int RANK[5000],HEIGHT[5000];
void BuildHEIGHT()
{
	for(int i=0;i<N;i++)RANK[SA[i]]=i;
	for(int i=0,ans=0;i<N;i++)
	{
		if(ans)ans--;
		if(RANK[i]==0){HEIGHT[0]=0;continue;}
		int a=i,b=SA[RANK[i]-1];
		while(S[a+ans]==S[b+ans])ans++;
		HEIGHT[RANK[i]]=ans;
	}
}
int SPARSE[30][5000];
void BuildSPARSE()
{
	for(int i=0;i<N;i++)SPARSE[0][i]=HEIGHT[i];
	for(int d=1;(1<<d)<=N;d++)
	{
		for(int i=0;i+(1<<d)<=N;i++)SPARSE[d][i]=min(SPARSE[d-1][i],SPARSE[d-1][i+(1<<(d-1))]);
	}
}
int Query(int a,int b)
{
	assert(a!=b);
	if(a>b)swap(a,b);
	a++;
	for(int d=30;d>=0;d--)if((1<<d)<=b-a+1)
	{
		return min(SPARSE[d][a],SPARSE[d][b-(1<<d)+1]);
	}
	assert(0);return -1;
}
bool Smaller(const int l,const int r)
{
	if(r+1>=N)return false;
	if(Query(RANK[l],RANK[r+1])>=r-l+1)return false;
	return RANK[l]<RANK[r+1];
}
int GetDP(const int l,const int r)
{
	int &dp=DP[l][r];
	if(dp!=-1)return dp;
	if(S[l]=='0')return dp=0;
	if(r==N-1)return dp=1;
	int end;
	if(Smaller(l,r))end=r+(r-l+1);
	else end=r+(r-l+2);
	return dp=(end<N?SUM[r+1][end]:0);
//	dp=0;
//	while(end<N)(dp+=GetDP(r+1,end))%=MOD,end++;
//	return dp;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		scanf("%s",S);
		BuildSA();
		BuildHEIGHT();
		BuildSPARSE();
		for(int i=0;i<N;i++)for(int j=i;j<N;j++)DP[i][j]=-1;
		for(int l=N-1;l>=0;l--)
		{
			SUM[l][N]=0;
			for(int r=N-1;r>=l;r--)(SUM[l][r]=SUM[l][r+1]+GetDP(l,r))%=MOD;
		}
//		int ans=0;
//		for(int i=0;i<N;i++)(ans+=GetDP(0,i))%=MOD;
		printf("%d\n",SUM[0][0]);
		break;
	}
	return 0;
}
