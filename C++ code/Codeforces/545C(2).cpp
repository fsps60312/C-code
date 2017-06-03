#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
#include<set>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Tree
{
	int x,h;
}S[100000];
struct Seg
{
	int l,r;
	Seg(){}
	Seg(const int _l,const int _r):l(_l),r(_r){}
	bool operator<(const Seg &s)const{return r!=s.r?r<s.r:l<s.l;}
};
int N,DP[300001];
vector<int>X;
int Id(const int v){return lower_bound(X.begin(),X.end(),v)-X.begin();}
bool Contain(set<int>&s,const int l,const int r)
{
	return s.upper_bound(r)!=s.lower_bound(l);
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		X.clear();
		set<int>restrict;
		for(int i=0;i<N;i++)
		{
			int &x=S[i].x,&h=S[i].h;
			scanf("%d%d",&x,&h);
			X.push_back(x-h),X.push_back(x),X.push_back(x+h);
			restrict.insert(x);
		}
		X.push_back(-2147483647);
		sort(X.begin(),X.end()),X.resize(unique(X.begin(),X.end())-X.begin());
		vector<Seg>segs;
		for(int i=0;i<N;i++)
		{
			if(!Contain(restrict,S[i].x-S[i].h,S[i].x-1))segs.push_back(Seg(Id(S[i].x-S[i].h),Id(S[i].x)));
			if(!Contain(restrict,S[i].x+1,S[i].x+S[i].h))segs.push_back(Seg(Id(S[i].x),Id(S[i].x+S[i].h)));
		}
		sort(segs.begin(),segs.end());
		for(int i=0;i<(int)X.size();i++)DP[i]=0LL;
		int x=1;
		for(const Seg &s:segs)
		{
			for(;x<s.r;x++)getmax(DP[x],DP[x-1]);
			getmax(DP[s.r],DP[s.l-1]+1);
		}
		printf("%d\n",DP[x]);
	}
	return 0;
}
