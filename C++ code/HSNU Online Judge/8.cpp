#include<cstdio>
int N;
struct Bit
{
	int v[300001];
	void Clear(){for(int i=1;i<=N;i++)v[i]=0;}
	int lowbit(int i){return i&(-i);}
	void Add(int i)
	{
		while(i<=N)
		{
			v[i]++;
			i+=lowbit(i);
		}
	}
	int Query(int i)
	{
		int ans=0;
		while(i)
		{
			ans+=v[i];
			i-=lowbit(i);
		}
		return ans;
	}
}BIT;
int main()
{
	while(scanf("%d",&N)==1)
	{
		BIT.Clear();
		int ans=0;
		for(int i=0;i<N;i++)
		{
			static int b,q;
			scanf("%d",&b);
			q=BIT.Query(b);
			if(q<i)
			{
				ans=q+1;
			}
			BIT.Add(b);
		}
		printf("%d\n",ans);
	}
	return 0;
}
