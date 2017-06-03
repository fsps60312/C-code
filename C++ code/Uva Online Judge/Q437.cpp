#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
struct Point
{
	int x,y;
	bool operator>(Point a)
	{
		return (x>a.x&&y>a.y)||(x>a.y&&y>a.x);
	}
};
struct Cube
{
	int x,y,z;
	Point getarea(int a)
	{
		if(a==0)return (Point){y,z};
		else if(a==1)return (Point){x,z};
		else return (Point){x,y};
	}
	int getheight(int a)
	{
		if(a==0)return x;
		else if(a==1)return y;
		else return z;
	}
};
vector<Cube> CUBE;
vector<Point> TO[90];
int BEST[90];
void getmax(int &a,int b){if(b>a)a=b;}
int getans(int u)
{
	if(BEST[u]!=-1)return BEST[u];
	BEST[u]=0;
	for(int i=0;i<TO[u].size();i++)
	{
		Point &p=TO[u][i];
		getmax(BEST[u],getans(p.x)+p.y);
	}
	return BEST[u];
}
int N;
int main()
{
	//freopen("in.txt","r",stdin);
	int kase=1;
	while(scanf("%d",&N)==1&&N)
	{
		CUBE.clear();
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<3;j++)
			{
				TO[i*3+j].clear();
				BEST[i*3+j]=-1;
			}
			int x,y,z;scanf("%d%d%d",&x,&y,&z);
			CUBE.push_back((Cube){x,y,z});
		}
		for(int i1=0;i1<CUBE.size();i1++)
		{
			for(int i2=0;i2<CUBE.size();i2++)
			{
				for(int a1=0;a1<3;a1++)
				{
					for(int a2=0;a2<3;a2++)
					{
						if(CUBE[i1].getarea(a1)>CUBE[i2].getarea(a2))
						{
							TO[i1*3+a1].push_back((Point){i2*3+a2,CUBE[i2].getheight(a2)});
						}
					}
				}
			}
		}
		int ans=0;
		for(int i=0;i<N;i++)
		{
			for(int a=0;a<3;a++)
			{
				getmax(ans,getans(i*3+a)+CUBE[i].getheight(a));
			}
		}
		printf("Case %d: maximum height = %d\n",kase++,ans);
	}
	return 0;
}
