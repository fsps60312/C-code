#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int N;
struct LL
{
	vector<int>s;
	LL(){}
	LL(const int v){s.clear();s.push_back(v);}
	void Carry()
	{
		for(int i=0;i<s.size();i++)if(s[i]>=10)
		{
			if(i+1==s.size())s.push_back(0);
			s[i+1]+=s[i]/10,s[i]%=10;
		}
	}
	void operator*=(const int v)
	{
		for(int i=0;i<s.size();i++)s[i]*=v;
		Carry();
	}
	void operator+=(const LL &a)
	{
		for(int i=0;i<a.s.size();i++)s[i]+=a.s[i];
		Carry();
	}
	void Print(){for(int i=s.size()-1;i>=0;i--)putchar('0'+s[i]);}
};
LL DP[801];
//DP[n]=(n-1)*DP[n-1]
int main()
{
	DP[1]=0,DP[2]=1;
	for(int i=3;i<=800;i++)DP[i]=DP[i-1],DP[i]+=DP[i-2],DP[i]*=i-1;
	while(scanf("%d",&N)==1&&N!=-1)
	{
		DP[N].Print();puts("");
	}
	return 0;
}
