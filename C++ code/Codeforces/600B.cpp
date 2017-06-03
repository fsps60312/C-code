#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
int N,M;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		map<int,int>s;
		for(int i=0,a;i<N;i++)scanf("%d",&a),++s[a];
		int sum=0;
		for(auto &it:s)it.second=(sum+=it.second);
		for(int i=0,b;i<M;i++)
		{
			scanf("%d",&b);
			auto it=s.upper_bound(b);
			if(i)putchar(' ');
			if(it==s.begin())printf("0");
			else printf("%d",(--it)->second);
		}
		puts("");
	}
	return 0;
}
