#include<cstdio>
#include<cstdlib>
int n,k;
const int errorrate=25;
class Big
{
	public:
	double n;
	int digit;
	Big(int a)
	{
		n=0,digit=0;
	}
	Big operator=(int a)
	{
		n=0,digit=0;
		return *this;
	}
	Big operator*=(Big a)
	{
		n*=a.n;
		digit+=a.digit;
		carry();
		return *this;
	}
	Big operator/=(Big a)
	{
		n/=a.n;
		digit-=a.digit;
		carry();
		return *this;
	}
	Big operator-=(Big a)
	{
		a.n*=-1;
		return *this+=a;
	}
	Big operator+=(Big a)
	{
		int b=digit-a.digit;
		if(b>errorrate) return *this;
		if(b<-errorrate) return a;
		while(digit>a.digit)
		{
			a.n/=10;
			a.digit++;
		}
		while(digit<a.digit)
		{
			n/=10;
			digit++;
		}
		n+=a.n;
		carry();
		return *this;
	}
	void carry()
	{
		if(n==0)
		{
			digit=0;
		}
		else if(n>0)
		{
			while(n>=10)
			{
				n/=10;
				digit++;
			}
			while(n<1)
			{
				n*=10;
				digit--;
			}
		}
		else
		{
			while(n<=-10)
			{
				n/=10;
				digit++;
			}
			while(n>-1)
			{
				n*=10;
				digit--;
			}
		}
	}
};
Big C(int a,int b)
{
	Big ans=0;
	if(a>b) return ans;
	ans.n=1;
	for(int i=1;i<=b-a;i++)
	{
		ans.n*=a+i;
		ans.n/=i;
		ans.carry();
	}
	return ans;
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int kase=0;
	while(scanf("%d%d",&n,&k)==2&&(n||k))
	{
		kase++;
		if(n==1) printf("Case %d: %.4lf\n",kase,0.0);
		else if(n-1<2*k) printf("Case %d: %.4lf\n",kase,(double)n);
		else
		{
			Big ans1=0;
			//C(k,n-1)+C(k-1,n-1)=C(k,n)
			//C(k+1,n-1)+C(k,n-1)=C(k+1,n)
			//	denominator:
			//C(2k,n-1)
			//	element1:
			//C(2k,n-1-2k)+C(2k,n-1-2k+1)+C(2k,n-1-2k+2)+...+C(2k,n-1-2k+k)
			//	C(2k+1,n-1-2k)+element1:
			//C(2k+1,n-1-2k)+C(2k,n-1-2k)+C(2k,n-1-2k+1)+...
			//=C(2k+1,n-1-2k+1)+C(2k,n-1-2k+1)+C(2k,n-1-2k+2)+...+C(2k,n-1-2k+k)
			//=C(2k+1,n-1-2k+2)+C(2k,n-1-2k+2)+...+C(2k,n-1-2k+k)
			//=C(2k+1,n-1-2k+k-1)+C(2k,n-1-2k+k)
			//=C(2k+1,n-1-2k+k+1)
			//C(2,2)
			ans1=C(2*k+1,n-k);//C(3,4)
			//printf("%lf %d\n",ans1.n,ans1.digit);
			ans1-=C(2*k+1,n-1-2*k);
			//printf("%lf %d\n",ans1.n,ans1.digit);
			ans1.n*=2;
			ans1.carry();
			//printf("%lf %d\n",ans1.n,ans1.digit);
			Big ans2=C(2*k,n-1-2*k);//C(2,3)
			ans2.n*=n-2*k-2;
			ans2.carry();
			//*(n-2k-2):C(2k,n-1-2k+k)
			//printf("+%lf %d\n",ans2.n,ans2.digit);
			ans1+=ans2;
			//printf("%lf %d\n",ans1.n,ans1.digit);
			ans1.n/=n;
			ans1/=C(2*k,n-1);//C(2,4)
			//printf("%lf %d\n",ans1.n,ans1.digit);
			while(ans1.digit>0)
			{
				ans1.n*=10;
				ans1.digit--;
			}
			while(ans1.digit<0)
			{
				ans1.n/=10;
				ans1.digit++;
			}
			printf("Case %d: %.4lf\n",kase,(1-ans1.n)*n);//1e-25有加沒加都WA 
		}
	}
	return 0;
}
