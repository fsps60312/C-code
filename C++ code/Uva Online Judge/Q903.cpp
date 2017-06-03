#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
LL GetNumber(const int x,const int y)
{
	const LL w=max(abs(x),abs(y));
	const LL l=w*2LL+1LL;
	LL cur=l*l;
	if(y==w)return cur-(w-x);
	cur-=2LL*w;
	if(x==-w)return cur-(w-y);
	cur-=2LL*w;
	if(y==-w)return cur-(x-(-w));
	cur-=2LL*w;
	assert(x==w);
	return cur-(y-(-w));
}
LL N,ANS[3][3];
void Solve(int &x,int &y)
{
	LL l;
	for(l=1LL;l*l<N;l+=2LL);
	LL dis=l*l-N;
	x=(l-1)/2,y=(l-1)/2;
	if(dis<=l-1){x-=dis;return;}
	dis-=l-1,x-=l-1;
	if(dis<=l-1){y-=dis;return;}
	dis-=l-1,y-=l-1;
	if(dis<=l-1){x+=dis;return;}
	dis-=l-1,x+=l-1;
	assert(dis<l-1);
	y+=dis;
}
void Solve()
{
	int x,y;
	Solve(x,y);
	for(int i=0;i<3;i++)for(int j=0;j<3;j++)ANS[i][j]=GetNumber(x+j-1,y+1-i);
}
int main()
{
	while(scanf("%lld",&N)==1)
	{
		Solve();
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)printf("%lld;",ANS[i][j]);
			puts("");
		}
	}
	return 0;
}
