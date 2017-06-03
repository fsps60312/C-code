#include<cstdio>
#include<cassert>
#include<queue>
#define scanf(x,...) assert(scanf(__VA_ARGS__)==x)
using namespace std;
typedef long long LL;
void getmax(LL &a,const LL b){if(b>a)a=b;}
int L,N,M;
LL D,W[100000];
struct Process
{
	LL time;
	int id;
	Process(){}
	Process(const LL _t,const int _i):time(_t),id(_i){}
	bool operator<(const Process &p)const{return time+W[id]>p.time+W[p.id];}
};
int main()
{
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	int testcase;scanf(1,"%d",&testcase);
	while(testcase--)
	{
		scanf(4,"%d%d%d%lld",&L,&N,&M,&D);
		for(int i=0;i<N;i++)scanf(1,"%lld",&W[i]);
		priority_queue<Process>washer;
		queue<LL>dryer;
		for(int i=0;i<N;i++)washer.push(Process(0LL,i));
		LL time=0LL;
		for(int i=0;i<L;i++)
		{
			const Process p=washer.top();washer.pop();
			washer.push(Process(p.time+W[p.id],p.id));
			getmax(time,p.time+W[p.id]);
			while(!dryer.empty()&&dryer.front()<=time)dryer.pop();
			while((int)dryer.size()>=M)
			{
				time=dryer.front();
				while(!dryer.empty()&&dryer.front()<=time)dryer.pop();
			}
			dryer.push(time+D);
		}
		LL ans=0LL;
		while(!dryer.empty())ans=dryer.front(),dryer.pop();
		static int kase=1;
		printf("Case #%d: %lld\n",kase++,ans);
	}
	scanf(-1,"%d",&testcase);
	return 0;
}
