#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		vector<int>s;
		for(int i=0;i<N;i++)
		{
			int v=1;
			while(!s.empty()&&s.back()==v)s.pop_back(),++v;
			s.push_back(v);
		}
		for(int i=0;i<(int)s.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",s[i]);
		}
		puts("");
	}
	return 0;
}
