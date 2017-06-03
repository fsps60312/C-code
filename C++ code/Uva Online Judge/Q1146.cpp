#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
//#define abs(x) (x)<0?-(x):(x)
int N,S[4000],VIS[4000],RN,REC[2000];
vector<int> SIDE[4000];
int abs(int a){return a<0?-a:a;}
void init(int p)
{
	for(int i=0;i<N*2;i++)
	{
		SIDE[i].clear();
		VIS[i]=0;
	}
	for(int a1=0;a1<N*2;a1+=2)
	{
		for(int a2=a1+2;a2<N*2;a2+=2)
		{
			if(abs(S[a1]-S[a2])<p)
			{
				SIDE[a1].push_back(a2^1);
				SIDE[a2].push_back(a1^1);
				//printf("push(%d,%d)(%d,%d)\n",a1,a2^1,a2,a1^1);
			}
			if(abs(S[a1]-S[a2^1])<p)
			{
				SIDE[a1].push_back(a2);
				SIDE[a2^1].push_back(a1^1);
			}
			if(abs(S[a1^1]-S[a2])<p)
			{
				SIDE[a1^1].push_back(a2^1);
				SIDE[a2].push_back(a1);
			}
			if(abs(S[a1^1]-S[a2^1])<p)
			{
				SIDE[a1^1].push_back(a2);
				SIDE[a2^1].push_back(a1);
			}
			//printf("check(%d,%d)(%d,%d)size=%d\n",a1,a1^1,a2,a2^1,SIDE[0].size());
			//printf("value(%d,%d)(%d,%d)\n",S[a1],S[a1^1],S[a2],S[a2^1]);
		}
	}
}
bool dfs(int u)
{
	if(VIS[u^1])return false;
	if(VIS[u])return true;
	VIS[u]=1;
	REC[RN++]=u;
	for(int i=0;i<SIDE[u].size();i++)
	{
		if(!dfs(SIDE[u][i]))return false;
	}
	return true;
}
bool solve(int p)
{
	init(p);
	/*for(int i=0;i<N*2;i++)
	{
		printf("p=%d,i=%d(%d)->",p,i,SIDE[i].size());
		for(int j=0;j<SIDE[i].size();i++)printf(" %d",SIDE[i][j]);printf("\n");
	}*/
	for(int i=0;i<N*2;i+=2)
	{
		//printf("i=%d\n",i);
		if(VIS[i]||VIS[i^1])continue;
		RN=0;
		if(!dfs(i))
		{
			while(RN)VIS[REC[--RN]]=0;
			if(!dfs(i^1))return false;
		}
	}
	return true;
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N*2;i+=2)scanf("%d%d",S+i,S+i+1);
		//for(int i=0;i<N*2;i++)printf("S%d->%d\n",i,S[i]);
		int L=1,R=10000001;
		while(L<R)
		{
			int mid=(L+R)/2;
			if(solve(mid))L=mid+1;
			else R=mid;
		}
		//printf("N=%d\n",N);
		printf("%d\n",R-1);
	}
	return 0;
}
/*
10
44 156
153 182
48 109
160 201
55 186
54 207
55 165
17 58
132 160
87 197
*/
