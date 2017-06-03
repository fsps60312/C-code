#include<cstdio>
#include<stack>
using namespace std;
int T,M,N;
char MAP[1001][1001];
int H[1001][1001];
void getmax(int &a,int b){if(b>a)a=b;}
struct Point
{
	int x,y;
	Point(){}
	Point(int x,int y):x(x),y(y){}
};
int main()
{
	scanf("%d",&T);
	for(int i=1;i<=1000;i++)H[i][0]=0;
	while(T--)
	{
		scanf("%d%d",&M,&N);
		for(int y=1;y<=M;y++)
		{
			for(int x=1;x<=N;x++)
			{
				char &c=MAP[x][y];
				scanf("%c",&c);
				if(c=='R')c=1;
				else if(c=='F')c=0;
				else x--;
			}
		}
		for(int h=1;h<=M;h++)for(int w=1;w<=N;w++)H[w][h]=(MAP[w][h]==1?0:H[w][h-1]+1);
		int ans=0;
		for(int y=1;y<=M;y++)
		{
			stack<Point> s;
			for(int x=1;x<=N;x++)
			{
				int &h=H[x][y];
				while(!s.empty()&&h<s.top().y)
				{
					Point p=s.top();s.pop();
					getmax(ans,(x-p.x)*p.y);
				}
				if(h)s.push(Point(x,h));
			}
			while(!s.empty())
			{
				Point p=s.top();s.pop();
				getmax(ans,(N+1-p.x)*p.y);
			}
		}
		printf("%d\n",ans*3);
	}
	return 0;
}
