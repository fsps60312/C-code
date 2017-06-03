#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int T,N;
struct Block
{
	int x,y;
	bool operator<(const Block &b)const{return x!=b.x?x<b.x:y<b.y;}
};
Block A[20],B[20],P;
vector<char>ANS;
void Move(int d)
{
	static char direction[4]={'D','L','U','R'};
	static int ddd[4][2]={{0,-1},{1,0},{0,1},{-1,0}};
	ANS.push_back(direction[d]);
	P.x+=ddd[d][0],P.y+=ddd[d][1];
}
void Move(const Block &a,const Block &b)//from origin point
{
	while(P.x!=a.x+1)Move(1);
	while(P.y!=a.y)Move(2);
	while(P.x!=1)Move(3);
	Move(2),Move(3);
	while(P.y!=b.y+1)Move(0);
	Move(1),Move(0);
	while(P.x!=b.x+1)Move(3);
	while(P.x!=0)Move(1);
	while(P.y!=0)Move(2);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d",&N);
			ANS.clear();
			int x,y;
			x=INF,y=INF;
			for(int i=0;i<N;i++)
			{
				Block &b=A[i];
				scanf("%d%d",&b.y,&b.x);
				x=min(x,b.x),y=min(y,b.y);
			}
			x-=2,y-=2;
			for(int i=0;i<N;i++)
			{
				Block &b=A[i];
				b.x-=x,b.y-=y;
			}
			for(int i=0;i<x;i++)Move(1);
			for(int i=0;i>x;i--)Move(3);
			for(int i=0;i>y;i--)Move(0);
			for(int i=0;i<y;i++)Move(2);
			P.x=P.y=0;
			x=-INF,y=-INF;
			for(int i=0;i<N;i++)
			{
				Block &b=B[i];
				scanf("%d%d",&b.y,&b.x);
				x=max(x,b.x),y=max(y,b.y);
			}
			x+=2,y+=2;
			for(int i=0;i<N;i++)
			{
				Block &b=B[i];
				b.x-=x,b.y-=y;
			}
			sort(A,A+N),sort(B,B+N);
			for(int i=0;i<N;i++)Move(A[i],B[i]);
			printf("%d\n",ANS.size());
			for(int i=0;i<ANS.size();i++)printf("%c",ANS[i]);puts("");
		}
	}
	return 0;
}
