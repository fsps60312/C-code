#include<cstdio>
#include<cassert>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Deq
{
	int S[500000],L,R;
	void Clear(){L=0,R=-1;}
	void PushBack(const int v){S[++R]=v;}
	void PopBack(){--R;}
	void PopFront(){++L;}
	int Front()const{return S[L];}
	int Back()const{return S[R];}
	int Size()const{return R-L+1;}
}DEQ;
int N,H[500000],ANS[500000],SQ[500000];
int main()
{
	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;++i)scanf("%d",&H[i]),ANS[i]=H[i];
	for(int a=1;;++a)
	{
		const int mn_dis=(a-1)*(a-1)+1,mx_dis=a*a;
		if(mn_dis>=N)break;
		for(int i=mn_dis;i<=mx_dis&&i<N;i++)SQ[i]=a;
	}
	DEQ.Clear();
	for(int i=1;i<N;++i)
	{
		while(DEQ.Size()&&H[i-1]>H[DEQ.Back()])DEQ.PopBack();
		DEQ.PushBack(i-1);
		getmax(ANS[i],H[DEQ.Front()]+SQ[i-DEQ.Front()]);
	}
	DEQ.Clear();
	for(int i=N-2;i>=0;--i)
	{
		while(DEQ.Size()&&H[i+1]>H[DEQ.Back()])DEQ.PopBack();
		DEQ.PushBack(i+1);
		getmax(ANS[i],H[DEQ.Front()]+SQ[DEQ.Front()-i]);
	}
	for(int i=0;i<N;i++)printf("%d\n",ANS[i]-H[i]);
	return 0;
}
