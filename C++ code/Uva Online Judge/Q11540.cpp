#include<cstdio>
#include<cstdlib>
#include<vector>
typedef long long LL;
using namespace std;
const LL MOD=1000000007;
LL T,color,now;
char S[10000];
LL gcd(LL a,LL b)
{
	return b==0?a:gcd(b,a%b);
}
struct Big
{
	vector<int> digit;
	Big()
	{
		digit.clear();
	}
	Big(int a)
	{
		digit.clear();
		while(a)
		{
			digit.push_back(a%10);
			a/=10;
		}
	}
	Big operator=(Big a)
	{
		digit.clear();
		for(int i=0;i<a.digit.size();i++) digit.push_back(a.digit[i]);
		return *this;
	}
	void print()
	{
		if(digit.size()) for(int i=digit.size()-1;i>=0;i--) printf("%d",digit[i]);
	}
	Big operator*(Big a)
	{
		Big ans=0;
		for(int i=digit.size()+a.digit.size();i>1;i--) ans.digit.push_back(0);
		for(int i=0;i<digit.size();i++)
		{
			for(int j=0;j<a.digit.size();j++)
			{
				ans.digit[i+j]+=digit[i]*a.digit[j];
			}
		}
		ans.carry();
		//this->print();printf("*");a.print();printf("=");ans.print();printf("\n");
		return ans;
	}
	Big operator*=(Big a)
	{
		return *this=*this*a;
	}
	bool operator==(Big a)
	{
		if(a.digit.size()!=digit.size()) return false;
		for(int i=0;i<digit.size();i++) if(digit[i]!=a.digit[i]) return false;
		return true;
	}
	bool operator!=(Big a)
	{
		return !(*this==a);
	}
	void carry()
	{
		for(int i=0;i<digit.size();i++)
		{
			if(digit[i]>=10)
			{
				if(digit.size()==i+1) digit.push_back(digit[i]/10);
				else digit[i+1]+=digit[i]/10;
				digit[i]%=10;
			}
			if(digit[i]<0)
			{
				digit[i+1]--;
				digit[i]+=10;
			}
		}
		//return;
		while(digit.size()&&digit[digit.size()-1]==0) digit.pop_back();
	}
	Big operator+=(Big a)
	{
		//this->print();printf("+");a.print();printf("=");
		if(a.digit.size()>digit.size())
		{
			for(int i=a.digit.size()-digit.size();i>0;i--)
			{
				digit.push_back(0);
			}
		}
		for(int i=0;i<a.digit.size();i++)
		{
			digit[i]+=a.digit[i];
		}
		carry();
		//this->print();printf("\n");
		return *this;
	}
	Big operator/(LL a)
	{
		vector<int> b;
		LL c=0,d=digit.size()-1;
		while(c<a&&d>=0)
		{
			c*=10;
			c+=digit[d];
			d--;
		}
		while(1)
		{
			b.push_back(c/a);
			if(d<0) break;
			c%=a;
			c*=10;
			c+=digit[d];
			d--;
		}
		Big ans=0;
		if(b.size()) for(int i=b.size()-1;i>=0;i--) ans.digit.push_back(b[i]);
		//print();printf("/");printf("%lld",a);ans.print();printf("=");printf("\n");
		return ans;
	}
	Big operator-(Big a)
	{
		Big ans=0;
		for(int i=0;i<digit.size();i++) ans.digit.push_back(digit[i]); 
		for(int i=0;i<a.digit.size();i++)
		{
			ans.digit[i]-=a.digit[i];
		}
		ans.carry();
		//this->print();printf("-");a.print();printf("=");ans.print();printf("\n");
		return ans;
	}
	Big operator%(LL a)
	{
		//print();printf("\n");
		return *this-*this/a*a;
	}
};
struct treap
{
	Big n;
	void reset()
	{
		n=-1;
		ch.clear();
	}
	void set()
	{
		//printf("%s\n",&S[now]);
		now++;
		while(S[now]!=']'&&S[now])
		{
			LL i=ch.size();
			treap j;
			j.reset();
			ch.push_back(j);
			ch[i].set();
		}
		now++;
		if(S[now]==',') now++;
		return;
	}
	vector<treap> ch;
	bool operator==(treap a)
	{
		if(a.ch.size()!=ch.size()) return false;
		for(LL i=0;i<ch.size();i++)
		{
			if(!(a.ch[i]==ch[i])) return false;
		}
		return true;
	}
	Big cal()
	{
		if(n!=-1) return n;
		if(ch.size()==0) return n=color;
		Big ans=1;
		for(LL i=0;i<ch.size();i++)
		{
			ans*=ch[i].cal();
			//ans%=MOD;
		}
		LL div=1;
		for(LL i=1;i<ch.size();i++)
		{
			bool canfix=true;
			for(LL j=0;j<ch.size();j++)
			{
				if(!(ch[j]==ch[(j+i)%ch.size()]))
				{
					canfix=false;
					break;
				}
			}
			if(canfix)
			{
				Big k=1;
				for(LL j=gcd(i,ch.size())-1;j>=0;j--)
				{
					k*=ch[j].cal();
				}
				ans+=k;
				div++;
			}
		}
		return ans*color/div;
	}
};
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%lld",&T);
	for(LL kase=1;kase<=T;kase++)
	{
		scanf("%s%lld",S,&color);
		now=0;
		Big ans=1;
		while(S[now]=='[')
		{
			treap a;
			a.reset();
			a.set();
			//if(a.ch.size()>=2) printf("%lld\n",a.ch[0]==a.ch[1]);
			ans*=a.cal();
			ans=ans%MOD;
			//printf("%d\n",now);
		}
		LL b=0;
		if(ans.digit.size())
		{
			for(int i=ans.digit.size()-1;i>=0;i--)
			{
				b*=10;
				b+=ans.digit[i];
			}
		}
		//ans.print();printf("\n");
		printf("Case #%lld: %lld\n",kase,b);
	}
	return 0;
}
