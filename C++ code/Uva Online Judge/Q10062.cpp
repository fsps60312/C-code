#include<cstdio>
#include<map>
#include<set>
#include<cassert>
using namespace std;
const int INF=2147483647;
int main()
{
//	freopen("in.txt","r",stdin);
	static char tmp[1002];
	static int cnt[129];
	while(fgets(tmp,INF,stdin))
	{
		for(int i=32;i<=128;i++)cnt[i]=0;
		for(int i=0;tmp[i]&&tmp[i]!='\n';i++)assert(tmp[i]>=32&&tmp[i]<=128),cnt[tmp[i]]++;
		map<int,set<int,greater<int> > >ans;
		for(int i=32;i<=128;i++)if(cnt[i])ans[cnt[i]].insert(i);
		static int kase=0;
		if(kase++)puts("");
		for(const auto &it:ans)for(const auto &v:it.second)printf("%d %d\n",v,it.first);
	}
	return 0;
}
