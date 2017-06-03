#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
int T,L,R;
LL S[100];
bool AllSame()
{
	for(int i=1;i<L;i++)if(S[i]!=S[0])return false;
	return true;
}
struct Matrix
{
	vector<vector<LL> >s;
	int n;
	Matrix(const int _n):n(_n){s.resize(n);for(auto &v:s)v.resize(n+1);}
	LL Gcd(const LL &a,const LL &b){return b?Gcd(b,a%b):a;}
	void Swap(const int r1,const int r2){for(int i=0;i<=n;i++)swap(s[r1][i],s[r2][i]);}
	void Mul(const int r,const LL &v){for(int i=0;i<=n;i++)s[r][i]*=v;}
	void Sub(const int r1,const int r2){for(int i=0;i<=n;i++)s[r1][i]-=s[r2][i];}
	void Reduce(const int r)
	{
		LL g=0LL;
		for(int i=0;i<=n;i++)g=Gcd(g,s[r][i]);
		for(int i=0;i<=n;i++)s[r][i]/=g;
	}
	void Eliminate(const int r1,const int r2,const int c)
	{
		if(!s[r2][c])return;
		assert(s[r1][c]);
		LL g=Gcd(s[r1][c],s[r2][c]),v1=s[r1][c]/g,v2=s[r2][c]/g;
		Mul(r1,v2),Mul(r2,v1);
		Sub(r2,r1);
		assert(!s[r2][c]);
		Reduce(r1),Reduce(r2);
	}
};
LL GetValue(const vector<LL>&equ,const LL &v)
{
	LL ans=0LL,tmp=1LL;
	for(int i=0;i<equ.size();i++)ans+=tmp*equ[i],tmp*=v;
	return ans;
}
bool Solve(const int n,vector<LL>&ans)
{
	Matrix board=Matrix(n);
	vector<vector<LL> >&s=board.s;
	for(int i=0;i<n;i++)
	{
		s[i][n]=S[i];
		LL tmp=1LL;
		for(int j=0;j<n;j++,tmp*=i)s[i][j]=tmp;
	}
	for(int i=0;i<n;i++)
	{
		if(s[i][i]==0LL)
		{
			bool found=false;
			for(int j=i+1;j<n;j++)if(s[j][i]){board.Swap(i,j);found=true;break;}
			assert(found&&"Solve(n,ans)");
		}
		for(int j=i+1;j<n;j++)board.Eliminate(i,j,i);
	}
	for(int i=n-1;i>=0;i--)for(int j=i-1;j>=0;j--)board.Eliminate(i,j,i);
	ans.clear();
	for(int i=0;i<n;i++)
	{
		board.Reduce(i);
		printf("(%lld,%lld)\n",s[i][i],s[i][n]);
		if(s[i][i]!=1LL){puts("a");return false;}
		ans.push_back(s[i][n]);
	}
	for(int i=n;i<L;i++)if(S[i]!=GetValue(ans,i)){puts("b");return false;}
	return true;
}
void Solve()
{
	vector<LL>ans;
	bool found=false;
	for(int n=2;n<=L;n++)if(Solve(n,ans)){printf("n=%d\n",n);found=true;break;}
	assert(found&&"Solve");
	for(int i=L;i<R;i++)S[i]=GetValue(ans,i);
}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&L,&R);
		R+=L;
		for(int i=0;i<L;i++)scanf("%lld",&S[i]);
		if(AllSame())for(int i=L;i<R;i++)S[i]=S[0];
		else Solve();
		for(int i=L;i<R;i++)
		{
			if(i>L)putchar(' ');
			printf("%d",S[i]);
		}
		puts("");
	}
	return 0;
}
