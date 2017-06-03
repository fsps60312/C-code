#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
int N;
struct Fraction
{
	LL up,down;
	Fraction(){}
	Fraction(const LL v):up(v),down(1LL){}
	Fraction(const LL _u,const LL _d):up(_u),down(_d){}
	LL Gcd(const LL &a,const LL &b){return b?Gcd(b,a%b):a;}
	void Carry()
	{
		assert(up>=0LL&&down>0LL);
		LL g=Gcd(up,down);
		up/=g,down/=g;
	}
	bool operator!=(const Fraction &f)const{return up!=f.up||down!=f.down;}
	Fraction operator+(const Fraction &f)const
	{
		Fraction ans=Fraction(up*f.down+f.up*down,down*f.down);
		ans.Carry();
		return ans;
	}
}DP[34],NONE=Fraction(-1);
const Fraction &GetDP(const int remain)
{
	Fraction &dp=DP[remain];
	if(dp!=NONE)return dp;
	//DP[i]==1+i/N*DP[i-1]+(N-i)/N*DP[i]
	//DP[i]*i/N==1+i/N*DP[i-1]
	//DP[i]==N/i+DP[i-1]
	return dp=Fraction(N,remain)+GetDP(remain-1);
}
void FillVector(LL n,vector<char>&ans)
{
	vector<char>tmp;
	tmp.push_back('0'+n%10LL),n/=10LL;
	while(n)tmp.push_back('0'+n%10LL),n/=10LL;
	for(int i=tmp.size()-1;i>=0;i--)ans.push_back(tmp[i]);
}
int main()
{
	while(scanf("%d",&N)==1)
	{
		DP[0]=Fraction(0);
		for(int i=1;i<=N;i++)DP[i]=NONE;
		Fraction ans=GetDP(N);
		if(ans.down==1LL)printf("%d\n",ans.up);
		else
		{
			vector<char>integer,up,down;
			FillVector(ans.up/ans.down,integer);
			ans.up%=ans.down;
			FillVector(ans.up,up);
			FillVector(ans.down,down);
			integer.push_back('\0'),up.push_back('\0'),down.push_back('\0');
			for(int i=0;i<integer.size();i++)putchar(' ');puts(&up[0]);
			printf("%s ",&integer[0]);for(int i=1;i<up.size()||i<down.size();i++)putchar('-');puts("");
			for(int i=0;i<integer.size();i++)putchar(' ');puts(&down[0]);
		}
	}
	return 0;
}
