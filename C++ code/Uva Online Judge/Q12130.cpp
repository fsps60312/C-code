#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
#define min(x,y) (x<y?x:y)
using namespace std;
int T,H,W,D,M[500][500],VIS[500][500];
struct Point
{
	int x,y,h;
	bool operator<(Point p)const{return h<p.h;}
	Point(){}
	Point(int x,int y,int h):x(x),y(y),h(h){}
};
vector<Point> S,ANS;
priority_queue<Point> PQ;
void showM()
{
	for(int i=0;i<H;i++)
	{
		for(int j=0;j<W;j++)
		{
			printf("%d",M[j][i]);
		}
		puts("");
	}
}
void showVIS()
{
	for(int i=0;i<H;i++)
	{
		for(int j=0;j<W;j++)
		{
			printf("%d",VIS[j][i]);
		}
		puts("");
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&H,&W,&D);
		PQ=priority_queue<Point>();
		ANS.clear(),S.clear();
		for(int h=0;h<H;h++)
		{
			for(int w=0;w<W;w++)
			{
				VIS[w][h]=0;
				int &v=M[w][h];
				scanf("%d",&v);
				S.push_back(Point(w,h,v));
			}
		}
		sort(S.begin(),S.end());
//		printf("showM\n");showM();
//		printf("*%d\n",PQ.top().h);
		for(int i=S.size()-1;i>=0;i--)
		{
//			printf("h=%d\n",S[i].h);
			bool toshow=false;//!VIS[S[i].x][S[i].y];
			if(toshow)
			{
				printf("bef(%d,%d):%d\n",S[i].x,S[i].y,S[i].h);
				showVIS();
			}
			PQ.push(S[i]);
			while(!PQ.empty())
			{
				Point p=PQ.top();PQ.pop();
				if(VIS[p.x][p.y])continue;
				VIS[p.x][p.y]=1;
				if(p.h==S[i].h)
				{
					ANS.push_back(p);
//					printf("%d %d =%d\n",p.x,p.y,p.h);
				}
				int &x=p.x,&y=p.y,&h=p.h;
				if(x&&M[x-1][y]-h<D)PQ.push(Point(x-1,y,min(h,M[x-1][y])));
				if(y&&M[x][y-1]-h<D)PQ.push(Point(x,y-1,min(h,M[x][y-1])));
				if(x+1<W&&M[x+1][y]-h<D)PQ.push(Point(x+1,y,min(h,M[x+1][y])));
				if(y+1<H&&M[x][y+1]-h<D)PQ.push(Point(x,y+1,min(h,M[x][y+1])));
			}
			if(toshow)
			{
				printf("aft(%d,%d):%d\n",S[i].x,S[i].y,S[i].h);
				showVIS();
			}
		}
		printf("%d\n",ANS.size());
	}
	return 0;
}
