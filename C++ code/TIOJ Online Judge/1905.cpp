#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const unsigned int INF=4294967295U;
struct QueryType
{
	int ID,L,R;
	QueryType(){}
	QueryType(const int _ID,const int _L,const int _R):ID(_ID),L(_L),R(_R){}
};
bool CmpL(const QueryType &a,const int QueryType &b){return a.L<b.L;}
bool CmpR(const QueryType &a,const int QueryType &b){return a.R<b.R;}
int N,Q;
unsigned int S[100000],ANS[100000];
vector<QueryType>QUERY;
void Solve(const vector<int>queries,)
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%u",&S[i]);
	scanf("%d",&Q);
	QUERY.clear();
	for(int i=0,l,r;i<Q;i++)
	{
		scanf("%d%d",&l,&r),--l,--r;
		QUERY.push_back(QueryType(i,l,r));
		ANS[i]=INF;
	}
	sort(QUERY.begin(),QUERY.end(),CmpL);
	return 0;
}
