#include<cstdio>
#include<cstdlib>
#include<stack>
using namespace std;
int GARBAGE[101][101],R,C;
struct Pre
{
	int r,c,gs,g,cnt;
	bool operator>(Pre a){return gs+a.g>a.gs;}
};
Pre PRE[100][100];
void getmax(int r1,int c1,int r2,int c2)
{
	Pre &p=PRE[r1][c1],&tp=PRE[r2][c2];
	if(tp.gs+p.g<p.gs)return;
	else if(tp.gs+p.g>p.gs)p.cnt=0;
	p.gs=tp.gs+p.g;
	p.cnt+=tp.cnt;
	p.r=r2,p.c=c2;
}
int main()
{
	freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d%d",&R,&C)==2&&!(R==-1&&C==-1))
	{
		for(int r=1;r<=R;r++)
		{
			for(int c=1;c<=C;c++)
			{
				PRE[r][c]=(Pre){-1,-1,-1,0,0};
			}
		}
		int a,b;
		while(scanf("%d%d",&a,&b)==2&&(a||b))
		{
			PRE[a][b].g=1;
		}
		PRE[1][1].gs=PRE[1][1].g;
		PRE[1][1].cnt=1;
		for(int c=2;c<=C;c++)
		{
			getmax(1,c,1,c-1);
		}
		for(int r=2;r<=R;r++)
		{
			getmax(r,1,r-1,1);
			for(int c=2;c<=C;c++)
			{
				getmax(r,c,r-1,c);
				getmax(r,c,r,c-1);
			}
		}
		for(int r=1;r<=R;r++)
		{
			for(int c=1;c<=C;c++)
			{
				printf(" (%d,%d)",PRE[r][c].g,PRE[r][c].gs);
			}printf("\n");
		}
		printf("CASE#%d:",kase++);
		Pre ans=PRE[R][C];
		printf(" %d %d",ans.gs,ans.cnt);
		stack<Pre> s;
		while(!(ans.r==-1&&ans.c==-1))
		{
			if(ans.g)s.push(ans);
			ans=PRE[ans.r][ans.c];
		}
		while(!s.empty())
		{
			Pre p=s.top();s.pop();
			printf(" (%d,%d)",p.r,p.c);
		}
		printf("\n");
	}
	return 0;
}
