#include<cstdio>
#include<vector>
using namespace std;
int T,N,K;
vector<int>A,B;
int main()
{
	for(scanf("%d",&T);T--;)
	{
		scanf("%d%d",&N,&K);
		A.clear(),B.clear();
		A.push_back(1),B.push_back(1);
		int i=0,j=0;
		while(A[i]<N)
		{
			i++;
			A.push_back(B[i-1]+1);
			while(A[j+1]*K<A[i])j++;
			if(A[j]*K<A[i])B.push_back(B[j]+A[i]);
			else B.push_back(A[i]);
		}
		static int kase=1;
		printf("Case %d: ",kase++);
		if(A[i]==N)puts("lose");
		else
		{
			int ans=-1;
			for(;N;i--)if(A[i]<=N)ans=A[i],N-=A[i];
			printf("%d\n",ans);
		}
	}
	return 0;
}
