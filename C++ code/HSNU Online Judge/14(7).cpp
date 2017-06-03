#include<cstdio>
#include<map>
#include<vector>
//#include<cassert>
using namespace std;
int T,N,M,K,GRID[150][10],POW[10];
inline int D(const int &s,const int &i){return s/POW[i]%4;}
inline bool Move(const int &s,const int &r,const int &c,const int &w,const int &h,int &t)
{
	if(r+h>N||c+w>M)return false;
	static int i,j;
	for(i=0;i<w;i++)if(D(s,c+i)>0)return false;
	for(i=0;i<h;i++)
	{
		for(j=0;j<w;j++)
		{
			if(GRID[r+i][c+j])return false;
		}
	}
	t=s;
	for(i=0;i<w;i++)t+=POW[c+i]*h;
	return true;
}
int TMP[150][10],ANS[150][10];
int DP[2][1<<20];
vector<int>V[2];
void getmax(int &a,const int &b,vector<int>&v,const int &i){if(a==-1)v.push_back(i);if(b>a)a=b;}
int Get(int r,int c,int d)
{
	static int i,j;
	if(++c==M)c=0,r++;
	if(r==N-1)
	{
		int ans=-1;
		for(i=0;i<V[d].size();i++)
		{
			int &s=V[d][i];
			int &v=DP[d][s];
			ans=max(ans,v);
			v=-1;
		}
		V[d].clear();
		return ans;
	}
//	printf("(%d,%d):%d\n",r,c,V[d].size());
//	for(i=0;i<(1<<20);i++)assert(DP[d^1][i]==-1);
	
	for(i=0;i<V[d].size();i++)
	{
		int &s=V[d][i];
		int &v=DP[d][s];
		if(!c)for(j=0;j<M;j++)if(D(s,j))s-=POW[j];
		getmax(DP[d^1][s],v,V[d^1],s);
		static int t;
		if(Move(s,r,c,2,3,t))getmax(DP[d^1][t],v+1,V[d^1],t);
		if(Move(s,r,c,3,2,t))getmax(DP[d^1][t],v+1,V[d^1],t);
		v=-1;
	}
	V[d].clear();
	return Get(r,c,d^1);
}
int main()
{
//	freopen("in.txt","r",stdin);
	POW[0]=1;
	for(int i=1;i<10;i++)POW[i]=POW[i-1]*4;
	for(int i=0;i<2;i++)for(int j=0;j<(1<<20);j++)DP[i][j]=-1;
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d%d",&N,&M,&K);
			for(int i=0;i<N;i++)
			{
				for(int j=0;j<M;j++)
				{
					GRID[i][j]=0;
				}
			}
			for(int i=0;i<K;i++)
			{
				static int x,y;
				scanf("%d%d",&x,&y);
				x--,y--;
				GRID[x][y]=1;
			}
			DP[0][0]=0;
			V[0].push_back(0);
			printf("%d\n",Get(0,-1,0));
		}
	}
	return 0;
}
