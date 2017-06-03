#include<cstdio>
#include<vector>
using namespace std;
const int P_MAXIMUM=500*500+500*500/3;
int TESTCASE,N,M,P,W_CNT,IDX[500][500],S[P_MAXIMUM],T[P_MAXIMUM];
bool VIS[P_MAXIMUM];
char MAT[500][500];
vector<int>TO[P_MAXIMUM];
bool MarkVertex()
{
	int b=0;
	W_CNT=0;
	P=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++)
		{
			char &v=MAT[i][j];
			if(v=='B')IDX[i][j]=P++,b++,P++;
			else if(v=='W') IDX[i][j]=P++,W_CNT++;
		}
	}
	return W_CNT==b*2;
}
void AddEdge(int idx,int i,int j)
{
	if(i<0||i>=N||j<0||j>=M)return;
	if(MAT[i][j]!='W')return; 
	TO[idx].push_back(IDX[i][j]);
}
void BuildTO()
{
	for(int i=0;i<P;i++)TO[i].clear();
	int idx=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<M;j++,idx++)
		{
			char &v=MAT[i][j];
			int &idx=IDX[i][j];
			if(v=='B')
			{
				AddEdge(idx,i-1,j);
				AddEdge(idx,i+1,j);
				AddEdge(idx+1,i,j-1);
				AddEdge(idx+1,i,j+1);
			}
		}
	}
}
int QuickMatch()
{
	int ans=0;
	for(int i=0;i<P;i++)
	{
		if(S[i]!=-1||T[i]!=-1)continue;
		for(int j=0;j<TO[i].size();j++)
		{
			int &k=TO[i][j];
			if(S[k]!=-1||T[k]!=-1)continue;
//			printf("qm(%d,%d)\n",i,k);
			T[i]=k,S[k]=i;
			ans++;
			break;
		}
	}
	return ans;
}
bool Dfs(int u)
{
	if(VIS[u])return false;
	VIS[u]=true;
	for(int i=0;i<TO[u].size();i++)
	{
		int &j=TO[u][i];
		if(S[j]!=-1)continue;
		if(T[j]==-1||Dfs(T[j]))
		{
			VIS[u]=false;
			T[u]=j;S[j]=u;
			T[j]=S[u]=-1;
			return true;
		}
	}
	VIS[u]=false;
	return false;
}
int MatchPair()
{
	for(int i=0;i<P;i++)
	{
		S[i]=T[i]=-1;
		VIS[i]=true;
	}
	int ans=QuickMatch();
//	printf("ans=%d\n",ans);
	int target=P-1;
	for(int i=0;;i++,i%=P)
	{
		if(S[i]==-1&&T[i]==-1&&Dfs(i))
		{
			ans++;
			target=i;
			continue;
		}
		if(i==target)break;
	}
	return ans;
}
bool solve()
{
	if(!MarkVertex())return false;
	BuildTO();
	int ans=MatchPair();
//	printf("ans=%d\n",ans);
//	for(int i=0;i<P;i++)
//	{
//		printf("%5d%5d\n",T[i],S[i]);
//	}
	return ans==W_CNT;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&TESTCASE);
	while(TESTCASE--)
	{
		scanf("%d%d",&N,&M);
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<M;j++)
			{
				char &c=MAT[i][j];
				do
				{
					scanf("%c",&c);
				}while(c!='B'&&c!='W'&&c!='.');
			}
		}
		printf("%s\n",solve()?"YES":"NO");
	}
	return 0;
}
