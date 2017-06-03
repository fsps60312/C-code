#include<bits/stdc++.h>
using namespace std;
int N;
struct Point
{
	int x,y;
	void canf(){scanf("%d%d",&x,&y);}
}O;
struct Wall
{
	Point a,b;
	void canf(){a.canf(),b.canf();}
}WALL[500];
bool AtRange(const int &o,const int &a,const int &b){return (a<=o&&o<=b)||(b<=o&&o<=a);}
int Solve(const Point &p)
{
	const int A=p.y-O.y,B=p.x-O.x,C=O.x*p.y-p.x*O.y;
	//(y2-y1)x-(x2-x1)y=x1y2-x2y1
	int ans=0;
	for(int i=0;i<N;i++)
	{
		const int &x1=WALL[i].a.x,&y1=WALL[i].a.y,&x2=WALL[i].b.x,&y2=WALL[i].b.y;
		const int a=y2-y1,b=x2-x1,c=x1*y2-x2*y1;
		//Ax-By==C
		//ax-by==c
		//Aax-Bay==Ca
		//Aax-Aby==Ac
		//(Ab-Ba)y==Ca-Ac
		//Ax-By==C
		//ax-by==c
		//Abx-Bby==Cb
		//Bax-Bby==Bc
		//(Ab-Ba)x==Cb-Bc
		if(A*b==B*a)
		{
			if(C*a==A*c&&C*b==B*c&&((p.y!=O.y&&(y1<O.y)==(p.y<O.y))||(p.x!=O.x&&(x1<O.x)==(p.x<O.x))))ans++;
		}
		else
		{
			int x=C*b-B*c,y=C*a-A*c,d=A*b-B*a;
			if(d<0)x*=-1,y*=-1,d*=-1;
			if(AtRange(x,d*x1,d*x2)&&AtRange(y,d*y1,d*y2))
			{
				if((p.x!=O.x&&(x<d*O.x)==(p.x<O.x))||(p.y!=O.y&&(y<d*O.y)==(p.y<O.y)))ans++;
			}
		}
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1&&N)
	{
		for(int i=0;i<N;i++)WALL[i].canf();
		O.canf();
		int ans=0;
		for(int i=0;i<N;i++)
		{
			ans=max(ans,max(Solve(WALL[i].a),Solve(WALL[i].b)));
		}
		printf("%d\n",ans);
	}
	return 0;
}
