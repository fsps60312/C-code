#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
template<class T>void getmax(T &a,const T &b){if(a<b)a=b;}
typedef long long LL;
struct Edge
{
	int a,b;
	Edge(){}
	Edge(const int _a,const int _b):a(_a),b(_b){}
};
struct Info
{
	int sz,depth;
	LL sum;
	Info(){}
	Info(const int _sz,const int _depth,const LL _sum):sz(_sz),depth(_depth),sum(_sum){}
};
bool operator<(const Info &a,const Info &b){return a.sz>b.sz;}
int N;
vector<Edge>EDGE;
vector<int>ET[1000000];
Info DP[1999998];
Info GetInfo(const int id)
{
	Info &ans=DP[id];
	if(ans.sz!=-1)return ans;
	const int u=(id&1?EDGE[id>>1].b:EDGE[id>>1].a);
	ans=Info(1,0,0LL);
	for(int i=0;i<(int)ET[u].size();i++)if(ET[u][i]!=(id>>1))
	{
		const int ei=ET[u][i];
		const int nxtid=ei*2+(u==EDGE[ei].a);
		const Info &ch_ans=GetInfo(nxtid);
		ans.sz+=ch_ans.sz;
		getmax(ans.depth,ch_ans.depth+1);
		ans.sum+=ch_ans.sum+ch_ans.sz;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		EDGE.clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),--a,--b;
			EDGE.push_back(Edge(a,b));
			ET[a].push_back(i),ET[b].push_back(i);
		}
		for(int i=0;i<(N-1)*2;i++)DP[i].sz=-1;
		if(N==1)puts("0");
		else
		{
			for(int u=0;u<N;u++)
			{
				vector<Info>infos;
				for(int i=0;i<(int)ET[u].size();i++)
				{
					const int ei=ET[u][i];
					const int id=ei*2+(u==EDGE[ei].a);
					infos.push_back(GetInfo(id));
				}
				sort(infos.begin(),infos.end());
				int sz_sum=0;
				for(int i=1;i<(int)infos.size();i++)sz_sum+=infos[i].sz;
				assert(sz_sum+infos[0].sz==N-1);
				LL ans;
				if(infos[0].sz>sz_sum+1)ans=-1;
				else
				{
					LL path_sum=0LL;
					for(int i=0;i<(int)infos.size();i++)path_sum+=infos[i].sum+infos[i].sz;
					if(infos[0].sz==sz_sum+1)ans=path_sum*2LL-(infos[0].depth+1);
					else
					{
						int depth_max=0;
						for(int i=0;i<(int)infos.size();i++)getmax(depth_max,infos[i].depth+1);
						ans=path_sum*2LL-depth_max;
					}
				}
				printf("%lld\n",ans);
			}
		}
	}
	return 0;
}
