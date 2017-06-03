#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct Operation
{
	int a,b;
	Operation(){}
	Operation(const int _a,const int _b):a(_a),b(_b){}
};
int N,M,S[200000],CUR;
Operation OPE[600000];
vector<Operation>ANS;
bool Solve(const int tick)
{
	static int val[200000],loc[200000];
	for(int i=0;i<N;i++)val[i]=S[i];
	for(int i=0;i<tick;i++)swap(val[OPE[i].a],val[OPE[i].b]);
	for(int i=0;i<N;i++)loc[val[i]]=i;
	vector<Operation>ans;
	for(int i=0;i<N;i++)if(val[i]!=i)
	{
		const int want=loc[i];
		ans.push_back(Operation(val[i],val[want]));
		swap(loc[val[i]],loc[val[want]]);
		swap(val[i],val[want]);
	}
	for(int i=0;i<N;i++)assert(val[i]==i);
	if((int)ans.size()>tick)return false;
	while((int)ans.size()<tick)ans.push_back(Operation(0,0));
	ANS.clear();
	for(int i=0;i<N;i++)val[i]=S[i],loc[val[i]]=i;
	for(int i=0;i<tick;i++)
	{
		swap(loc[val[OPE[i].a]],loc[val[OPE[i].b]]);
		swap(val[OPE[i].a],val[OPE[i].b]);
		ANS.push_back(Operation(loc[ans[i].a],loc[ans[i].b]));
		swap(val[loc[ans[i].a]],val[loc[ans[i].b]]);
		swap(loc[ans[i].a],loc[ans[i].b]);
	}
	for(int i=0;i<N;i++)assert(val[i]==i);
	return true;
}
int main()
{
//	freopen("in.txt","r",stdin);
	int testcount;scanf("%d",&testcount);
	while(testcount--)
	{
		scanf("%d",&N);
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		scanf("%d",&M);
		for(int i=0;i<M;i++)scanf("%d%d",&OPE[i].a,&OPE[i].b);
		int l=0,r=M;
		while(l<r)
		{
			const int mid=(l+r)/2;
			if(Solve(mid))r=mid;
			else l=mid+1;
		}
		assert(r<M);
		Solve(r);
		printf("%d\n",(int)ANS.size());
		for(const Operation &o:ANS)printf("%d %d\n",o.a,o.b);
	}
	return 0;
}
