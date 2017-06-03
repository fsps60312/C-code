#include<cstdio>
#include<cassert>
#include<map>
#include<set>
using namespace std;
const int INF=2147483647;
int N,M,S[500000];
pair<int,int>ALIVE[2000000];
pair<int,int>Merge(const pair<int,int>&a,const pair<int,int>&b)
{
	if(!a.second||!b.second)return a.second?a:b;
	if(a.first==b.first)return make_pair(a.first,a.second+b.second);
	if(a.second>=b.second)return make_pair(a.first,a.second-b.second);
	else return make_pair(b.first,b.second-a.second);
}
void Build(const int id,const int l,const int r)
{
	if(l==r){ALIVE[id]=make_pair(S[r],1);return;}
	const int mid=(l+r)/2;
	Build(id*2,l,mid),Build(id*2+1,mid+1,r);
	ALIVE[id]=Merge(ALIVE[id*2],ALIVE[id*2+1]);
}
pair<int,int>Query(const int id,const int l,const int r,const int bl,const int br)
{
	if(r<bl||br<l)return make_pair(-1,0);
	if(bl<=l&&r<=br)return ALIVE[id];
	const int mid=(l+r)/2;
	return Merge(Query(id*2,l,mid,bl,br),Query(id*2+1,mid+1,r,bl,br));
}
map<int,map<int,int> >COMPANY;
int main()
{
//	freopen("in.txt","r",stdin);
//	freopen("kur15a.in","r",stdin);
//	freopen("out.txt","w",stdout);
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;i++)scanf("%d",&S[i]),COMPANY[S[i]][i]=-1;
	for(map<int,map<int,int> >::iterator it=COMPANY.begin();it!=COMPANY.end();it++)
	{
		it->second[INF]=-1;
		int cnt=0;
		for(map<int,int>::iterator iu=it->second.begin();iu!=it->second.end();iu++)iu->second=cnt++;
	}
	Build(1,0,N-1);
	for(int i=0,a,b;i<M;i++)
	{
		scanf("%d%d",&a,&b),a--,b--;
		const int ans=Query(1,0,N-1,a,b).first;
		const int cnt=(COMPANY[ans].upper_bound(b)->second)-(COMPANY[ans].lower_bound(a)->second);
		printf("%d\n",cnt*2>b-a+1?ans:0);
	}
	return 0;
}
