#include<cstdio>
#include<cassert>
using namespace std;
struct DisjointSets
{
	int S[200001];
	void Clear(const int N){for(int i=0;i<N;i++)S[i]=i;}
	int Find(const int a){return S[a]==a?a:(S[a]=Find(S[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;S[a]=b;return true;}
}DJ,RI;
int N,Q;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&Q)==2)
	{
		DJ.Clear(N),RI.Clear(N+1);
		for(int type,x,y;Q--;)
		{
			scanf("%d%d%d",&type,&x,&y),--x,--y;
			switch(type)
			{
				case 1:
				{
					DJ.Merge(x,y);
				}break;
				case 2:
				{
					for(int cur=x;;)
					{
						cur=RI.Find(cur)+1;
						if(cur>y)break;
						RI.Merge(cur-1,cur),DJ.Merge(cur-1,cur);
					}
				}break;
				case 3:
				{
					puts(DJ.Find(x)==DJ.Find(y)?"YES":"NO");
				}break;
				default:assert(0);break;
			}
		}
	}
	return 0;
}
