#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
int N;
int TO[100001];
bool VIS[100001];
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("bureau.in","r",stdin);
	freopen("bureau.out","w",stdout);
	while(scanf("%d",&N)==1)
	{
		for(int i=1;i<=N;i++)
		{
			static char type[100];
			scanf("%s",type);
			if(type[0]=='d')TO[i]=0;
			else assert(type[0]=='c'),scanf("%d",&TO[i]);
			VIS[i]=true;
		}
		vector<int>ans;
		for(int i=N;i>=1;i--)if(VIS[i])
		{
			ans.push_back(i);
			VIS[TO[i]]=false;
		}
		printf("%d\n",(int)ans.size());
		for(int i=(int)ans.size()-1;i>=0;i--)
		{
			printf("%d",ans[i]);
			if(i)putchar(' ');
		}
		puts("");
	}
	return 0;
}
