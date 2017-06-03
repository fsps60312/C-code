#include<cstdio>
#include<vector>
#define max(x,y) (x>y?x:y)
using namespace std;
int T,N,W,H;
bool getmax(int &a,int b){if(b>a){a=b;return true;}return false;}
void getmin(int &a,int b){if(b<a)a=b;}
struct Point
{
	int x,y;
	Point(){}
	Point(int x,int y):x(x),y(y){}
};
vector<Point> TREE;
int Squa(int x,int y,int minw)
{
	int ans=min(W-x,H-y);
	for(int i=0;i<N;i++)
	{
		Point &p=TREE[i];
		if(p.x<=x||p.y<=y)continue;
		getmin(ans,max(p.x-x,p.y-y));
	}
	return ans>minw?ans:0;
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		if(kase++>1)printf("\n");
		scanf("%d%d%d",&N,&W,&H);
		TREE.clear();
		for(int i=0,x,y;i<N;i++)
		{
			scanf("%d%d",&x,&y);
			TREE.push_back(Point(x,y));
		}
		int ans=0;Point p;
		if(getmax(ans,Squa(0,0,0)))p=Point(0,0);
		for(int i=0;i<N;i++)
		{
			if(getmax(ans,Squa(0,TREE[i].y,TREE[i].x)))p=Point(0,TREE[i].y);
			if(getmax(ans,Squa(TREE[i].x,0,TREE[i].y)))p=Point(TREE[i].x,0);
		}
		for(int i1=0;i1<N;i1++)
		{
			for(int i2=0;i2<N;i2++)
			{
				Point &p1=TREE[i1],&p2=TREE[i2];
				if(p1.y>p2.y&&p1.x<p2.x)if(getmax(ans,Squa(p1.x,p2.y,max(p1.y-p2.y,p2.x-p1.x))))p=Point(p1.x,p2.y);
				else if(p1.y<p2.y&&p1.x>p2.x)if(getmax(ans,Squa(p2.x,p1.y,max(p2.y-p1.y,p1.x-p2.x))))p=Point(p2.x,p1.y);
			}
		}
		printf("%d %d %d\n",p.x,p.y,ans);
	}
	return 0;
}
