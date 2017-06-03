#include<cstdio>
int N,S[100001];
struct Bit
{
	int v[100001];
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
		for(int i=1;i<=N;i++)scanf("%d",&S[i]);
		BIT.Clear();
		long long ans=0;
		for(int i=1;i<=N;i++)
		{
			ans+=BIT.Query(N)-BIT.Query(S[i]);
			BIT.Add(S[i]);
		}
		long long now=ans;
		for(int i=1;i<N;i++)
		{
			now-=S[i]-1;
			now+=N-S[i];
			if(now<ans)ans=now;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
