#include<cstdio>
int T,N,A[50];
bool solve()
{
	if(N==1)return A[0]&1;
	if(N==2)
	{
		if(Sum()%2==0)return 1;
		if(Sum()%2==1)
		{
			if(Have1(1))return 1;
			else return 0;
		}
	}
	if(N==3)
	{
		if(Have1(3))return 0;
		if(Sum()%2==1)return 1;
		if(Sum()%2==0)return 0;
	}
	if(N==4)
	{
		if(Have1(4))return 1;
		if(Sum()%2==0)return 1;
		if(Sum()%2==1)
		{
			if(Have1(1~3))return 1;
			return 0;
		}
	}
	if(N==5)
	{
		if(Have1(5))return 0;
		if(Have1(4))return 0;
		if(Have1(3))return 0;
		if(Have1(2))
		{
			
		}
		if(Sum()%2==1)
		{
			if(Have1(3~5))return 0;
			return 1;
		}
	}
}
int main()
{
	scanf("%d",&T);
	int kase=1;
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		printf("Case #%d: %s\n",kase++,solve()?"Alice":"Bob");
	}
	return 0;
}
