#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
const int INF=2147483647;
struct Deq
{
	int S[1000000],L,R;
	void Clear(){L=0,R=-1;}
	void PushBack(const int v){S[++R]=v;}
	void PopBack(){--R;}
	void PopFront(){++L;}
	int Back()const{return S[R];}
	int Front()const{return S[L];}
	bool Empty()const{return R<L;}
}DEQ;
void getmin(int &a,const int b){if(b<a)a=b;}
int DP[1000000];
int N,M,K,H[1000000];
bool IsBetter(const int a,const int b)
{
	if(DP[a]!=DP[b])return DP[a]<DP[b];
	return H[a]>H[b];
}
void Discretize()
{
	vector<int>v;
	for(int i=0;i<N;i++)v.push_back(H[i]);
	sort(v.begin(),v.end()),v.resize(M=(int)(unique(v.begin(),v.end())-v.begin()));
	for(int i=0;i<N;i++)H[i]=(int)(lower_bound(v.begin(),v.end(),H[i])-v.begin());
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d",&H[i]);
		Discretize();
		int querycount;scanf("%d",&querycount);
		while(querycount--)
		{
			scanf("%d",&K);
			DP[0]=0;
			DEQ.Clear();
			DEQ.PushBack(0);
			for(int i=1;i<N;i++)
			{
				while(!DEQ.Empty()&&DEQ.Front()<i-K)DEQ.PopFront();
				DP[i]=DP[DEQ.Front()]+(H[i]>=H[DEQ.Front()]?1:0);
				while(!DEQ.Empty()&&IsBetter(i,DEQ.Back()))DEQ.PopBack();
				DEQ.PushBack(i);
			}
			printf("%d\n",DP[N-1]);
		}
	}
	return 0;
}
