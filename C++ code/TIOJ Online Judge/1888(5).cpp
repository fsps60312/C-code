#include<cstdio>
#include<cassert>
#include<vector>
#include<utility> 
using namespace std;
struct Operation
{
	int a,b;
	Operation(){}
	Operation(const int _a,const int _b):a(_a),b(_b){}
};
int N,M;
int S[200000];
Operation OPE[600000];
int CUR;
void Move(const int goal)
{
	for(;CUR<goal;CUR++)swap(S[OPE[CUR].a],S[OPE[CUR].b]);
	for(;CUR>goal;CUR--)swap(S[OPE[CUR-1].a],S[OPE[CUR-1].b]);
}
vector<Operation>GetSwaps(const int goal)
{
	Move(goal);
	static int loc[200000];
	for(int i=0;i<N;i++)loc[S[i]]=i;
	vector<Operation>ans,history;
	for(int i=0;i<N;i++)if(S[i]!=i)
	{
		const int want=loc[i];
		history.push_back(Operation(i,want));
		ans.push_back(Operation(S[i],S[want]));
		swap(loc[S[i]],loc[S[want]]);
		swap(S[i],S[want]);
	}
	for(int i=0;i<N;i++)assert(loc[S[i]]==i);
	for(auto o=history.rbegin();o!=history.rend();o++)swap(S[o->a],S[o->b]);
	return ans;
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
		CUR=0;
		int l=0,r=min(N-1,M);
		while(l<r)
		{
			const int mid=(l+r)/2;
			const vector<Operation>&ans=GetSwaps(mid);
			if((int)ans.size()<=mid)r=mid;
			else l=mid+1;
		}
		vector<Operation>ans=GetSwaps(r);
		if((int)ans.size()<r)ans.push_back(Operation(0,0));
		assert((int)ans.size()==r);
		printf("%d\n",r);
		Move(0);
		static int loc[200000];
		for(int i=0;i<N;i++)loc[S[i]]=i;
		for(Operation *o=OPE;o<OPE+r;o++)
		{
			const int i=o-OPE;
			swap(loc[S[o->a]],loc[S[o->b]]);
			swap(S[o->a],S[o->b]);
			const int a=loc[ans[i].a],b=loc[ans[i].b];
			printf("%d %d\n",a,b);
			swap(loc[S[a]],loc[S[b]]);
			swap(S[a],S[b]);
		}
		for(int i=0;i<N;i++)assert(loc[S[i]]==i);
	}
	return 0;
}
