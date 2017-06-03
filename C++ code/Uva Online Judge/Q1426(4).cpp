#include<cstdio>
#include<vector>
#include<algorithm>
typedef long long LL;
#define int long long
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
using namespace std;
int X,N,R;
vector<int>P,F,ANS;
struct Pf
{
	int p,n;
	Pf(){}
	Pf(int p,int n):p(p),n(n){}
};
vector<Pf>PF;
void dfs(int dep,int p)
{
	if(dep==PF.size())
	{
		F.push_back(p);
		return;
	}
	for(int i=0;i<=PF[dep].n;i++,p*=PF[dep].p)dfs(dep+1,p);
}
void gcd(int a,int b,int &g,int &x,int &y)
{
	if(!b)
	{
		g=a;
		x=1,y=0;
		return;
	}
	gcd(b,a%b,g,y,x);
	//(a%b)x+by==g
	//ax+by-a/b*b*x==g
	//ax+b(y-a/b*x)==g
	y-=a/b*x;
}
void check(int f)//A=f,B=N/f,C=2*R
{
	int A=f,B=N/f;
	int g,a,b,c=2*R;
	gcd(A,B,g,a,b);
	if(c%g)return;
	a*=c/g;//b*=c/g;//aA+bB=c
	B/=g;
	a=(a%B+B)%B;
	c=A*B;
	for(g=a*A-R;g<N;g+=c)
	{
		if(g>=0)ANS.push_back(g);
	}
}
#undef int
int main()
{
	#define int long long
	P.push_back(2),P.push_back(3);
	for(int i=2,j;;i++)
	{
		P.push_back(P[i-1]);
		do
		{
			P[i]+=2;
			for(j=0;P[j]*P[j]<=P[i];j++)if(P[i]%P[j]==0)break;
		}while(P[i]%P[j]==0);
		if(P[i]*P[i]>1000000000)break;
	}
//	for(int i=0;i<100;i++)printf("%d\n",P[i]);
	int kase=1;
	while(scanf("%lld%lld%lld",&X,&N,&R)&&(X||N||R))
	{
		PF.clear(),F.clear(),ANS.clear();
		for(int i=0,n=N,cnt=0;;i++,cnt=0)
		{
			while(n%P[i]==0)cnt++,n/=P[i];
			if(cnt)PF.push_back(Pf(P[i],cnt));
			if(P[i]*P[i]>n){PF.push_back(Pf(n,1));break;}
			else if(n==1)break;
		}
		dfs(0,1);
		for(int i=0;i<F.size();i++)check(F[i]);
		sort(ANS.begin(),ANS.end());
//		for(int i=0;i<ANS.size();i++)printf(" %d",ANS[i]);printf("\n");
		printf("Case %lld:",kase++);
		for(int i=0;i<ANS.size();i++)if(i==0||ANS[i]!=ANS[i-1])printf(" %lld",ANS[i]);
		printf("\n");
	}
	return 0;
}
