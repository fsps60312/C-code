#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N;
struct Point
{
	LL x,y;
	void canf(){scanf("%lld%lld",&x,&y);}
}O;
struct Wall
{
	Point a,b;
	void canf(){a.canf(),b.canf();}
}WALL[500];
bool AtRange(const LL &o,const LL &a,const LL &b){return (a<=o&&o<=b)||(b<=o&&o<=a);}
inline LL Solve(const Point &p)
{
	const LL A=p.y-O.y,B=p.x-O.x,C=O.x*p.y-p.x*O.y;
	//(y2-y1)x-(x2-x1)y=x1y2-x2y1
	LL ans=0LL;
	for(LL i=0LL;i<N;i++)
	{
		const LL &x1=WALL[i].a.x,&y1=WALL[i].a.y,&x2=WALL[i].b.x,&y2=WALL[i].b.y;
		const LL a=y2-y1,b=x2-x1,c=x1*y2-x2*y1;
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
			LL x=C*b-B*c,y=C*a-A*c,d=A*b-B*a;
			if(d<0LL)x*=-1LL,y*=-1LL,d*=-1LL;
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
	while(scanf("%lld",&N)==1&&N)
	{
		for(LL i=0LL;i<N;i++)WALL[i].canf();
		O.canf();
		LL ans=0LL;
		for(LL i=0LL;i<N;i++)
		{
			ans=max(ans,max(Solve(WALL[i].a),Solve(WALL[i].b)));
		}
		printf("%lld\n",ans);
	}
	return 0;
}
