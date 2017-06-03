#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<utility>
#include<cmath>
using namespace std;
template<class T>inline void getmax(T&a,const T&b){if(a<b)a=b;}
int W,H,N;
vector<pair<int,int> >S[200000];
int QueryOffset(const long long d,const long long r)
{
//	a*a+d*d<=r*r
	long long a=(long long)sqrt(r*r-d*d);
	while((a+1)*(a+1)+d*d<=r*r)++a;
	while(a*a+d*d>r*r)--a;
	return (int)a;
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("circles.in","r",stdin);
	freopen("circles.out","w",stdout);
	while(scanf("%d%d%d",&W,&H,&N)==3)
	{
		for(int i=0;i<H;i++)S[i].clear();
		for(int i=0,x,y,r;i<N;i++)
		{
			scanf("%d%d%d",&x,&y,&r);
			for(int j=max(0,y-r);j<=min(H-1,y+r);j++)S[j].push_back(make_pair(max(0,x-QueryOffset(abs(y-j),r)),min(W-1,x+QueryOffset(abs(y-j),r))));
		}
		long long ans=(long long)W*H;
		for(int i=0;i<H;i++)if(!S[i].empty())
		{
			auto &s=S[i];
			sort(s.begin(),s.end());
			pair<int,int>now=s[0];
			for(const auto &p:s)
			{
				if(p.first<=now.second+1)getmax(now.second,p.second);
				else ans-=now.second-now.first+1,now=p;
			}
			ans-=now.second-now.first+1;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
