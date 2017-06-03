#include<cstdio>
int N,K,DJ[150000];
int Find(const int &a){return DJ[a]==a?a:(DJ[a]=Find(DJ[a]));}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&K)==2)
	{
		for(int i=0;i<N*3;i++)DJ[i]=i;
		int ans=0;
		while(K--)
		{
			static int d,x,y;
			scanf("%d%d%d",&d,&x,&y);
			x--,y--;
			if(x>=N||y>=N)ans++;
			else if(d==1)
			{
				if(Find(x)==Find(y+N)||Find(x)==Find(y+N+N))ans++;
				else for(int i=0;i<3;i++)DJ[Find(x+N*i)]=Find(y+N*i);
			}
			else
			{
				if(Find(x)==Find(y)||Find(x)==Find(y+N+N))ans++;
				else for(int i=0;i<3;i++)DJ[Find(x+N*i)]=Find(y+N*((i+1)%3));
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
