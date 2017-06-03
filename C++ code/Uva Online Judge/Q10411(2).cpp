#include<bits/stdc++.h>
using namespace std;
int T,N,S[101];
struct Ans
{
	int type,column;
	Ans(){}
	Ans(const int &t,const int &c):type(t),column(c){}
};
vector<Ans>ANS;
void Solve()
{
	for(int i=2;i<=N;i++)
	{
		while(S[i]<S[i-1])
		{
			ANS.push_back(Ans(1,i));
			S[i]+=4;
		}
	}
	for(int i=N;i>=2;i--)
	{
		while(S[i-1]+4<=S[i])
		{
			ANS.push_back(Ans(i,i-1));
			S[i-1]+=4;
		}
	}
	if(S[1]==S[N])return;
	
}
int main()
{
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d",&N);
			ANS.clear();
			for(int i=1;i<=N;i++)scanf("%d",&S[i]);
			Solve();
			for(int i=0;i<ANS.size();i++)
			{
				printf("%d %d\n",ANS[i].type,ANS[i].column);
			}
			printf("-1 -1");
		}
	}
	return 0;
}
