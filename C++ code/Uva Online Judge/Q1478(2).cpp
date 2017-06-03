#include<cstdio>
#include<vector>
using namespace std;
#define LL long long
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
const LL BigCarry=1000000000LL;
LL N,K;
struct Big
{
	vector<LL> d;
	Big(LL a){d.push_back(a);}
	void operator+=(Big a)
	{
		while(d.size()<a.d.size())d.push_back(0LL);
		for(int i=0;i<a.d.size();i++)d[i]+=a.d[i];
		carry();
	}
	void operator*=(LL a)
	{
		for(int i=0;i<d.size();i++)d[i]*=a;
		carry();
	}
	void operator/=(LL a)
	{
		LL remain=0LL;
		for(int i=d.size()-1;i>=0;i--)
		{
			remain=remain*BigCarry+d[i];
			d[i]=remain/a;
			remain%=a;
		}
		if(remain!=0LL)termin();
		rem0();
	}
	void rem0()
	{
		for(int sz=d.size()-1;sz>0&&!d[sz];sz--)d.pop_back();
	}
	void carry()
	{
		LL carry=0LL;
		for(int i=0;;i++)
		{
			d[i]+=carry;
			carry=d[i]/BigCarry;
			d[i]%=BigCarry;
			if(i+1==d.size())
			{
				if(carry)d.push_back(0LL);
				else break;
			}
		}
	}
	void rintf()
	{
		int i=d.size()-1;if(i>9)i=9;
		while(!d[i]&&i>0)i--;
		printf("%lld",d[i]);
		for(i--;i>=0;i--)printf("%09d",d[i]);
		printf("\n");
	}
};
int main()
{
//K ups and K downs: C(N,2K)*(C(2K,K)-C(2K,K+1))
//=N!/(2K)!/(N-2K)!*((2K)!/K!/K!-(2K)!/(K+1)!/(K-1)!)
//=N!/(N-2K)!*(((K+1)!(K-1)!-K!K!) / K!K!(K+1)!(K-1)!)
//=N!/(N-2K)!*((K-1)!(K-1)!K / K!K!(K+1)!(K-1)!)
//=N!/(N-2K)!*(1 / K!(K+1)!)
//=N!/K!(K+1)!(N-2K)!
//=A_K
//A_(K+1)=N!/(K+1)!(K+2)!(N-2K-2)!
//=A_K*(N-2K)(N-2K-1)/(K+1)(K+2)
//	Big a=BigCarry;
//	a.rintf();
//	a*=BigCarry;
//	a.rintf();
//	a*=BigCarry;
//	a.rintf();
//	a*=BigCarry;
//	a.rintf();
//	a*=BigCarry;
//	a.rintf();
//	a*=BigCarry;
//	a.rintf();
//	a/=BigCarry;
//	a.rintf();
//	a/=BigCarry;
//	a.rintf();
//	a/=BigCarry;
//	a.rintf();
//	a/=BigCarry;
//	a.rintf();
//	a/=BigCarry;
//	a.rintf();
	while(scanf("%lld",&N)==1)
//	for(N=3;N<=10000;N++)
	{
		Big tmp=1LL;
		Big ans=0LL;//+=tmp
		for(K=0LL;(K<<1)<=N;K++)
		{
			ans+=tmp;
			tmp*=(N-(K<<1))*(N-(K<<1)-1LL);
			tmp/=(K+1LL)*(K+2LL);
		}
//		printf("%d\n",N);
		ans.rintf();
	}
	return 0;
}
