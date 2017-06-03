#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N,M,MAT[100][100];
void Expand(int s,int &ans)
{
	for(int i=s+1;i<N;i++)
	{
		for(int j=i+1;j<N;j++)
		{
			int &a=MAT[s][i],&b=MAT[s][j];
			if(a==INF||b==INF)continue;
			int &l=MAT[i][j];
			if(l!=INF&&a+b+l<ans)
			{
				printf("(%d<->%d<->%d)ans=%d\n",i+1,s+1,j+1,a+b+l);
				ans=a+b+l;
			}
			if(l>a+b)printf("%d:(%d,%d):%d->%d\n",s+1,i+1,j+1,l,a+b);
			l=MAT[j][i]=min(l,a+b);
		}
	}
//	printf("%d:ans=%d\n",s+1,ans);
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)MAT[i][j]=INF;
		for(int i=0,a,b,c;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			a--,b--;
			if(c<MAT[a][b]&&a!=b)MAT[a][b]=MAT[b][a]=c;
		}
		int ans=INF;
		for(int i=0;i<N;i++)
		{
			Expand(i,ans);
		}
		if(ans==INF)puts("No solution.");
		else printf("%d\n",ans);
	}
	return 0;
}
