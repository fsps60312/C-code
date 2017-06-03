#include<cstdio>
#include<set>
#include<cassert>
#include<vector>
using namespace std;
int N,S[1100000],H[1100000];
struct CmpS{bool operator()(const int a,const int b)const{return S[a]<S[b];}};
struct CmpH{bool operator()(const int a,const int b)const{return H[a]!=H[b]?H[a]<H[b]:a<b;}};
set<int,CmpS>GS;
set<int,CmpH>GH;
void TrimUp(const int v)
{
	vector<int>remove;
	for(auto it=GS.end();it!=GS.begin();)
	{
		it--;
		if(S[*it]<v)break;
		remove.push_back(*it);
	}
	for(const auto u:remove)GS.erase(u),GH.erase(u);
}
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++)scanf("%d",&S[i]);
	for(int i=0;i<N;i++)H[i]=S[i]-i;
	vector<int>vl,vr;
	for(int i=0;i<N;i++)
	{
		TrimUp(S[i]);
		auto it=GH.lower_bound(i);
//		printf("i=%d,h=%d:",i,H[i]);
//		for(auto it:GS)printf(" %d",it);puts("");
		if(it!=GH.begin()&&H[*(--it)]==H[i])
		{
			vl.push_back(*it);
			vr.push_back(i);
			TrimFront(*it);
		}
		GS.insert(i),GH.insert(i);
		assert(GS.size()==GH.size());
	}
	printf("%d\n",vl.size());
	for(int i=0;i<vl.size();i++)printf("%d %d\n",vl[i]+1,vr[i]+1);
	return 0;
}
