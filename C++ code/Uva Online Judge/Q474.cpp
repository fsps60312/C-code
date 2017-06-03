#include<cstdio>
int N;
double A[1000001];
int B[1000001];
int NumLen(const double &v)
{
	static char tmp[10];
	sprintf(tmp,"%.3f",v);
	int ans=-1;while(tmp[++ans]);
	return ans;
}
int main()
{
	A[0]=1.0,B[0]=0;
	for(int i=1;i<=1000000;i++)
	{
		A[i]=A[i-1]*5.0;
		B[i]=B[i-1]+1;
		if(NumLen(A[i])!=5)A[i]/=10.0,B[i]--;
	}
	while(scanf("%d",&N)==1)printf("2^-%d = %.3fe-%d\n",N,A[N],B[N]);
	return 0;
}
