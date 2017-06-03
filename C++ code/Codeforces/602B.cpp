#include<cstdio>
#include<cassert>
#include<vector>
#include<utility>
using namespace std;
void getmax(int &a,const int b){if(a<b)a=b;}
int N;
vector<pair<int,int> >S;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		S.clear();
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			if(S.empty()||S.back().first!=v)S.push_back(make_pair(v,1));
			else ++S.back().second;
		}
		N=(int)S.size();
		int ans=S[0].second;
		pair<int,int>p=make_pair(S[0].second,S[0].second);
		for(int i=1;i<N;i++)
		{
			if(S[i-1].first+1==S[i].first)
			{
				p=make_pair(p.second+S[i].second,S[i].second);
				getmax(ans,p.first);
			}
			else
			{
				assert(S[i-1].first-1==S[i].first);
				p=make_pair(S[i].second,p.first+S[i].second);
				getmax(ans,p.second);
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
