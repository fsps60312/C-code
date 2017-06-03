#include<cstdio>
#include<cassert>
using namespace std;
void getmax(int &a,const int b){if(b>a)a=b;}
struct Deq
{
	int S[1000000],L,R;
	void Clear(){L=0,R=-1;}
	int Size()const{return R-L+1;}
	void PushBack(const int v){S[++R]=v;}
	void PopBack(){--R;}
	void PopFront(){++L;}
	int Front()const{return S[L];}
	int Back()const{return S[R];}
	bool Empty()const{return R<L;}
}DEQ;
int N,L[1000000],R[1000000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d%d",&L[i],&R[i]);
		DEQ.Clear();
		int ans=0;
		for(int i=0,l=-1;i<N;i++)
		{
			while(!DEQ.Empty()&&R[i]<L[DEQ.Front()])l=DEQ.Front(),DEQ.PopFront();
			while(!DEQ.Empty()&&L[i]>=L[DEQ.Back()])DEQ.PopBack();
			DEQ.PushBack(i);
			getmax(ans,i-l);
		}
		printf("%d\n",ans);
	}
	return 0;
}
