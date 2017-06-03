#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int N;
struct LL
{
	vector<char>s;
	LL(){}
	LL(const int v){s.clear();s.push_back(v);}
	void RemoveZero(){for(int i=s.size()-1;i>0&&s[i]==0;i--)s.pop_back();}
	void Carry()
	{
		s.push_back(0);
		for(int i=0;i+1<s.size();i++)s[i+1]+=s[i]/10,s[i]%=10;
		RemoveZero();
	}
	void operator*=(const int v){for(int i=0;i<s.size();i++)s[i]*=v;Carry();}
	void operator+=(const LL &a)
	{
		while(s.size()<a.s.size())s.push_back(0);
		for(int i=0;i<a.s.size();i++)s[i]+=a.s[i];
		Carry();
	}
	void operator-=(const LL &a)
	{
		while(s.size()<a.s.size())s.push_back(0);
		for(int i=0;i<a.s.size();i++)
		{
			s[i]-=a.s[i];
			if(s[i]<0)s[i+1]--,s[i]+=10,assert(s[i]>=0);
		}
		RemoveZero();
	}
	LL operator*(const LL &a)const
	{
		LL ans;
		for(int i=0;i<s.size()+a.s.size();i++)ans.s.push_back(0);
		for(int i=0;i<s.size();i++)
		{
			for(int j=0;j<a.s.size();j++)
			{
				ans.s[i+j]+=s[i]*a.s[j];
				ans.s[i+j+1]+=ans.s[i+j]/10,ans.s[i+j]%=10;
			}
		}
		ans.RemoveZero();
		return ans;
	}
	void Print(){for(int i=s.size()-1;i>=0;i--)putchar('0'+s[i]);}
};
LL C[801][801],LEVEL[801];
int main()
{
	LEVEL[0]=1;
	for(int i=1;i<=800;i++)
	{
		LEVEL[i]=LEVEL[i-1],LEVEL[i]*=i;
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++)C[i][j]=C[i-1][j-1],C[i][j]+=C[i-1][j];
	}
	while(scanf("%d",&N)==1&&N!=-1)
	{
		LL ans=0;
		for(int i=0;i<=N;i++)
		{
			if(i%2==0)ans+=C[N][i]*LEVEL[N-i];
			else ans-=C[N][i]*LEVEL[N-i];
		}
		ans.Print();puts("");
	}
	return 0;
}
