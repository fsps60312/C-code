#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
vector<int>L,R;
struct Pair
{
	int v,i;
	bool operator<(const Pair &p)const{return i<p.i;}
}S[65000];
int N;
int main()
{
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		static int v;scanf("%d",&v);
		S[v-1].v=v,S[v-1].i=i;
	}
	static char tmp[2];
	int l=-1,r=N;
	while(scanf("%s",tmp)==1)
	{
		static int x;
		switch(tmp[0])
		{
			case'A':
			{
				scanf("%d",&x);
				S[--x].i=l--;
			}break;
			case'B':
			{
				scanf("%d",&x);
				S[--x].i=r++;
			}break;
			default:
			{
				sort(S,S+N);
				for(int i=0;i<N;i++)
				{
					if(i)printf(" ");
					printf("%d",S[i].v);
				}
				puts("");
				return 0;
			}break;
		}
	}
	return 0;
}
