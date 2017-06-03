#include<cstdio>
#include<map>
#include<cassert>
using namespace std;
int N,CACHE[30];
map<int,int>TIME[30],TYPE[30];
int MISS[30];
void Access(const int type)
{
	static int kase=0;
	for(int i=0;i<N;i++)
	{
		assert(TIME[i].size()==TYPE[i].size());
		const auto it=TIME[i].find(type);
		if(it!=TIME[i].end())
		{
			TYPE[i].erase(TYPE[i].find(it->second));
			TYPE[i][it->second=kase++]=type;
		}
		else
		{
			MISS[i]++;
			assert(TIME[i].size()<=CACHE[i]);
			if(TIME[i].size()==CACHE[i])
			{
				const auto remove=TYPE[i].begin();
				TIME[i].erase(TIME[i].find(remove->second));
				TYPE[i].erase(remove);
			}
			TYPE[i][TIME[i][type]=kase++]=type;
		}
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)
		{
			scanf("%d",&CACHE[i]);
			TIME[i].clear(),TYPE[i].clear();
			MISS[i]=0;
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
