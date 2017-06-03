#include<cstdio>
#include<cassert>
using namespace std;
int T,N,G[3][3],A[3][3];
inline bool Valid(const int &sum)
{
	if(A[0][0]+A[1][1]+A[2][2]!=sum||A[0][2]+A[1][1]+A[2][0]!=sum)return false;
	for(int i=0;i<3;i++)
	{
		if(A[i][0]+A[i][1]+A[i][2]!=sum||A[0][i]+A[1][i]+A[2][i]!=sum)return false;
		for(int j=0;j<3;j++)
		{
			if(G[i][j]&&G[i][j]!=A[i][j])return false;
			if(A[i][j]<1||A[i][j]>N)return false;
		}
	}
	return true;
}
bool Solve()
{
	int limit=N*N*N*N;
	for(int s=0;s<limit;s++)
	{
		int a=s%N,b=s/N%N,c=s/N/N%N,d=s/N/N/N;
		a++,b++,c++,d++;
		if(G[0][0]&&a!=G[0][0])continue;
		if(G[1][1]&&b!=G[1][1])continue;
		if(G[2][2]&&c!=G[2][2])continue;
		if(G[0][2]&&d!=G[0][2])continue;
		int sum=a+b+c;
		A[0][0]=a,A[1][1]=b,A[2][2]=c,A[0][2]=d;
		A[2][0]=sum-b-d;
		A[1][0]=sum-A[0][0]-A[2][0];
		A[0][1]=sum-A[0][0]-A[0][2];
		A[2][1]=sum-A[2][0]-A[2][2];
		A[1][2]=sum-A[0][2]-A[2][2];
		if(Valid(sum))return true;
	}
	return false;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<3;i++)for(int j=0;j<3;j++)scanf("%d",&G[i][j]);
		if(Solve())
		{
			puts("Yes");
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					printf("%d%c",A[i][j],j==2?'\n':' ');
				}
			}
		}
		else puts("No");
	}
	return 0;
}
