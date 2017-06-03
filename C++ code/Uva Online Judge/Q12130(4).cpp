#include<cstdio>
#include<queue>
#define min(x,y) (x<y?x:y)
using namespace std;
int T,H,W,D,M[500][500],VIS[500][500],CNT,ANS;
struct Point
{
	int x,y,h;
	bool operator<(Point p)const{return h<p.h;}
	Point(){}
	Point(int x,int y,int h):x(x),y(y),h(h){}
};
priority_queue<Point> S;
queue<Point> PQ;
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
		S=priority_queue<Point>();
		PQ=queue<Point>();
		ANS=0;
		for(int h=0;h<H;h++)
		{
			for(int w=0;w<W;w++)
			{
				VIS[w][h]=-1;
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
//				printf("bef\n");
//				showVIS();
			PQ.push(S.top());S.pop();
			bool found=true;
			CNT=0;
			while(!PQ.empty())
			{
				Point p=PQ.front();PQ.pop();
				if(VIS[p.x][p.y]!=-1)
				{
					if(VIS[p.x][p.y]>top)found=false;
					continue;
				}
				VIS[p.x][p.y]=top;
				if(M[p.x][p.y]==top)
				{
					CNT++;
//					printf("%d %d =%d\n",p.x,p.y,p.h);
				}
				int &x=p.x,&y=p.y,&h=p.h;
				if(x&&h-M[x-1][y]<D)PQ.push(Point(x-1,y,h));
				if(y&&h-M[x][y-1]<D)PQ.push(Point(x,y-1,h));
				if(x+1<W&&h-M[x+1][y]<D)PQ.push(Point(x+1,y,h));
				if(y+1<H&&h-M[x][y+1]<D)PQ.push(Point(x,y+1,h));
			}
//				printf("aft\n");
//				showVIS();
			if(found)ANS+=CNT;
		}
		printf("%d\n",ANS);
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
2 5 1
 2 1 4 5 2
 4 1 4 3 4

*/
