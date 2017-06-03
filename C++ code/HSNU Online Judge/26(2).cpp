#include<bits/stdc++.h>
using namespace std;
int N;
bool VIS[100][100];
queue<int>Q;
void Push(const int &x,const int &y,const int &t){if(x<0||y<0||x>99||y>99)return;Q.push(t*10000+x*100+y);}
void Pop(int &x,int &y,int &t){static int v;v=Q.front();Q.pop();t=v/10000,v%=10000,x=v/100,v%=100,y=v;}
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
	if((x+y-tx-ty)%2){puts("impossible\n");return 0;}
	while(!Q.empty())
	{
		Pop(x,y,t);
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
