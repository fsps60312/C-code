#include<cstdio>
#include<vector>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int H,W,N,K,GRID[251][251],SUM[251][251],MN[251][251];
int Sum(int h1,int h2,int w1,int w2){return SUM[h2][w2]-SUM[h1-1][w2]-SUM[h2][w1-1]+SUM[h1-1][w1-1];}
struct Rect
{
	int h1,h2,w1,w2;
	Rect(){}
	Rect(const int _h1,const int _h2,const int _w1,const int _w2):h1(_h1),h2(_h2),w1(_w1),w2(_w2){}
};
vector<Rect>RECT;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d%d%d%d",&H,&W,&N,&K);
	for(int i=0;i<=H;i++)for(int j=0;j<=W;j++)GRID[i][j]=0,MN[i][j]=INF;
	for(int i=0,y,x;i<N;i++)
	{
		scanf("%d%d",&y,&x);
		GRID[y][x]++;
	}
	for(int i=0;i<=H;i++)SUM[i][0]=0;
	for(int i=0;i<=W;i++)SUM[0][i]=0;
	for(int i=1;i<=H;i++)for(int j=1;j<=W;j++)SUM[i][j]=GRID[i][j]+SUM[i-1][j]+SUM[i][j-1]-SUM[i-1][j-1];
	RECT.clear();
	for(int h1=1;h1<=H;h1++)for(int h2=h1;h2<=H;h2++)
	{
		for(int l=1,r=1;l<=W;l++)
		{
			while(r<=W&&Sum(h1,h2,l,r)<K)r++;
			if(r>W)break;
			if(Sum(h1,h2,l,r)==K)
			{
				RECT.push_back(Rect(h1,h2,l,r));
				getmin(MN[h1][l],2*(h2-h1+1)+2*(r-l+1));
			}
		}
	}
	for(int i=H-1;i>=1;i--)for(int j=1;j<=W;j++)getmin(MN[i][j],MN[i+1][j]);
	for(int i=1;i<=H;i++)for(int j=W-1;j>=1;j--)getmin(MN[i][j],MN[i][j+1]);
	int ans=INF;
	for(int i=0;i<RECT.size();i++)
	{
		const Rect &r=RECT[i];
		int v=INF;
		if(r.h2<H)getmin(v,MN[r.h2+1][1]);
		if(r.w2<W)getmin(v,MN[1][r.w2+1]);
		if(v==INF)continue;
		getmin(ans,2*(r.h2-r.h1+r.w2-r.w1+2)+v);
	}
	if(ans==INF)puts("NO");
	else printf("%d\n",ans);
	return 0;
}
