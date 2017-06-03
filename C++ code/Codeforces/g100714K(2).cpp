#include<cstdio>
#include<vector>
#include<utility>
//#include<cassert>
using namespace std;
//template<class T>inline void getmin(T&a,const T&b){if(b<a)a=b;}
//template<class T>inline void getmax(T&a,const T&b){if(a<b)a=b;}
int N,M;
void assert(bool valid){if(!valid)for(;;){int a=1,b=0;a/=b+1;printf("%d %d",a,b);}}
int main()
{
//	assert(0);
	scanf("%d%d",&N,&M);
	vector<pair<int,int> >s[2];
	for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)s[0].push_back(make_pair(i,j));
	for(int d=0;;d^=1)
	{
		assert(!s[d].empty());
		printf("%d %d\n",s[d][0].first,s[d][0].second);
		fflush(stdout);
		static char respond[100];
		scanf("%s",respond);
		if(respond[1]=='E')return 0;
		int di,dj;
		switch(respond[0])
		{
			case'U':di=-1,dj=0;break;
			case'D':di=1,dj=0;break;
			case'L':di=0,dj=-1;break;
			case'R':di=0,dj=1;break;
			default:assert(0);break;
		}
		s[d^1].clear();
		for(int _=1;_<(int)s[d].size();_++)
		{
			const auto &p=s[d][_];
			int i=p.first+di,j=p.second+dj;
			if(1<=i&&i<=N&&1<=j&&j<=M)s[d^1].push_back(make_pair(i,j));
		}
	}
}
