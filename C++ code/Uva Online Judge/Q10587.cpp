#include<cstdio>
#include<cstdlib>
int T,N;
struct BItreetype
{
	int w[10000001];
	int lowbit(int a){return (-a)&a;}
	void clear(){for(int i=1;i<=N;i++)w[i]=0;}
	int sum(int i)
	{
		int ans=0;
		while(i)
		{
			ans+=w[i];
			i-=lowbit(i);
		}
		return ans;
	}
	int value(int i){return sum(i)-sum(i-1);}
	void setvalue(int l,int r,int v)
	{
		//TLE, need to use for(...)
	}
};
BItreetype bi;
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		bi.clear();
	}
	return 0;
}
