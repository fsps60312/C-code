#include<cstdio>
#include<cassert>
#include<algorithm>
#include<utility>
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
	Fraction(const LL _up,const LL _down):up(_up),down(_down)
	{
		if(down<0)up*=-1,down*=-1;
	}
	Fraction operator-(const Fraction &f)const{return Fraction(up*f.down-f.up*down,down*f.down);}
	Fraction operator/(const Fraction &f)const
	{
		LL g1=__gcd(abs(up),abs(f.up)),g2=__gcd(down,f.down);
		return Fraction((up/g1)*(f.down/g2),(f.up/g1)*(down/g2));
	}
	bool operator<(const Fraction &f)const
	{
//		LL g1=Gcd(abs(up),abs(f.up)),g2=Gcd(down,f.down);
//		if(g1==0LL)g1=1LL;
		return (long double)up*f.down<(long double)f.up*down;
	}
	bool operator>(const Fraction &f)const
	{
//		LL g1=Gcd(abs(up),abs(f.up)),g2=Gcd(down,f.down);
//		if(g1==0LL)g1=1LL;
		return (long double)up*f.down>(long double)f.up*down;
	}
	bool operator==(const Fraction &f)const
	{
//		LL g1=Gcd(abs(up),abs(f.up)),g2=Gcd(down,f.down);
//		if(g1==0LL)g1=1LL;
		return (long double)up*f.down==(long double)f.up*down;
	}
	bool operator>=(const Fraction &f)const
	{
//		LL g1=Gcd(abs(up),abs(f.up)),g2=Gcd(down,f.down);
//		if(g1==0LL)g1=1LL;
		return (long double)up*f.down>=(long double)f.up*down;
	}
	bool operator<=(const Fraction &f)const
	{
//		LL g1=Gcd(abs(up),abs(f.up)),g2=Gcd(down,f.down);
//		if(g1==0LL)g1=1LL;
		return (long double)up*f.down<=(long double)f.up*down;
	}
};
struct Competitor
{
	int s,r,id;
	bool operator<(const Competitor &c)const{return Fraction(1,r)-Fraction(1,s)>Fraction(1,c.r)-Fraction(1,c.s);}
}S[200000];
int N;
Fraction GetA(const int i){return Fraction(1,S[i].r)-Fraction(1,S[i].s);}
Fraction GetB(const int i){return Fraction(1,S[i].s);}
Fraction GetX(const int i1,const int i2)
{
	return (GetB(i1)-GetB(i2))/(GetA(i2)-GetA(i1));
}//(1)(2)/(3)(4)
bool IsParallel(const int i)
{
	if(DEQ.Size()==0)return false;
	return GetA(DEQ.Back(0))==GetA(i);
}
bool NeedPopBack(const int i)
{
	if(DEQ.Size()==0)return false;
	if(IsParallel(i))return GetB(DEQ.Back(0))>=GetB(i);
	if(GetX(DEQ.Back(0),i)<=Fraction(0,1))return true;
	if(DEQ.Size()==1)return false;
	return GetX(DEQ.Back(0),i)<=GetX(DEQ.Back(1),DEQ.Back(0));
}
bool CanPushBack(const int i)
{
	if(DEQ.Size()==0)return true;
	if(IsParallel(i))
	{
		assert(GetB(i)>GetB(DEQ.Back(0)));
		return false;
	}
	return GetX(DEQ.Back(0),i)<Fraction(1,1);
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
		for(int i=0;i<N;i++)scanf("%d%d",&S[i].s,&S[i].r),S[i].id=i+1;
		sort(S,S+N);
		DEQ.Clear();
		for(int i=0;i<N;i++)
		{
			while(NeedPopBack(i))DEQ.PopBack();
			if(CanPushBack(i))DEQ.PushBack(i);
		}
		vector<int>ans;
		for(int i=0,j=0;i<N;i++)
		{
			while(j<DEQ.Size()&&GetA(DEQ.Front(j))>GetA(i))j++;
			if(j==DEQ.Size())break;
			if(GetA(DEQ.Front(j))==GetA(i)&&GetB(DEQ.Front(j))==GetB(i))ans.push_back(S[i].id);
			else if(j>0&&!(GetA(DEQ.Front(j))==GetA(i))&&GetX(DEQ.Front(j),i)==GetX(DEQ.Front(j-1),DEQ.Front(j)))ans.push_back(S[i].id);
		}
		sort(ans.begin(),ans.end());
		for(int i=0;i<(int)ans.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]);
		}
		puts("");
	}
	return 0;
}
