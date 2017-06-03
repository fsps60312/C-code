#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int Gcd(int a,int b)
{
	while((a%=b)&&(b%=a));
	return a>b?a:b;
}
void Reduce(int &a,int &b)
{
	const int g=Gcd(a,b);
	a/=g,b/=g;
}
vector<char>ToString(const vector<int>&s)
{
	vector<int>a;
	a.push_back(1);
	for(int i=0;i<(int)s.size();i++)
	{
		for(int j=0;j<(int)a.size();j++)a[j]*=s[i];
		for(int j=0;j<(int)a.size();j++)if(a[j]>=10)
		{
			if(j+1==(int)a.size())a.push_back(0);
			a[j+1]+=a[j]/10;
			a[j]%=10;
		}
	}
	vector<char>ans;
	for(int i=(int)a.size()-1;i>=0;i--)ans.push_back((char)('0'+a[i]));
	return ans;
}
int N,S[1000];
vector<vector<char> >ANSU,ANSD;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		bool zeroed=false;
		vector<int>upon,down;
		ANSU.clear(),ANSD.clear();
		for(int i=N-1;i>=0;i--)
		{
			const int val=S[i];
			if(val==1)zeroed=true;
			if(zeroed){vector<char>s;s.push_back('0');ANSU.push_back(s),s[0]='1',ANSD.push_back(s);continue;}
			down.push_back(val);
			for(int j=0;j<(int)upon.size();j++)Reduce(upon[j],down.back());
			ANSU.push_back(ToString(upon)),ANSD.push_back(ToString(down));
			upon.push_back(val-1);
			for(int j=0;j<(int)down.size();j++)Reduce(upon.back(),down[j]);
		}
		for(int i=N-1;i>=0;i--)
		{
			ANSU[i].push_back('\0'),ANSD[i].push_back('\0');
			printf("%s/%s\n",&ANSU[i][0],&ANSD[i][0]);
		}
	}
	return 0;
}
