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
int N,H[500000],ANS[500000];
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;++i)scanf("%d",&H[i]),ANS[i]=H[i];
	for(int a=1;;++a)
	{
		const int mn_dis=(a-1)*(a-1)+1,mx_dis=a*a;
		if(mn_dis>=N)break;
//		printf("(%d,%d)\n",mn_dis,mx_dis);
		DEQ.Clear();
		for(int i=mn_dis;i<N;++i)
		{
			while(DEQ.Size()&&DEQ.Front()<i-mx_dis)DEQ.PopFront();
			while(DEQ.Size()&&H[i-mn_dis]>=H[DEQ.Back()])DEQ.PopBack();
			DEQ.PushBack(i-mn_dis);
			getmax(ANS[i],H[DEQ.Front()]+a);
		}
		DEQ.Clear();
		for(int i=N-1-mn_dis;i>=0;--i)
		{
			while(DEQ.Size()&&DEQ.Front()>i+mx_dis)DEQ.PopFront();
			while(DEQ.Size()&&H[i+mn_dis]>=H[DEQ.Back()])DEQ.PopBack();
			DEQ.PushBack(i+mn_dis);
			getmax(ANS[i],H[DEQ.Front()]+a);
		}
	}
	for(int i=0;i<N;i++)printf("%d\n",ANS[i]-H[i]);
	return 0;
}
