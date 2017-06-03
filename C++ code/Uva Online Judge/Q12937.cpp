#include<cstdio>
#include<map>
#include<queue>
using namespace std;
typedef long long LL;
int N,M,A,B;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d%d%d",&N,&M,&A,&B)==4)
	{
		LL now=0LL,ans=0LL,flip=(1LL<<N)-1LL;
		map<LL,LL>m;
		queue<LL>qa,qb;
		qa.push(0LL),qb.push(0LL);
		for(int i=0;i<M;i++)
		{
			static char s[51];
			scanf("%s",s);
			LL t=0LL;
			for(int j=0;j<N;j++)
			{
				t<<=1;
				if(s[j]=='1')t|=1LL;
			}
			now^=t;
			if(qa.size()==A)
			{
				LL u=qa.front();qa.pop();
				if(m.find(u)==m.end())m[u]=1LL;
				else m[u]++;
			}
			if(qb.size()>B)
			{
				LL u=qb.front();qb.pop();
				m[u]--;
			}
			if(m.find(now^flip)!=m.end())ans+=m[now^flip];
			qa.push(now),qb.push(now);
		}
		static int kase=1;
		printf("Case %d: %lld\n",kase++,ans);
	}
	return 0;
}
