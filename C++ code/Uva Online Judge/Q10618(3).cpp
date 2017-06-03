#include<cstdio>
#include<cassert>
const int INF=2147483647;
int N,COST[7]={3,3,5,5,7,7,1};
char S[72];
int DP[71][4][4][7];//left/right tap, left/right move adjacent, left/right move cross, no action
int PRE[71][4][4][7][3];
inline void getmin(const int &i,const int &l2,const int &r2,const int &a2,const int &l1,const int &r1,const int &a1,const int &cost)
{
	if(DP[i-1][l1][r1][a1]==INF)return;
	if(DP[i-1][l1][r1][a1]+cost>=DP[i][l2][r2][a2])return;
	DP[i][l2][r2][a2]=DP[i-1][l1][r1][a1]+cost;
	int *pre=PRE[i][l2][r2][a2];
	pre[0]=l1,pre[2]=r1,pre[1]=a1;
}
//struct Action
//{
//	int l,r1,r2,cost;
//	Action(){}
//	Action(const int &l,const int &r1,const int &r2,const int &c):l(l),r1(r1),r2(r2),cost(c){}
//};
//vector<int>ACT;
bool AVAIL[4][4][4];
void Init()
{
	for(int l=0;l<4;l++)
	{
		for(int r1=0;r1<4;r1++)
		{
			for(int r2=0;r2<4;r2++)
			{
				bool &a=AVAIL[l][r1][r2];
				if(l==r1||l==r2)a=false;
				else if(l==3)a=true;
				else if(l==0)a=true;
				else if(l==2)a=true;
				else if(l==1)
				{
					if(r1==r2)a=(r1==0||r1==2)?true:false;
					else a=false;
				}
			}
		}
	}
}
inline int GetType(const int &f,const int &a,const int &b,const bool &tap)
{
	if(a==b)return tap?f:6;
	if((a-b)%2==0)return 4+f;
	return 2+f;
}
inline bool Valid(const char &c,const int &d)
{
	switch(c)
	{
		case'.':return true;
		case'U':return d==0;
		case'R':return d==1;
		case'D':return d==2;
		case'L':return d==3;
		default:assert(0);
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	Init();
	while(scanf("%s",S+1)==1)
	{
		if(S[1]=='#'&&S[2]=='\0')break;
		N=0;while(S[++N]);N--;
		for(int i=0;i<=N;i++)for(int j=0;j<4;j++)for(int k=0;k<4;k++)for(int l=0;l<7;l++)DP[i][j][k][l]=INF;
		DP[0][3][1][6]=0;
		for(int i=1;i<=N;i++)
		{
			for(int l=0;l<4;l++)
			{
				for(int r1=0;r1<4;r1++)
				{
					if(S[i]=='.')for(int a=0;a<7;a++)getmin(i,l,r1,a,l,r1,6,0);
					for(int r2=0;r2<4;r2++)
					{
						if(!AVAIL[l][r1][r2])continue;
						for(int a=0;a<7;a++)
						{
							//move right
							if(Valid(S[i],r2))getmin(i,l,r1,a,l,r2,GetType(1,r1,r2,S[i]!='.'),COST[a]);
							//move left
							if(Valid(S[i],3-r2))getmin(i,3-r1,l,a,3-r2,l,GetType(0,3-r1,3-r2,S[i]!='.'),COST[a]);
						}
					}
				}
			}
		}
		int ans=INF;
		for(int i=0;i<4;i++)for(int j=0;j<4;j++)for(int k=0;k<7;k++)if(DP[N][i][j][k]<ans)ans=DP[N][i][j][k];
		printf("%d\n",ans);
	}
	return 0;
}
