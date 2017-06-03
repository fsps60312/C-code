#include<cstdio>
#include<cassert>
using namespace std;
struct Deq
{
	int S[3000000],L,R;
	void Clear(){L=0,R=-1;}
	void PushBack(const int v){S[++R]=v;}
	void PopBack(){--R;}
	void PopFront(){++L;}
	int Front()const{return S[L];}
	int Back()const{return S[R];}
	int Size()const{return R-L+1;}
	bool Empty()const{return R<L;}
}MNQ,MXQ;
int T,N,S[3000000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&T,&N)==2)
	{
		for(int i=0;i<N;i++)scanf("%d",&S[i]);
		MNQ.Clear(),MXQ.Clear();
		int ans=0;
		for(int i=0,l=-1;i<N;i++)
		{
			while(!MNQ.Empty()&&S[MNQ.Back()]>=S[i])MNQ.PopBack();
			while(!MXQ.Empty()&&S[MXQ.Back()]<=S[i])MXQ.PopBack();
			MNQ.PushBack(i),MXQ.PushBack(i);
			while(S[MXQ.Front()]-S[MNQ.Front()]>T)
			{
				Deq &deq=(MNQ.Front()<MXQ.Front()?MNQ:MXQ);
				l=deq.Front();
				deq.PopFront();
			}
			const int ta=i-l;
			if(ta>ans)ans=ta;
		}
		printf("%d\n",ans);
	}
	return 0;
}
