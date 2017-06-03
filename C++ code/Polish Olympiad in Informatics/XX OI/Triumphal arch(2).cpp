#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
struct Fraction
{
	int up,down;
	Fraction(){}
	Fraction(const int _up,const int _down):up(_up),down(_down){}
	Fraction Merge(const Fraction &f)const{return Fraction(up+f.up,down+f.down);}
	bool operator<(const Fraction &f)const{return (long long)up*f.down<(long long)f.up*down;}
};
int N;
vector<int>ET[300000];
Fraction Dfs(const int u,const int parent,const Fraction &f)
{
	Fraction ans=f;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(nxt!=parent)
		{
			const Fraction &ta=Dfs(nxt,u,f.Merge(Fraction((int)ET[nxt].size()-1,1)));
			if(ans<ta)ans=ta;
		}
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d",&N)==1)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=0,a,b;i<N-1;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].push_back(b),ET[b].push_back(a);
		}
		const Fraction &ans=Dfs(0,-1,Fraction(ET[0].size(),1));
		printf("%d\n",(ans.up+ans.down-1)/ans.down);
	}
	return 0;
}
