#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define LL long long
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
LL N,LIMIT;
vector<LL> P,F;
struct Pf
{
	LL p;
	int n;
	Pf(LL p,int n):p(p),n(n){}
};
vector<Pf> PF;
struct Ans
{
	LL t1,t2,t3;
	Ans(LL t1,LL t2,LL t3):t1(t1),t2(t2),t3(t3)
	{
//		if(t1>t2)swap(t1,t2);
//		if(t1>t3)swap(t1,t3);
//		if(t2>t3)swap(t2,t3);
	}
	bool operator<(Ans a)const
	{
		if(t1!=a.t1)return t1<a.t1;
		if(t2!=a.t2)return t2<a.t2;
		return t3<a.t3;
	}
};
vector<Ans> ANS;
void getLIMIT()
{
	LIMIT=1000025LL;
	LL l=25LL,mid;
	while(l<LIMIT)
	{
		mid=(l+LIMIT+1LL)>>1;
		if((mid-25LL)*(mid-25LL)*(mid-25LL)>N)LIMIT=mid-1LL;
		else l=mid;
	}
}
void dfs(int dep,LL p)
{
	if(dep==PF.size())
	{
		F.push_back(p);
		return;
	}
	for(int i=0;i<=PF[dep].n&&p<=LIMIT;i++,p*=PF[dep].p)
	{
		dfs(dep+1,p);
	}
}
LL gcd(LL a,LL b)
{
	return b?gcd(b,a%b):a;
}
LL lcm(LL a,LL b)
{
	return a/gcd(a,b)*b;
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
//	printf("%lld\n",1000025LL*1000025LL*1000025LL);
	P.push_back(2LL),P.push_back(3LL);
	for(int i=2,j;;i++)
	{
		P.push_back(P[i-1]);
		do
		{
			P[i]+=2LL;
			for(j=0;P[i]%P[j]&&P[j]*P[j]<=P[i];j++);
		}while(P[i]%P[j]==0);
		if(P[i]>1000025LL)break;
	}
	int kase=1;
	while(scanf("%lld",&N)==1&&N)
	{
		PF.clear(),F.clear(),ANS.clear();
		getLIMIT();
		LL n=N;
		for(int i=0,cnt=0;P[i]<=LIMIT;i++,cnt=0)
		{
			while(n%P[i]==0LL)cnt++,n/=P[i];
			if(cnt)PF.push_back(Pf(P[i],cnt));
			if(n==1LL)break;
			else if(P[i]*P[i]>n){PF.push_back(Pf(n,1));break;}
		}
		dfs(0,1LL);
//		for(int i=0;i<F.size();i++)printf(" %lld",F[i]);puts("");
		sort(F.begin(),F.end());
		for(int t3=F.size()-1;t3>=2;t3--)
		{
			for(int t2=t3-1;t2>=1&&F[t3]-F[t2]<=25LL;t2--)
			{
				for(int t1=t2-1;t1>=0&&F[t3]-F[t1]<=25LL;t1--)
				{
					if(lcm(F[t1],lcm(F[t2],F[t3]))==N)ANS.push_back(Ans(F[t1],F[t2],F[t3]));
				}
			}
		}
		printf("Scenario %d:\n",kase++);
		if(!ANS.size())puts("Such bells don't exist");
		else
		{
			sort(ANS.begin(),ANS.end());
			for(int i=0;i<ANS.size();i++)
			{
				Ans &a=ANS[i];
				if(a.t1>=a.t2||a.t2>=a.t3)termin();
				printf("%lld %lld %lld\n",a.t1,a.t2,a.t3);
			}
		}
		puts("");
	}
	return 0;
}
