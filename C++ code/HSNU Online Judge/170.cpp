#include<cstdio>
char S[52][3];
int BossScore(const int start)
{
	int cntA=0;
	int score=0;
	for(int i=0;;i++)
	{
		if(i==2)i=start;
		if(score>21)
		{
			if(cntA)cntA--,score-=10;
			else return -1;
		}
		if(score>=17)return score;
		const char c=S[i][0];
		if(c=='A')cntA++,score+=11;
		else if(c>='2'&&c<='9')score+=(c-'0');
		else score+=10;
	}
}
int Solve()
{
	int cntA=0;
	int score=0;
	bool tie=false;
	for(int i=2;;i++)
	{
		if(score>21)
		{
			if(cntA)cntA--,score-=10;
			else break;
		}
		if(i>=4)
		{
			const int boss=BossScore(i);
			if(boss<score)return 0;
			else if(boss==score)tie=true;
		}
		const char c=S[i][0];
		if(c=='A')cntA++,score+=11;
		else if(c>='2'&&c<='9')score+=(c-'0');
		else score+=10;
	}
	return tie?1:2;
}
int main()
{
//	freopen("in.txt","r",stdin);
	static int testcase;scanf("%d",&testcase);
	while(testcase--)
	{
		for(int i=0;i<52;i++)scanf("%s",S[i]);
		static char ans[3][5]={"win","push","lose"};
		puts(ans[Solve()]);
	}
	return 0;
}
