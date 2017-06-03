#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef vector<int> Big;
bool operator<(const Big &a,const Big &b)
{
	if(a.size()!=b.size())return a.size()<b.size();
	for(int i=(int)a.size()-1;i>=0;i--)if(a[i]!=b[i])return a[i]<b[i];
	return false;
}
void getmax(Big &a,const Big &b){if(a<b)a=b;}
void Print(const Big &a)
{
	for(int i=(int)a.size()-1;i>=0;i--)printf("%d",a[i]);
}
void Carry(Big &a)
{
	for(int i=0;i<(int)a.size();i++)if(a[i]>=10)
	{
		if(i+1==(int)a.size())a.push_back(0);
		a[i+1]+=a[i]/10;
		a[i]%=10;
	}
}
Big operator*(const Big &a,const Big &b)
{
	Big ans;
	ans.resize((int)(a.size()+b.size())-1,0);
	for(int i=0;i<(int)a.size();i++)for(int j=0;j<(int)b.size();j++)ans[i+j]+=a[i]*b[j];
	Carry(ans);
	return ans;
}
void operator*=(Big &a,const Big &b){a=(a*b);}
void operator++(Big &a){a[0]++;Carry(a);}
Big MakeBig(const int b){Big a;a.push_back(b);Carry(a);return a;}
int N;
Big DP[700][3];
vector<int>ET[700];
struct Type
{
	Big yes,no,one;
	Type(){}
	Type(const Big &_yes,const Big &_no,const Big &_one):yes(_yes),no(_no),one(_one){}
	bool operator<(const Type &t)const{return no*t.yes<yes*t.no;}
};
Big Dfs(const int u,const int fa,const int dep)
{
	Big &ans=DP[u][dep];
	if(!ans.empty())return ans;
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
		vector<Big>yes,no,part;
		yes.resize(sz+1),no.resize(sz+1),part.resize(sz+1);
		if(true)
		{
			Big v1=yes[0]=MakeBig(1),v2=part[0]=MakeBig(dep==1?2:1);
			for(int i=1;i<=sz;i++)v1*=chinfo[i-1].yes,++v2,yes[i]=v1,part[i]=v2;
			v1=no[sz]=MakeBig(1);
			for(int i=sz-1;i>=0;i--)v1*=chinfo[i].no,no[i]=v1;
		}
		for(int i=0;i<=sz;i++)getmax(ans,yes[i]*no[i]*part[i]);
	}
	if(dep==1)return ans;
	if(sz)
	{
		vector<Big>left,right;
		left.resize(sz),right.resize(sz);
		Big tmp=left[0]=MakeBig(1);
		for(int i=1;i<sz;i++)tmp*=chinfo[i-1].no,left[i]=tmp;
		tmp=right[sz-1]=MakeBig(1);
		for(int i=sz-2;i>=0;i--)tmp*=chinfo[i+1].no,right[i]=tmp;
		for(int i=0;i<sz;i++)getmax(ans,left[i]*right[i]*chinfo[i].one);
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
			for(int j=0;j<N;j++)for(int k=0;k<3;k++)DP[j][k].clear();
			Big ta=Dfs(i,-1,2);
			getmax(ans,ta);
		}
		Print(ans);puts("");
	}
	return 0;
}
