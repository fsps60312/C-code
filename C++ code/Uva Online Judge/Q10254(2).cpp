#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
const char ZERO=0,TEN=10;
struct Big
{
	vector<char>s;
	int sz;
	Big(){}
	Big(const char v){assert(v>=ZERO&&v<TEN);s.clear(),s.push_back(v),sz=1;}
	void Carry()
	{
		for(int i=0;i<sz;i++)if(s[i]>=TEN)
		{
			if(i+1==sz)s.push_back(ZERO),sz++;
			s[i+1]+=s[i]/TEN;
			s[i]%=TEN;
		}
	}
	void operator*=(const char v)
	{
		assert(v>ZERO&&v<TEN);
		for(int i=0;i<sz;i++)s[i]*=v;
		Carry();
	}
	void operator+=(const char v)
	{
		assert(v>ZERO&&v<TEN);
		s[0]+=v;
		for(int i=0;s[i]>=TEN;i++)
		{
			if(i+1==sz)s.push_back(ZERO),sz++;
			s[i+1]+=s[i]/TEN;
			s[i]%=TEN;
		}
	}
	void operator+=(const Big &a)
	{
		for(int i=0;i<a.sz;i++)s[i]+=a.s[i];
		Carry();
	}
	void Print()
	{
		for(int i=sz-1;i>=0;i--)putchar('0'+s[i]);
	}
}F3[10001],F4[10001];
int main()
{
	F3[0]=(char)0;
	for(int i=1;i<=10000;i++)F3[i]=F3[i-1],F3[i]*=(char)2,F3[i]+=(char)1;
	F4[0]=(char)0,F4[1]=(char)1,F4[2]=(char)3;
	for(int k=1,a=1,b=2,i=3;i<=10000;i++,k++)
	{
		F4[i]=F4[k],F4[i]*=(char)2,F4[i]+=F3[i-k];
		if(k==a)a+=(b++),k--;
	}
	static int n;
	while(scanf("%d",&n)==1)F4[n].Print(),puts("");
	return 0;
}
