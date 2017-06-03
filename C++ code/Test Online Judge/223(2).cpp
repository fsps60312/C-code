#include<cstdio>
#include<map>
#include<algorithm>
#include<cassert>
#include<vector>
using namespace std;
typedef long long LL;
LL T,P,N,INV10;
char S[1000001];
void ExGcd(const LL a,const LL b,LL &g,LL &x,LL &y)
{
	if(b==0LL){g=a,x=1LL,y=0LL;return;}
	ExGcd(b,a%b,g,y,x);
	//(a-a/b*b)x+by==g
	//ax+b(y-a/b*x)==g
	y-=a/b*x;
}
void GetINV10()
{
	LL x,y,g;
	ExGcd(10LL,P,g,x,y);
	assert(g==1LL);
	//10x+Py==1
	INV10=(x%P+P)%P;
}
LL Pow(LL a,LL b)
{
	LL ans=1LL;
	while(b!=0LL)
	{
		if((b&1LL)==1LL)(ans*=a)%=P;
		(a*=a)%=P;
		b>>=1;
	}
	return ans;
}
map<LL,LL>LOC;
vector<int>SA,TMP[3];
void BuildSA()
{
	int *x=&TMP[0][0],*y=&TMP[1][0],*c=&TMP[2][0],p=1000;
	for(int i=0;i<p;i++)c[i]=0;
	for(int i=0;i<N;i++)c[x[i]=S[i]]++;
	for(int i=1;i<p;i++)c[i]+=c[i-1];
	for(int i=N-1;i>=0;i--)SA[--c[x[i]]]=i;
	for(int move=1;move<N;move<<=1)
	{
//		printf("x ");for(int i=0;i<N;i++)printf(" %d",x[i]);puts("");
		int idx=0;
		for(int i=N-move;i<N;i++)y[idx++]=i;
		for(int i=0;i<N;i++)if(SA[i]>=move)y[idx++]=SA[i]-move;//y[rank]=loc,SA[rank]=loc
//		printf("y ");for(int i=0;i<N;i++)printf(" %d",y[i]);puts("");
		for(int i=0;i<p;i++)c[i]=0;
		for(int i=0;i<N;i++)c[x[i]]++;
		for(int i=1;i<p;i++)c[i]+=c[i-1];
		for(int i=N-1;i>=0;i--)SA[--c[x[y[i]]]]=y[i];
//		printf("sa");for(int i=0;i<N;i++)printf(" %d",SA[i]);puts("");
		swap(x,y);
		p=0;x[SA[0]]=p++;
		for(int i=1;i<N;i++)
		{
			if(y[SA[i]]!=y[SA[i-1]])x[SA[i]]=p++;
			else if((SA[i]+move<N)!=(SA[i-1]+move<N))x[SA[i]]=p++;
			else
			{
//				assert(SA[i]+move<N&&SA[i-1]+move<N);
				if(y[SA[i]+move]==y[SA[i-1]+move])x[SA[i]]=p-1;
				else x[SA[i]]=p++;
			}
		}
		if(p==N)break;
	}
}
vector<int>HEIGHT,RANK;
vector<int>SPARSE[20];
void BuildHEIGHT()
{
	for(int i=0;i<N;i++)RANK[SA[i]]=i;
	for(int i=0,now=0;i<N;i++)
	{
		if(now)now--;
		int rank=RANK[i];
		if(rank==0)assert(now==0),HEIGHT[rank]=0;
		else
		{
			while(S[i+now]==S[SA[rank-1]+now])now++;
			HEIGHT[rank]=now;
		}
	}
	for(int i=1;i<N;i++)SPARSE[0][i]=HEIGHT[i];
	for(int d=1;(1<<d)<=N;d++)
	{
		for(int i=1;i+(1<<d)<=N;i++)
		{
			SPARSE[d][i]=min(SPARSE[d-1][i],SPARSE[d-1][i+(1<<(d-1))]);
		}
	}
}
int Query(const int ia,const int ib)
{
	int a=RANK[ia],b=RANK[ib];
	assert(a!=b);
	if(a>b)swap(a,b);
	a++;
	int d;
	for(d=0;(1<<(d+1))<=b-a+1;d++);
	return min(SPARSE[d][a],SPARSE[d][b-(1<<d)+1]);
}
void TestSA()
{
	char s[]="aabaaaab";
	N=-1;while(s[++N])S[N]=s[N];S[N]=0;
	BuildSA();
	BuildHEIGHT();
	for(int i=0;i<N;i++)printf(" %d",SA[i]);puts("");
	for(int i=0;i<N;i++)printf(" %d",HEIGHT[i]);puts("");
	int a,b;while(scanf("%d%d",&a,&b)==2)printf("%d\n",Query(a,b));
	assert(0);
}
int main()
{
//	TestSA();
	scanf("%lld",&T);
	while(T--)
	{
		scanf("%s%lld",S,&P);
		N=-1LL;while(S[++N]);
		SA.resize(N),TMP[0].resize(N),TMP[1].resize(N),TMP[2].resize(max(1000,(int)N)),HEIGHT.resize(N),RANK.resize(N);
		for(int i=0;i<20;i++)SPARSE[i].resize(N);
		BuildSA();
		BuildHEIGHT();
		GetINV10();
//		printf("INV10=%lld\n",INV10);
//		for(int i=0;i<N;i++)printf(" %d",RANK[i]);puts("");
		LOC.clear();
		LOC[0LL]=-1;
		LL lans=0LL,rans=9223372036854775807LL;
		for(LL i=0LL,now=0LL;i<N;i++)
		{
			now=(now*10LL+(S[i]-'0'))%P;
			LL tmp=(now*Pow(INV10,i+1LL))%P;
			auto it=LOC.find(tmp);
			if(it!=LOC.end())
			{
				if(i-it->second<rans-lans)rans=i,lans=it->second;
				else if(i-it->second==rans-lans&&Query(lans+1,it->second+1)<rans-lans&&RANK[it->second+1]<RANK[lans+1])rans=i,lans=it->second;
			}
			LOC[tmp]=i;
		}
		if(rans==9223372036854775807LL)puts("-1");
		else printf("%lld %lld\n",lans+2LL,rans+1LL);
	}
	return 0;
}
