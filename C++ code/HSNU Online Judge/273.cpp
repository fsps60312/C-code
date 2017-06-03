#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<map>
#include<set>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
typedef long long LL;
const int INF=2147483647;
const LL MOD=1000000000LL;
void getmin(int &a,const int b){if(b<a)a=b;}
struct Tree
{
	map<int,int>LAYER[100001];
	vector<set<int> >ET;
	int CNT[100000],N;
	void AddEdge(const int u,const map<int,int>&s,const int key)
	{
		const auto it=s.find(key);
		if(it==s.end())return;
		ET[u].insert(it->second);
		assert((it->second)<u);
		ET[it->second].insert(u);
	}
	void BuildTree(const int check_sum)
	{
		N=0,ET.clear();
		int sum=0;
		for(int i=0;!LAYER[i].empty();i++)
		{
			static vector<int>layer;layer.clear();
			for(const auto &it:LAYER[i])layer.push_back(it.first);
			int cur=0;
			for(auto it=LAYER[i].begin();cur<(int)layer.size();)
			{
				int &cnt=CNT[N]=1;
				ET.push_back(set<int>());
				if(i)AddEdge(N,LAYER[i-1],layer[cur]);
				it->second=N;
				while(cur+1<(int)layer.size()&&layer[cur]+1==layer[cur+1])
				{
					cur++,it++,cnt++;
					it->second=N;
					if(i)AddEdge(N,LAYER[i-1],layer[cur]);
				}
				N++,cur++,it++;
				sum+=cnt;
			}
		}
		assert(sum==check_sum);
	}
	LL ANS;
	vector<LL>SZ,PATH;
	void Dfs(const int u,const int fa)
	{
		SZ[u]=CNT[u],PATH[u]=0LL;
		vector<LL>chsz,chpath;
		for(const int nxt:ET[u])if(nxt!=fa)
		{
			Dfs(nxt,u);
			chsz.push_back(SZ[nxt]),chpath.push_back(PATH[nxt]);
			SZ[u]+=SZ[nxt],PATH[u]+=PATH[nxt];
			(ANS+=(LL)CNT[u]*PATH[nxt])%=MOD;//from u to ch nodes
		}
		LL szsum=0LL,pathsum=0LL; 
		for(int i=1;i<(int)chsz.size();i++)(ANS+=chpath[i]*(szsum+=chsz[i-1])+chsz[i]*(pathsum+=chpath[i-1]))%=MOD;
		PATH[u]+=SZ[u];
	}
	void Solve()
	{
//		for(int i=0;i<N;i++)
//		{
//			printf("node %d, cnt=%d:",i,CNT[i]);
//			for(auto nxt:ET[i])printf(" %d",nxt);puts("");
//		}
		ANS=0LL;
		SZ.resize(N),PATH.resize(N);
		Dfs(0,-1);
		if(ANS<0LL)ANS+=MOD;
		assert(ANS>=0LL&&ANS<MOD);
	}
}RT,CT;
int N;
void ReadInput()
{
	static vector<int>x,y;
	for(int i=0,a,b;i<N;i++)scanf(2,"%d%d",&a,&b),x.push_back(a),y.push_back(b);
	int mn=INF;
	for(const auto v:x)getmin(mn,v);
	for(auto &v:x)v-=mn;
	mn=INF;
	for(const auto v:y)getmin(mn,v);
	for(auto &v:y)v-=mn;
	for(int i=0;i<=N;i++)RT.LAYER[i].clear(),CT.LAYER[i].clear();
	for(int i=0;i<N;i++)RT.LAYER[y[i]][x[i]]=CT.LAYER[x[i]][y[i]]=-1;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf(1,"%d",&N);
	ReadInput();
	RT.BuildTree(N),CT.BuildTree(N);
//	puts("pass");
	RT.Solve(),CT.Solve();
//	printf("%lld %lld\n",RT.ANS,CT.ANS);
	printf("%lld\n",(RT.ANS+CT.ANS)%MOD);
}
