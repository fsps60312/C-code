#include<cstdio>
#include<queue>
#include<vector>
//#include<cassert>
using namespace std;
void assert(bool valid){if(valid)return;for(;;)putchar('E');}
typedef long long LL;
const LL INF=9223372036854775807LL;
void getmin(LL &a,const LL b){if(b<a)a=b;}
int T;
char S[1000002];
LL Solve()
{
	priority_queue<LL,vector<LL>,greater<LL> >pq;
	LL ans=0LL;
	for(int i=0,h=0;;i++)
	{
		if(S[i]=='\0'||S[i]=='\n')
		{
			if(h!=0)return INF;
			return ans;
		}
		else if(S[i]=='?')
		{
			LL l,r;
			static char tmp[1000];
			fgets(tmp,1000,stdin);
			sscanf(tmp,"%lld%lld",&l,&r);
			pq.push(l-r);
			ans+=r,h--;
		}
		else if(S[i]=='(')h++;
		else if(S[i]==')')h--;
//		else assert(0);
		else
		{
			const char c=S[i];
//			assert(c==' '||c=='\t');
			assert(c<'0'||(c>'9'&&c<'A')||(c>'Z'&&c<'a')||c>'z');
//			assert((c>='0'&&c<='9')||(c>='A'&&c<='Z')||(c>='a'&&c<='z'));
//			assert(c<'0'||(c>'9'&&c<'A')||(c>'Z'&&c<'a')||c>'z'||(c>='0'&&c<='9')||(c>='A'&&c<='Z')||(c>='a'&&c<='z'));
		}
		if(h<0)
		{
			if(pq.empty())return INF;
			ans+=pq.top();pq.pop();
			h+=2;
		} 
	}
	assert(0);
}
int main()
{
//	char c=1;
//	for(;c;c++)
//	{
//		if(c<'0'||(c>'9'&&c<'A')||(c>'Z'&&c<'a')||c>'z')continue;
//		if((c>='0'&&c<='9')||(c>='A'&&c<='Z')||(c>='a'&&c<='z'))continue;
//		printf("c=%d\n",c);
//	}
//	puts("pass");
//	printf("%d %d %d\n",'0','A','a');
//	freopen("in.txt","r",stdin);
	fgets(S,1000002,stdin);
	sscanf(S,"%d",&T);
	while(T--)
	{
		fgets(S,1000002,stdin);
//		puts(S);
		LL ans=Solve();
		if(ans==INF)puts("IMBA");
		else printf("%lld\n",ans);
	}
	return 0;
}
