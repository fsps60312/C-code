#include<cstdio>
#include<cassert>
#include<vector>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
int N,M;
bool EDGE[1000][1000];
struct DpType
{
	int nxtl,nxtr,nxtd;
	DpType(){}
	DpType(const int _l,const int _r,const int _d):nxtl(_l),nxtr(_r),nxtd(_d){}
}DP[1000][1000][2];
bool GetDP(const int l,const int r,const int d)
{
	DpType &dp=DP[l][r][d];
	if(dp.nxtl==-2)return false;
	else if(dp.nxtl!=-1)return true;
	if((r+1)%N==l)return true;
	const int start=(d==0?l:r),nxtl=(l-1+N)%N,nxtr=(r+1)%N;
	const bool tol=(EDGE[start][nxtl]&&GetDP(nxtl,r,0)),tor=(EDGE[start][nxtr]&&GetDP(l,nxtr,1));
	if(nxtl<nxtr)
	{
		if(tol){dp=DpType(nxtl,r,0);return true;}
		if(tor){dp=DpType(l,nxtr,1);return true;}
	}
	else
	{
		if(tor){dp=DpType(l,nxtr,1);return true;}
		if(tol){dp=DpType(nxtl,r,0);return true;}
	}
	dp.nxtl=-2;return false;
}
int Solve()
{
	for(int i=0;i<N;i++)if(GetDP(i,i,0))return i;
	return -1;
}
void PrintAns(const DpType &s,vector<int>&ans)
{
	ans.push_back(s.nxtd==0?s.nxtl:s.nxtr);
	if((s.nxtr+1)%N==s.nxtl)return;
//	printf("(%d,%d,%d)\n",s.nxtl,s.nxtr,s.nxtd);
	const DpType &nxt=DP[s.nxtl][s.nxtr][s.nxtd];
	PrintAns(nxt,ans);
}
int main()
{
	scanf(2,"%d%d",&N,&M);
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)DP[i][j][0].nxtl=DP[i][j][1].nxtl=-1,EDGE[i][j]=false;
	for(int i=0,a,b;i<M;i++)scanf(2,"%d%d",&a,&b),a--,b--,EDGE[a][b]=EDGE[b][a]=true;
	const int result=Solve();
	if(result==-1)puts("-1");
	else
	{
		vector<int>ans;ans.push_back(result);
		PrintAns(DP[result][result][0],ans);
		assert((int)ans.size()==N);
		for(int i=0;i<N;i++)printf("%d\n",ans[i]+1);
	}
	return 0;
}
