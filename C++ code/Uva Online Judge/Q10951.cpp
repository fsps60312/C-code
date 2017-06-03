#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<map>
using namespace std;
int p;
int mod(int a)
{
	return (a%p+p)%p;
}
int solve(int a,int b)//a+bx===0
{
	int sq=sqrt(p);
	map<int,int> c;
	a=mod(-a);
	int now=0;
	for(int i=0;i<=p;i++)
	{
		if(now==a) return i;
		if(c.find(now)==c.end())
		{
			c[now]=i;
		}
		now=(now+b)%p;
	}
	for(int i=1;i<=p;i++)
	{
		a=mod(a-now);
		if(c.find(0)!=c.end())
		{
			return i*p+c[0];
		}
	}
	return -1;
}
struct polynomial
{
	int n;
	int s[101];
	polynomial operator/(polynomial a)
	{
		if(a.n>n) return *this;
		for(;n>=a.n;n--)
		{
			//printf(" %d\n",n);
			int j=solve(s[n],a.s[a.n]);
			//while(s[n])
			{
				for(int i=0;i<=a.n;i++)
				{
					s[n-i]+=a.s[a.n-i]*j;
					s[n-i]%=p;
				}
			}
		}
		while(!s[n]&&n>0) n--;
		return *this;
	}
	void show()
	{
		printf("%d",n);
		for(int i=n;i>=0;i--) printf(" %d",s[i]);
	}
};
polynomial p1,p2;
polynomial dfs(polynomial a,polynomial b)
{
	if(b.n==0) return a;
	return dfs(b,a/b);
}
polynomial makeone(polynomial a)
{
	while(a.s[a.n]!=1)
	{
		for(int i=a.n;i>=0;i--)
		{
			a.s[i]*=2;
			a.s[i]%=p;
		}
	}
	return a;
}
void terminat()
{
	int a=-100000;
	int b[a][a][a][a];
}
int pp[500];
bool isp[1501];
int main()
{
	for(int i=0;i<=1500;i++) isp[i]=false;
	pp[0]=2,pp[1]=3;
	for(int i=2,j;;i++)
	{
		pp[i]=pp[i-1];
		do
		{
			pp[i]+=2;
			for(j=0;pp[j]*pp[j]<=pp[i];j++)
			{
				if(pp[i]%pp[j]==0) break;
			}
		}while(pp[i]%pp[j]==0);
		if(pp[i]>1500) break;
	}
	for(int i=0;pp[i]<=1500;i++)
	{
		isp[pp[i]]=true;
	}
	int kase=1;
	while(scanf("%d",&p)==1&&p)
	{
		if(!isp[p])
		{
			terminat();
			break;
		}
		scanf("%d",&p1.n);
		for(int i=p1.n;i>=0;i--) scanf("%d",&p1.s[i]);
		scanf("%d",&p2.n);
		for(int i=p2.n;i>=0;i--) scanf("%d",&p2.s[i]);
		printf("Case %d: ",kase++);
		makeone(dfs(p1,p2)).show();
		printf("\n");
	}
	return 0;
}
