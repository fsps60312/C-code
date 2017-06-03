#include<cstdio>
#include<vector>
using namespace std;
typedef long long LL;
struct Fraction
{
	LL v;
	int d;
	Fraction(){}
	Fraction(double a)
	{
		v=a*10.0+0.5,d=1;
		Carry();
	}
	void SetINF(){v=9223372036854775807LL,d=0;}
	void Carry()
	{
		while(d>0&&!(v%10LL))v/=10LL,d--;
	}
	bool operator<(const Fraction &f)const
	{
		LL a=v,b=f.v;
		if(d<f.d)for(int i=f.d-d;i>0;i--)a*=10LL;
		else for(int i=d-f.d;i>0;i--)b*=10LL;
		return a<b;
	}
	Fraction operator*(const Fraction &f)
	{
		Fraction ans;
		ans.v=v,ans.d=d;
		while(9223372036854775807LL/ans.v<f.v)ans.v/=10LL,ans.d--;
		ans.v*=f.v;
		ans.d+=f.d;
		ans.Carry();
		return ans;
	}
};
struct Edge
{
	int to;
	Fraction c;
	Edge(){}
	Edge(int to,double c):to(to),c(c){}
};
vector<Edge>AD[2000];
Fraction MN[2000];
int CNT[2000];
bool INQ[2000];
#include<queue>
void Push(queue<int>&q,int v)
{
	if(INQ[v])return;
	q.push(v);
	INQ[v]=true;
}
int N,M,A,B;
LL V;
LL Solve()
{
	queue<int>q;
	Push(q,A);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		if(CNT[u]++>N)return 0LL;
		for(int i=0;i<AD[u].size();i++)
		{
			Edge &e=AD[u][i];
			Fraction f=MN[u]*e.c;
			if(f<MN[e.to])
			{
				MN[e.to]=f;
				Push(q,e.to);
			}
		}
	}
	LL ans=MN[B].v;
	if(MN[B].d==0)return ans;
	for(int i=1;i<MN[B].d;i++)ans/=10LL;
	if(ans%10LL>=5)return ans/10LL+1LL;
	else return ans/10LL;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%lld%d%d",&N,&M,&V,&A,&B)==5)
	{
		A--,B--;
		for(int i=0;i<N;i++)
		{
			AD[i].clear();
			MN[i].SetINF();
			CNT[i]=0;
			INQ[i]=false;
		}
		MN[A].v=V,MN[A].d=0,MN[A].Carry();
		for(int i=0;i<M;i++)
		{
			static int a,b;
			static double c;
			scanf("%d%d%lf",&a,&b,&c);
			a--,b--;
			AD[a].push_back(Edge(b,c));
		}
		printf("%lld\n",Solve());
	}
	return 0;
}
