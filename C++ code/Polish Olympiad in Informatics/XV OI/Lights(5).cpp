#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
LL Gcd(LL a,LL b)
{
	while((a%=b)&&(b%=a));
	return a>b?a:b;
}
void Reduce(LL &a,LL &b,LL &result)
{
	const LL g=Gcd(a,b);
	a/=g,b/=g,result*=g;
}
vector<char>ToString(const vector<LL>&s)
{
	vector<char>ans;
	for(int i=(int)s.size()-1;i>=0;i--)ans.push_back((char)('0'+s[i]));
	return ans;
}
void Mul(vector<LL>&s,const LL val)
{
	for(int i=0;i<(int)s.size();i++)s[i]*=val;
	for(int i=0;i<(int)s.size();i++)if(s[i]>=10)
	{
		if(i+1==(int)s.size())s.push_back(0);
		s[i+1]+=s[i]/10;
		s[i]%=10;
	}
}
void Div(vector<LL>&s,const LL val)
{
	vector<LL>ans;
	LL remain=0;
	for(int i=(int)s.size()-1;i>=0;i--)
	{
		(remain*=10)+=s[i];
		ans.push_back(remain/val);
		remain%=val;
	}
	assert(!remain);
	reverse(ans.begin(),ans.end());
	while(ans.back()==0)ans.pop_back();
	s.swap(ans);
}
int N,S[1000];
vector<vector<char> >ANSU,ANSD;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		vector<LL>upon,down;
		vector<LL>ansu,ansd;
		ansu.push_back(1),ansd.push_back(1);
		ANSU.clear(),ANSD.clear();
		bool zeroed=false;
		for(int i=N-1;i>=0;i--)
		{
			const int val=S[i];
			if(zeroed){vector<char>s;s.push_back('0');ANSU.push_back(s),s[0]='1',ANSD.push_back(s);continue;}
			LL result;
			down.push_back(val),result=1;
			for(int j=0;j<(int)upon.size();j++)Reduce(upon[j],down.back(),result);
			Mul(ansd,down.back());
			Div(ansu,result);
			ANSU.push_back(ToString(ansu)),ANSD.push_back(ToString(ansd));
			if(val==1){zeroed=true;continue;}
			upon.push_back(val-1),result=1;
			for(int j=0;j<(int)down.size();j++)Reduce(upon.back(),down[j],result);
			Mul(ansu,upon.back());
			Div(ansd,result);
		}
		for(int i=N-1;i>=0;i--)
		{
			ANSU[i].push_back('\0'),ANSD[i].push_back('\0');
			printf("%s/%s\n",&ANSU[i][0],&ANSD[i][0]);
		}
	}
	return 0;
}
