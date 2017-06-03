#include<cstdio>
#include<cassert>
#include<algorithm>
#include<set>
using namespace std;
int N,M[3];
struct Criminal
{
	multiset<int>s;
	void clear(){s.clear();}
	void insert(const int v){s.insert(v);}
	bool empty(){return s.empty();}
	int back(){auto it=s.end();return *--it;}
	void defeat(const int v)
	{
		auto it=s.upper_bound(v);
		if(it==s.begin())return;
		s.erase(--it);
	}
	void defeat(const int a,const int b)
	{
		if(s.size()<=1)defeat(a+b);
		else
		{
			auto ita=s.begin(),itb=s.begin();
			itb++;
			if((*ita)<=a&&(*itb)<=b)defeat(b),defeat(a);
			else defeat(a+b);
		}
	}
}CRIM;
int Solve()
{
	if(CRIM.back()>M[0]+M[1]+M[2])return -1;
	int ans=0;
	while(!CRIM.empty())
	{
		if(CRIM.back()<=M[2])
		{
			CRIM.defeat(M[2]);
			CRIM.defeat(M[0],M[1]);
		}
		else if(CRIM.back()<=M[0]+M[1])CRIM.defeat(M[0]+M[1]),CRIM.defeat(M[2]);
		else if(CRIM.back()<=M[0]+M[2])CRIM.defeat(M[0]+M[2]),CRIM.defeat(M[1]);
		else if(CRIM.back()<=M[1]+M[2])CRIM.defeat(M[1]+M[2]),CRIM.defeat(M[0]);
		else CRIM.defeat(M[0]+M[1]+M[2]);
		ans++;
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		CRIM.clear();
		for(int i=0;i<3;i++)scanf("%d",&M[i]);
		for(int i=0,c;i<N;i++)scanf("%d",&c),CRIM.insert(c);
		sort(M,M+3);
		int ans=Solve();
		printf("%d\n",ans);
		break;
	}
	return 0;
}
