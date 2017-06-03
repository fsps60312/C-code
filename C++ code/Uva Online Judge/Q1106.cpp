#include<cstdio>
#include<cassert>
#include<set>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;
typedef long long LL;
struct Machine
{
	LL day,price,resell,profit;
	Machine():day(),price(),resell(),profit(){}
	Machine(const LL &_day,const LL &_price,const LL &_resell,const LL &_profit):day(_day),price(_price),resell(_resell),profit(_profit){}
	bool operator<(const Machine &m)const{return day<m.day;}
};
vector<Machine>MACHINE;
int N,D;
LL DP[100001];
LL GetA(const int i){return MACHINE[i].profit;}
LL GetB(const int i)
{
	const Machine &m=MACHINE[i];
	return DP[i]-m.profit*m.day+(m.resell-m.price);
}
double GetX(const int i1,const int i2){return (double)(GetB(i1)-GetB(i2))/(GetA(i2)-GetA(i1));}
struct LineComparer{bool operator()(const int i1,const int i2){return GetA(i1)!=GetA(i2)?GetA(i1)<GetA(i2):i1<i2;}};
set<int,LineComparer>DEQ;
map<double,set<int,LineComparer>::iterator>LOC,SLOPE;
void Erase(set<int,LineComparer>::iterator itd)
{
	SLOPE.erase(GetA(*itd));
	if(true)
	{
		auto itdr=itd,itdl=itd;itdr++;
		if(itdl!=DEQ.begin())itdl--,LOC.erase(GetX(*itdl,*itd)),itdl++;
		if(itdr!=DEQ.end())LOC.erase(GetX(*itd,*itdr));
		if(itdl!=DEQ.begin()&&itdr!=DEQ.end())itdl--,LOC[GetX(*itdl,*itdr)]=itdl,itdl++;
	}
	DEQ.erase(itd);
}
void Insert(set<int,LineComparer>::iterator itd)
{
	assert(itd!=DEQ.end());
	SLOPE[GetA(*itd)]=itd;
	if(true)
	{
		auto itdl=itd,itdm=itd,itdr=itd;itdr++;
		if(itdr!=DEQ.end())
		{
			itdr++,itdm++;
			while(itdr!=DEQ.end()&&GetX(*itdl,*itdm)>=GetX(*itdm,*itdr))
			{
				auto tmp=itdm;itdm++,itdr++;
				Erase(tmp);
			}
			LOC[GetX(*itdl,*itdm)]=itdl;
		}
	}
	if(true)
	{
		auto itdl=itd,itdm=itd,itdr=itd;
		if(itdl!=DEQ.begin())
		{
			itdl--,itdm--;
			for(;;)
			{
				if(itdl==DEQ.begin())break;
				itdl--;
				if(GetX(*itdl,*itdm)<GetX(*itdm,*itdr))break;
				auto tmp=itdm;itdm--;
				Erase(tmp);
			}
			LOC[GetX(*itdm,*itdr)]=itdm;
		}
	}
}
void Insert(const int i)
{
	auto its=SLOPE.lower_bound(GetA(i));
	if(its==SLOPE.end())
	{
		DEQ.insert(i);
		Insert(DEQ.find(i));
	}
	else if(GetA(*(its->second))==GetA(i))
	{
		if(GetB(i)>GetB(*(its->second)))
		{
			Erase(its->second);
			DEQ.insert(i);
			Insert(DEQ.find(i));
		}
	}
	else
	{
		auto itd=its->second;
		assert(itd!=DEQ.begin());
		auto itdl=itd;itdl--;
		if(GetA(i)*GetX(*itdl,*itd)+GetB(i)>GetA(*itdl)*GetX(*itdl,*itd)+GetB(*itdl))
		{
			DEQ.insert(i);
			Insert(DEQ.find(i));
		}
	}
	printf("(%d,%d,%d)\n",(int)DEQ.size(),(int)LOC.size(),(int)SLOPE.size());
	assert(DEQ.size()==LOC.size()+1&&DEQ.size()==SLOPE.size());
}
LL Query(const LL &x)
{
	auto itl=LOC.lower_bound(x);
	if(itl==LOC.end())
	{
		auto itd=DEQ.end();itd--;
		return GetA(*itd)*x+GetB(*itd);
	}
	auto itd=itl->second;
	return GetA(*itd)*x+GetB(*itd);
}
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d%lld%d",&N,&DP[0],&D)==3)
	{
		if(N==0&&DP[0]==0LL&&D==0)break;
		MACHINE.clear();
		MACHINE.push_back(Machine(0LL,0LL,0LL,0LL));
		for(int i=1,d,p,r,g;i<=N;i++)scanf("%d%d%d%d",&d,&p,&r,&g),MACHINE.push_back(Machine(d,p,r,g));
		sort(MACHINE.begin(),MACHINE.end());
		DEQ.clear(),LOC.clear();
		Insert(0);
		for(int i=1;i<=N;i++)
		{
			const Machine &m=MACHINE[i];
			DP[i]=Query(m.day-1LL);
			Insert(i);
		}
		static int kase=1;
		printf("Case %d: %lld\n",kase++,DP[N]);
	}
	return 0;
}
