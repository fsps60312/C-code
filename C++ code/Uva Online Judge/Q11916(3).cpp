#include<cstdio>
#include<cstdlib>
#include<map>
using namespace std;
struct pairtype
{
	long long x;
	long long y;
};
const long long MOD=100000007;
long long T,M,N,K,B,R;
pairtype S[510],tmp[510];
bool cmp(pairtype a,pairtype b)
{
	if(a.y!=b.y) return a.y<b.y;
	return a.x<b.x;
}
void rangeS(long long a,long long b)
{
	if(a==b) return;
	long long mid=(a+b)/2;
	rangeS(a,mid);
	rangeS(mid+1,b);
	long long c=a,d=mid+1;
	for(long long i=a;i<=b;i++)
	{
		if(d>b||(c<=mid&&cmp(S[c],S[d])))
		{
			tmp[i]=S[c];
			c++;
		}
		else
		{
			tmp[i]=S[d];
			d++;
		}
	}
	for(long long i=a;i<=b;i++) S[i]=tmp[i];
}
bool cancolorbelow(long long a)//!=M&&can't find (S[a].x+1,S[a].y)
{
	if(S[a].x==M) return false;
	if(a==B-1) return true;
	return !(S[a+1].x==S[a].x+1&&S[a+1].y==S[a].y);
}
long long mulm(long long a,long long b)
{
	return a*b%MOD;
}
long long powm(long long a,long long b)
{
	long long ans=1;
	while(b)
	{
		if(b%2)
		{
			ans=mulm(ans,a);
		}
		a=mulm(a,a);
		b/=2;
	}
	return ans;
}
pairtype euclidean(long long a,long long b,pairtype c,pairtype d)//MOD*c.x+A*c.y==a, so do b&d
{
	if(b==0)
	{
		c.y=(c.y%MOD+MOD)%MOD;
		if(a!=1)//ans is not exist
		{
			c.x=c.y=-1;
		}
		return c;
	}
	long long e=a/b;
	c.x-=d.x*e;
	c.y-=d.y*e;
	//a%b==a-b*(a/b)
	return euclidean(b,a%b,d,c);
}
long long invers(long long a)//find what*a==1
{
	//a*x==1
	//a*x-MOD*y==1
	//find (x,y) that makes above holds
	pairtype b,c;
	b.x=1;
	b.y=0;//MOD==1*MOD+0*a
	c.x=0;
	c.y=1;//a==0*MOD+1*a
	long long ans=euclidean(MOD,a,b,c).y;
	return ans;
}
long long logm(long long a,long long b)//find a^what==b
{
	long long m=10001;//m*m>MOD
	map<long long,long long> c;//a^c[i]==i
	c.clear();
	long long now=1;
	c[1]=0;
	for(long long i=1;i<m;i++)
	{
		now=mulm(now,a);//now==a^i
		if(c.find(now)==c.end())
		{
			c[now]=i;
		}
	}
	long long invnow=invers(mulm(now,a));
	for(long long i=0;i<m;i++)
	{
		if(c.find(b)!=c.end())
		{
			return i*m+c[b];
		}
		b=mulm(b,invnow);
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
			scanf("%lld%lld",&S[i].x,&S[i].y);
			if(S[i].x>M) M=S[i].x;
		}
		//printf("a\n");
		if(B) rangeS(0,B-1);
		//for(int i=0;i<B;i++) printf(" %lld %lld\n",S[i].x,S[i].y);
		//printf("b\n");
		long long areanum=N;
		for(long long i=0;i<B;i++)
		{
			if(cancolorbelow(i))
			{
				areanum++;
			}
		}
		//printf(" %lld\n",areanum);
		for(long long i=0;i<B;i++)
		{
			if(S[i].x==1)
			{
				areanum--;
			}
		}
		//printf(" %lld\n",areanum);
		//areanum is the sum of areas that seperated by uncolor blocks
		long long now=mulm(powm(K,areanum),powm(K-1,M*N-B-areanum));//the case num of N*M
		if(now==R)
		{
			printf("Case %lld: %lld",kase,M);
		}
		else
		{
			areanum=0;
			for(long long i=0;i<B;i++)
			{
				if(S[i].x==M)
				{
					areanum++;
				}
			}
			M++;
			now=mulm(now,powm(K,areanum));
			now=mulm(now,powm(K-1,N-areanum));
			if(now==R) printf("Case %lld: %lld",kase,M);
			else
			{
				printf("Case %lld: %lld",kase,M+logm(powm(K-1,N),mulm(invers(now),R)));
				//continue;
				/*for(long long i=2;;i++)
				{
					now=mulm(now,powm(K-1,N));
					if(now==R)
					{
						printf("Case %lld: %lld\n",kase,M+i);
						break;
					}
				}*/
			}
		}
		printf("\n");
	}
	return 0;
}
