#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
int N;
vector<int>ET[10000];
int Dfs(const int u,const int fa,const int bound)
{
	vector<int>ch;
	for(const int nxt:ET[u])if(nxt!=fa)
	{
		const int result=Dfs(nxt,u,bound);
//		printf("(%d,%d)(%d)=%d\n",u+1,nxt+1,bound,result);
		if(result>bound)return INF;
		ch.push_back(result);
	}
	int sz=ch.size();
	sort(ch.begin(),ch.end());
	if(sz%2==0)
	{
		bool found=true;
		for(int l=0,r=sz-1;l<r;l++,r--)if(ch[l]+ch[r]>bound){found=false;break;}
		if(found)return 1;
		if(ch[sz-1]>bound)return INF;
		ch.pop_back(),sz--;
	}
	assert(sz%2==1);
	for(int l=0,r=sz-2;l<r;l++,r--)if(ch[l]+ch[r]>bound)return INF;
	for(int l=0,r=sz-2;l<r;l++,r--)if(ch[l]+ch[r+1]>bound)return 1+ch[r+1];
	for(int l=sz/2-1,r=sz/2+1;l>=0;l--,r++)if(ch[l+1]+ch[r]>bound)return 1+ch[l+1];
	return 1+ch[0];
}
int main()
{
//	freopen("in.txt","r",stdin);
	assert(scanf("%d",&N)==1);
	for(int i=0;i<N;i++)ET[i].clear();
	for(int i=0,a,b;i<N-1;i++)
	{
		assert(scanf("%d%d",&a,&b)==2),a--,b--;
		ET[a].push_back(b),ET[b].push_back(a);
	}
	int ans=0;
	for(int i=0;i<N;i++)if((int)ET[i].size()%2==1)ans++;
	assert(ans%2==0);ans/=2;
	int l=0,r=N-1;
	const bool deg=((int)ET[0].size()%2==1);
	while(l<r)
	{
		const int mid=(l+r)/2;
		if((deg&&Dfs(0,-1,mid)-1<=mid)||(!deg&&Dfs(0,-1,mid)==1))r=mid;
		else l=mid+1;
	}
	printf("%d %d\n",ans,r);
	return 0;
}
