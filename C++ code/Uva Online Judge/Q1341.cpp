#include<cstdio>
#include<cassert>
#include<queue>
using namespace std;
const int INF=2147483647;
int N;
int LEN[65536];
bool INQ[65536];
int Bfs(const int digit)
{
	assert(digit>=1&&digit<=9);
	for(int i=0;i<N;i++)LEN[i]=INF,INQ[i]=false;
	queue<int>q;
	LEN[digit%N]=1,q.push(digit%N),INQ[digit%N]=true;
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		INQ[u]=false;
		const int nxt=(u*10+digit)%N;
		if(LEN[u]+1<LEN[nxt])
		{
			LEN[nxt]=LEN[u]+1;
			if(!INQ[nxt])q.push(nxt),INQ[nxt]=true;
		}
	}
	return LEN[0];
}
int main()
{
//	for(int i=1;i<=9;i++)
//	{
//		printf("%2d %2d %2d %2d %2d %2d %2d %2d %2d\n",i*1%16,i*11%16,i*111%16,i*1111%16,i*11111%16,i*111111%16,i*1111111%16,i*11111111%16,i*111111111%16);
//	}
	while(scanf("%d",&N)==1&&N)
	{
		int dans=-1,len=INF;
		for(int d=1;d<=9;d++)
		{
			int tl=Bfs(d);
			if(tl<len)len=tl,dans=d;
		}
		if(dans==-1)printf("%d\n",N);
		else
		{
			for(int i=0;i<len;i++)putchar('0'+dans);
			puts("");
		}
	}
	return 0;
}
