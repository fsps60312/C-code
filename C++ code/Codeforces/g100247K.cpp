#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
struct Team
{
	int a,b,c;
	Team():a(),b(),c(){}
	Team(const int _a,const int _b,const int _c):a(_a),b(_b),c(_c){}
};
struct Bit
{
	int n;
	int data[200001];
	void Clear(const int _n){n=_n;for(int i=1;i<=n;i++)data[i]=0;}
	void Add(int i,const int v){while(i<=n)data[i]+=v,i+=(i&(-i));}
	int Query(int i){int ans=0;while(i)ans+=data[i],i-=(i&(-i));return ans;}
}BIT;
LL ANS;
vector<Team>TEAM;
void Solve(const int l,const int r,const vector<int>&teams)
{
	if(l==r)return;
	const int mid=(l+r)/2;
	vector<int>left_teams,right_teams;
	for(const int &t:teams)(TEAM[t].a<=mid?left_teams:right_teams).push_back(t);
	vector<int>::const_iterator lt=left_teams.begin();
	for(vector<int>::const_iterator rt=right_teams.begin();rt!=right_teams.end();rt++)
	{
		while(lt!=left_teams.end()&&TEAM[*lt].b<TEAM[*rt].b)BIT.Add(TEAM[*lt++].c,1);
		ANS+=BIT.Query(TEAM[*rt].c);
	}
	while(lt!=left_teams.begin())BIT.Add(TEAM[*--lt].c,-1);
	Solve(l,mid,left_teams),Solve(mid+1,r,right_teams);
	vector<int>().swap(left_teams);
	vector<int>().swap(right_teams);
}
int N;
int main()
{
//	freopen("in.txt","r",stdin);
	scanf("%d",&N);
	TEAM.clear();
	for(int i=0,a,b,c;i<N;i++)scanf("%d%d%d",&a,&b,&c),TEAM.push_back(Team(a,b,c));
	sort(TEAM.begin(),TEAM.end(),[](const Team &a,const Team &b)->bool{return a.b<b.b;});
	vector<int>teams;
	for(int i=0;i<N;i++)teams.push_back(i);
	ANS=0LL;
	BIT.Clear(N);
	Solve(1,N,teams);
	printf("%I64d\n",(LL)N*(N-1LL)/2LL-ANS);
	return 0;
}
