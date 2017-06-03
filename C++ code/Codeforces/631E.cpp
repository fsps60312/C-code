#include<cstdio>
#include<cassert>
#include<algorithm>
using namespace std;
typedef long long LL;
void getmax(LL &a,const LL &b){if(b>a)a=b;}
struct Deq
{
	int DATA[200000],L,R;
	void Clear(){L=0,R=-1;}
	void PushBack(const int v){DATA[++R]=v;}
	void PopBack(){R--;}
	void PopFront(){L++;}
	int Front(const int i)const{return DATA[L+i];}
	int Back(const int i)const{return DATA[R-i];}
	int Size()const{return R-L+1;}
}DEQ;
int N;
LL A[200001],SUM[200001];
LL GetA(const int i){return A[i];}
LL GetB(const int i){return SUM[i]-A[i]*i;}
double GetX(const int i1,const int i2){return (double)(GetB(i1)-GetB(i2))/(GetA(i2)-GetA(i1));}
bool NeedPopBack(const int i)
{
	if(DEQ.Size()==0)return false;
	if(GetA(i)==GetA(DEQ.Back(0)))return GetB(i)>=GetB(DEQ.Back(0));
	if(DEQ.Size()==1)return false;
	return GetX(DEQ.Back(0),i)<=GetX(DEQ.Back(1),DEQ.Back(0));
}
void BuildConvexHull()
{
	vector<int>order;
	for(int i=1;i<=N;i++)order.push_back(i);
	sort(order.begin(),order.end(),[](const int a,const int b)->bool{return A[a]<A[b];});
	DEQ.Clear();
	for(const int i:order)
	{
		while(NeedPopBack(i))DEQ.PopBack();
		DEQ.PushBack(i);
	}
}
LL Solve()
{
	LL change=0LL;
	for(int i=0;i<=N;i++)
	{
		while(DEQ.Size()>=2&&GetX(DEQ.Front(0),DEQ.Front(1))<=i)DEQ.PopFront();
//		printf("i=%d,DEQ.Front()=%d,a=%I64d,b=%I64d\n",i,DEQ.Front(0),GetA(DEQ.Front(0)),GetB(DEQ.Front(0)));
		getmax(change,GetA(DEQ.Front(0))*i+GetB(DEQ.Front(0))-SUM[i]);
	}
	LL initial_cost=0LL;
	for(int i=1;i<=N;i++)initial_cost+=A[i]*i;
//	printf("initial_cost=%I64d,change=%I64d\n",initial_cost,change);
	return initial_cost+change;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		SUM[0]=0LL;
		for(int i=1;i<=N;i++)scanf("%I64d",&A[i]),SUM[i]=SUM[i-1]+A[i];
		BuildConvexHull();
		printf("%I64d\n",Solve());
	}
	return 0;
}
