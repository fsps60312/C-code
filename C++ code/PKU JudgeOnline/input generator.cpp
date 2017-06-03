#include<cstdio>
#include<cstdlib>
#include<cassert>
#include<ctime>
#include<set>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
#include<map>
#define LL long long
#define cout(...) fprintf(in,##__VA_ARGS__)
//FC "C:\Users\Burney\Desktop\C++ Code\Uva Online Judge\new.txt" "C:\Users\Burney\Desktop\C++ Code\Uva Online Judge\out.txt" /n
using namespace std;
struct Big
{
	vector<char>d;
	bool nega;
	Big(){d.clear();nega=false;}
	Big(LL a){nega=a<0LL;if(a<0LL)a=-a;d.clear();while(a)d.push_back(a%10),a/=10;}
	Big(const Big &a){nega=a.nega;d.clear();for(int i=0;i<(int)a.d.size();i++)d.push_back(a.d[i]);}
	void showd(){for(int i=0;i<(int)d.size();i++)printf("%ddigit: %d\n",i,(int)d[i]);}
	void carry()
	{
		if(!d.size()){nega=false;return;}
		index1:;
		for(int i=0;;i++)
		{
			int a=(d[i]%10+10)%10;
			if(i+1==(int)d.size())
			{
				if(d[i]>a)d.push_back(0);
				else if(d[i]<a)
				{
					nega^=true;
					for(int j=0;j<(int)d.size();j++)d[j]*=-1;
					goto index1;
				}
				else break;
			}
			d[i+1]+=(d[i]-a)/10;
			d[i]=a;
		}
		if(!d.size()){nega=false;return;}
		for(int i=d.size()-1;i>=0&&d[i]==0;i--)d.pop_back();
		if(!d.size()){nega=false;return;}
	}
	void rintf()
	{
		if(nega)printf("-");
		if(!d.size()){printf("0");return;}
		for(int i=d.size()-1;i>=0;i--)printf("%d",d[i]);
	}
	char* c_str()
	{
		char *ans=new char[d.size()+2];
		int i=0;
		if(nega)ans[i++]='-';
		if(!d.size())ans[i++]='0';
		else for(int j=d.size()-1;j>=0;i++,j--)ans[i]='0'+d[j];
		ans[i]=0;
		return ans;
	}
	void AddDigits(const Big &a)
	{
		while(d.size()<a.d.size())d.push_back(0);
		for(int i=0;i<(int)a.d.size();i++)d[i]+=a.d[i];
		carry();
	}
	void MinusDigits(const Big &a)
	{
		while(d.size()<a.d.size())d.push_back(0);
		for(int i=0;i<(int)a.d.size();i++)d[i]-=a.d[i];
		carry();
	}
	Big DigitsMoveLeft(int m=1)
	{
		Big ans=Big();
		while(m--)ans.d.push_back(0);
		for(int i=0;i<(int)d.size();i++)ans.d.push_back(d[i]);
		return ans;
	}
	Big DigitsMoveRight(int m=1)
	{
		Big ans=Big();
		for(int i=0;i<(int)d.size();i++)
		{
			if(i<m)assert(!d[i]&&"should be zero on the right\n");
			ans.d.push_back(d[i]);
		}
		return ans;
	}
	Big Abs(){Big ans=Big(*this);ans.nega=0;return ans;}
	bool operator!()const{return !d.size();}
	bool operator==(const Big &a)const{if(d.size()!=a.d.size())return false;for(int i=0;i<(int)d.size();i++)if(d[i]!=a.d[i])return false;return true;}
	bool operator!=(const Big &a)const{return !((*this)==a);}
	bool operator<(const Big &a)const
	{
		if(nega!=a.nega)return nega;
		if(d.size()!=a.d.size())return (d.size()<a.d.size())^nega;
		if(!d.size())return false;
		for(int i=d.size()-1;i>=0;i--)if(d[i]!=a.d[i])return (d[i]<a.d[i])^nega;
		return false;
	}
	bool operator>(const Big &a)const
	{
		if(nega!=a.nega)return a.nega;
		if(d.size()!=a.d.size())return (d.size()>a.d.size())^nega;
		if(!d.size())return false;
		for(int i=d.size()-1;i>=0;i--)if(d[i]!=a.d[i])return (d[i]>a.d[i])^nega;
		return false;
	}
	bool operator<=(const Big &a)const
	{
		if(nega!=a.nega)return nega;
		if(d.size()!=a.d.size())return (d.size()<a.d.size())^nega;
		if(!d.size())return true;
		for(int i=d.size()-1;i>=0;i--)if(d[i]!=a.d[i])return (d[i]<a.d[i])^nega;
		return true;
	}
	bool operator>=(const Big &a)const
	{
		if(nega!=a.nega)return a.nega;
		if(d.size()!=a.d.size())return (d.size()>a.d.size())^nega;
		if(!d.size())return true;
		for(int i=d.size()-1;i>=0;i--)if(d[i]!=a.d[i])return (d[i]>a.d[i])^nega;
		return true;
	}
	Big operator+(Big &a)
	{
		Big ans=Big();
		if(nega==a.nega)
		{
			ans.AddDigits(*this);
			ans.AddDigits(a);
			ans.nega=nega;
		}
		else
		{
			bool thisnega=nega;
			nega=a.nega=false;
			if((*this)>a)
			{
				ans.AddDigits(*this);
				ans.MinusDigits(a);
				ans.nega=thisnega;
			}
			else
			{
				ans.AddDigits(a);
				ans.MinusDigits(*this);
				ans.nega=thisnega^true;
			}
			nega=thisnega,a.nega=thisnega^true;
		}
		ans.carry();
		return ans;
	}
	Big operator-()
	{
		Big ans=Big(*this);
		ans.nega^=true;
		ans.carry();
		return ans;
	}
	Big operator-(Big &a)
	{
		a.nega^=true;
		Big ans=(*this)+a;
		a.nega^=true;
		return ans;
	}
	Big operator*(const Big &a)const
	{
		if(!(*this)||!a)return Big();
		Big ans=Big();
		ans.nega=nega^a.nega;
		for(int i=0,limit=d.size()+a.d.size();i<limit;i++)ans.d.push_back(0);
		for(int i=0;i<(int)d.size();i++)
		{
			for(int j=0;j<(int)a.d.size();j++)
			{
				ans.d[i+j]+=d[i]*a.d[j];
				ans.d[i+j+1]+=ans.d[i+j]/10;
				ans.d[i+j]%=10;
			}
		}
		ans.carry();
		return ans;
	}
	Big operator/(Big &a)
	{
		if(!(*this)||Abs()<a.Abs())return Big();
		Big tmp=Big(*this),ans=Big();
		tmp.nega=false;
		for(int i=0,limit=d.size()-a.d.size();i<=limit;i++)ans.d.push_back(0);
		for(int i=d.size()-a.d.size();i>=0;i--)
		{
			char &_=ans.d[i];
			Big b=a.DigitsMoveLeft(i).Abs();
			while(tmp>=b)tmp-=b,_++;
			assert(_<10&&"digit exceed range when div: _\n");
		}
		assert(tmp<a.Abs()&&"can't full divided: tmp");
		ans.nega=nega^a.nega;
		ans.carry();
		return ans;
	}
	Big operator%(Big &a){Big div=((*this)/a)*a;return (*this)-div;}
	Big operator+=(Big &a){return (*this)=(*this)+a;}
	Big operator-=(Big &a){return (*this)=(*this)-a;}
	Big operator*=(Big &a){return (*this)=(*this)*a;}
	Big operator/=(Big &a){return (*this)=(*this)/a;}
	Big operator%=(Big &a){return (*this)=(*this)%a;}
};
int ran()
{
	int j=rand(),k=10;while(k--)j*=rand(),j+=rand();
	return j;
}
int ran(int minval,int maxval)
{
	int j=ran();
	j%=(maxval-minval+1);
	if(j<0)j+=(maxval-minval+1);
	return minval+j;
}
LL ranL()
{
	LL j=rand(),k=10;while(k--)j*=rand(),j+=rand();
	return j;
}
LL ranL(LL minval,LL maxval)
{
	LL j=ran();
	j%=(maxval-minval+1LL);
	if(j<0)return j+maxval+1LL;
	return j+minval;
}
unsigned long long ranLU()
{
	unsigned long long j=rand(),k=10;while(k--)j*=rand(),j+=rand();
	return j;
}
FILE *in;
//////////////////////////////////////////////////////////////////////////////
int main()
{
	srand(time(NULL));
	in=fopen("in.txt","w");
//	cout("10\n");
	for(int testcase=1;testcase<=10;testcase++)
	{
		printf("case %d...\n",testcase);
		if(testcase>1)cout("\n");
		int N=ran(100000,100000);
		cout("%d\n",N);
		for(int i=0;i<N;i++)cout("%d ",1000000000);cout("\n");
	}
	cout("0\n");
	return 0;
}
