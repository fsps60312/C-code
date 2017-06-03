#include<cstdio>
#include<map>
#include<vector>
#include<cassert>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
struct Dot
{
	int x,y;
	Dot(){}
	Dot(const int _x,const int _y):x(_x),y(_y){}
	bool operator<(const Dot &a)const{return x!=a.x?x<a.x:y<a.y;}
};
int T,K,N;
LL L;
map<Dot,int>IDX[100];
vector<Dot>DOT[100];
struct Matrix
{
	LL *s;
	Matrix():s(new LL[N*N]){}
	Matrix operator*(const Matrix &a)const
	{
		Matrix ans=Matrix();
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)
		{
			ans.s[i*N+j]=0LL;
			for(int k=0;k<N;k++)(ans.s[i*N+j]+=s[i*N+k]*a.s[k*N+j])%=MOD;
		}
		return ans;
	}
	void Init(const Matrix &a){for(int i=0;i<N*N;i++)s[i]=a.s[i];}
};
void AddToMatrix(const int mod,const int from,const Dot &to,Matrix &a,const LL &v)
{
	auto it=IDX[(mod+1)%K].find(to);
	assert(it!=IDX[(mod+1)%K].end());
//	if(mod==1)printf("(%d,%d)->(%d,%d): %lld\n",DOT[mod][from].x,DOT[mod][from].y,to.x,to.y,v);
	assert(it->second<N&&from<N);
	a.s[it->second*N+from]+=v;
}
Matrix Pow(Matrix a,LL b)
{
	Matrix ans=Matrix();
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)ans.s[i*N+j]=(i==j?1LL:0LL);
	while(b!=0LL)
	{
		if((b&1LL)==1LL)ans.Init(ans*a);
		a.Init(a*a);
		b>>=1;
	}
	return ans;
}
LL Solve()
{
	Matrix a=Matrix(),b=Matrix();
	for(int i=0;i<N;i++)for(int j=0;j<N;j++)b.s[i*N+j]=a.s[i*N+j]=(i==j?1LL:0LL);
	for(int mod=0;mod<K;mod++)
	{
//		if(mod<=2)
//		{
//			printf("mod %d\n",mod);
//			for(int i=0;i<N*N;i++)if(b.s[i])printf("a.s(%d,%d): %lld\n",i/N,i%N,b.s[i]);
//		}
		if((LL)mod==L%K)a.Init(b);
		Matrix tmp=Matrix();
		for(int i=0;i<N*N;i++)tmp.s[i]=0LL;
		for(int i=0;i<DOT[mod].size();i++)
		{
			const Dot &d=DOT[mod][i];
			if(d.y+1<K)AddToMatrix(mod,i,Dot(d.x,d.y+1),tmp,(LL)(K-d.y));
			else AddToMatrix(mod,i,Dot(0,d.x),tmp,1LL);
			if(d.x+1<=d.y)AddToMatrix(mod,i,Dot(d.x+1,d.y),tmp,(LL)(d.y-d.x));
		}
		b.Init(tmp*b);
//		if(mod<=1)
//		{
//			for(int i=0;i<N;i++)printf("(%d,%d),(%d,%d)\n",DOT[mod][i].x,DOT[mod][i].y,DOT[mod+1][i].x,DOT[mod+1][i].y);
//			for(int i=0;i<N;i++)
//			{
//				for(int j=0;j<N;j++)printf(" %3lld",tmp.s[i*N+j]);puts("");
//			}
//		}
	}
	a.Init(a*Pow(b,L/K));
//	for(int i=0;i<N;i++)printf("(%d,%d),(%d,%d)\n",DOT[0][i].x,DOT[0][i].y,DOT[L%K][i].x,DOT[L%K][i].y);
//	for(int i=0;i<N;i++)
//	{
//		for(int j=0;j<N;j++)printf(" %3lld",a.s[i*N+j]);puts("");
//	}
	auto it=IDX[0].find(Dot(0,0));
	assert(it!=IDX[0].end());
	LL ans=0LL;
	for(int i=0;i<N;i++)
	{
//		printf("(%d,%d): %lld\n",DOT[L%K][i].x,DOT[L%K][i].y,a.s[i*N+it->second]);
		(ans+=a.s[i*N+it->second])%=MOD;
	}
	return ans;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lld%d",&L,&K);
		N=-1;
		for(int i=0;i<K;i++)
		{
			IDX[i].clear();
			IDX[i][Dot(0,i)]=-1;
			for(int l=1,r=i-1;l<=r;l++,r--)IDX[i][Dot(l,r)]=-1;
			for(int l=i+1,r=K-1;l<=r;l++,r--)IDX[i][Dot(l,r)]=-1;
			DOT[i].clear();
			int cnt=0;
			for(auto &it:IDX[i])DOT[i].push_back(it.first),it.second=cnt++;
			if(cnt>N)N=cnt;
		}
		printf("%lld\n",Solve());
	}
	return 0;
}
