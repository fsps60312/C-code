#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
const long long MOD=100000007;
struct pairtype
{
	long long x;
	long long y;
};
long long T,N,M,K,B,R;
pairtype uncolor[500];
pairtype tmp[500];
long long mul(long long a,long long b)
{
	return a*b%MOD;
}
long long pow(long long a,long long b)
{
	long long ans=1;
	while(b)
	{
		if(b%2) ans=mul(ans,a);
		a=mul(a,a);
		b/=2;
	}
	return ans;
}
//find an integer make a*x%MOD==1
//otherwise a*x-n*y==1, find the integer solution
pairtype euclidean(long long a,long long b,pairtype c,pairtype d)//a is A*c.x+B*c.y, so do b
{
	if(b==0)
	{
		if(a!=1)
		{
			c.x=0;
			c.y=0;
		}
		return c;
	}
	int e=a/b;
	c.x-=d.x*e;
	c.y-=d.y*e;
	return euclidean(b,a%b/*a-b*e*/,d,c);
}
//find an integer make a*x%MOD==1
//a*x-n*y==1, find the integer solution
long long rev(long long a)
{
	return enclidean(n,a).x;
}
bool cmp(pairtype a,pairtype b)
{
	if(a.x!=b.x) return a.x<b.x;
	return a.y<b.y;
}
void range(long long a,long long b)
{
	if(a==b) return;
	long long mid=(a+b)/2;
	range(a,mid);
	range(mid+1,b);
	long long c=a,d=mid+1;
	for(long long i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&cmp(uncolor[c],uncolor[d])))
		{
			tmp[i]=uncolor[c];
			c++;
		}
		else
		{
			tmp[i]=uncolor[d];
			d++;
		}
	}
	for(long long i=a;i<=b;i++) uncolor[i]=tmp[i];
}
long long logm(long long a,long long b)//find a^x==b
{
	long long m=sqrt(MOD);
	map<long long,long long> c;
	//a^c[x]==x
	c[1]=0;
	long long now=1;
	for(int i=1;i<m;i++)
	{
		now=mul(now,a);//now==a^i
		if(c.find()==c.end())
		{
			c[now]=i;
		}
	}
	long long renow=rev(mul(now,a));
	for(int i=0;i<m;i++)
	{
		if(c.find(b)!=c.end())
		{
			return i*m+c[b];
		}
		m=mul(m,renow);
	}
	return -1;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%lld",&T);
	for(long long kase=1;kase<=T;kase++)
	{
		M=1;
		scanf("%lld%lld%lld%lld",&N,&K,&B,&R);
		for(long long i=0;i<B;i++)
		{
			scanf("%lld%lld",&uncolor[i].x,&uncolor[i].y);
			if(uncolor[i].x>M) M=uncolor[i].x;
		}
		long long areanum=N;
		//printf("a\n");
		if(B) range(0,B-1);
		//printf("b\n");
		for(long long i=0;i<B;i++)
		{
			pairtype j=uncolor[i];
			if(j.x!=M&&(i==B-1||!(uncolor[i+1].x==j.x+1&&uncolor[i+1].y==j.y)))
			{
				areanum++;
			}
		}
		for(long long i=0;i<B;i++)
		{
			if(uncolor[i].x==1) areanum--;
		}
		//printf("%lld\n",areanum);
		//areanum: the num of area that seperated by blank blocks
		long long now=mul(pow(K,areanum),pow(K-1,N*M-areanum-B));
		if(now==R)
		{
			printf("Case %lld: %lld\n",kase,M);
		}
		else
		{
			areanum=0;
			for(long long i=0;i<B;i++)
			{
				if(uncolor[i].x==M)
				{
					areanum++;
				}
			}
			now=mul(mul(now,pow(K,areanum)),pow(K-1,N-areanum));
			//now*K^areanum*(K-1)^(N-areanum)
			if(now==R)
			{
				printf("Case %lld: %lld\n",kase,M+1);
			}
			else
			{
				areanum=pow(K-1,N);
				for(long long i=2;;i++)
				{
					now=mul(now,areanum);
					if(now==R)
					{
						printf("Case %lld: %lld\n",kase,M+i);
						break;
					}
				}
			}
		}
	}
}
