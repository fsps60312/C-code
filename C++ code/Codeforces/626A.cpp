#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		map<pair<int,int>,int>s;
		pair<int,int>now=make_pair(0,0);
		s[now]++;
		static char str[201];scanf("%s",str);
		int ans=0;
		for(int i=0;i<N;i++)
		{
			switch(str[i])
			{
				case'U':now.first++;break;
				case'D':now.first--;break;
				case'L':now.second++;break;
				case'R':now.second--;break;
				default:assert(0);break;
			}
			ans+=s[now]++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
