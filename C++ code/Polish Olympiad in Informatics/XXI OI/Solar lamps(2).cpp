#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
struct Lamp
{
	int ID,K;
	LL X,Y;
	Lamp(){}
	Lamp(const int _ID,const LL _X,const LL _Y):ID(_ID),X(_X),Y(_Y){}
};
int N;
LL X1,Y1,X2,Y2;
Lamp L[200000];
void ReadInput()
{
	scanf("%lld%lld%lld%lld",&X1,&Y1,&X2,&Y2);
	bool flipx=false,flipy=false;
	if(X1<0)X1*=-1,X2*=-1,flipx=true;
	if(Y1<0)Y1*=-1,Y2*=-1,flipy=true;
	//Y1x-X1y
	const bool flip1=(Y1*X2-X1*Y2<0LL),flip2=(Y2*X1-X2*Y1<0LL);
	for(int i=0;i<N;i++)
	{
		static LL x,y;
		scanf("%lld%lld",&x,&y);
		if(flipx)x*=-1;
		if(flipy)y*=-1;
		L[i]=Lamp(i,(flip1?-1:1)*(Y1*x-X1*y),(flip2?-1:1)*(Y2*x-X2*y));
	}
	for(int i=0;i<N;i++)scanf("%d",&L[i].K);
}
void Discretize()
{
	vector<LL>v;
	for(int i=0;i<N;i++)v.push_back(L[i].X);
	sort(v.begin(),v.end()),v.resize(unique(v.begin(),v.end())-v.begin());
	for(int i=0;i<N;i++)L[i].X=lower_bound(v.begin(),v.end(),L[i].X)-v.begin();
	v.clear();
	for(int i=0;i<N;i++)v.push_back(L[i].Y);
	sort(v.begin(),v.end()),v.resize(unique(v.begin(),v.end())-v.begin());
	for(int i=0;i<N;i++)L[i].Y=lower_bound(v.begin(),v.end(),L[i].Y)-v.begin();
}
vector<int>ET[200000];
bool CmpX(const Lamp &a,const Lamp &b){return a.X>b.X;}
void Update(map<LL,int>&ld,const int u)
{
	map<LL,int>::iterator it=ld.upper_bound(L[u].Y);
	if(it!=ld.begin())
	{
		--it;
		if(L[it->second].X<=L[u].X)return;
		if(L[it->second].Y==L[u].Y)ld.erase(it++);
		else ++it;
	}
	while(it!=ld.end()&&L[it->second].X>=L[u].X)ld.erase(it++);
	ld[L[u].Y]=u;
}
void BuildET()
{
	sort(L,L+N,CmpX);
	map<LL,int>ld;
	for(int u=0;u<N;u++)
	{
		ET[u].clear();
		for(map<LL,int>::const_reverse_iterator it=ld.rbegin();it!=ld.rend()&&it->first>=L[u].Y;it++)ET[u].push_back(it->second);
		Update(ld,u);
	}
}
int REMAIN[200000],TAG[200000],MN[200000];
#include<queue>
void InitializeTree()
{
	int *degree=new int[N];
	for(int i=0;i<N;i++)degree[i]=(int)ET[i].size();
	for(int i=0;i)
	delete[]degree;
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		ReadInput();
		Discretize();
		BuildET();
		InitializeTree();
	}
	return 0;
}
