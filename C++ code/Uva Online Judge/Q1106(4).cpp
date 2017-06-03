#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
void getmax(LL &a,const LL &b){if(b>a)a=b;}
struct Machine
{
	LL day,price,resell,profit;
	Machine(){}
	Machine(const LL &_day,const LL &_price,const LL &_resell,const LL &_profit):day(_day),price(_price),resell(_resell),profit(_profit){}
};
struct Deq
{
	int s[100002],l,r;
	void clear(){l=0,r=-1;}
	void push_back(const int v){s[++r]=v;}
	void pop_back(){r--;}
//	void pop_front(){l++;}//這個不會用到 
	int size(){return r-l+1;}
	int operator[](const int i)const{return s[l+i];}
	int back(const int i){return s[r-i];}
}DEQ;
vector<Machine>MACHINE;
LL DP[100002];
LL GetA(const int i){return MACHINE[i].profit;}
LL GetB(const int i)
{
	const Machine &m=MACHINE[i];
	return DP[i]+(m.resell-m.price)-m.profit*m.day;
}
double GetX(const int i1,const int i2){assert(GetA(i1)!=GetA(i2));return (double)(GetB(i1)-GetB(i2))/(GetA(i2)-GetA(i1));}
int N,D;
void Query(const vector<int>&machines)
{
	if((int)machines.size()==1)return;
	assert(!machines.empty());
	const int half=(int)machines.size()/2;
	vector<int>left_machines,right_machines;
	for(int i=0;i<(int)machines.size();i++)(i<half?left_machines:right_machines).push_back(machines[i]);
	Query(left_machines);
	sort(left_machines.begin(),left_machines.end(),[](const int a,const int b)->bool{return GetA(a)<GetA(b);});
	DEQ.clear();
	const auto &lm=left_machines;
	for(int i=0;i<(int)lm.size();i++)
	{
		if(DP[lm[i]]<MACHINE[lm[i]].price)continue;//買不起這台機器 
		if(DEQ.size()&&GetA(DEQ.back(0))==GetA(lm[i]))//注意斜率相同的情況 
		{
			if(GetB(DEQ.back(0))<=GetB(lm[i]))DEQ.pop_back();
			else continue;
		}
		while(DEQ.size()>=2&&GetX(DEQ.back(0),lm[i])<=GetX(DEQ.back(1),DEQ.back(0)))DEQ.pop_back();
		DEQ.push_back(lm[i]);
	}
	if(DEQ.size())
	{
		for(int i=2;i<DEQ.size();i++)assert(GetX(DEQ[i-2],DEQ[i-1])<=GetX(DEQ[i-1],DEQ[i]));
		const auto &rm=right_machines;
		for(int i=0,j=0;j<(int)rm.size();i++)
		{
			for(;j<(int)rm.size()&&(i+1==DEQ.size()||GetX(DEQ[i],DEQ[i+1])>=MACHINE[rm[j]].day-1LL);j++)
				getmax(DP[rm[j]],GetA(DEQ[i])*(MACHINE[rm[j]].day-1LL)+GetB(DEQ[i]));
		}
	}
	Query(right_machines);
}
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	while(scanf("%d%lld%d",&N,&DP[0],&D)==3)
	{
		if(N==0&&DP[0]==0LL&&D==0)break;
		MACHINE.clear(),MACHINE.push_back(Machine(0LL,0LL,0LL,0LL));
		for(int i=1,d,p,r,g;i<=N;i++)assert(scanf("%d%d%d%d",&d,&p,&r,&g)==4),MACHINE.push_back(Machine(d,p,r,g));
		for(int i=1;i<=N+1;i++)DP[i]=DP[0];
		MACHINE.push_back(Machine(D+1LL,0LL,0LL,0LL));
		sort(MACHINE.begin(),MACHINE.end(),[](const Machine &a,const Machine &b)->bool{return a.day<b.day;});
		assert(MACHINE[0].day==0LL);assert(MACHINE[N+1].day==D+1LL);
		assert((int)MACHINE.size()==N+2);
		vector<int>machines;
		for(int i=0;i<=N+1;i++)machines.push_back(i);
		Query(machines);
		static int kase=1;
		printf("Case %d: %lld\n",kase++,DP[N+1]);
	}
	return 0;
}
