#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
struct DisjointSets
{
	vector<int>DATA;
	void Clear(const int n){DATA.resize(n);for(int i=0;i<n;i++)DATA[i]=i;}
	int Find(const int a){return DATA[a]==a?a:(DATA[a]=Find(DATA[a]));}
	bool Merge(int a,int b){if((a=Find(a))==(b=Find(b)))return false;DATA[a]=b;return true;}
}DJ;
int main()
{
	DJ.Clear(2010);
	int cnt=2010;
	for(int i=0;i<=2009;i++)if(DJ.Merge(i,i*i%2010))--cnt;
	printf("cnt=%d\n",cnt);//cnt=48
	return 0;
}
