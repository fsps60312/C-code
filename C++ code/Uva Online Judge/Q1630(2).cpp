#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int N;
char S[101];
vector<char>DP[100][100];
int GetCycle(const int l,const int r)
{
	
}
vector<char>&GetDP(const int l,const int r)
{
	vector<char>&dp=DP[l][r];
	if(!dp.empty())return dp;
	for(int i=l;i<=r;i++)dp.push_back(S[i]);
	if(r-l<2)return dp;
	for(int gap=1;gap*2<=r-l+1;gap++)if((r-l+1)%gap==0)
	{
		const int n=(r-l+1)/gap;
		assert(n>=2);
		bool valid=true;
		const vector<char>&seg=GetDP(l,l+gap-1);
		for(int j=1;j<n;j++)if(!Same(seg,GetDP(l+j*gap,l+j*gap+gap-1))){valid=false;break;}
		if(!valid)continue;
		vector<char>ta;
		if(n>=100)ta.push_back('0'+n/100);
		if(n>=10)ta.push_back('0'+n/10%10);
		ta.push_back('0'+n%10);
		ta.push_back('(');
		for(const auto c:seg)ta.push_back(c);
		ta.push_back(')');
		if(ta.size()<dp.size())dp=ta;
		break;
	}
	for(int i=l;i<r;i++)
	{
		vector<char>ta;
		const vector<char>&dpl=GetDP(l,i),&dpr=GetDP(i+1,r);
		for(const char c:dpl)ta.push_back(c);
		for(const char c:dpr)ta.push_back(c);
		if(ta.size()<dp.size())dp=ta;
	}
	return dp;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%s",S)==1)
	{
		N=-1;while(S[++N]);
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)DP[i][j].clear();
		vector<char>ans=GetDP(0,N-1);
		ans.push_back('\0');
		printf("%s\n",&ans[0]);
	}
	return 0;
}
