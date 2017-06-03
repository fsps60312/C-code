#include<cstdio>
int T,N,S[503];
struct Bit
{
	int bse[501];
	void clear(){for(int i=0;i<=N;i++)bse[i]=0;}
	int lowbit(int i){return i&(-i);}
	void add(int i,int v)
	{
		while(i<=N)
		{
			bse[i]+=v;
			i+=lowbit(i);
		}
	}
	int query(int i)
	{
		int ans=0;
		while(i)
		{
			ans+=bse[i];
			i-=lowbit(i);
		}
		return ans;
	}
}BIT;
bool solve()
{
	for(int i=0;i<N;i++)
	{
		BIT.clear();
		static int inv;
		inv=0;
		for(int cnt=0,j=i-1;cnt<N;cnt++,j--)
		{
			if(j<0)j+=N;
			BIT.add(S[j],1);
			inv+=BIT.query(S[j]-1);
		}
		if((inv&1)==0)return true;
	}
	return false;
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)
		{
			scanf("%d",&S[i]);
		}
		printf("%s\n",solve()?"possible":"impossible");
	}
	return 0;
}
