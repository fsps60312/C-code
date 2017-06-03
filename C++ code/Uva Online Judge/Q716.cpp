#include<cstdio>
void termin(){int a[9];for(int i=0;;i--)a[i]=9;}
int T,N,B[1000000];
struct Bit
{
	int v[1000001],sz;
	int lowbit(int &i){return i&(-i);}
	void clear(int _sz){sz=_sz;for(int i=1;i<=sz;i++)v[i]=0;}
	void add(int i)
	{
		while(i<=sz)
		{
			v[i]++;
			i+=lowbit(i);
		}
	}
	int query(int i)
	{
		int ans=0;
		while(i>0)
		{
			ans+=v[i];
			i-=lowbit(i);
		}
		return ans;
	}
}BIT;
bool solve()
{
	int x=-1,y=-1,z=-1,oe=0;
	for(int i=0,limit=N*N*N;i<limit;i++)
	{
		int &b=B[i];
		scanf("%d",&b);
		if(b)
		{
			oe^=BIT.query(b);
			BIT.add(b);
		}
		else
		{
			int j=i;
			z=j/(N*N),j%=N*N;
			y=j/N,x=j%N;
		}
	}
//	printf("oe=%d\n",oe&1);
	if(x<0)termin();
	if(N&1)
	{
		if(oe&1)return false;
		else return true;
	}
	else
	{
		oe^=(N-1-y)+(N-1-z);
		if(oe&1)return true;
		else return false;
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		BIT.clear(N*N*N);
		printf(solve()?"Puzzle can be solved.\n":"Puzzle is unsolvable.\n");
	}
	return 0;
}
