#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int MOD=10000;
struct Big
{
	vector<int>*data;
	int size()const{return data->size();}
	bool operator<(const Big &a)const
	{
		if(size()!=a.size())return size()<a.size();
		for(int i=(int)size()-1;i>=0;i--)if((*data)[i]!=(*a.data)[i])return (*data)[i]<(*a.data)[i];
		return false;
	}
	void Carry()
	{
		for(int i=0;i<size();i++)if((*data)[i]>=MOD)
		{
			if(i+1==size())data->push_back(0);
			(*data)[i+1]+=(*data)[i]/MOD;
			(*data)[i]%=MOD;
		}
	}
	Big operator*(const Big &a)const
	{
		Big ans;
		ans.data->resize((int)(size()+a.size())-1,0);
		for(int i=0;i<(int)size();i++)for(int j=0;j<(int)a.size();j++)(*ans.data)[i+j]+=(*data)[i]*(*a.data)[j];
		ans.Carry();
		return ans;
	}
	void operator*=(const Big &a){(*this)=(*this)*a;}
	void operator++(){(*data)[0]++;Carry();}
	Big():data(new vector<int>()){}
	Big(const int b):data(new vector<int>()){data->push_back(b);Carry();}
	Big(const Big &a):data(new vector<int>())
	{
		data->resize(a.size());
		for(int i=0;i<a.size();i++)(*data)[i]=(*a.data)[i];
	}
};
void getmax(Big &a,const Big &b){if(a<b)a=b;}
void Print(const Big &a)
{
	bool printed=false;
	for(int i=(int)a.size()-1;i>=0;i--)
	{
		const int v=(*a.data)[i];
		printf(printed?"%04d":"%d",v);
		printed=true;
	}
}
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
	if(!(ans.data->empty()))return ans;
	if(true)
	{
		ans=Big(1);
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
			Big v1=Big(1),v2=Big(dep==1?2:1);
			yes[0]=Big(v1),part[0]=Big(v2);
			for(int i=1;i<=sz;i++)v1*=chinfo[i-1].yes,++v2,yes[i]=Big(v1),part[i]=Big(v2);
			v1=Big(1);
			no[sz]=Big(v1);
			for(int i=sz-1;i>=0;i--)v1*=chinfo[i].no,no[i]=Big(v1);
		}
		for(int i=0;i<=sz;i++)getmax(ans,yes[i]*no[i]*part[i]);
	}
	if(dep==1)return ans;
	if(sz)
	{
		vector<Big>left,right;
		left.resize(sz),right.resize(sz);
		Big tmp=Big(1);
		left[0]=Big(tmp);
		for(int i=1;i<sz;i++)tmp*=chinfo[i-1].no,left[i]=Big(tmp);
		tmp=Big(1);
		right[sz-1]=Big(tmp);
		for(int i=sz-2;i>=0;i--)tmp*=chinfo[i+1].no,right[i]=Big(tmp);
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
		Big ans=Big(0);
		for(int i=0;i<=0;i++)
		{
			for(int j=0;j<N;j++)for(int k=0;k<3;k++)DP[j][k].data->clear();
			Big ta=Dfs(i,-1,2);
			getmax(ans,ta);
		}
		Print(ans);puts("");
	}
	return 0;
}
