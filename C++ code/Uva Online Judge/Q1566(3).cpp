#include<cstdio>
int T,N,A[47];
bool solve()
{
	int ans=0,cnt=0;
	bool up1=false;
	for(int i=0;i<N;i++)
	{
		ans^=A[i];
		if(A[i]==1)cnt++;
		else if(A[i]>1)up1=true;
	}
	if(!up1)return !(cnt&1);
	return ans>0;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		printf(solve()?"John\n":"Brother\n");
	}
	return 0;
}
