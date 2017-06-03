#include<cstdio>
#include<stack>
#include<cmath>
using namespace std;
#define termin(x,...) {while(1)printf(x,##__VA_ARGS__);;}
typedef long long LL;
int max(int a,int b){return a>b?a:b;}
int min(int a,int b){return a<b?a:b;}
int abs(int a){return a>=0?a:-a;}
//void RunTimeError(){puts("Run Time Error\n");int a,b=0;while(1)a/=b;}
int N,M,Q,W[200][50001],ANS[10];
char LINE[10];
struct Input
{
	char type;
	int a,b,c,d,e;
	Input(){}
	Input(char type,int a,int b,int c,int d,int e):type(type),a(a),b(b),c(c),d(d),e(e){}
};
stack<Input> INPUT;
int findDJ(int idx,int a)
{
	int &w=W[idx][a];
	if(w==a)return a;
	return w=findDJ(idx,w);
}
void DrawColor(int &y,int x,int xr,int &c)
{
	for(x=findDJ(y,x);x<=xr;x=findDJ(y,x))
	{
		ANS[c]++;
		W[y][x]=x+1;
	}
}
void Circle(int &xc,int &yc,int &r,int &c)
{
	for(int dy=max(-yc,-r),limit_dy=min(M-1-yc,r),y;dy<=limit_dy;dy++)
	{
		y=yc+dy;
		DrawColor(y,xc+max(-xc,-(int)sqrt(r*r-dy*dy))
		,xc+min(N-1-xc,(int)sqrt(r*r-dy*dy)),c);
	}
}
void Diamond(int &xc,int &yc,int &r,int &c)
{
	for(int dy=max(-yc,-r),limit_dy=min(M-1-yc,r),y;dy<=limit_dy;dy++)
	{
		y=yc+dy;
		DrawColor(y,xc+max(-xc,-(r-abs(dy)))
		,xc+min(N-1-xc,r-abs(dy)),c);
	}
}
void Rectangle(int &xc,int &yc,int &l,int &w,int &c)
{
	for(int dy=max(-yc,0),limit_dy=min(M-1-yc,w-1),y;dy<=limit_dy;dy++)
	{
		y=yc+dy;
		DrawColor(y,xc+max(-xc,0),xc+min(N-1-xc,l-1),c);
	}
}
void Triangle(int &xc,int &yc,int &w,int &c)
{
	for(int dy=0,limit_dy=min(M-1-yc,(w-1)/2),y;dy<=limit_dy;dy++)
	{
		y=yc+dy;
		DrawColor(y,xc-min(xc,(w-1)/2-dy)
		,xc+min(N-1-xc,(w-1)/2-dy),c);
	}
}
void Handle(Input &s)
{
	switch(s.type)
	{
		case'C':Circle(s.a,s.b,s.c,s.e);break;
		case'D':Diamond(s.a,s.b,s.c,s.e);break;
		case'R':Rectangle(s.a,s.b,s.c,s.d,s.e);break;
		case'T':Triangle(s.a,s.b,s.c,s.e);break;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&N,&M,&Q)==3)
	{
		INPUT=stack<Input>();
		for(int a,b,c,d,e;Q--;)
		{
			scanf("%s",LINE);
			switch(LINE[0])
			{
				case'C':
				case'D':
				case'T':
				{
					scanf("%d%d%d%d",&a,&b,&c,&e);
				}break;
				case'R':
				{
					scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
				}break;
				default:termin("Can't handle %c\n",LINE[0]);break;
			}
			INPUT.push(Input(LINE[0],a,b,c,d,e));
		}
		for(int i=0;i<M;i++)for(int j=0;j<=N;j++)W[i][j]=j;
		for(int i=1;i<=9;i++)ANS[i]=0;
		while(!INPUT.empty())
		{
			Input s=INPUT.top();INPUT.pop();
			Handle(s);
		}
		printf("%d",ANS[1]);for(int i=2;i<=9;i++)printf(" %d",ANS[i]);puts("");
	}
//	termin("Finish\n");
	return 0;
}
