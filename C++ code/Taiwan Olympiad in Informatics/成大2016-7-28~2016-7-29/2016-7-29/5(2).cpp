#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
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
Big Gcd(Big a,Big b)
{
	if(b==Big(0))return a;
	return Gcd(b,a%b);
}
struct Fraction
{
	Big UPON,DOWN;
	Fraction(){}
	Fraction(const Big _UPON,const Big _DOWN):UPON(_UPON),DOWN(_DOWN)
	{
		Big g=Gcd(UPON,DOWN);
		UPON=UPON/g,DOWN=DOWN/g;
	}
};
Fraction operator*(const Fraction &a,const Fraction &b){return Fraction(a.UPON*b.UPON,a.DOWN*b.DOWN);}
Fraction operator+(const Fraction &a,const Fraction &b)
{
	Big c=a.UPON*b.DOWN,d=b.UPON*a.DOWN;
	return Fraction(c+d,a.DOWN*b.DOWN);
}
int N,S[5];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		int SUM=0;
		for(int i=0;i<N;i++)scanf("%d",&S[i]),SUM+=S[i];
		Fraction ans=Fraction(0,1);
		for(int color=0;color<N;color++)
		{
			static Fraction dp[251][51];
			for(int i=0;i<=SUM;i++)for(int j=0;j<=S[color];j++)dp[i][j]=Fraction(0,1);
			dp[SUM][S[color]]=Fraction(1,1);
			for(int i=SUM;i>=1;i--)
			{
				for(int remain=1;remain<=S[color];remain++)
				{
					const Fraction &d=dp[i][remain];
					if(i==remain)ans=ans+Fraction(SUM-remain,1)*d;
					else
					{
						dp[i-1][remain]=dp[i-1][remain]+d*Fraction(i-remain,i);
						dp[i-1][remain-1]=dp[i-1][remain-1]+d*Fraction(remain,i);
					}
				}
			}
		}
		ans.DOWN.rintf(),putchar(' '),ans.UPON.rintf();puts("");
	}
	return 0;
}
