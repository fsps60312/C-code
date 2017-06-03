#include<cstdio>
#include<cassert>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long LL;
struct Deq
{
	int S[200000],L,R;
	void Clear(){L=0,R=-1;}
	int Size(){return R-L+1;}
	void PushBack(const int v){S[++R]=v;}
	void PopBack(){R--;}
	void PopFront(){L++;}
	int Back(const int i){return S[R-i];}
	int Front(const int i){return S[L+i];}
}DEQ;
struct Fraction
{
	LL up,down;
	Fraction(){}
	Fraction(const LL _up,const LL _down):up(_up),down(_down){if(down<0)up*=-1,down*=-1;}
	bool operator-(const Fraction &f)const{return Fraction(up*f.down-f.up*down,down*f.down);}
};
struct Competitor
{
	int s,r;
	bool operator<(const Competitor &c)const{return Fraction(1,r)-Fraction(1,s)>Fraction(1,c.r)-Fraction(1,c.s);}
}S[200000];
int N;
Fraction GetA(const int i){return Fraction(1,S[i].r)-Fraction(1,S[i].s);}
Fraction GetB(const int i){return Fraction(1,S[i].s);}
Fraction GetX(const int i1,const int i2){return (GetB(i1)-GetB(i2))/(GetA(i2)-GetA(i1));}
bool IsParallel(const int i)
{
	if(DEQ.Size()==0)return false;
	return fabs(GetA(DEQ.Back(0))-GetA(i))<EPS;
}
bool NeedPopBack(const int i)
{
	if(DEQ.Size()==0)return false;
	if(IsParallel(i))return GetB(DEQ.Back(0))>=GetB(i);
	if(DEQ.Size()==1)return false;
	return GetX(DEQ.Back(0),i)<=GetX(DEQ.Back(1),DEQ.Back(0));
}
int main()
{
//	freopen("in.txt","r",stdin);
//	R/r+S/s
//	x/r+(1-x)/s
//	=1/s+x/r-x/s
//	=1/s+x(1/r-1/s)
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)scanf("%d%d",&S[i].s,&S[i].r);
		sort(S,S+N);
		DEQ.Clear();
		for(int i=0;i<N;i++)
		{
			while(NeedPopBack(i))DEQ.PopBack();
			if(!IsParallel(i)||GetB(i)<GetB(DEQ.Back(0)))DEQ.PushBack(i);
		}
		while(DEQ.Size()>=2&&GetX(DEQ.Front(0),DEQ.Front(1))<=0.0+EPS)DEQ.PopFront();
		while(DEQ.Size()>=2&&GetX(DEQ.Back(0),DEQ.Back(1))>=1.0-EPS)DEQ.PopBack();
		for(int i=0;i<DEQ.Size();i++)
		{
			if(i)putchar(' ');
			printf("%d",DEQ.Front(i)+1);
		}
		puts("");
	}
	return 0;
}
