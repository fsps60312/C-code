#include<cstdio>
#include<cassert>
#include<map>
#include<stack>
using namespace std;
typedef long long LL;
map<char,pair<LL,LL> >M;
void ReadInput()
{
	int matrixcount;
	scanf("%d",&matrixcount);
	M.clear();
	for(LL a,b;matrixcount--;)
	{
		static char name[2];
		scanf("%s%lld%lld",name,&a,&b);
		M[name[0]]=make_pair(a,b);
	}
}
char S[10000000];
int LEFT[10000000];
pair<LL,LL>GetM(const char c)
{
	const auto it=M.find(c);
	if(it==M.end())printf("c=%c\n",c),assert(0);
	return it->second;
}
pair<LL,LL>GetValue(const int l,const int r,LL &ans)
{
	assert(l<=r);
//	printf("(%d,%d):",l,r);for(int i=l;i<=r;i++)putchar(S[i]);puts("");
	if(l==r)return GetM(S[r]);
	pair<LL,LL>a,b;
	if(S[l]!='('&&S[r]!=')')assert(l+1==r),a=GetM(S[l]),b=GetM(S[r]);
	else if(S[l]!='(')a=GetM(S[l]),b=GetValue(l+2,r-1,ans);
	else if(S[r]!=')')a=GetValue(l+1,r-2,ans),b=GetM(S[r]);
	else
	{
		if(LEFT[r]==l)return GetValue(l+1,r-1,ans);
		a=GetValue(l+1,LEFT[r]-2,ans),b=GetValue(LEFT[r]+1,r-1,ans);
	}
	if(ans==-1LL||a.second!=b.first)ans=-1LL;
	else ans+=a.first*b.first*b.second;
	return make_pair(a.first,b.second);
}
int main()
{
//	freopen("in.txt","r",stdin);
	ReadInput();
	while(scanf("%s",S)==1)
	{
		int n;
		stack<int>stk;
		for(n=0;S[n];n++)
		{
			if(S[n]=='(')stk.push(n);
			if(S[n]==')')LEFT[n]=stk.top(),stk.pop();
		}
		assert(stk.empty());
		LL ans=0LL;
		GetValue(0,n-1,ans);
		if(ans==-1LL)puts("error");
		else printf("%lld\n",ans);
	}
	return 0;
}
