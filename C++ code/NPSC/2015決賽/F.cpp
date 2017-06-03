#include<cstdio>
#include<vector>
using namespace std;
int DP[2000001],N;
vector<int>S;
int main()
{
	static char tmp[1000001];
	while(scanf("%s",&tmp)==1)
	{
		S.clear(),S.push_back('\0');
		N=-1;while(tmp[++N])S.push_back(tmp[N]),S.push_back('\0');
		N=S.size();
		DP[0]=1;
		for(int i=1,mx=0;i<N;i++)
		{
			if(mx+DP[mx]-1>i)DP[i]=min(mx+DP[mx]-1-i+1,DP[mx-(i-mx)]);
			else DP[i]=1;
			while(i-DP[i]>=0&&i+DP[i]<N&&S[i-DP[i]]==S[i+DP[i]])DP[i]++;
			if(i+DP[i]>mx+DP[mx])mx=i;
		}
		int ans=0;
		for(int i=1;i+1<N;i++)if(i-DP[i]+1>0&&i+DP[i]-1<N-1)
		{
			ans=max(ans,min(i,N-1-i));
		}
		printf("%d\n",ans);
	}
	return 0;
}
