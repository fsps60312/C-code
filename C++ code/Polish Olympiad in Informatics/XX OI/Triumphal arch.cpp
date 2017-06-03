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
	Fraction Split(const Fraction &f)const{return Fraction(up-f.up,down-f.down);}
	bool operator<(const Fraction &f)const{return (long long)up*f.down<(long long)f.up*down;}
};
int N;
vector<int>ET[300000];
Fraction DP[300000];
Fraction Dfs(const int u,const int parent)
{
//	printf("u=%d,parent=%d\n",u,parent);
	vector<pair<Fraction,Fraction> >fs,ds;
	int ch_cnt=0;
	for(int i=0;i<(int)ET[u].size();i++)
	{
		const int nxt=ET[u][i];
		if(nxt!=parent)
		{
			ch_cnt++;
			Fraction f=Dfs(nxt,u);
			pair<Fraction,Fraction>p=make_pair(f,DP[nxt]);
			p.first.down++;
			fs.push_back(p);
		}
	}
	sort(fs.begin(),fs.end());
	for(int l=0,r=(int)fs.size()-1;l<r;l++,r--)swap(fs[l],fs[r]);
	Fraction ans=Fraction(ch_cnt,1);
	if(!fs.empty()&&ans<fs[0].second)
	{
		ans=ans.Merge(fs[0].second);
		for(int i=1,mn=0;i<(int)fs.size();i++)
		{
			Fraction ta=ans.Merge(fs[i].first);
			if(fs[i].first.Split(fs[i].second)<fs[mn].first.Split(fs[mn].second))
			{
				ta=ta.Merge(fs[mn].first.Split(fs[mn].second));
				ta=ta.Split(fs[i].first.Split(fs[i].second));
				mn=i;
			}
			if(ans<ta)ans=ta;
		}
	}
	DP[u]=ans;
	ans=Fraction(ch_cnt,1);
	for(int i=0;i<(int)fs.size()&&ans<fs[i].first;i++)ans=ans.Merge(fs[i].first);
//	printf("DP[%d]=(%d/%d),ans=(%d/%d)\n",u,DP[u].up,DP[u].down,ans.up,ans.down);
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
		Dfs(0,-1);
		printf("%d\n",(DP[0].up+DP[0].down-1)/DP[0].down);
	}
	return 0;
}
