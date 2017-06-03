#include<cstdio>
#include<cstdlib>
int T,x[8],y[8];
double ddd[4];
int gcd(int a,int b)
{
	return b==0?(a>=0?a:-a):gcd(b,a%b);
}
int mod(int a)
{
	return (a%10+10)%10;
}
int trans[]={1,10,5,10,5,2,5,10,5,10};
int fin(int a,int b)
{
	for(int i=0;i<10;i++)
	{
		if(a*i%10==b) return i;
	}
	return -1;
}
struct pairtype
{
	int x,y;
};
pairtype dfs(int a,int b,pairtype c,pairtype d)//a==A*c.x+B*c.y
{
	if(b==0)
	{
		if(a!=1) c.x=2147483647;
		return c;
	}
	int e=a/b;
	c.x-=e*d.x;
	c.y-=e*d.y;
	return dfs(b,a%b,d,c);
}
pairtype solve(int a,int b,int c)
{
	pairtype e;
	pairtype f;
	e.y=f.x=0;
	if(c==0)
	{
		e.x=0;
		return e;
	}
	e.x=f.y=1;
	int d=gcd(a,gcd(b,c));
	a/=d,b/=d,c/=d;
	pairtype ans=dfs(a,b,e,f);
	if(ans.x==2147483647) return ans;
	ans.x*=c,ans.y*=c;
	return ans;
}
int LCM(int a,int b)
{
	return a/gcd(a,b)*b;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		for(int i=0;i<4;i++) scanf("%lf",&ddd[i]);
		x[0]=ddd[0]*10,y[0]=ddd[1]*10;
		x[1]=ddd[2]*10,y[1]=ddd[3]*10;
		x[2]=x[1]-x[0],y[2]=y[1]-y[0];
		int gc=gcd(x[2],y[2]);
		if(gc<0) gc=-gc;
		x[3]=x[2]/gc,y[3]=y[2]/gc;
		//x[0]+a*x[3]===0
		//y[0]+a*y[3]===0
		x[4]=mod(-x[0]),y[4]=mod(-y[0]);
		x[5]=mod(x[3]),y[5]=mod(y[3]);
		x[6]=fin(x[5],x[4]);
		y[6]=fin(y[5],y[4]);
		if(x[6]==-1||y[6]==-1)
		{
			printf("0\n");
			continue;
		}
		//x[6]*x[5]===x[4]
		//y[6]*y[5]===y[4]
		//x[6]+trans[x[5]]*a==y[6]+trans[y[5]]*b
		x[7]=trans[x[5]],y[7]=trans[y[5]];
		//x[6]+x[7]*a==y[6]+y[7]*b
		pairtype ans=solve(x[7],-y[7],y[6]-x[6]);
		//ans.x is a, ans.y is b
		int a=x[6]+x[7]*ans.x,b=LCM(x[7],y[7]);
		a=(a%b+b)%b;
		if(ans.x==-1||a>gc)
		{
			printf("0\n");
			continue;
		}
		printf("%d\n",(gc-a)/b+1);
	}
}
