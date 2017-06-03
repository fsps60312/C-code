#include<cstdio>
#include<queue>
#include<vector>
#include<cassert>
using namespace std;
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL b){if(b<a)a=b;}
int T;
char S[500001];
LL Solve()
{
	priority_queue<LL,vector<LL>,greater<LL> >pq;
	LL ans=0LL;
	for(int i=0,h=0;;i++)
	{
		if(S[i]=='\0')
		{
			if(h!=0)return INF;
			return ans;
		}
		else if(S[i]=='?')
		{
			LL l,r;
			scanf("%lld%lld",&l,&r);
			if(ans==INF)continue;
			pq.push(l-r);
			ans+=r,h--;
		}
		else if(S[i]=='(')h++;
		else if(S[i]==')')h--;
		else assert(0);
		if(ans==INF)continue;
		if(h<0)
		{
			if(pq.empty())ans=INF;
			else
			{
				ans+=pq.top(),pq.pop();
				h+=2;
			}
		} 
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",S);
		LL ans=Solve();
		if(ans==INF)puts("IMBA");
		else printf("%lld\n",ans);
	}
	return 0;
}
