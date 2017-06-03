#include<cstdio>
#include<cassert>
typedef long long LL;
struct Deq
{
	int s[100000],l,r;
	void clear(){l=0,r=-1;}
	void push_back(const int v){s[++r]=v;}
	void pop_back(){r--;}
//	void pop_front(){l++;}
//	int front()const{return s[l];}
	int back()const{return s[r];}
	bool empty()const{return r<l;}
	int size()const{return r-l+1;}
	int operator[](const int i)const{return s[l+i];}
}DEQ;
int N,L,R;
LL S[100000],SUM[100001],ANS;
int Back2()
{
	assert(!DEQ.empty());
	if(DEQ.size()==1)return -1;
	return DEQ[DEQ.size()-2];
}
void Update(const LL &ans,const int l,const int r)
{
	if(ans<=ANS)return;
//	printf("Update(%lld,%d,%d)\n",ans,l,r);
	ANS=ans;
	L=l,R=r;
}
LL Sum(const int a,const int b){return SUM[b+1]-SUM[a];}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		SUM[0]=0LL;
		for(int i=0;i<N;i++)scanf("%lld",&S[i]),SUM[i+1]=SUM[i]+S[i];
		DEQ.clear();
		L=R=-1;ANS=-1LL;
		for(int i=0;i<N;i++)
		{
			while(!DEQ.empty()&&S[i]<=S[DEQ.back()])
			{
				Update(S[DEQ.back()]*Sum(Back2()+1,i-1),Back2()+1,i-1);
				DEQ.pop_back();
			}
			DEQ.push_back(i);
//			for(int i=0;i<DEQ.size();i++)printf(" %d",DEQ[i]);puts("");
		}
		while(!DEQ.empty())
		{
			Update(S[DEQ.back()]*Sum(Back2()+1,N-1),Back2()+1,N-1);
			DEQ.pop_back();
		}
		assert(L!=-1);
		static int kase=0;
		if(kase++)puts("");
		printf("%lld\n%d %d\n",ANS,L+1,R+1);
	}
	return 0;
}
