#include<cstdio>
#include<vector>
using namespace std;
int T,W,H;
char MAT[100][101];
struct Point
{
	int x,y;
	Point(){}
	Point(int x,int y):x(x),y(y){}
};
vector<Point>CYC[50];
inline int sq(int a){return a*a;}
inline int hypot(int a,int b){return sq(a)+sq(b);}
void BuildCYC(int r)
{
	vector<Point>&cyc=CYC[r];
	Point p=Point(r,0);
	int bound=sq(r*2);
	while(p.y<r)
	{
		cyc.push_back(p);
		static int dis;
		dis=hypot((p.x-r)*2+1,(r-p.y)*2-1);
		if(dis<=bound)p.x++;
		if(dis>=bound)p.y++;
	}
	int sz=cyc.size();
	for(int i=0,r2=r*2;i<sz;i++)
	{
		static Point p;
		static int &x=p.x,&y=p.y;
		p=cyc[i];
		cyc.push_back(Point(r2-y,x));
		cyc.push_back(Point(r2-x,r2-y));
		cyc.push_back(Point(y,r2-x));
	}
//	printf("sz[%d]=%d\n",r,cyc.size()); 
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	for(int r=5;r<50;r++)BuildCYC(r);
//for(int i=0;i<=10;i++){for(int j=0;j<=10;j++)MAT[i][j]='0';MAT[i][11]=0;}
//for(int i=0;i<CYC[5].size();i++)MAT[CYC[5][i].y][CYC[5][i].x]='1';
//for(int i=0;i<=10;i++)puts(MAT[i]);
	while(T--)
	{
		scanf("%d%d",&W,&H);
		for(int h=0;h<H;h++)scanf("%s",MAT[h]);
		vector<int>ansr,ansx,ansy;
		int r,x,y,i,bound_1,bound_2,bound_3,sz,cnt;
		for(r=5,bound_1=((W<H?W:H)-1)/2;r<=bound_1;r++)
		{
			vector<Point>&cyc=CYC[r];
			sz=cyc.size();
			for(x=0,bound_2=W-1-r*2;x<=bound_2;x++)
			{
				for(y=0,bound_3=H-1-r*2;y<=bound_3;y++)
				{
					cnt=0;
					for(i=0;i<sz;i++)
					{
						Point &p=cyc[i];
						static int x0,y0;
						x0=x+p.x,y0=y+p.y;
						if(MAT[y0][x0]=='1')cnt++;
					}
					if(cnt*10/7>=sz)ansr.push_back(r),ansx.push_back(x+r),ansy.push_back(y+r);
				}
			}
		}
		static int kase=1;
		printf("Case %d: %d",kase++,ansr.size());
		for(int i=0;i<ansr.size();i++)printf(" (%d,%d,%d)",ansr[i],ansx[i],ansy[i]);
		puts("");
	}
	return 0;
}
