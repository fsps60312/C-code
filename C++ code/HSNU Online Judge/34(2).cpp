#include<cstdio>
#include<cassert>
#include<map>
#include<vector>
using namespace std;
int N;
bool VIS[250000];
struct Dj
{
	int s[250000],h[250000];
	void clear(){for(int i=0;i<N;i++)s[i]=i;}
	int Find(const int a){return s[a]==a?a:(s[a]=Find(s[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;s[a]=b;return true;}
	int &H(const int i){return h[Find(i)];}
}DJ;
int main()
{
	scanf("%d",&N);
	map<int,vector<int>,greater<int> >sot;
	for(int i=0,w,h;i<N;i++)VIS[i]=false,scanf("%d%d",&w,&h),sot[h].push_back(i);
	DJ.clear();
	int ans=0;
	for(const auto &it:sot)
	{
		for(const int loc:it.second)
		{
			VIS[loc]=true,DJ.H(loc)=it.first;
			if(loc&&VIS[loc-1])
			{
				if(DJ.H(loc-1)!=it.first)ans++;
				DJ.Merge(loc-1,loc);
			}
			if(loc+1<N&&VIS[loc+1])
			{
				if(DJ.H(loc+1)!=it.first)ans++;
				DJ.Merge(loc+1,loc);
			}
		}
	}
	printf("%d\n",++ans);
	return 0;
}
