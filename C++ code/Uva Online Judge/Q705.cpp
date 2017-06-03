#include<cstdio>
#include<queue>
#include<cassert>
using namespace std;
int W,H;
char S[77][77];
bool VIS[77][77][2],RIM[77][77][2];
void Push(queue<int>&q1,queue<int>&q2,queue<int>&q3,const int v1,const int v2,const int v3){q1.push(v1),q2.push(v2),q3.push(v3);}
void Pop(queue<int>&q1,queue<int>&q2,queue<int>&q3,int &v1,int &v2,int &v3){v1=q1.front(),v2=q2.front(),v3=q3.front();q1.pop(),q2.pop(),q3.pop();}
int Flow(const int s1,const int s2,const int s3)
{
	queue<int>q1,q2,q3;
	Push(q1,q2,q3,s1,s2,s3);
	int ans=0;
	bool overflow=false;
	while(!q1.empty())
	{
		int u1,u2,u3;
		Pop(q1,q2,q3,u1,u2,u3);
		if(RIM[u1][u2][u3]){overflow=true;continue;}
		if(VIS[u1][u2][u3])continue;
		VIS[u1][u2][u3]=true;
		ans++;
		if(u3==0)
		{
			if(S[u1][u2]=='/')Push(q1,q2,q3,u1,u2,1);
			else if(S[u1][u2]=='\\')Push(q1,q2,q3,u1-1,u2,1);
			if(S[u1][u2+1]=='/')Push(q1,q2,q3,u1-1,u2+1,1);
			else if(S[u1][u2+1]=='\\')Push(q1,q2,q3,u1,u2+1,1);
		}
		else if(u3==1)
		{
			if(S[u1][u2]=='/')Push(q1,q2,q3,u1,u2,0);
			else if(S[u1][u2]=='\\')Push(q1,q2,q3,u1,u2-1,0);
			if(S[u1+1][u2]=='/')Push(q1,q2,q3,u1+1,u2-1,0);
			else if(S[u1+1][u2]=='\\')Push(q1,q2,q3,u1+1,u2,0);
		}
		else assert(0);
	}
	return overflow?0:ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&W,&H)==2&&(W||H))
	{
		for(int i=0;i<=H+1;i++)for(int j=0;j<=W+1;j++)for(int d=0;d<2;d++)VIS[i][j][d]=false,RIM[i][j][d]=true;
		for(int i=1;i<=H;i++)for(int j=1;j<=W;j++)
		{
			char &c=S[i][j];
			do
			{
				scanf("%c",&c);
			}while(c!='\\'&&c!='/');
			if(j<W)RIM[i][j][0]=false;
			if(i<H)RIM[i][j][1]=false;
		}
		int ans=0,cnt=0;
		for(int i=1;i<=H;i++)for(int j=1;j<=W;j++)for(int d=0;d<2;d++)if(!VIS[i][j][d])
		{
			const int ta=Flow(i,j,d);
			if(ta>ans)ans=ta;
			if(ta>0)cnt++;
		}
		static int kase=1;
		printf("Maze #%d:\n",kase++);
		if(ans==0)puts("There are no cycles.");
		else printf("%d Cycles; the longest has length %d.\n",cnt,ans);
		puts("");
	}
	return 0;
}
