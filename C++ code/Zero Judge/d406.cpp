   /***************************************************
  ***  Edited by Burney(�E�f��-�̺ɳd�����Ū�)     ***
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
			PIPE[r][0]=0;//�N��ɷ�@�S������
			for(int c=1;c<=M;c++)
			{
				ANS[r][c]=0;//�٨S�y�L��M�O0~XD 
				scanf("%d",&PIPE[r][c]);
			}
			PIPE[r][M+1]=0;//�o��]�O
		}
		for(int c=1;c<=M;c++)PIPE[0][c]=PIPE[N+1][c]=0;//�o��]�O
		queue<Data> q;
		//�ˤ��A�˭˭�~ 
		for(int c=1;c<=M;c++)
		{
			if(PIPE[1][c])
			{
				q.push((Data){1,c,1});
			}
		}
		//�}�l�y�A�y�y�y~
		while(!q.empty())
		{
			Data d=q.front();q.pop();
			if(!PIPE[d.r][d.c])continue;//�S������ 
			if(ANS[d.r][d.c])continue;//�y�L�F 
			ANS[d.r][d.c]=d.t;//�����̦��y�L���ɶ� 
			if(S==1)q.push((Data){d.r-1,d.c,d.t+1});//�i�H���W�y 
			q.push((Data){d.r+1,d.c,d.t+1});//�y
			q.push((Data){d.r,d.c-1,d.t+1});//�y
			q.push((Data){d.r,d.c+1,d.t+1});//�y
		}
		//���U�ӬO�ܰ�������X����XD 
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
