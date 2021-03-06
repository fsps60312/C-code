#include<cstdio>
#include<vector>
#include<cmath>
#include<cassert>
using namespace std;
//16^2=((2^2)^2)^2=256
//2^2^2^2=65536
struct Big
{
	vector<int>s;
	Big(){}
	Big(const int v){s.clear(),s.push_back(v);Carry();}
	void Carry()
	{
		for(int i=0;i<s.size();i++)if(s[i]>=10)
		{
			if(i+1==s.size())s.push_back(0);
			s[i+1]+=s[i]/10,s[i]%=10;
		}
	}
	void operator*=(const int a){assert(a>0);for(int &v:s)v*=a;Carry();}
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
		while(c!=-1&&(c<'0'||c>'9'))c=getchar();
		if(c==-1)return false;
		while(c>='0'&&c<='9')stk.push_back(c-'0'),c=getchar();
		assert(!stk.empty());
		s.clear();
		for(int i=stk.size()-1;i>=0;i--)s.push_back(stk[i]);
		for(int i=s.size()-1;i>0&&s[i]==0;i--)s.pop_back();
	}
};
Big N;
vector<int>SEQ[333];//log(10^100)/log(2)
double MX[333];
int Log(const Big &n,const int bse)
{
	Big tmp=bse;
	int ans=0;
	while(tmp<=n)tmp*=bse,ans++;
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	MX[2]=log(log(2.0)),SEQ[2].push_back(2);
	MX[3]=log(log(3.0)),SEQ[3].push_back(3);
	//log(log(a^pow(b)))=log(log(a)*pow(b))=log(log(a))+b
	for(int n=4;n<=332;n++)
	{
		MX[n]=-1e100;
		for(int bse=2;bse*2<=n;bse++)
		{
			int cnt=n/bse;
			assert(cnt>=2);
			const double tmx=log(log(bse))+exp(MX[cnt]);
			if(tmx>MX[n])
			{
				MX[n]=tmx;
				SEQ[n].clear();
				SEQ[n].push_back(bse);
				for(const int v:SEQ[cnt])SEQ[n].push_back(v);
			}
		}
		if(MX[n]<log(log(n)))MX[n]=log(log(n)),SEQ[n].clear(),SEQ[n].push_back(n);
	}
	while(N.Scanf())
	{
		vector<int>ans;
		double mx=-1e100;
		for(int bse=2;bse<=15;bse++)
		{
			const int cnt=Log(N,bse);
			if(cnt==0)break;
			assert(cnt<=332);
			const double tmx=log(log((double)bse))+(cnt==1?0.0:exp(MX[cnt]));
			if(tmx>mx+1e-9)
			{
//				printf("bse=%d,cnt=%d,tmx=%.3f\n",bse,cnt,tmx);
				mx=tmx;
				ans.clear();
				ans.push_back(bse);
				for(const int v:SEQ[cnt])ans.push_back(v);
			}
		}
		assert(mx!=-1e100);
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
9
*/
