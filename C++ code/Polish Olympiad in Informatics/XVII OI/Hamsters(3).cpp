#include<cstdio>
#include<cassert>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
template<class T>void getmin(T &a,const T &b){if(b<a)a=b;}
struct Matrix
{
	int N;
	LL **S;
	Matrix(const int _N):N(_N),S(new LL*[N])
	{
		for(int i=0;i<N;i++)S[i]=new LL[N];
	}
};
Matrix operator*(const Matrix &a,const Matrix &b)
{
	const int N=a.N;
	assert(b.N==N);
	Matrix ans=Matrix(N);
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)
	{
		LL &v=ans.S[i][j]=INF;
		for(int k=0;k<N;k++)if(a.S[i][k]!=INF&&b.S[k][j]!=INF)getmin(v,a.S[i][k]+b.S[k][j]);
	}
	return ans;
}
Matrix Pow(Matrix a,int p)
{
	const int N=a.N;
	Matrix ans=Matrix(N);
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)ans.S[i][j]=(i==j?0LL:INF);
	for(;p;p>>=1)
	{
		if(p&1)ans=ans*a;
		a=a*a;
	}
	return ans;
}
int Solve(const string &a,const string &b)
{
	static int z[100000];
	z[0]=0;
	for(int i=1,mx=0;i<(int)a.size();i++)
	{
		if(mx+z[mx]-1>=i)z[i]=min(mx+z[mx]-i,z[mx-(i-mx)]);
		else z[i]=0;
		while(i+z[i]<(int)a.size()&&a[i+z[i]]==b[z[i]])++z[i];
		if(i+z[i]==(int)a.size())return (int)b.size()-z[i];
		if(i+z[i]>=mx+z[mx])mx=i;
	}
	return (int)b.size();
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int N,M;scanf("%d%d",&N,&M)==2;)
	{
		vector<string>S;
		for(int i=0;i<N;i++)
		{
			static char str[100001];
			scanf("%s",str);
			S.push_back(str);
		}
		Matrix a=Matrix(N);
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)a.S[i][j]=Solve(S[i],S[j]);//,printf("(%d,%d)=%d\n",i,j,a.S[i][j]);
		a=Pow(a,M-1);
		LL ans=INF;
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(a.S[i][j]!=INF)
		{
//			printf("%d+%d\n",(int)S[i].size(),a.S[i][j]);
			getmin(ans,(LL)S[i].size()+a.S[i][j]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
