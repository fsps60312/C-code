#include<cstdio>
#include<cassert>
using namespace std;
void getmin(int &a,const int b){if(b<a)a=b;}
int ANS;
void Dfs(const int depth,const int LA,const int LB,const int RA,const int RB)
{
	if(depth>5)return;
	if(LA<0||LB<0||RA<0||RB<0)return;
	if(LB>LA||RB>RA)return;
	if(RA==0&&RB==0){getmin(ANS,depth);return;}
	if(depth%2==0)
	{
		Dfs(depth+1,LA+2,LB,RA-2,RB);
		Dfs(depth+1,LA,LB+2,RA,RB-2);
		Dfs(depth+1,LA+1,LB+1,RA-1,RB-1);
		Dfs(depth+1,LA+1,LB,RA-1,RB);
		Dfs(depth+1,LA,LB+1,RA,RB-1);
	}
	else
	{
		Dfs(depth+1,LA-2,LB,RA+2,RB);
		Dfs(depth+1,LA,LB-2,RA,RB+2);
		Dfs(depth+1,LA-1,LB-1,RA+1,RB+1);
		Dfs(depth+1,LA-1,LB,RA+1,RB);
		Dfs(depth+1,LA,LB-1,RA,RB+1);
	}
}
int LA,LB,RA,RB;
int main()
{
	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d%d%d%d",&LA,&LB,&RA,&RB);
		ANS=6;
		Dfs(0,LA,LB,RA,RB);
		if(ANS==6)puts("Too hard!!!");
		else printf("Cracked in %d step(s)!!!\n",ANS);
	}
	return 0;
}
