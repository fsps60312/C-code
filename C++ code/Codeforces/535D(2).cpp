#include<cstdio>
#include<cassert>
#include<algorithm>
#include<set>
using namespace std;
const int MOD=1e9+7;
void BuildFail(const char *s,int *fail)
{
	fail[0]=fail[1]=0;
	for(int i=1;s[i];i++)
	{
		int &f=fail[i+1]=fail[i];
		while(f&&s[i]!=s[f])f=fail[f];
		if(s[i]==s[f])f++;
	}
}
int N,L,M,Y[1000000];
char P[1000001];
int FAIL[1000001];
set<int>SUF;
int Solve()
{
	for(int i=1;i<M;i++)if(Y[i]-Y[i-1]<L&&SUF.find(L-(Y[i]-Y[i-1]))==SUF.end())return 0;
	int cnt=0;
	if(M==0)cnt=N;
	else
	{
		cnt+=(Y[0]-1)-0;
		cnt+=N-(Y[M-1]+L-1);
		for(int i=1;i<M;i++)if(Y[i]-Y[i-1]>L)cnt+=(Y[i]-1)-(Y[i-1]+L-1);
	}
	long long ans=1;
	for(int i=0;i<cnt;i++)(ans*=26)%=MOD;
	return (int)ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		scanf("%s",P);
		L=-1;while(P[++L]);
		for(int i=0;i<M;i++)scanf("%d",&Y[i]);
		BuildFail(P,FAIL);
		SUF.clear();
		for(int cur=FAIL[L];cur;cur=FAIL[cur])SUF.insert(cur);
		printf("%d\n",Solve());
	}
	return 0;
}
