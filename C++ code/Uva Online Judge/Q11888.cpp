#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
int T,N;
char INPUT[200002];
vector<char>S;
vector<int>DP;
vector<bool>VIS;
int Solve()
{
	DP.resize(N);
	DP[0]=1;
	for(int i=1,mx=0;i<N;i++)
	{
		if(mx+DP[mx]-1>=i)DP[i]=min(mx+DP[mx]-1-i+1,DP[mx-DP[mx]+1]);
		else DP[i]=1;
		while(i-DP[i]>=0&&i+DP[i]<N&&S[i-DP[i]]==S[i+DP[i]])DP[i]++;
		if(i+DP[i]>mx+DP[mx])mx=i;
	}
	VIS.clear();
	for(int i=0;i<N;i++)VIS.push_back(false);
	for(int i=1;i<N;i++)if(i-DP[i]+1==0)VIS[i+DP[i]-1]=true;
//	for(int i=0;i<N;i++)printf("%d",(int)VIS[i]);puts("");
	for(int i=0;i+1<N;i++)if(i+DP[i]-1==N-1&&VIS[i-DP[i]+1])return 2;
	if(VIS[N-1])return 1;
	return 0;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		assert(scanf("%s",INPUT)==1);
		N=-1;
		while(INPUT[++N])
		{
			if(INPUT[N]=='\n'){INPUT[N]='\0';break;}
			assert(N<200002);
		}
		S.clear(),S.push_back('\0');
		for(int i=0;i<N;i++)S.push_back(INPUT[i]),S.push_back('\0');
		N=S.size();
		int ans=Solve();
		if(ans==0)puts("simple");
		else if(ans==1)puts("palindrome");
		else if(ans==2)puts("alindrome");
		else assert(0);
	}
	return 0;
}
