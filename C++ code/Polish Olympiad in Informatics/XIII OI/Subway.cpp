#include<cstdio>
#include<cassert>
#include<set>
#include<queue>
using namespace std;
struct Pq
{
	int u,len;
	Pq(){}
	Pq(const int _u,const int _len):u(_u),len(_len){}
	bool operator<(const Pq &p)const{return len>p.len;}
};
int N,L;
set<int>ET[1000000];
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&L)==2)
	{
		for(int i=0;i<N;i++)ET[i].clear();
		for(int i=1,a,b;i<N;i++)
		{
			scanf("%d%d",&a,&b),a--,b--;
			ET[a].insert(b),ET[b].insert(a);
		}
		priority_queue<Pq>pq;
		for(int i=0;i<N;i++)if((int)ET[i].size()==1)pq.push(Pq(i,1));
		int ans=N;
		while((int)pq.size()>L*2)
		{
			const Pq p=pq.top();pq.pop();
//			printf("p.u=%d,to_delete=%d\n",p.u+1,to_delete);
//			assert((int)ET[p.u].size()==1);
			const int parent=*ET[p.u].begin();
			ET[parent].erase(p.u),ET[p.u].erase(parent);
			if((int)ET[parent].size()==1)pq.push(Pq(parent,p.len+1));
			else ans-=p.len;
		}
		printf("%d\n",ans);
	}
	return 0;
}
