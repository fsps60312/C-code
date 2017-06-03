   /***************************************************
  ***  Edited by Burney(余柏序-最盡責的美宣長)     ***
 ***  ZeroJudge d406                              ***
***************************************************/

#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
int S,N,M,PIPE[102][102],ANS[102][102];
struct Data
{
	int r,c,t;
};
int main()
{
	int kase=1;
	while(scanf("%d",&S)==1)
	{
		scanf("%d%d",&N,&M);
		for(int r=1;r<=N;r++)
		{
			PIPE[r][0]=0;//將邊界當作沒有水管
			for(int c=1;c<=M;c++)
			{
				ANS[r][c]=0;//還沒流過當然是0~XD 
				scanf("%d",&PIPE[r][c]);
			}
			PIPE[r][M+1]=0;//這邊也是
		}
		for(int c=1;c<=M;c++)PIPE[0][c]=PIPE[N+1][c]=0;//這邊也是
		queue<Data> q;
		//倒水，倒倒倒~ 
		for(int c=1;c<=M;c++)
		{
			if(PIPE[1][c])
			{
				q.push((Data){1,c,1});
			}
		}
		//開始流，流流流~
		while(!q.empty())
		{
			Data d=q.front();q.pop();
			if(!PIPE[d.r][d.c])continue;//沒有水管 
			if(ANS[d.r][d.c])continue;//流過了 
			ANS[d.r][d.c]=d.t;//紀錄最早流過的時間 
			if(S==1)q.push((Data){d.r-1,d.c,d.t+1});//可以往上流 
			q.push((Data){d.r+1,d.c,d.t+1});//流
			q.push((Data){d.r,d.c-1,d.t+1});//流
			q.push((Data){d.r,d.c+1,d.t+1});//流
		}
		//接下來是很高興的輸出答案XD 
		printf("Case %d:\n",kase++);
		for(int r=1;r<=N;r++)
		{
			printf("%d",ANS[r][1]);
			for(int c=2;c<=M;c++)
			{
				printf(" %d",ANS[r][c]);
			}
			printf("\n");
		}
	}
	return 0;
}
