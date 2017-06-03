#include<cstdio>
#include<cassert>
#include<set>
using namespace std;
const int INF=2147483647;
void getmin(int &a,const int b){if(b<a)a=b;}
int N;
multiset<int>A,B;
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		A.clear(),B.clear();
		scanf("%d",&N);
		for(int i=0,type,x,y;i<N;i++)
		{
			scanf("%d%d%d",&type,&x,&y);
			if(type==0)A.insert(x+y),B.insert(x-y);
			else
			{
				int ans=INF;
				{
					auto it=A.lower_bound(x+y);
					if(it!=A.end())getmin(ans,(*it)-(x+y));
					if(it!=A.begin())getmin(ans,(x+y)-(*--it));
				}
				{
					auto it=B.lower_bound(x-y);
					if(it!=B.end())getmin(ans,(*it)-(x-y));
					if(it!=B.begin())getmin(ans,(x-y)-(*--it));
				}
				printf("%d\n",ans);
			}
		}
	}
	return 0;
}
