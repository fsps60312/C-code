#include<cstdio>
#include<vector>
using namespace std;
int N,D;
struct LL
{
	vector<char>s;
	LL(){}
	LL(const int v){s.clear(),s.push_back(v);}
	void operator+=(const LL &v)
	{
		while(s.size()<v.s.size())s.push_back(0);
		for(int i=0;i<v.s.size();i++)s[i]+=v.s[i];
		s.push_back(0);
		for(int i=0;i+1<s.size();i++)s[i+1]+=s[i]/10,s[i]%=10;
		for(int i=s.size()-1;i>0&&s[i]==0;i--)s.pop_back();
	}
	void Print()const{for(int i=s.size()-1;i>=0;i--)putchar('0'+s[i]);}
};
LL DP[300][151][2];
LL Solve()
{
	if((N&1)==1)return LL(0);
	for(int i=0;i<=D;i++)DP[0][i][0]=DP[0][i][1]=0;
	DP[0][1][D==1?1:0]=1;
	for(int i=1;i<N;i++)
	{
		for(int j=0;j<D;j++)
		{
			DP[i][j][0]=0;
			if(j+1<D)DP[i][j][0]+=DP[i-1][j+1][0];
			if(j-1>=0)DP[i][j][0]+=DP[i-1][j-1][0];
		}
		for(int j=0;j<=D;j++)
		{
			DP[i][j][1]=0;
			if(j+1<=D)DP[i][j][1]+=DP[i-1][j+1][1];
			if(j-1>=0)DP[i][j][1]+=DP[i-1][j-1][1];
		}
		DP[i][D][1]+=DP[i-1][D-1][0];
	}
	return DP[N-1][0][1];
}
int main()
{
	while(scanf("%d%d",&N,&D)==2)
	{
		const LL &ans=Solve();
		ans.Print();puts(""); 
	}
	return 0;
}
