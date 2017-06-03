#include<cstdio>
#include<cassert>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
int N,TYPE[100000],COLOR[100000];
vector<int>ET[100000];
int TagType(const int u,const int parent,const int type)
{
	TYPE[u]=type;
	int ans=(type==0?1:0);
	for(const int nxt:ET[u])if(nxt!=parent)ans+=TagType(nxt,u,type^1);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("bicoloring.in","r",stdin);
	freopen("bicoloring.out","w",stdout);
	scanf("%d",&N),N/=2;
	for(int i=0;i<N*2;i++)ET[i].clear();
	for(int i=0,a,b;i<N*2-1;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		ET[a].push_back(b),ET[b].push_back(a);
	}
	if(TagType(0,-1,0)>N)
	{
		for(int i=0;i<N*2;i++)TYPE[i]^=1;
	}
	if(true)
	{
		int cnt=0;
		for(int i=0;i<N*2;i++)if(TYPE[i]==0)cnt++;
		if(cnt>N)for(;;)putchar('E');
	}
	for(int i=0;i<N*2;i++)COLOR[i]=-1;
	for(int i=0,now=1;i<N*2;i++)if(TYPE[i]==0)COLOR[i]=now++;
	vector<int>order;
	for(int i=0;i<N*2;i++)if(TYPE[i]==1)order.push_back(i);
	sort(order.begin(),order.end(),[](const int a,const int b)->bool{return ET[a]>ET[b];});
	set<int>remain;
	for(int i=1;i<=N+1;i++)remain.insert(i);
	for(const int i:order)
	{
		set<int>restrict;
		for(const int nxt:ET[i])restrict.insert(COLOR[nxt]);
		assert(restrict.find(-1)==restrict.end());
		int &ans=COLOR[i];assert(ans==-1);
		for(auto it=remain.begin();ans==-1&&it!=remain.end();it++)if(restrict.find(*it)==restrict.end())ans=*it;
		assert(ans!=-1);
		remain.erase(ans);
	}
	for(int i=0;i<N*2;i++)
	{
		if(i)putchar(' ');
		printf("%d",COLOR[i]);
	}
	puts("");
	return 0;
}
