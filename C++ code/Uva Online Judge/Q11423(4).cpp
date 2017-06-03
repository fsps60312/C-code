#include<cstdio>
#include<queue>
#include<cassert>
using namespace std;
int N,CACHE[30];
int TIME[30][1<<24];
queue<int>TYPE[30];
int MISS[30],SZ[30];
bool VIS[1<<24];
inline void Access(const int type)
{
	if(!VIS[type])
	{
		for(int i=0;i<N;i++)TIME[i][type]=0;
		VIS[type]=true;
	}
	for(int i=0;i<N;i++)
	{
		if(TIME[i][type]>0)
		{
			TIME[i][type]++;
			TYPE[i].push(type);
		}
		else
		{
			assert(TIME[i][type]==0);
			MISS[i]++;
			if(SZ[i]==CACHE[i])
			{
				while(--TIME[i][TYPE[i].front()])assert(!TYPE[i].empty()),TYPE[i].pop();
				assert(!TYPE[i].empty());
				TYPE[i].pop();
				SZ[i]--;
			}
			TIME[i][type]++;
			TYPE[i].push(type);
			SZ[i]++;
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<(1<<24);i++)VIS[i]=false;
		for(int i=0;i<N;i++)
		{
			scanf("%d",&CACHE[i]);
			while(!TYPE[i].empty())TYPE[i].pop();
			MISS[i]=SZ[i]=0;
		}
		for(;;)
		{
			static char command[6];scanf("%s",command);
			if(command[0]=='E')break;
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
			else if(command[0]=='A')
			{
				static int x;scanf("%d",&x);
				Access(x);
			}
			else if(command[0]=='R')
			{
				static int b,y,n;scanf("%d%d%d",&b,&y,&n);
				for(int k=0;k<n;k++)Access(b+y*k);
			}
			else assert(0&&"Invalid Command");
		}
	}
	return 0;
}
