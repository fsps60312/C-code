#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int T,N,MAT[100][100],VIS[100][100];
struct Pair{int x,y,z;bool operator<(Pair a){return x<a.x||(x==a.x&&y<a.y);}};
vector<Pair> ANS;
void addans(int a,int b)
{
	if(a>b)a^=b^=a^=b;
	ANS.push_back((Pair){a,b,MAT[a][b]});
	for(int i=ANS.size()-1;i>0;i--)
	{
		if(ANS[i-1]<ANS[i])break;
		Pair p=ANS[i];
		ANS[i]=ANS[i-1];
		ANS[i-1]=p;
	}
}
bool dfs(int a,int b)
{
	if(VIS[a][b])return true;
	VIS[a][b]=VIS[b][a]=1;
	for(int i=0;i<N;i++)
	{
		if(i==a||i==b)continue;
		if(MAT[a][i]+MAT[i][b]==MAT[a][b])return dfs(a,i)&&dfs(i,b);
		if(MAT[a][i]+MAT[i][b]<MAT[a][b])return false;
	}
	addans(a,b);
	return true;
}
bool solve()
{
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(i==j)continue;
			if(!dfs(i,j))return false;
		}
	}
	return true;
}
int main()
{
	int kase=1;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		ANS.clear();
		for(int i=0;i<N;i++)
		{
			MAT[i][i]=0;
			for(int j=0;j<N;j++)VIS[i][j]=0;
		}
		for(int i=1;i<N;i++)
		{
			for(int j=0;j<i;j++)
			{
				int a;scanf("%d",&a);
				MAT[i][j]=MAT[j][i]=a;
			}
		}
		printf("Case #%d:\n",kase++);
		if(!solve())printf("Need better measurements.\n");
		else
		{
			printf("%d\n",ANS.size());
			for(int i=0;i<ANS.size();i++)
			{
				printf("%d %d %d\n",ANS[i].x+1,ANS[i].y+1,ANS[i].z);
			}
		}
		printf("\n");
	}
	return 0;
}
