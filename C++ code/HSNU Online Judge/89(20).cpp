#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
const int INF=2147483647;
int N,X,Y,K;
int VIS[10][901][910];
struct Edge
{
	int d,u,c;
	Edge(){}
	Edge(const int _d,const int _u,const int _c):d(_d),u(_u),c(_c){}
//	bool operator<(const Edge &e)const{if((u+d*K)%10!=(e.u+e.d*K)%10)return (u+d*K)%10<(e.u+e.d*K)%10;return d<e.d;}
	bool operator<(const Edge &e)const{if(d!=e.d)return d<e.d;return u<e.u;}
};
vector<Edge>ET[10];
vector<int>ANS,KS;
bool Dfs(const int u,const int dsum,const int ksum)
{
	int n=N-ANS.size();
	if(n<=VIS[u][dsum][ksum])return false;
	VIS[u][dsum][ksum]=n;
//printf("u=%d,dsum=%d,ksum=%d,ANS=",u,dsum,ksum);for(int i=0;i<ANS.size();i++)printf("%d",ANS[i]);printf(" KS=");for(int i=0;i<KS.size();i++)printf("%d",KS[i]);puts("");
	if(dsum+n*9<X||dsum>X)return false;
	if(dsum==X&&ksum==Y&&u==0)return true;
	if(ANS.size()==N)return false;
	for(int i=0;i<ET[u].size();i++)
	{
		const Edge &e=ET[u][i];
		ANS.push_back(e.d);
		KS.push_back((e.u+e.d*K)%10);
		if(Dfs(e.u,dsum+e.d,ksum+(e.u+e.d*K)%10))return true;
		KS.pop_back();
		ANS.pop_back();
	}
	return false;
}
bool Solve()
{
	int now=1;
	for(int i=0;i<=9;i++)
	{
		KS.push_back(i);
		for(int j=0;j<ET[i].size();j++)
		{
			const Edge &e=ET[i][j];
			if(e.d==0)continue;
			assert(e.d>=now);
			now=e.d;
			ANS.push_back(e.d);
			KS.push_back((e.u+e.d*K)%10);
			if(Dfs(e.u,e.d,i+(e.u+e.d*K)%10))return true;
			KS.pop_back();
			ANS.pop_back();
		}
		KS.pop_back();
	}
	return false;
}
int main()
{
	N=2,X=9,Y=9,K=5;
//	freopen("out.txt","w",stdout);
	scanf("%d%d%d%d",&N,&X,&Y,&K);
	for(int i=0;i<10;i++)for(int j=N*9;j>=0;j--)for(int k=(N+1)*9;k>=0;k--)VIS[i][j][k]=-1;
	for(int i=0;i<10;i++)ET[i].clear();
	for(int i=0;i<10;i++)//initial number
	{
		for(int n=0,v,c;n<10;n++)//add n*k
		{
			v=i+n*K,c=v/10+v%10-i;
			ET[v/10].push_back(Edge(n,i,c));
		}
	}
	for(int i=0;i<10;i++)sort(ET[i].begin(),ET[i].end());
	if(!Solve())puts("-1");
	else
	{
		while(ANS.size()<N)ANS.push_back(0);
		for(int i=0;i<N;i++)printf("%d",ANS[i]);
		puts("");
	}
	return 0;
}
