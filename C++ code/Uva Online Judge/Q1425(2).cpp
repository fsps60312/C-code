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
	DP[1][0]=DP[0][1]=1;
	for(int len=2;len<N;len++)
	{
		for(int i=0;i<len-1;i++)if(NoDotAbove(i,len))DP[len][len-1]+=DP[i][len-1];
		for(int i=0;i<len-1;i++)DP[len][i]+=DP[len-1][i];
		for(int i=0;i<len-1;i++)if(NoDotBelow(i,len))DP[len-1][len]+=DP[len-1][i];
		for(int i=0;i<len-1;i++)DP[i][len]+=DP[i][len-1];
	}
	return DP[N-1][N-2]+DP[N-2][N-1];
}
bool CmpX(const Dot &a,const Dot &b){return a.x<b.x;}
int main()
{
//	freopen("in.txt","r",stdin);
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
