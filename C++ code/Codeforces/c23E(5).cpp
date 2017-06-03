#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
typedef LL Big;
void getmax(Big &a,const Big &b){if(a<b)a=b;}
void Print(const Big &a)
{
	printf("%I64d",a);
}
Big MakeBig(const int b){return b;}
int N;
Big DP[700][3];
vector<int>ET[700];
struct Type
{
	Big yes,no,one;
	Type(){}
	Type(const Big &_yes,const Big &_no,const Big &_one):yes(_yes),no(_no),one(_one){}
	bool operator<(const Type &t)const{return yes*t.no>no*t.yes;}
};
Big Dfs(const int u,const int fa,const int dep)
{
	Big &ans=DP[u][dep];
	if(ans!=-1LL)return ans;
	if(true)
	{
		ans=MakeBig(1);
		for(const int nxt:ET[u])if(nxt!=fa)ans*=Dfs(nxt,u,2);
	}
	if(dep==0)return ans;
	vector<Type>chinfo;
	for(const int nxt:ET[u])if(nxt!=fa)chinfo.push_back(Type(Dfs(nxt,u,0),Dfs(nxt,u,2),Dfs(nxt,u,1)));
	sort(chinfo.begin(),chinfo.end());
	const int sz=chinfo.size();
	if(true)
	{
//		LL ta=1LL,sz=(dep==1?2LL:1LL)+(LL)chinfo.size();
//		for(const auto &v:chinfo)ta*=v.yes;
//		ans=sz*ta;
//		for(const auto &v:chinfo)
//		{
//			(ta/=v.yes)*=v.no,sz--;
//			getmax(ans,sz*ta);
//			printf(" %lld,%lld",sz,ta);
//		}puts("");
		vector<Big>yes,no,part;
		yes.resize(sz+1),no.resize(sz+1),part.resize(sz+1);
		if(true)
		{
			Big v1=yes[0]=MakeBig(1),v2=part[0]=MakeBig(dep==1?2:1);
			for(int i=1;i<=sz;i++)v1*=chinfo[i-1].yes,yes[i]=v1,++v2,part[i]=v2;
			v1=no[sz]=MakeBig(1);
			for(int i=sz-1;i>=0;i--)v1*=chinfo[i].no,no[i]=v1;
		}
		assert(part[sz]==(dep==1?2:1)+(LL)chinfo.size());
		for(int i=0;i<=sz;i++)getmax(ans,yes[i]*no[i]*part[i]);//,printf("(%lld,%lld)",yes[i]*no[i],part[i]);puts("");
//		printf("dep=%d\n",dep);
//		system("pause");
	}
	if(dep==1)return ans;
	if(sz)
	{
		LL ta=1LL;
		for(const int nxt:ET[u])if(nxt!=fa)ta*=Dfs(nxt,u,2);
		for(const int nxt:ET[u])if(nxt!=fa)
		{
			getmax(ans,ta/Dfs(nxt,u,2)*Dfs(nxt,u,1));
		}
//		vector<Big>left,right;
//		left.resize(sz),right.resize(sz);
//		Big tmp=left[0]=MakeBig(1);
//		for(int i=1;i<sz;i++)tmp*=chinfo[i-1].no,left[i]=tmp;
//		tmp=right[sz-1]=MakeBig(1);
//		for(int i=sz-2;i>=0;i--)tmp*=chinfo[i+1].no,right[i]=tmp;
//		for(int i=0;i<sz;i++)getmax(ans,left[i]*right[i]*chinfo[i].one);
	}
	assert(dep==2);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		Big ans=MakeBig(0);
		for(int i=0;i<N;i++)
		{
			for(int j=0;j<N;j++)for(int k=0;k<3;k++)DP[j][k]=-1LL;
			Big ta=Dfs(i,-1,2);
			getmax(ans,ta);
		}
		Print(ans);puts("");
	}
	return 0;
}
