#include<cstdio>
#include<vector>
#include<cassert>
#include<map>
#include<queue>
using namespace std;
typedef long long LL;
void getmax(LL &a,const LL b){if(b>a)a=b;}
int N,ET[1000000],IN[1000000];
LL L[1000000];
bool VIS[1000000];
struct Deq
{
	int s[2000000],l,r;
	void clear(){l=0,r=-1;}
	void push_back(const int v){s[++r]=v;}
	void pop_back(){r--;}
	void pop_front(){l++;}
	int back(){return s[r];}
	int front(){assert(!empty());return s[l];}
	bool empty(){return r<l;}
}DEQ;
LL DIST[1000000];
LL Solve(const vector<int>&elements)
{
	LL ans=0LL;
	queue<int>q;
	for(int i=0;i<elements.size();i++)
	{
		const int u=elements[i];
		DIST[u]=0LL;
		if(IN[u]==0)q.push(u);
	}
	while(!q.empty())
	{
		const int u=q.front();q.pop();
//		printf("u=%d\n",u+1);
		VIS[u]=true;
		getmax(ans,DIST[u]+L[u]+DIST[ET[u]]);
		getmax(DIST[ET[u]],DIST[u]+L[u]);
		if(!--IN[ET[u]])q.push(ET[u]);
	}
	int source=-1;
	for(int i=0;i<elements.size();i++)if(!VIS[elements[i]]){source=elements[i];break;}
	assert(source!=-1&&IN[source]>0);
	vector<LL>h,gap;
	h.push_back(DIST[source]);
	gap.push_back(0LL),gap.push_back(L[source]);
	for(int i=ET[source];i!=source;i=ET[i])h.push_back(DIST[i]),gap.push_back(L[i]);
	int len=h.size();
	for(int i=0;i<len;i++)h.push_back(h[i]),gap.push_back(gap[i+1]);
	for(int i=1;i<gap.size();i++)gap[i]+=gap[i-1];
	DEQ.clear();DEQ.push_back(0);
	for(int i=1;i<h.size();i++)
	{
		while(i-DEQ.front()>=len)DEQ.pop_front();
		getmax(ans,h[i]+gap[i]-gap[DEQ.front()]+h[DEQ.front()]);
		while(!DEQ.empty()&&h[i]>=h[DEQ.back()]+gap[i]-gap[DEQ.back()])DEQ.pop_back();
		DEQ.push_back(i);
	}
	return ans;
}
vector<int>SUB[1000000];
int DJ[1000000];
int FindDJ(const int a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
void BuildSUB()
{
	map<int,int>idx;
	for(int i=0;i<N;i++)
	{
		map<int,int>::iterator it=idx.find(FindDJ(i));
		if(it==idx.end())
		{
			int sz=idx.size();
			SUB[sz].clear();
			SUB[sz].push_back(i);
			idx[FindDJ(i)]=sz;
		}
		else SUB[it->second].push_back(i);
	}
	N=idx.size();
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)DJ[i]=i,IN[i]=0,VIS[i]=false;
	for(int i=0;i<N;i++)
	{
		scanf("%d%lld",&ET[i],&L[i]);
		ET[i]--;
		IN[ET[i]]++;
		DJ[FindDJ(i)]=FindDJ(ET[i]);
	}
	BuildSUB();
	LL ans=0LL;
	for(int i=0;i<N;i++)ans+=Solve(SUB[i]);
	printf("%lld\n",ans);
	return 0;
}
