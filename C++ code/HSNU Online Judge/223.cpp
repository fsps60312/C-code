#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int T,N,M,V,E,ANS[300000];
bool VIS[300000];
void dfsprint(int u,int dep)
{
	if(dep==M)return;
	dfsprint(u/N,dep+1);
	printf("%d",u%N);
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		V=1;
		for(int i=1;i<M;i++)V*=N;
		E=V*N;
		for(int i=0;i<E;i++)VIS[i]=false;
		int u=0,coda=N-1;
		for(int i=0;i<E;i++)
		{
//			printf("u=%d,",u);dfsprint(u,0);puts("");
			static bool found;found=false;
			for(int j=0;j<N;j++)
			{
				static int e;e=u*N+j;
				if(!VIS[e]&&!(e%V==0&&!coda&&i!=E-1))
				{
					VIS[e]=found=true;
					ANS[i]=e;
					u=e%V;
					if(!u)coda--;
					break;
				}
			}
			if(!found){for(int j=0;j<i;j++)printf("%d",ANS[j]%N);puts("");}
			assert(found);
		}
		printf("%d",ANS[0]%N);
		for(int i=1;i<E;i++)printf("%d",ANS[i]%N);
		puts("");
	}
	return 0;
}
