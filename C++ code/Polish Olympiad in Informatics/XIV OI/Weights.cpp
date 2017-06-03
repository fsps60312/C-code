#include<cstdio>
#include<cassert>
#include<algorithm>
#include<set>
#include<utility>
#include<functional>
using namespace std;
int N,M,A[100000],B[100000];
multiset<pair<int,int>,greater<pair<int,int> > >PQ,MX;
void Add(const int i,const int val)
{
//	printf("Add(%d)\n",val);
	multiset<pair<int,int>,greater<pair<int,int> > >::iterator it;
	it=PQ.find(make_pair(A[i],i));
	assert(it!=PQ.end());
	PQ.erase(it);
	assert(A[i]-val>=0);
	PQ.insert(make_pair(A[i]-=val,i));
	MX.insert(make_pair(val,i));
}
void Remove(const int i,const int val)
{
//	printf("Rem(%d)\n",val);
	multiset<pair<int,int>,greater<pair<int,int> > >::iterator it;
	it=MX.find(make_pair(val,i));
	assert(it!=MX.end());
	MX.erase(it);
	it=PQ.find(make_pair(A[i],i));
	assert(it!=PQ.end());
	PQ.erase(it);
	PQ.insert(make_pair(A[i]+=val,i));
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&A[i]);
		for(int i=0;i<M;i++)scanf("%d",&B[i]);
		PQ.clear(),MX.clear();
		for(int i=0;i<N;i++)PQ.insert(make_pair(A[i],i));
		sort(B,B+M,greater<int>());
		for(int i=0;i<M;i++)
		{
			if(B[i]>PQ.begin()->first)
			{
				if(MX.empty())continue;
				Remove(MX.begin()->second,MX.begin()->first);
			}
			Add(PQ.begin()->second,B[i]);
		}
		printf("%d\n",(int)MX.size());
	}
	return 0;
}
