#include<cstdio>
int N,S[100001],LOC[100001],LU[100001],RU[100001],LD[100001],RD[100001];
struct Bit
{
	int v[200001];
	void Clear(){for(int i=1;i<=N*2;i++)v[i]=0;}
	int lowbit(int i){return i&(-i);}
	void Add(int i)
	{
		while(i<=N*2)
		{
			v[i]++;
			i+=lowbit(i);
		}
	}
	void Minus(int i)
	{
		while(i<=N*2)
		{
			v[i]--;
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
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)
		{
			scanf("%d",&S[i]);
			LOC[S[i]]=i; 
		}
		long long ans=0;
		BIT.Clear();
		for(int i=1;i<=N;i++)
		{
			LU[i]=i-1-BIT.Query(S[i]);
			LD[i]=i-1-LU[i];
			ans+=LU[i];
			BIT.Add(S[i]);
		}
		BIT.Clear();
		for(int i=N;i>=1;i--)
		{
			RU[i]=N-i-BIT.Query(S[i]);
			RD[i]=N-i-RU[i];
			BIT.Add(S[i]);
		}
		long long now=ans;
//		printf("%d\n",now);
		for(int i=1;i<N;i++)
		{
			//when i become largest
			//inverse pairs:
			//lose LU[LOC[i]]
			//gain RU[LOC[i]]
			//lose LD[LOC[i]]
			//gain RD[LOC[i]]
			now-=LU[LOC[i]]+LD[LOC[i]];
			now+=RU[LOC[i]]+RD[LOC[i]];
//			printf("%d\n",now);
			if(now<ans)ans=now;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
