#include<cstdio>
int N,S[100001],LOC[100001],LD[100001],RD[100001];
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
int Lu(int loc){return loc-1-LD[loc];}
int Ru(int loc){return (N-loc)-RD[loc];}
int Ld(int loc){return LD[loc];}
int Rd(int loc){return RD[loc];}
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
		BIT.Clear();
		long long ans=0;
		for(int i=1;i<=N;i++)
		{
			LD[i]=BIT.Query(S[i]);
			ans+=i-1-LD[i];
			BIT.Add(S[i]);
		}
		BIT.Clear();
		for(int i=N;i>=1;i--)
		{
			RD[i]=BIT.Query(S[i]);
			BIT.Add(S[i]);
		}
		long long now=ans;
		printf("%d\n",now);
		for(int i=1;i<N;i++)
		{
			//left larger no need move
			//right larger need move
//			printf("(%d,%d)\n",Ru(LOC[i]),Lu(LOC[i]));
			int v=Ru(LOC[i])-Lu(LOC[i])+Rd(LOC[i]);
			now+=v;
			printf("%d\n",now);
			if(now<ans)ans=now;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
