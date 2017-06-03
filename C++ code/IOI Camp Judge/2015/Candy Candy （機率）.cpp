#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
typedef long long LL;
const LL MOD=1000000007;
LL T,n,s,S[20],sum,ans;
LL mod(LL a)
{
	return (a%MOD+MOD)%MOD;
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
		digit.push_back(a);
		carry();
	}
	Big operator+(Big a)
	{
		Big ans=0;
		for(int i=0;i<digit.size();i++) ans.adddigit(digit[i],i);
		for(int i=0;i<a.digit.size();i++) ans.adddigit(a.digit[i],i);
		ans.carry();
		return ans;
	}
	Big operator+=(Big a)
	{
		return (*this)=(*this)+a;
	}
	Big operator-(Big a)
	{
		Big ans=0;
		for(int i=0;i<digit.size();i++) ans.adddigit(digit[i],i);
		for(int i=0;i<a.digit.size();i++) ans.adddigit(-a.digit[i],i);
		ans.carry();
		//printf("\n");print();printf("-");a.print();printf("=");ans.print();printf("\n");
		return ans;
	}
	Big operator-=(Big a)
	{
		return (*this)=(*this)-a;
	}
	Big operator*(Big a)
	{
		Big ans=0;
		for(int i=0;i<digit.size();i++)
		{
			for(int j=0;j<a.digit.size();j++)
			{
				ans.adddigit(digit[i]*a.digit[j],i+j);
			}
		}
		ans.carry();
		return ans;
	}
	Big operator*=(Big a)
	{
		return (*this)=(*this)*a;
	}
	Big operator/(LL a)
	{
		vector<int> ans;
		LL b=0,c=digit.size()-1;
		while(b<a&&c>=0)
		{
			b*=10;
			b+=digit[c];
			c--;
		}
		while(c>=0)
		{
			ans.push_back(b/a);
			b%=a;
			b*=10;
			b+=digit[c];
			c--;
		}
		ans.push_back(b/a);
		Big d=0;
		for(int i=ans.size()-1;i>=0;i--)
		{
			d.digit.push_back(ans[i]);
		}
		d.carry();
		//print();printf("/%lld=",a);d.print();printf("\n");
		return d;
	}
	Big operator/=(LL a)
	{
		return (*this)=(*this)/a;
	}
	void adddigit(int a,int b)
	{
		while(digit.size()<=b) digit.push_back(0);
		digit[b]+=a;
	}
	void carry()
	{
		for(int i=0;i<digit.size();i++)
		{
			if(digit[i]>=10)
			{
				if(i==digit.size()-1)
				{
					digit.push_back(digit[i]/10);
				}
				else digit[i+1]+=digit[i]/10;
				digit[i]%=10;
			}
			else while(digit[i]<0)
			{
				digit[i+1]--;
				digit[i]+=10;
			}
		}
		while(digit.size()&&digit[digit.size()-1]==0) digit.pop_back();
	}
	void print()
	{
		for(int i=digit.size()-1;i>=0;i--)
		{
			printf("%d",digit[i]);
		}
		if(digit.size()==0) printf("0");
	}
};
LL mod(Big a)
{
	//a.print();printf(" ");
	a-=a/MOD*MOD;
	//a.print();//printf("\n");
	LL ans=0;
	if(a.digit.size())
	{
		for(int i=a.digit.size()-1;i>=0;i--)
		{
			ans*=10;
			ans+=a.digit[i];
		}
	}
	//printf(" %lld\n",ans);
	return ans;
}
LL C(LL a,LL b)
{
	if(b<=a/2) b=a-b;
	Big c=1;
	for(int i=1;i<=a-b;i++)
	{
		c*=(b+i);
		c/=i;
		//c.print();printf("\n");
	}
	//printf("C(%lld,%lld)=%lld\n",a,b,mod(c));
	return mod(c);
}
LL H(LL a,LL b)
{
	//a==3,b==5
	//OOOOOXX
	if(b<0) return 0LL;
	return C(a+b-1,b);
}
void dfs(LL a,LL b,LL c)//a(th) kind,minus b kind,remain c candys
{
	if(a==n)
	{
		if(b&1)
		{
			ans-=H(n,c);
			//printf("-%lld\n",H(n,c));
		}
		else
		{
			ans+=H(n,c);
			//printf("+%lld\n",H(n,c));
		}
		ans=mod(ans);
		//printf("ans=%lld\n",ans);
		return;
	}
	dfs(a+1,b,c);
	if(S[a]<c) dfs(a+1,b+1,c-S[a]-1);
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%lld%lld",&n,&s);
		sum=0;
		for(int i=0;i<n;i++)
		{
			scanf("%lld",&S[i]);
			sum+=S[i];
		}
		//take out (sum-s) candy
		//H(n,sum)-H(n,sum-(c1~cn))
		ans=0;
		//printf("take out %lld from {",sum-s);for(int i=0;i<n;i++) printf(" %d",S[i]);printf(" }\n");
		dfs(0,0,sum-s);
		printf("%lld\n",ans);
	}
	return 0;
}
