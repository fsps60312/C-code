#include<cstdio>
#include<queue>
#include<cassert>
#include<vector>
using namespace std;
const int INF=2147483647;
int N;
char S[72];
int DP[71][4][4][3],INQ[71][4][4][3],KASE=0,PRE[71][4][4][3][3];
struct State
{
	int i,l,r,a;
	State(){}
	State(const int &i,const int &l,const int &r,const int &a):i(i),l(l),r(r),a(a){}
	inline bool MoveL(const int &loc,const bool &tap,State &t,int &cost)
	{
		if(r==loc)return false;
		if(r==3)
		{
			if(l!=loc)return false;
			if(loc==1)return false;
		}
		t.i=i+1,t.l=loc,t.r=r,t.a=1;
		if(l==loc&&!tap)cost=0,t.a=0;
		else if(a!=1)cost=1;
		else if(l==loc)cost=3;
		else if((loc-l)%2==0)cost=7;
		else cost=5;
		return true;
	}
	inline bool MoveR(const int &loc,const bool &tap,State &t,int &cost)
	{
		if(l==loc)return false;
		if(l==1)
		{
			if(r!=loc)return false;
			if(r==3)return false;
		}
		t.i=i+1,t.l=l,t.r=loc,t.a=2;
		if(r==loc&&!tap)cost=0,t.a=0;
		else if(a!=2)cost=1;
		else if(r==loc)cost=3;
		else if((loc-r)%2==0)cost=7;
		else cost=5;
		return true;
	}
};
queue<State>Q;
int &Dp(const State &s){return DP[s.i][s.l][s.r][s.a];}
void Push(const State &s)
{
	int &inq=INQ[s.i][s.l][s.r][s.a];
	if(inq==KASE)return;
	inq=KASE;
	Q.push(s);
}
void Pop(State &s)
{
	s=Q.front();Q.pop();
	INQ[s.i][s.l][s.r][s.a]=0;
}
bool Update(const State &s,const State &t,const int &cost)
{
	if(Dp(s)+cost>=Dp(t))return false;
	Dp(t)=Dp(s)+cost;
	int *pre=PRE[t.i][t.l][t.r][t.a];
	pre[0]=s.l,pre[1]=s.r,pre[2]=s.a;
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<=70;i++)for(int j=0;j<4;j++)for(int k=0;k<4;k++)for(int l=0;l<3;l++)INQ[i][j][k][l]=0;
	while(scanf("%s",S+1)==1)
	{
		if(S[1]=='#'&&S[2]=='\0')break;
		N=0;while(S[++N]);N--;
		for(int i=0;i<=N;i++)for(int j=0;j<4;j++)for(int k=0;k<4;k++)for(int l=0;l<3;l++)DP[i][j][k][l]=INF;
		Q=queue<State>();
		KASE++;
		DP[0][3][1][0]=0;
		Push(State(0,3,1,0));
		State ans=State(-1,-1,-1,-1);
		while(!Q.empty())
		{
			static State s;Pop(s);
			if(s.i==N){if(ans.i==-1||Dp(s)<Dp(ans))ans=s;continue;}
			static State t;
			static int cost;
			if(S[s.i+1]=='.')
			{
				for(int i=0;i<4;i++)
				{
					if(s.MoveL(i,false,t,cost)&&Update(s,t,cost))Push(t);
					if(s.MoveR(i,false,t,cost)&&Update(s,t,cost))Push(t);
				}
			}
			else
			{
				int i;
				switch(S[s.i+1])
				{
					case'U':i=0;break;
					case'R':i=1;break;
					case'D':i=2;break;
					case'L':i=3;break;
					default:assert(0);
				}
				if(s.MoveL(i,true,t,cost)&&Update(s,t,cost))Push(t);
				if(s.MoveR(i,true,t,cost)&&Update(s,t,cost))Push(t);
			}
		}
		assert(ans.l!=-1);
//		printf("%d\n",Dp(ans));
//vector<int>lf,rf,dp;
		vector<char>str;
		for(int i=N;;i--)
		{
//lf.push_back(ans.l),rf.push_back(ans.r),dp.push_back(Dp(ans));
			assert(ans.l!=-1);
			if(ans.a==0)str.push_back('.');
			else if(ans.a==1)str.push_back('L');
			else if(ans.a==2)str.push_back('R');
			else assert(0);
			if(i==1)break;
			int *pre=PRE[ans.i][ans.l][ans.r][ans.a];
			ans=State(i-1,pre[0],pre[1],pre[2]);
		}
		for(int i=str.size()-1;i>=0;i--)printf("%c",str[i]);puts("");
//for(int cnt=1,i=lf.size()-1;i>=0;i--)printf("%c%c(%d,%d):%d\n",str[i],S[cnt++],lf[i],rf[i],dp[i]);
	}
	return 0;
}
