#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
#include<queue>
#include<cassert>
using namespace std;
int N,UNIT;
vector<int>W;
void GetW()
{
	set<int>s;
	for(int i=0,w;i<N;i++)scanf("%d",&w),s.insert(w);
	UNIT=*s.begin();
	s.erase(s.begin());
	W.clear();
	for(const int v:s)assert(v%UNIT==0),W.push_back(v/UNIT);
	N=W.size();
}
//4 3 6: 6
//2 0 1 1
//0 1 1 1
//
//2 0 1 1
//0 1 1 1
//
//
int VIS[100000001],KASE=0;
int PRE[100000001];
int main()
{
//	freopen("inn.txt","r",stdin);
	for(int i=0;i<=100000000;i++)VIS[i]=0;
	while(scanf("%d",&N)==1&&N)
	{
		static int kase=1;
		printf("Set #%d\n",kase++);
		GetW();
		for(int a,b;scanf("%d%d",&a,&b)==2&&!(a==0&&b==0);)
		{
			assert(a>0&&b>0);
			KASE++;
			queue<int>qu,qpre;
			qu.push(a),qpre.push(-1);
			while(!qu.empty())
			{
				const int u=qu.front(),pre=qpre.front();
				qu.pop(),qpre.pop();
				if(VIS[u]==KASE)continue;
				VIS[u]=KASE,PRE[u]=pre;
				if(u==b)break;
				for(int i=0;i<N;i++)
				{
					if(u%W[i]==0)qu.push(u/W[i]),qpre.push(u);
					if(u<=100000000/W[i])qu.push(u*W[i]),qpre.push(u);
				}
			}
			printf("Ratio %d:%d:",a,b);
			if(VIS[b]!=KASE)puts(" Impossible");
			else
			{
				int u=b;
				for(;u!=a;u=PRE[u])
				{
					if(PRE[u]<u)printf(" %d:%d",UNIT,UNIT*(u/PRE[u]));
					else printf(" %d:%d",UNIT*(PRE[u]/u),UNIT);
				}
				puts("");
			}
		}
		puts("");
	}
	return 0;
}
