#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int R,C,HEIGHT[10000];
vector<int> TO[10000];
int main()
{
	freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d%d",&R,&C)==2&&!(R==-1&&C==-1))
	{
		for(int r=0;r<R;r++)
		{
			for(int c=0;c<C;c++)
			{
				TO[r*C+c].clear();
				HEIGHT[r*C+c]=0;
			}
		}
		int a,b;
		while(scanf("%d%d",&a,&b)==2&&(a||b))
		{
			a--,b--;
			PRE[a][b].g=1;
		}
	}
	return 0;
}
