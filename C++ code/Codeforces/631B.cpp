#include<cstdio>
#include<cassert>
#include<utility>
#include<algorithm>
using namespace std;
int R,C,K;
pair<int,int>COL[5000],ROW[5000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d",&R,&C,&K)==3)
	{
		for(int i=0;i<R;i++)ROW[i]=make_pair(-1,0);
		for(int i=0;i<C;i++)COL[i]=make_pair(-1,0);
		for(int type,x,a,i=0;i<K;i++)
		{
			scanf("%d%d%d",&type,&x,&a);
			if(type==1)ROW[--x]=make_pair(i,a);
			else if(type==2)COL[--x]=make_pair(i,a);
			else assert(0);
		}
		for(int i=0;i<R;i++)
		{
			for(int j=0;j<C;j++)
			{
				if(j)putchar(' ');
				printf("%d",max(ROW[i],COL[j]).second);
			}
			puts("");
		}
	}
	return 0;
}
