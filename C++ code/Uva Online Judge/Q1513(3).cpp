#include<cstdio>
int V[200001],MOVIE[200001];
struct Bit
{
	int sz;
	void clear(int _sz){sz=_sz;for(int i=1;i<=sz;i++)V[i]=0;}
	int lowbit(int i){return i&(-i);}
	void add(int i)
	{
		while(i<=sz)
		{
			V[i]++;
			i+=lowbit(i);
		}
	}
	void sub(int i)
	{
		while(i<=sz)
		{
			V[i]--;
			i+=lowbit(i);
		}
	}
	int query(int i)
	{
		int ans=0;
		while(i)
		{
			ans+=V[i];
			i-=lowbit(i);
		}
		return ans;
	}
}BIT;
int T,N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&N,&M);
		BIT.clear(N+M);
		for(int i=1;i<=N;i++)
		{
			BIT.add(M+i);
			MOVIE[i]=M+i;
		}
		for(int i=M,v;i;i--)
		{
			scanf("%d",&v);
			if(i<M)printf(" ");
			printf("%d",BIT.query(MOVIE[v]-1));
			BIT.sub(MOVIE[v]);
			MOVIE[v]=i;
			BIT.add(MOVIE[v]);
		}
		puts("");
	}
	return 0;
}
