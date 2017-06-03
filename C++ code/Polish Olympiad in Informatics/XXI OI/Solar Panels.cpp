#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
int GetNxt(const int l,const int r,const int x)
{
	const int y=r/x+1;
	//r/x=y
	return r/y;
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0,w1,w2,h1,h2;i<N;i++)
		{
			scanf("%d%d%d%d",&w1,&w2,&h1,&h2),--w1,--h1;
			int x=1e9+1;
			while(w1/x==w2/x||h1/x==h2/x)
			{
				x=max(GetNxt(w1,w2,x),GetNxt(h1,h2,x));
			}
			printf("%d\n",x);
		}
	}
}
