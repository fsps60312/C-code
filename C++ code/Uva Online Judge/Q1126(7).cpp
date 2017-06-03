#include<cstdio>
#include<vector>
#include<cmath>
#include<cassert>
using namespace std;
const double INF=1e100,EPS=1e-9;
struct Big
{
	vector<int>s;
	Big(){}
	Big(const int v){s.clear(),s.push_back(v);Carry();Check();}
	void Check()
	{
		assert(!s.empty());
		assert(s[s.size()-1]>=1&&s[s.size()-1]<=9);
		for(int i=0;i<s.size();i++)assert(s[i]>=0&&s[i]<=9);
	}
	void Carry()
	{
		for(int i=0;i<s.size();i++)if(s[i]>=10)
		{
			if(i+1==s.size())s.push_back(0);
			s[i+1]+=s[i]/10,s[i]%=10;
		}
	}
	void operator*=(const int a){assert(a>0);for(int &v:s)v*=a;Carry();Check();}
	bool operator<=(const Big &a)const
	{
		if(s.size()!=a.s.size())return s.size()<a.s.size();
		for(int i=s.size()-1;i>=0;i--)if(s[i]!=a.s[i])return s[i]<a.s[i];
		return true;
	}
	bool Scanf()
	{
		vector<int>stk;
		char c=getchar();
		while(c!=-1&&(c<'0'||c>'9'))assert(c==' '||c=='\n'||c=='\t'),c=getchar();
		if(c==-1)return false;
		while(c>='0'&&c<='9')stk.push_back(c-'0'),c=getchar();
		assert(!stk.empty());
		s.clear();
		for(int i=stk.size()-1;i>=0;i--)s.push_back(stk[i]);
		for(int i=s.size()-1;i>0&&s[i]==0;i--)s.pop_back();
		Check();
		return true;
	}
};
Big N;
vector<int>SEQ_BASE[333];//log(10^100)/log(2)
double MX_BASE[333];
double &Mx(const int i){assert(i>=0&&i<333);return MX_BASE[i];}
vector<int>&Seq(const int i){assert(i>=0&&i<333);return SEQ_BASE[i];}
int Log(const Big &n,const int bse)
{
	Big tmp=bse;
	int ans=0;
	while(tmp<=n)tmp*=bse,ans++;
	return ans;
}
int main()
{
	//a^b^c^d
	//b^c^d log a
	//log(log(a))+c^d*log(b)
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	for(int i=1;i<=332;i++)Mx(i)=-INF,Seq(i).clear();
	Mx(1)=1.0;
	Mx(2)=2.0,Seq(2).push_back(2);
	Mx(3)=3.0,Seq(3).push_back(3);
	for(int n=4;n<=332;n++)
	{
		for(int bse=2;bse*2<=n;bse++)
		{
			int cnt=n/bse;
			assert(cnt>=2);
			const double tmx=(Mx(cnt)==INF||log(bse)*Mx(cnt)>=log(INF)?INF:pow(bse,Mx(cnt)));
			if(tmx>Mx(n)+EPS)
			{
				Mx(n)=tmx;
				Seq(n).clear();
				Seq(n).push_back(bse);
				for(const int v:Seq(cnt))Seq(n).push_back(v);
			}
		}
		if((double)n>Mx(n)+EPS)Mx(n)=n,Seq(n).clear(),Seq(n).push_back(n);
//		printf("%d:",n);for(const auto v:SEQ[n])printf(" %d",v);puts("");
//		printf("%.0f\n",MX[n]);
	}
//	return 0;
	while(N.Scanf())
	{
		vector<int>ans;
		double mx=-INF;
		for(int bse=2;bse<=15;bse++)
		{
			const int cnt=Log(N,bse);
			if(cnt==0)break;
			const double tmx=(Mx(cnt)==INF?INF:log((double)bse)*Mx(cnt));
			if(tmx>mx+EPS)
			{
				mx=tmx;
				ans.clear();
				ans.push_back(bse);
				for(const int v:Seq(cnt))ans.push_back(v);
			}
		}
		if(mx<INF)
		{
			double n=0.0;for(int i=N.s.size()-1;i>=0;i--)n*=10.0,n+=N.s[i];
			if(mx<log(n))mx=log(n),ans.clear(),ans.push_back((int)(n+0.5));
		}
		assert(mx!=-INF);
		for(int i=0;i<ans.size();i++)
		{
			if(i)putchar('^');
			printf("%d",ans[i]);
		}
		puts("");
	}
	return 0;
}
/*
16 80 49 1025 12341234 12345678901234567890
*/
