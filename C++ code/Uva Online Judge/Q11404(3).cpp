#include<cstdio>
#include<vector>
#include<cassert>
using namespace std;
int N;
char A[1001],B[1001];
int DP[1000][1000],PRE[1000][1000],LOC[1000][1000];
bool Better(const int r1,const int c1,const int r2,const int c2)
{
	if(DP[r1][c1]!=DP[r2][c2])return DP[r1][c1]>DP[r2][c2];
	if(A[LOC[r1][c1]/N]!=A[LOC[r2][c2]/N])return A[LOC[r1][c1]/N]<A[LOC[r2][c2]/N];
	const int pre1=PRE[r1][c1],pre2=PRE[r2][c2];
	if(pre1==pre2)return false;
	return Better(pre1/N,pre1%N,pre2/N,pre2%N);
}
void Update(const int r1,const int c1,const int r2,const int c2)
{
	if(!Better(r2,c2,r1,c1))return;
	DP[r1][c1]=DP[r2][c2];
	LOC[r1][c1]=LOC[r2][c2];
	PRE[r1][c1]=PRE[r2][c2];
}
void Initialize(const int r,const int c)
{
	DP[r][c]=(A[r]==B[c]?1:0);
	LOC[r][c]=(A[r]==B[c]?r*N+c:-1);
	PRE[r][c]=-1;
}
int main()
{
//	freopen("inn.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(fgets(A,1001,stdin))
	{
		N=-1;while(A[++N])if(A[N]=='\n')break;
		if(!N){puts("");continue;}
		for(int i=0;i<N;i++)B[N-1-i]=A[i];
		B[N]='\0';
		Initialize(0,0);
		for(int i=1;i<N;i++)
		{
			Initialize(0,i),Initialize(i,0);
			Update(0,i,0,i-1),Update(i,0,i-1,0);
		}
		for(int i=1;i<N;i++)
		{
			for(int j=1;j<N;j++)
			{
				DP[i][j]=-1;
				if(A[i]==B[j])DP[i][j]=DP[i-1][j-1]+1,LOC[i][j]=i*N+j,PRE[i][j]=LOC[i-1][j-1];
				Update(i,j,i,j-1);
				Update(i,j,i-1,j);
//				printf("PRE[%d][%d]=(%d,%d)\n",i,j,PRE[i][j]/N,PRE[i][j]%N);
//				printf("LOC[%d][%d]=(%d,%d)\n",i,j,LOC[i][j]/N,LOC[i][j]%N);
			}
		}
//		for(int i=0;i<N;i++){for(int j=0;j<N;j++)printf(" %d",DP[i][j]);puts("");}
//		puts(A);puts(B);
//		printf("DP=%d\n",DP[N-1][N-1]);
		int u=0;
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(Better(i,j,u/N,u%N))u=i*N+j;
		const int len=DP[u/N][u%N];
//		printf("len=%d\n",len);
		vector<char>ans;
		for(int i=0;i<(len+1)/2;i++)assert(u!=-1),ans.push_back(A[LOC[u/N][u%N]/N]),u=PRE[u/N][u%N];
		for(int i=ans.size();i<len;i++)ans.push_back(ans[len-1-i]);
		ans.push_back('\0');
		puts(&ans[0]);
	}
	return 0;
}
