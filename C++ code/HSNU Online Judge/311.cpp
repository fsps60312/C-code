#include<cstdio>
#include<cassert>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
const int WEST=1<<0,NORTH=1<<1,EAST=1<<2,SOUTH=1<<3;
void getmax(int &a,const int b){if(b>a)a=b;}
int R,C;
int GRID[2500],DJ[2500],SZ[2500];
int Find(const int a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
void Merge(int a,int b,int &cnt,int &mx){if((a=Find(a))==(b=Find(b)))return;getmax(mx,SZ[a]+=SZ[b]),SZ[b]=0,DJ[b]=a,cnt--;}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(2,"%d%d",&C,&R);
	for(int i=0;i<R*C;i++)DJ[i]=i,SZ[i]=1;
	int cnt=R*C,maxarea=1;
	for(int i=0;i<R*C;i++)
	{
		int &g=GRID[i];
		scanf(1,"%d",&g);
		if(!(g&WEST))Merge(i,i-1,cnt,maxarea);
		if(!(g&NORTH))Merge(i,i-C,cnt,maxarea);
		if(!(g&EAST))Merge(i,i+1,cnt,maxarea);
		if(!(g&SOUTH))Merge(i,i+C,cnt,maxarea);
	}
//	for(int i=0;i<R;i++)
//	{
//		for(int j=0;j<C;j++)printf(" %d",SZ[Find(i*C+j)]);
//		puts("");
//	}
	int maxmerge=0,wall_loc=-1;
	char wall_direction='\0';
	for(int c=0;c<C;c++)for(int r=R-1;r>=0;r--)
	{
		const int u=r*C+c;
		const int a=Find(u);
		int b;
		if(r-1>=0&&a!=(b=Find(u-C))&&SZ[a]+SZ[b]>maxmerge)maxmerge=SZ[a]+SZ[b],wall_loc=u,wall_direction='N';
		if(c+1<C&&a!=(b=Find(u+1))&&SZ[a]+SZ[b]>maxmerge)maxmerge=SZ[a]+SZ[b],wall_loc=u,wall_direction='E';
	}
	assert(wall_loc!=-1);
	printf("%d\n",cnt);
	printf("%d\n",maxarea);
	printf("%d\n",maxmerge);
	printf("%d %d %c\n",wall_loc/C+1,wall_loc%C+1,wall_direction);
	return 0;
}
