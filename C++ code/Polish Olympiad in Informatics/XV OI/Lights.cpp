#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
struct Big
{
	vector<long long>S;
	Big(){}
	Big(const int val){S.push_back(val);Carry();}
	void Carry()
	{
		for(int i=0;i<(int)S.size();i++)if(S[i]>=10)
		{
			if(i+1==(int)S.size())S.push_back(0);
			S[i+1]+=S[i]/10;
			S[i]%=10;
		}
	}
	void operator*=(const int val)
	{
		for(int i=0;i<(int)S.size();i++)S[i]*=val;
		Carry();
	}
	void Print()const{for(int i=(int)S.size()-1;i>=0;i--)putchar((char)('0'+S[i]));}
};
void Reduce(Big &a,Big &b)
{
	
}
int N;
Big UPON[1000],DOWN[1000];
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0,v;i<N;i++)
		{
			scanf("%d",&v);
			UPON[i]=Big(1);
			DOWN[i]=Big(v);
			for(int j=0;j<i;j++)UPON[j]*=v-1,DOWN[j]*=v;
		}
		for(int i=0;i<N;i++)
		{
			Reduce(UPON[i],DOWN[i]);
			UPON[i].Print(),printf("/"),DOWN[i].Print();puts("");
		}
	}
	return 0;
}
