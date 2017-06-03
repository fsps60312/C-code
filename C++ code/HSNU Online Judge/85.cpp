#include<cstdio>
#include<queue>
#include<algorithm>
#include<vector>
#include<cassert>
using namespace std;
typedef long long LL;
int N;
struct Worm
{
	LL carbon,endure;
}WORM[300000];
bool CmpEndure(const Worm &a,const Worm &b){return a.endure<b.endure;}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)
	{
		Worm &w=WORM[i];
		scanf("%lld%lld",&w.carbon,&w.endure);
	}
	sort(WORM,WORM+N,CmpEndure);
	priority_queue<LL>mx;
	priority_queue<LL,vector<LL>,greater<LL> >mn;
	LL carbon=0LL,cnt=0LL,ans=0LL;
	for(int i=N-1;i>=0;i--)
	{
		const Worm &w=WORM[i];
		mn.push(w.carbon);
		while(cnt>0LL&&mx.top()>mn.top())
		{
			const LL v=mx.top();
			cnt--,carbon-=v,mx.pop();
			mn.push(v);
		}
		while(!mn.empty()&&(cnt+1LL)*w.endure>=carbon+mn.top())
		{
			const LL v=mn.top();
			cnt++,carbon+=v,mx.push(v);
			mn.pop();
		}
		ans=max(ans,cnt);
	}
	printf("%lld\n",ans);
	return 0;
}
