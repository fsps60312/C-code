#include<cstdio>
#include<cassert>
using namespace std;
int R,C;
char S[4000][4001];
bool VIS[2][4000];
int main()
{
//	freopen("in.txt","r",stdin);
	assert(scanf("%d%d",&C,&R)==2);
	{
		for(int i=0;i<R;i++)assert(scanf("%s",S[i])==1);
		int d=0;
		for(int i=0;i<C;i++)VIS[0][i]=true;
		for(int i=0;i<R;i++,d^=1)
		{
			for(int j=0;j<C;j++)VIS[d^1][j]=false;
			for(int j=0;j<C;j++)if(VIS[d][j])
			{
				switch(S[i][j])
				{
					case'/':
					{
						if(j-1>=0&&S[i][j-1]=='/')assert(!VIS[d^1][j-1]),VIS[d^1][j-1]=true;
					}break;
					case'\\':
					{
						if(j+1<C&&S[i][j+1]=='\\')assert(!VIS[d^1][j+1]),VIS[d^1][j+1]=true;
					}break;
					default:assert(0);break;
				}
			}
		}
		int ans=0;
		for(int i=0;i<C;i++)if(VIS[d][i])++ans;
		if(!ans)assert(0),printf("I can't escape.\n");
		else printf("%d\n",ans);
//		break;
	}
	assert(scanf("%d",&R)!=1);
	return 0;
}
