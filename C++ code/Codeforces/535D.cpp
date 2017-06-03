#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
const int INF=2147483647,MOD=1e9+7;
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
int N,L,M,Y[1000001],DP[1000002],SUM[1000002];
char P[1000001];
int FAIL[1000001];
int Solve()
{
	for(int i=N-L+1;i>=0;i--)
	{
		const int right=*lower_bound(Y,Y+M,i);
		if(right==i)
		{
			const int next=*upper_bound(Y,Y+M,i);
			if(next<=i+L-1)
			{
				bool found=false;
				for(int j=FAIL[L];j;j=FAIL[j])if(i+j==next){found=true;break;}
				if(!found)return 0;
			}
			DP[i]=0;
			continue;
		}
		bool found=false;
		for(int j=FAIL[L];j;j=FAIL[j])if(right==i+L-j){found=true;break;}
		if(!found&&right<=i+L-1){DP[i]=0;continue;}
		DP[i]=1;
		for(int j=N-L+1;j>i+L-1;j--)(DP[i]+=DP[j])%=MOD;
		for(int j=FAIL[L];j;j=FAIL[j])(DP[i]+=DP[i+L-j])%=MOD;
	}
	int ans=1;
	for(int i=0;i)
}
int main()
{
	freopen("in.txt","R",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		scanf("%s",P);
		L=-1;while(P[++L]);
		for(int i=0;i<M;i++)scanf("%d",&Y[i]);
		Y[M]=INF;
		BuildFail(P,FAIL);
	}
	return 0;
}
