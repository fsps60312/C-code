#include<bits/stdc++.h>
using namespace std;
const int INF=2147483647;
int T,N,M;
struct Obj
{
	int x,y,r;
}BOMB[15],ENEMY[9];
int TOUCH[15];
int Sq(const int &x){return x*x;}
int cntbits(int a)
{
	a=((a&0xaaaaaaaa)>>1)+(a&0x55555555);
	a=((a&0xcccccccc)>>2)+(a&0x33333333);
	a=((a&0xf0f0f0f0)>>4)+(a&0x0f0f0f0f);
	a=((a&0xff00ff00)>>8)+(a&0x00ff00ff);
	a=((a&0xffff0000)>>16)+(a&0x0000ffff);
	return a;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&M,&N);
		for(int i=0;i<M;i++)
		{
			Obj &o=BOMB[i];
			scanf("%d%d%d",&o.x,&o.y,&o.r);
		}
		for(int i=0;i<N;i++)
		{
			Obj &o=ENEMY[i];
			scanf("%d%d%d",&o.x,&o.y,&o.r);
		}
		for(int i=0;i<M;i++)
		{
			Obj &a=BOMB[i];
			TOUCH[i]=0;
			for(int j=0;j<N;j++)
			{
				Obj &b=ENEMY[j];
				if(Sq(a.x-b.x)+Sq(a.y-b.y)<=Sq(a.r+b.r))TOUCH[i]|=1<<j;
			}
		}
		int goal=(1<<N)-1;
		int ans=INF;
		for(int s=1,k,a=0;s<(1<<M);s++,a=0)
		{
			for(k=0;k<M;k++)if(s&(1<<k))a|=TOUCH[k];
			if(a==goal)ans=min(cntbits(s),ans);
		}
		if(ans==INF)puts("Impossible");
		else printf("%d\n",ans);
	}
	return 0;
}
