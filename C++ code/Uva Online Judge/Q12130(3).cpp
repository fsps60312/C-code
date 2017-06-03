#include<cstdio>
#include<queue>
#include<vector>
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
vector<Point> ANS;
priority_queue<Point> S,PQ;
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
//	freopen("out.txt","w",stdout);
	scanf("%d",&T);
//	int cnt=0;
	while(T--)
	{
		scanf("%d%d%d",&H,&W,&D);
		PQ=priority_queue<Point>();
		S=priority_queue<Point>();
		ANS.clear();
		for(int h=0;h<H;h++)
		{
			for(int w=0;w<W;w++)
			{
				VIS[w][h]=0;
				int &v=M[w][h];
				scanf("%d",&v);
				S.push(Point(w,h,v));
			}
		}
//		printf("showM\n");showM();
//		printf("*%d\n",PQ.top().h);
		while(!S.empty())
		{
			int top=S.top().h;
			while(!S.empty()&&S.top().h==top)
			{
				PQ.push(S.top());S.pop();
			}
				printf("bef\n");
				showVIS();
			while(!PQ.empty())
			{
				Point p=PQ.top();PQ.pop();
				if(VIS[p.x][p.y])continue;
				VIS[p.x][p.y]=1;
				if(M[p.x][p.y]==top)
				{
					ANS.push_back(p);
					printf("%d %d =%d\n",p.x,p.y,p.h);
				}
				int &x=p.x,&y=p.y,&h=p.h;
				if(x&&M[x-1][y]-h<D)PQ.push(Point(x-1,y,min(h,M[x-1][y])));
				if(y&&M[x][y-1]-h<D)PQ.push(Point(x,y-1,min(h,M[x][y-1])));
				if(x+1<W&&M[x+1][y]-h<D)PQ.push(Point(x+1,y,min(h,M[x+1][y])));
				if(y+1<H&&M[x][y+1]-h<D)PQ.push(Point(x,y+1,min(h,M[x][y+1])));
			}
				printf("aft\n");
				showVIS();
		}
		printf("%d\n",ANS.size());
//		cnt++;
//		if(cnt==671)
//		{
//			printf("%d %d %d\n",H,W,D);
//			for(int i=0;i<H;i++)
//			{
//				for(int j=0;j<W;j++)
//				{
//					printf(" %d",M[j][i]);
//				}
//				puts("");
//			}
//			return 0;
//		}
	}
	return 0;
}
/*
1
3 4 2
 5 1 1 2
 1 4 1 1
 3 3 2 3

*/
