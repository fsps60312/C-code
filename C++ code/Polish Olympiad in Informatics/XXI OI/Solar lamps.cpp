#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
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
int ANS[200000];
void Solve(const int l,const int r)
{
	if(l==r)return;
	const int mid=(l+r)/2;
	Solve(l,mid);
	vector<Lamp>left_lamps,rigt_lamps;
	for(int i=l;i<=r;i++)(i<=mid?left_lamps:rigt_lamps).push_back(L[i]);
	sort(left_lamps.begin(),left_lamps.end());
	sort(rigt_lamps.begin(),rigt_lamps.end());
	for(int i=0,j=0;j<(int)rigt_lamps.size();j++)
	{
		while(i<(int)left_lamps.size()&&)
	}
	Solve(mid+1,r);
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		ReadInput();
		Discretize();
		for(int i=0;i<N;i++)ANS[i]=i;
		Solve(0,N-1);
		for(int i=0;i<N;i++)
		{
			if(i)putchar(' ');
			printf("%d",ANS[i]);
		}
		puts("");
	}
	return 0;
}
