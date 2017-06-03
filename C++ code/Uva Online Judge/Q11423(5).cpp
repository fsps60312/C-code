#include<cstdio>
int TIME;
struct Bit
{
	int s[10000001];
	void clear(){for(int i=1;i<=10000000;i++)s[i]=0;}
	inline int lowbit(const int i){return i&(-i);}
	void Add(int i,const int v){while(i<=10000000)s[i]+=v,i+=lowbit(i);}
	int Query(int i)
	{
		int ans=0;
		while(i)ans+=s[i],i-=lowbit(i);
		return ans;
	}
}BIT;
int N,CACHE[30],MISS[30];
int PRE[1<<24];
void Access(const int type)
{
	BIT.Add(++TIME,1);
	if(PRE[type]==0)for(int i=0;i<N;i++)MISS[i]++;
	else
	{
		const int cnt=BIT.Query(TIME)-BIT.Query(PRE[type]);
		for(int i=0;i<N&&cnt>CACHE[i];i++)MISS[i]++;
		BIT.Add(PRE[type],-1);
	}
	PRE[type]=TIME;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<(1<<24);i++)PRE[i]=0;
		for(int i=0;i<N;i++)
		{
			scanf("%d",&CACHE[i]);
			MISS[i]=0;
		}
		BIT.clear();
		TIME=0;
		for(;;)
		{
			static char command[6];scanf("%s",command);
			if(command[0]=='E')break;
			else if(command[0]=='A')
			{
				static int v;scanf("%d",&v);
				Access(v);
			}
			else if(command[0]=='R')
			{
				static int b,y,n;scanf("%d%d%d",&b,&y,&n);
				for(int k=0;k<n;k++)Access(b+y*k);
			}
			else if(command[0]=='S')
			{
				for(int i=0;i<N;i++)
				{
					if(i)putchar(' ');
					printf("%d",MISS[i]);
					MISS[i]=0;
				}
				puts("");
			}
		}
	}
	return 0;
}
