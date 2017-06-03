#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>
#include<set>
#include<cassert>
using namespace std;
int N,DP[200000];
struct Company
{
	int d1,d2,idx,rank,pri;
	Company(){}
	Company(const int &d1,const int &d2,const int &idx):d1(d1),d2(d2),idx(idx){}
};
struct Cmpidx{bool operator()(const Company &a,const Company &b)const{return a.idx>b.idx;}};
struct Cmprank{bool operator()(const Company &a,const Company &b)const{return a.rank>b.rank;}};
bool cmpd2(const Company &a,const Company &b){return a.d2<b.d2;}
bool cmpidx(const Company &a,const Company &b){return a.idx<b.idx;}
vector<Company>COMPANY;
priority_queue<Company,vector<Company>,Cmpidx>PQ;
set<Company,Cmprank>S;
vector<Company>ANS;
bool Insertable(const Company &c)
{
	if(S.find(c)!=S.end())return false;
	auto it=S.upper_bound(c);
	if(it==S.begin())return true;
	it--;
	return it->pri<c.pri;
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	COMPANY.clear();
	for(int i=1;i<=N;i++)
	{
		static int d1,d2;
		scanf("%d%d",&d1,&d2);
		COMPANY.push_back(Company(d1,d2,i));
	}
	sort(COMPANY.begin(),COMPANY.end(),cmpd2);
	int len=0;
	for(int i=0;i<N;i++)
	{
		Company &c=COMPANY[i];
		c.pri=i;
		int l=0,r=len,mid;
		while(l<r)
		{
			mid=(l+r+1)/2;
			if(c.d1>DP[mid-1])l=mid;
			else r=mid-1;
		}
//		printf("(%d,%d)%d %d\n",c.d1,c.d2,l,len);
//		for(int i=0;i<len;i++)printf(" %d",DP[i]);puts("");
		c.rank=l;
		if(l==len)DP[l]=c.d2,len++;
	}
//	for(int i=0;i<N;i++){Company &c=COMPANY[i];printf("(%d,%d)%d\n",c.d1,c.d2,c.rank);}
	for(int i=N-1,l=len-1;i>=0;i--)
	{
		Company &c=COMPANY[i];
		if(c.rank>=l)
		{
			PQ.push(c);
//			printf("(%d,%d)pri=%d,rank=%d,idx=%d\n",c.d1,c.d2,c.pri,c.rank,c.idx);
		}
		if(c.rank==l)l--;
	}
	S.clear();
	for(int i=0;i<len;i++)
	{
		Company c;
		do{c=PQ.top();PQ.pop();}while(!Insertable(c));
		S.insert(c);
	}
	printf("%d\n",len);
	ANS.clear();
	for(auto it=S.begin();it!=S.end();it++)ANS.push_back(*it);
	sort(ANS.begin(),ANS.end(),cmpidx);
	for(int i=0;i<ANS.size();i++)printf("%d ",ANS[i].idx);
	puts("");
	assert(ANS.size()==len);
	return 0;
}
