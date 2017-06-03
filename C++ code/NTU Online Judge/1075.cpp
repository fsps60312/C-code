#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
struct DisjointSets
{
	int S[1000000];
	void Clear(const int N){for(int i=0;i<N;i++)S[i]=i;}
	int Find(const int a){return S[a]==a?a:(S[a]=Find(S[a]));}
	bool Merge(int a,int b){return (a=Find(a))==(b=Find(b))?false:(S[a]=b,true);}
}DJ;
int H,W,Q;
int G[1000000],ANS[1000000];
vector<int>QUERIES[1000001],LOC[1000001];
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d",&H,&W);
		for(int i=0;i<H;i++)for(int j=0;j<W;j++)scanf("%d",&G[i*W+j]);
		scanf("%d",&Q);
		for(int i=0;i<=1000000;i++)QUERIES[i].clear(),LOC[i].clear();
		for(int i=0,v;i<Q;i++)scanf("%d",&v),QUERIES[v].push_back(i);
		DJ.Clear(H*W);
		for(int i=0;i<H*W;i++)LOC[G[i]].push_back(i);
		int island=0;
		for(int h=1000000;h>=0;h--)
		{
			for(const int qi:QUERIES[h])ANS[qi]=island;
			static const int d[4][2]={{-1,0},{0,1},{1,0},{0,-1}};
			for(const int loc:LOC[h])
			{
				++island;
				for(int i=0;i<4;i++)
				{
					const int r=loc/W+d[i][0],c=loc%W+d[i][1];
					if(r<0||r>=H||c<0||c>=W)continue;
					if(G[r*W+c]>=h&&DJ.Merge(r*W+c,loc))--island;
				}
			}
		}
		for(int i=0;i<Q;i++)printf("%d\n",ANS[i]);
	}
	return 0;
}
