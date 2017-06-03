#include<cstdio>
#include<cstdlib>
#include<map>
#include<string>
using namespace std;
int N,MAT[200][200];
map<string,int> IDX;
char tstr[2][31];
int getidx(char *a)
{
	if(IDX.find(a)!=IDX.end())return IDX[a];
	int sz=IDX.size();
	IDX[a]=sz;
	return sz;
}
void setMAT(int i,int j,int w)
{
	if(i<j)i^=j^=i^=j;
	MAT[i][j]=w;
}
int getMAT(int i,int j)
{
	if(i<j)i^=j^=i^=j;
	return MAT[i][j];
}
void getmax(int &a,int b){if(b>a)a=b;}
#define min(x,y) (x)<(y)?(x):(y)
int solve(int sp,int ep)
{
	for(int k=0;k<N;k++)
	{
		for(int i1=0;i1<N;i1++)
		{
			for(int i2=0;i2<i1;i2++)
			{
				getmax(MAT[i1][i2],min(getMAT(i1,k),getMAT(k,i2)));
			}
		}
	}
	return getMAT(sp,ep);
}
int main()
{
	freopen("in.txt","r",stdin);
	freopen("New.txt","w",stdout);
	int r,kase=1;
	while(scanf("%d%d",&N,&r)==2&&(N||r))
	{
		IDX.clear();
		for(int i=0;i<N;i++)for(int j=0;j<=i;j++)MAT[i][j]=0;
		while(r--)
		{
			int w;scanf("%s%s%d",tstr[0],tstr[1],&w);
			setMAT(getidx(tstr[0]),getidx(tstr[1]),w);
		}
		scanf("%s%s",tstr[0],tstr[1]);
		printf("Scenario #%d\n%d tons\n\n",kase++,solve(getidx(tstr[0]),getidx(tstr[1])));
	}
	return 0;
}
