#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
#define termin(x,...) {printf(x,##__VA_ARGS__);assert(0);}
using namespace std;
void getmin(int &a,int b){if(b<a)a=b;}
const int INF=2147483645;
int N,M,VIS[1000];
struct Road
{
	int j1,j2,v,inuse,idx;
	Road(){}
	Road(int j1,int j2,int v,int idx):j1(j1),j2(j2),v(v),inuse(0),idx(idx){}
	bool operator<(const Road &a)const{if(v!=a.v)return v<a.v;return idx<a.idx;}
};
vector<Road>RD;
vector<int>TO[200];
void BuildTO()
{
	for(int i=0;i<N;i++)TO[i].clear();
	for(int i=0;i<RD.size();i++)
	{
		Road &rd=RD[i];
		TO[rd.j1].push_back(i);
		TO[rd.j2].push_back(i);
	}
}
int CNT;
int Dfs(int u,int t,int mn,int mx)
{
	if(u==t)return mx-mn;
	for(int i=0;i<TO[u].size();i++)
	{
		int &j=TO[u][i];
		if(!RD[j].inuse||VIS[j]==CNT)continue;
		VIS[j]=CNT;
		Road &rd=RD[j];
		static int tmp;
		if((tmp=Dfs(rd.j1==u?rd.j2:rd.j1,t,min(mn,rd.v),max(mx,rd.v)))!=-1)
		{
			return tmp;
		}
	}
	return -1;
}
int Connected(int a,int b)
{
	CNT++;
	return Dfs(a,b,INF,-INF);
}
int Cost(int a,int b)
{
	int l=0,r=0,tmp,ans=INF;
	for(;;)
	{
		while(r<M&&(tmp=Connected(a,b))==-1)RD[r++].inuse=1;
		while((tmp=Connected(a,b))!=-1){getmin(ans,tmp);RD[l++].inuse=0;}
		if(r==M)break;
	}
	while(l<M)RD[l++].inuse=0;
	if(ans<0)termin("negative ans\n");
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(int i=0;i<1000;i++)VIS[i]=0;
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
		BuildTO();
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
