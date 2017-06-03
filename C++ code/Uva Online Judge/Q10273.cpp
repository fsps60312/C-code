#include<cstdio>
#include<vector>
#include<set>
#include<algorithm>
#include<cassert>
using namespace std;
int T,N;
vector<vector<int> >MILK;
struct Cow
{
	int idx,amount;
	Cow(){}
	Cow(const int _i,const int _a):idx(_i),amount(_a){}
	bool operator<(const Cow &c)const{return amount!=c.amount?amount<c.amount:idx<c.idx;}
};
vector<set<Cow> >CYC[11];
void Erase(set<Cow>&s,const Cow &c)
{
	assert(s.find(c)!=s.end());
	s.erase(c);
}
void Insert(set<Cow>&s,const Cow &c)
{
	assert(s.find(c)==s.end());
	s.insert(c);
}
bool EatCow(const int day)
{
	vector<Cow>tmp;
	for(int i=1;i<=10;i++)if(!CYC[i][day%i].empty())
	{
		auto it=CYC[i][day%i].begin();
		const Cow &cow=*it;
		tmp.push_back(cow);
		if(CYC[i][day%i].size()>=2&&(*(++it)).amount==cow.amount)tmp.push_back(*it);
	}
	sort(tmp.begin(),tmp.end());
	if(tmp.size()>=2&&tmp[0].amount==tmp[1].amount)return false;
	const Cow &cow=tmp[0];
	const auto &mk=MILK[cow.idx];
	for(int i=0;i<mk.size();i++)Erase(CYC[mk.size()][i],Cow(cow.idx,mk[i]));
//	printf("day %d eat cow %d\n",day,cow.idx);
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&N);
		MILK.clear();
		for(int i=0,t;i<N;i++)
		{
			scanf("%d",&t);
			vector<int>tmp;
			tmp.resize(t);
			for(int j=0;j<t;j++)scanf("%d",&tmp[j]);
			MILK.push_back(tmp);
		}
		for(int i=1;i<=10;i++)CYC[i].clear(),CYC[i].resize(i);
		for(int j=0;j<N;j++)
		{
			const auto &mk=MILK[j];
			for(int i=0;i<mk.size();i++)Insert(CYC[mk.size()][i],Cow(j,mk[i]));
		}
//		for(int i=1;i<=10;i++)
//		{
//			printf("cycle %d\n",i);
//			for(int j=0;j<i;j++)
//			{
//				putchar('{');
//				for(const auto &c:CYC[i][j])printf("(%d,%d)",c.idx,c.amount);
//				putchar('}');
//			}
//			puts("");
//		}
		int last=-1,remain=N;
		for(int day=0;day<=last+8*9*5*7;day++)if(EatCow(day))last=day,remain--;
		printf("%d %d\n",remain,last+1);
	}
	return 0;
}
