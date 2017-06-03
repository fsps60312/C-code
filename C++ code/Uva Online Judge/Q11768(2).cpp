#include<cstdio>
#include<cstdlib>
int T,x[10],y[10],gc;
struct pairtype
{
	int x,y;
};
int gcd(int a,int b)
{
	if(b==0) return a>=0?a:-a;
	return gcd(b,a%b);
}
int mod(int a)
{
	return (a%10+10)%10;
}
int fin(int a,int b)
{
	//a=mod(a),b=mod(b);
	for(int i=0;i<10;i++)
	{
		if(a*i%10==b) return i;
	}
	return -1;
}
int trans[]={1,10,5,10,5,2,5,10,5,10};
pairtype dfs(int a,int b,pairtype c,pairtype d)//a==A*c.x+B*c.y
{
	if(b==0)
	{
		if(a!=1) c.x=-1;
		return c;
	}
	int e=a/b;
	c.x-=e*d.x;
	c.y-=e*d.y;
	return dfs(b,a%b,d,c);
}
pairtype solve(int a,int b,int c)//ax+by==c
{
	//printf("solve:%d %d %d\n",a,b,c);
	int d=gcd(a,gcd(b,c));
	a/=d,b/=d,c/=d;
	pairtype e;
	pairtype f;
	e.y=f.x=0;
	if(c==0)
	{
		e.x=0;
		return e;
	}
	e.x=f.y=1;
	pairtype ans=dfs(a,b,e,f);
	if(ans.x==-1) return ans;
	ans.x*=c,ans.y*=c;
	return ans;
	//a ans.x+b ans.y==c
}
int LCM(int a,int b)
{
	return a*b/gcd(a,b);
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		double ddd[4];
		for(int i=0;i<4;i++) scanf("%lf",&ddd[i]);
		x[0]=ddd[0]*10,y[0]=ddd[1]*10;
		x[1]=ddd[2]*10,y[1]=ddd[3]*10;
		//printf("%d %d %d %d\n",x[0],x[1],y[0],y[1]);
		x[2]=x[1]-x[0],y[2]=y[1]-y[0];
		//if(x[2]<0) x[2]=-x[2];
		//if(y[2]<0) y[2]=-y[2];
		gc=gcd(x[2],y[2]);
		if(gc<0) gc=-gc;
		x[3]=x[2]/gc,y[3]=y[2]/gc;
		//x[0]+x[3]*a===0
		//y[0]+y[3]*a===0
		x[4]=mod(-x[0]),y[4]=mod(-y[0]);
		x[5]=mod(x[3]),y[5]=mod(y[3]);
		//x[5]*a===x[4]
		//y[5]*a===y[4]
		x[6]=fin(x[5],x[4]),y[6]=fin(y[5],y[4]);
		if(x[6]==-1||y[6]==-1)
		{
			printf("1:0\n");
			continue;
		}
		//x[6] is the min times make x[3](mod=x[5])*x[6]+x[0]===0
		//y[6] is the min times make y[3](mod=y[5])*y[6]+y[0]===0
		x[7]=trans[x[5]],y[7]=trans[y[5]];
		//x[7] is the min times make x[3]*x[7]===0
		//y[7] is the min times make y[3]*y[7]===0
		//ans==x[6]+a*x[7](a>=0)
		//ans==y[6]+b*y[7](b>=0)
		//a*x[7]-b*y[7]==y[6]-x[6]
		//ans%x[7]==x[6]
		//ans%y[7]==y[6]
		//ans==y[7]*x[6]*y[7]^-1+x[7]*y[6]*x[7]^-1
		//for(int i=0;i<=7;i++) printf("%d: %d %d\n",i,x[i],y[i]);
		pairtype ans=solve(x[7],y[7],y[6]-x[6]);
		int a=x[6]+ans.x*x[7];
		a%=LCM(x[7],y[7]);
		if(a<0) a+=LCM(x[7],y[7]);
		//printf("x[2]:%d a:%d LCM:%d %d %d\n",x[2],a,LCM(x[7],y[7]),ans.x,ans.y);
		if(x[2]<0) x[2]=-x[2];
		if(ans.x==-1||a>x[2])
		{
			printf("2:0 %d %d\n",a,x[2]);
			continue;
		}
		//printf("%d %d %d\n",a,x[2]-a,LCM(x[7],y[7]));
		//ans==min(a+?*LCM(x[7],y[7]))
		printf("%d\n",(x[2]-a*x[3])/LCM(x[7],y[7])+1);
	}
	return 0;
}
