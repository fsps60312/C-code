#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Dot
{
	int x,y;
	Dot(){}
	Dot(const int _x,const int _y):x(_x),y(_y){}
	Dot operator-(const Dot &d)const{return Dot(x-d.x,y-d.y);}
};
vector<Dot>DOT;
int DP[50][50];
LL Cross(const Dot &a,const Dot &b){return (LL)a.x*b.y-(LL)b.x*a.y;}
bool NoDotAbove(const int &ia,const int &ib)
{
	const Dot o=DOT[ib]-DOT[ia];
	for(int i=ia+1;i<ib;i++)if(Cross(o,DOT[i]-DOT[ia])>=0LL)return false;
	return true;
}
bool NoDotBelow(const int &ia,const int &ib)
{
	const Dot o=DOT[ib]-DOT[ia];
	for(int i=ia+1;i<ib;i++)if(Cross(o,DOT[i]-DOT[ia])<=0LL)return false;
	return true;
}
int T,N;
int Solve()
{
	for(int i=0;i<N*N;i++)DP[i/N][i%N]=0;
	for(int i=1;i<N;i++)
	{
		if(NoDotAbove(0,i))DP[i][0]=1;
		if(NoDotBelow(0,i))DP[0][i]=1;
	}
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)if(i!=j)
		{
			if(i>0)for(int k=0;k<i;k++)if(DP[k][j]&&NoDotAbove(k,i))DP[i][j]+=DP[k][j],printf("a(%d,%d)->(%d,%d)\n",k,j,i,j);
			if(j>0)for(int k=0;k<j;k++)if(DP[i][k]&&NoDotBelow(k,j))DP[i][j]+=DP[i][k],printf("b(%d,%d)->(%d,%d)\n",i,k,i,j);
		}
	}
	int ans=0;
	for(int i=0;i<N-1;i++)ans+=DP[i][N-1],ans+=DP[N-1][i];
	return ans;
}
bool CmpX(const Dot &a,const Dot &b){return a.x<b.x;}
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		DOT.clear();
		for(int i=0,x,y;i<N;i++)scanf("%d%d",&x,&y),DOT.push_back(Dot(x,y));
		sort(DOT.begin(),DOT.end(),CmpX);
		printf("%d\n",Solve());
	}
	return 0;
}
