#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
typedef long long LL;
int K;
LL N;
LL L[7],R[7];
struct Big
{
	vector<LL>s;
	Big(){}
	Big(const LL v)
	{
		s.push_back(v);
		Carry();
	}
	void operator+=(const Big &a)
	{
		while(s.size()<a.s.size())s.push_back(0LL);
		for(int i=0;i<a.s.size();i++)s[i]+=a.s[i];
		Carry();
	}
	void operator-=(const Big &a)
	{
		while(s.size()<a.s.size())s.push_back(0LL);
		for(int i=0;i<a.s.size();i++)s[i]-=a.s[i];
		for(int i=0;i<s.size();i++)if(s[i]<0LL)s[i]+=10LL,s[i+1]--;
		RemoveZero();
	}
	void operator*=(const LL v){for(int i=0;i<s.size();i++)s[i]*=v;Carry();}
	Big operator/(const LL v)const
	{
		LL tmp=0LL;
		vector<LL>stk;
		for(int i=s.size()-1;i>=0;i--)
		{
			tmp*=10LL,tmp+=s[i];
			stk.push_back(tmp/v);
			tmp%=v;
		}
		assert(tmp==0LL);
		Big ans;
		for(int i=stk.size()-1;i>=0;i--)ans.s.push_back(stk[i]);
		ans.RemoveZero();
		return ans;
	}
	void operator/=(const LL v){(*this)=(*this)/v;}
	void RemoveZero(){for(int i=s.size()-1;i>0&&s[i]==0LL;i--)s.pop_back();}
	void Carry()
	{
		for(int i=0;i<s.size();i++)if(s[i]>=10LL)
		{
			if(i+1==s.size())s.push_back(0LL);
			s[i+1]+=s[i]/10LL,s[i]%=10LL;
		}
		RemoveZero();
	}
	void Print()const{for(int i=s.size()-1;i>=0;i--)putchar('0'+s[i]);}
};
Big C(const LL a,const LL b)
{
	if(a<b)return Big(0LL);
	Big ans=Big(1LL);
	for(LL i=a-b+1LL;i<=a;i++)ans*=i,ans/=i-(a-b);
	return ans;
}
Big Solve()
{
	for(int i=0;i<K;i++)N-=L[i],R[i]-=L[i];
	if(N<0)return Big(0);
	vector<Big>posi,nega;
	for(int s=0;s<(1<<K);s++)
	{
		LL n=N;
		bool sign=false;
		for(int i=0;i<K;i++)if(s&(1<<i))
		{
			//i-th exceed R[i]
			n-=R[i]+1LL,sign^=true;
		}
		if(sign)nega.push_back(C(n+K-1LL,K-1LL));
		else posi.push_back(C(n+K-1LL,K-1LL));
	}
	Big ans=Big(0);
	for(const Big &v:posi)ans+=v;
	for(const Big &v:nega)ans-=v;
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%lld",&K,&N)==2)
	{
		for(int i=0;i<K;i++)scanf("%lld%lld",&L[i],&R[i]);
		const Big ans=Solve();
		ans.Print();puts("");
	}
	return 0;
}
