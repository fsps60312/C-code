#include<bits/stdc++.h>
using namespace std;
int N;
bool VIS[100][100];
queue<int>QX,QY,QT;
void Push(const int &x,const int &y,const int &t){QX.push(x),QY.push(y),QT.push(t);}
void Pop(int &x,int &y,int &t){x=QX.front(),y=QY.front(),t=QT.front();QX.pop(),QY.pop(),QT.pop();}
int main()
{
	scanf("%d",&N);
	static int x,y,t,tx,ty;
	for(x=0;x<=99;x++)for(y=0;y<=99;y++)VIS[x][y]=false;
	for(;N--;)
	{
		scanf("%d%d",&x,&y);
		VIS[x][y]=true;
	}
	scanf("%d%d",&x,&y);
	Push(x,y,0);
	scanf("%d%d",&tx,&ty);
	while(!QX.empty())
	{
		Pop(x,y,t);
		if(x<0||x>99||y<0||y>99)continue;
		if(x==tx&&y==ty){printf("%d\n",t);return 0;}
		t++;
		if(!VIS[x][y-1])Push(x-1,y-3,t),Push(x+1,y-3,t);
		if(!VIS[x][y+1])Push(x-1,y+3,t),Push(x+1,y+3,t);
		if(!VIS[x-1][y])Push(x-3,y-1,t),Push(x-3,y+1,t);
		if(!VIS[x+1][y])Push(x+3,y-1,t),Push(x+3,y+1,t);
	}
	puts("impossible\n");
	return 0;
}
