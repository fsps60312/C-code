#include<cstdio>
#include<cassert>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;
struct Point
{
	int ID,X,Y;
	bool VIS;
	int D1,D2;//0¡ô1¡÷2¡õ3¡ö 
	Point(){}
	Point(const int _ID,const int _X,const int _Y,const int _D1,const int _D2):ID(_ID),X(_X),Y(_Y),VIS(false),D1(min(_D1,_D2)),D2(max(_D1,_D2)){}
};
int Direction(const int x0,const int y0,const int x1,const int y1)
{
	if(x1==x0)
	{
		if(y1>y0)return 0;
		if(y1<y0)return 2;
	}
	if(y1==y0)
	{
		if(x1>x0)return 1;
		if(x1<x0)return 3;
	}
	assert(0);return -1;
}
vector<Point>P;
void AddCorner(const int x0,const int y0,const int x1,const int y1,const int x2,const int y2)
{
	const Point p=Point((int)P.size(),x0,y0,Direction(x0,y0,x1,y1),Direction(x0,y0,x2,y2));
	P.push_back(p);
}
void AddWall(const int x1,const int y1,const int x2,const int y2)
{
	int x0=x1,y0=y1,dx,dy;
	switch(Direction(x1,y1,x2,y2))
	{
		case 0:dx=0,dy=1;break;
		case 1:dx=1,dy=0;break;
		case 2:dx=0,dy=-1;break;
		case 3:dx=-1,dy=0;break;
		default:assert(0);break;
	}
	while(!(((x0+=dx)==x2)&((y0+=dy)==y2)))
	{
		const Point p=Point((int)P.size(),x0,y0,Direction(x0,y0,x1,y1),Direction(x0,y0,x2,y2));
		P.push_back(p);
	}
}
int N;
void ReadInput()
{
	scanf("%d",&N);
	static int x[100000],y[100000];
	for(int i=0;i<N;i++)scanf("%d%d",&x[i],&y[i]);
	P.clear();
	for(int i=0;i<N;i++)
	{
		AddCorner(x[i],y[i],x[(i-1+N)%N],y[(i-1+N)%N],x[(i+1)%N],y[(i+1)%N]);
		AddWall(x[i],y[i],x[(i+1)%N],y[(i+1)%N]);
	}
}
bool CmpUR(const int a,const int b){return P[a].X+P[a].Y<P[b].X+P[b].Y;}
bool CmpUL(const int a,const int b){return P[a].X-P[a].Y<P[b].X-P[b].Y;}
map<int,vector<int> >UR,UL;
int EmitDirection(const int d1,const int d2)//0¡ù1¡û2¡ú3¡ø
{
	assert(d1<d2);
	if(d1==0&&d2==1)return 0;
	if(d1==1&&d2==2)return 1;
	if(d1==2&&d2==3)return 2;
	if(d1==0&&d2==3)return 3;
	assert(0);return -1;
}
int ReflectDirection(const int d0,const bool is_vertical)
{
	if(is_vertical)
	{
		switch(d0)
		{
			case 0:return 3;
			case 3:return 0;
			case 1:return 2;
			case 2:return 1;
			default:assert(0);return -1;
		}
	}
	else
	{
		switch(d0)
		{
			case 0:return 1;
			case 1:return 0;
			case 2:return 3;
			case 3:return 2;
			default:assert(0);return -1;
		}
	}
}
Point &NxtPoint(const Point &p,const int direction)//0¡ù1¡û2¡ú3¡ø
{
	switch(direction)
	{
		case 0:
		{
			const vector<int>&s=UL[p.X-p.Y];
			const int id=(int)(upper_bound(s.begin(),s.end(),p.ID,CmpUR)-s.begin());
			assert(0<=id&&id<(int)s.size());
			return P[s[id]];
		}
		case 1:
		{
			const vector<int>&s=UR[p.X+p.Y];
			const int id=(int)(upper_bound(s.begin(),s.end(),p.ID,CmpUL)-s.begin());
			assert(0<=id&&id<(int)s.size());
			return P[s[id]];
		}
		case 2:
		{
			const vector<int>&s=UL[p.X-p.Y];
			const int id=(int)(lower_bound(s.begin(),s.end(),p.ID,CmpUR)-s.begin())-1;
			assert(0<=id&&id<(int)s.size());
//			for(int i=0;i<(int)s.size();i++)printf(" (%d,%d)\n",P[s[i]].X,P[s[i]].Y);
//			printf("(%d,%d)->(%d,%d)(%d,%d)\n",p.X,p.Y,P[s[id]].X,P[s[id]].Y);//,P[s[id+1]].X,P[s[id+1]].Y);
			return P[s[id]];
		}
		case 3:
		{
			const vector<int>&s=UR[p.X+p.Y];
			const int id=(int)(lower_bound(s.begin(),s.end(),p.ID,CmpUL)-s.begin())-1;
			assert(0<=id&&id<(int)s.size());
			return P[s[id]];
		}
		default:assert(0);static Point error;return error;
	}
}
void Travel(Point &p,const int direction)//0¡ù1¡û2¡ú3¡ø
{
	printf("(%d,%d,%d)\n",p.X,p.Y,direction);
	if((p.D1+p.D2)%2==1)
	{
		const int d=EmitDirection(p.D1,p.D2);
		assert(d!=direction);
		if((d+2)%4==direction){assert(!p.VIS);p.VIS=true;return;}
		else
		{
			Travel(NxtPoint(p,direction),direction);
		}
	}
	else
	{
		const int nxt_direction=ReflectDirection(direction,p.D1%2==0);
		assert(!p.VIS);p.VIS=true;
		Travel(NxtPoint(p,nxt_direction),nxt_direction);
	}
}
int Solve()
{
	UR.clear(),UL.clear();
	for(int i=0;i<(int)P.size();i++)UR[P[i].X+P[i].Y].push_back(i),UL[P[i].X-P[i].Y].push_back(i);
	if(true)
	{
		map<int,vector<int> >::iterator it;
		for(it=UR.begin();it!=UR.end();++it)sort(it->second.begin(),it->second.end(),CmpUL);
		for(it=UL.begin();it!=UL.end();++it)sort(it->second.begin(),it->second.end(),CmpUR);
	}
	int ans=0;
	for(int i=0;i<(int)P.size();i++)if((P[i].D1+P[i].D2)%2==1&&!P[i].VIS)
	{
		P[i].VIS=true;
		const int d=EmitDirection(P[i].D1,P[i].D2);
		Travel(NxtPoint(P[i],d),d);
		++ans;
	}
	return ans;
}
int main()
{
	freopen("in.txt","r",stdin);
	ReadInput();
	printf("%d\n",Solve());
	return 0;
}
