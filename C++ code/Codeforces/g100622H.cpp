#include<cstdio>
#include<cassert>
#include<map>
#include<set>
using namespace std;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("homo.in","r",stdin);
	freopen("homo.out","w",stdout);
	while(scanf("%d",&N)==1)
	{
		map<int,int>cnt;
		multiset<int>s;
		for(int i=0,v;i<N;i++)
		{
			static char type[100];
			scanf("%s%d",type,&v);
			if(type[0]=='i')
			{
				if(cnt[v])s.erase(s.find(cnt[v]));
				++cnt[v];
				s.insert(cnt[v]);
//				printf("cnt[v]=%d %d\n",cnt[v],*s.rend());
			}
			else
			{
				assert(type[0]=='d');
				if(cnt.find(v)!=cnt.end())
				{
					s.erase(s.find(cnt[v]));
					if(!--cnt[v])cnt.erase(cnt.find(v));
					else s.insert(cnt[v]);
				}
			}
			bool a,b;
			if((int)cnt.size()>=2)a=true;
			else a=false;
			if(!s.empty()&&*s.rbegin()>=2)b=true;
			else b=false;
			if(a&&b)puts("both");
			else if(a&&!b)puts("hetero");
			else if(!a&&b)puts("homo");
			else puts("neither");
		}
	}
	return 0;
}
