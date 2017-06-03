#include<cstdio>
#include<cassert>
using namespace std;
int N;
int S[1025][1025];
struct Bit
{
	void clear(){for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)S[i][j]=0;}
	int lowbit(const int &x){return x&(-x);}
	void Add(int x,int _y,const int &v)
	{
		while(x<=N)
		{
			int y=_y;
			while(y<=N)
			{
				S[x][y]+=v;
				y+=lowbit(y);
			}
			x+=lowbit(x);
		}
	}
	int Query(int x,int _y)
	{
		int ans=0;
		while(x)
		{
			int y=_y;
			while(y)
			{
				ans+=S[x][y];
				y-=lowbit(y);
			}
			x-=lowbit(x);
		}
		return ans;
	}
}BIT;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	BIT.clear();
	int type;
	while(scanf("%d",&type)==1)
	{
		if(type==1)
		{
			static int x,y,v;
			scanf("%d%d%d",&x,&y,&v);
			x++,y++;
			BIT.Add(x,y,v);
		}
		else if(type==2)
		{
			static int x1,y1,x2,y2;
			int sum=0;
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			x1++,x2++,y1++,y2++;
			printf("%d\n",BIT.Query(x2,y2)-BIT.Query(x1-1,y2)-BIT.Query(x2,y1-1)+BIT.Query(x1-1,y1-1));
		}
		else assert(0);
	}
	return 0;
}
