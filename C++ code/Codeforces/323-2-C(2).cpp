#include<bits/stdc++.h>
using namespace std;
int gcd(const int &a,const int &b){return b?gcd(b,a%b):a;}
int N;
multiset<int,greater<int> >S;
vector<int>V;
int main()
{
	while(scanf("%d",&N)==1)
	{
		S.clear(),V.clear();
		for(int i=0;i<N*N;i++)
		{
			static int v;
			scanf("%d",&v);
			S.insert(v);
		}
		for(int i=0;i<N;i++)
		{
			if(i)printf(" ");
			int v=*S.begin();
			printf("%d",v);
			for(int j=0;j<V.size();j++)S.erase(S.find(gcd(V[j],v))),S.erase(S.find(gcd(V[j],v)));
			V.push_back(v);
			S.erase(S.find(v));
		}
		puts("");
	}
	return 0;
}
