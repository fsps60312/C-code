#include<cstdio>
#include<cstdlib>
const double exp=1e-100;
int T,n;
double S,digit[100];
int abs(double a)
{
	return a>=0?a:-a;
}
struct largenum
{
	int d;
	double n;//n*10^d
	void refresh()
	{
		if(abs(n)<exp)
		{
			n=0;
			d=0;
			return;
		}
		while(abs(n)>=10)
		{
			n/=10;
			d++;
		}
		while(abs(n)<1)
		{
			n*=10;
			d--;
		}
	}
	double toshow()
	{
		if(d>0)
		{
			return n*digit[d];
		}
		return n/digit[-d];
	}
};
largenum level[50000],pow[50000];
largenum mul(largenum a,double b)
{
	largenum ans;
	ans.n=a.n*b;
	ans.d=a.d;
	ans.refresh();
	return ans;
}
largenum add(largenum a,largenum b)
{
	a.refresh();
	b.refresh();
	largenum ans;
	if(a.d>b.d)
	{
		ans.d=a.d;
		ans.n=a.n;
		int c=ans.d-b.d;
		if(c>=100) return ans;
		ans.n+=b.n/digit[c];
		ans.refresh();
		return ans;
	}
	else
	{
		ans.d=b.d;
		ans.n=b.n;
		int c=ans.d-a.d;
		if(c>=100) return ans;
		ans.n+=a.n/digit[c];
		ans.refresh();
		return ans;
	}
}
largenum div(largenum a,largenum b)
{
	largenum ans;
	ans.d=a.d-b.d;
	ans.n=a.n/b.n;
	ans.refresh();
	return ans;
}
largenum C(int a,int b)
{
	return div(div(level[a],level[b]),level[a-b]);
}
int main()
{
	/*freopen("in.txt","w",stdout);
	for(int i=1;i<=1000;i++)
	{
		//for(int j=0;j<100;j++) printf("%d ",i);
		printf("%d ",123456789%i);
	}return 0;*/
	digit[0]=1;
	for(int i=1;i<100;i++) digit[i]=digit[i-1]*10;
	pow[0].n=1,pow[0].d=0;
	level[0].n=1,pow[0].d=0;
	for(int i=1;i<50000;i++)
	{
		pow[i]=mul(pow[i-1],2);
		level[i]=mul(level[i-1],i);
	}
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	largenum ans;
	for(int kase=1;kase<=T;kase++)
	{
		scanf("%d",&n);
		n--;
		ans.n=0;
		ans.d=0;
		for(int i=0;i<=n;i++)
		{
			scanf("%lf",&S);
			//printf(" %lf %lf\n",S,C(n,i));
			ans=add(ans,mul(C(n,i),S));//S*C(n,i);
		}
		//ans/=pow(2,n);//2^n
		ans=div(ans,pow[n]);
		printf("Case #%d: %.3lf\n",kase,ans.toshow());
	}
	return 0;
}
