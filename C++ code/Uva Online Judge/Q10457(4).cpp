#include<cstdio>
#include<algorithm>
#include<cassert>
#include<vector>
#define termin(x,...) {printf(x,##__VA_ARGS__);assert(0);}
using namespace std;
void getmin(int &a,int b){if(b<a)a=b;}
const int INF=2147483645;
int N,M;
struct Road
{
	int j1,j2,v,idx;
	Road(){}
	Road(int j1,int j2,int v,int idx):j1(j1),j2(j2),v(v),idx(idx){}
	bool operator<(const Road &a)const{if(v!=a.v)return v<a.v;return idx<a.idx;}
};
vector<Road>RD;
int find(int a,int *s){return s[a]==a?a:(s[a]=find(s[a],s));}
int Cost(int a,int b)
{
	static int DJ[200];
	int ans=INF;
	for(int l=0;l<M;l++)
	{
		for(int i=0;i<N;i++)DJ[i]=i;
		for(int r=l;r<M;r++)
		{
			DJ[find(RD[r].j1,DJ)]=find(RD[r].j2,DJ);
			if(find(a,DJ)==find(b,DJ)){getmin(ans,RD[r].v-RD[l].v);break;}
		}
	}
	if(ans<0)termin("negative ans\n");
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		RD.clear();
		for(int i=0,a,b,v;i<M;i++)
		{
			scanf("%d%d%d",&a,&b,&v);
			a--,b--;
			RD.push_back(Road(a,b,v,i));
		}
		sort(RD.begin(),RD.end());
		int begin,end;
		scanf("%d%d",&begin,&end);
		static int T;
		scanf("%d",&T);
		while(T--)
		{
			static int a,b;
			scanf("%d%d",&a,&b);
			a--,b--;
			printf("%d\n",begin+Cost(a,b)+end);
		}
	}
	return 0;
}
