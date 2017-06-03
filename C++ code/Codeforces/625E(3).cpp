#include<cstdio>
#include<cassert>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const int INF=2147483647;
struct Frog{int id,p,a;};
struct Gap
{
	int id;
	int x,y,a,executed,deadline;
	Gap(){}
	Gap(const int _id,const int _x,const int _a,const int _d):id(_id),x(_x),y(_x),a(_a),executed(0),deadline(_d){}
	bool operator<(const Gap &g)const{return deadline!=g.deadline?deadline<g.deadline:id<g.id;}
};
int N,M,LEFT[100000],RIGT[100000];
int GetDeadline(const Gap &g1,const Gap &g2)
{
	const int time=g1.executed;
//	printf("''time=%d\n",time);
	const LL p1=g1.y+(LL)time*g1.a,p2=(g1.x<g2.x?g2.y:g2.y+M)+(LL)time*g2.a;
//	puts("a");
	if(g1.id<g2.id&&p1+g1.a>=p2)return time;
//	puts("b");
	if(g1.a<=g2.a)return INF;
//	puts("c");
	const int ans=((g2.id<g1.id?p2+g2.a:p2)-p1-g2.a-1)/(g1.a-g2.a);
	return time+ans;
}
Gap GAP[100000];
set<Gap>S;
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&N,&M)==2)
	{
		vector<Frog>frog;
		for(int i=0;i<N;i++)
		{
			static Frog f;
			f.id=i;
			scanf("%d%d",&f.p,&f.a);
			f.p--;
			frog.push_back(f);
		}
		sort(frog.begin(),frog.end(),[](const Frog &a,const Frog &b)->bool{return a.p<b.p;});
		S.clear();
		for(int i=0;i<N;i++)
		{
			const Frog &f=frog[i];
			GAP[f.id]=Gap(f.id,f.p,f.a,-1);
		}
		for(int i=0;i<N;i++)
		{
			const Frog &f1=frog[i],&f2=frog[(i+1)%N];
			GAP[f1.id].deadline=GetDeadline(GAP[f1.id],GAP[f2.id]);
			S.insert(GAP[f1.id]);
//			printf("id=(%d,%d),deadline=%d\n",f1.id+1,f2.id+1,GAP[f1.id].deadline);
			RIGT[f1.id]=f2.id;
			LEFT[f2.id]=f1.id;
		}
		for(LL time=0LL;;)
		{
			Gap &g=GAP[S.begin()->id];
			if(g.deadline==INF)break;
			S.erase(*S.begin());
			time=g.deadline+1LL;
//			printf("time=%lld\n",time);
//			printf("frog=%d,a=%d\n",g.id+1,g.a);
			int erased=0;
			for(;RIGT[g.id]!=g.id;)
			{
				const int nxt=RIGT[g.id];
//				printf("erase(%d)\n",nxt+1);
				RIGT[LEFT[nxt]]=RIGT[nxt];
				LEFT[RIGT[nxt]]=LEFT[nxt];
				S.erase(GAP[nxt]),erased++;
				const Gap &gr=GAP[RIGT[g.id]];
//				printf("loc(%d,%d)=(%lld,%lld)\n",g.id,gr.id,g.y+time*g.a,(gr.x>g.x?gr.y:gr.y+M)+(gr.id>g.id?time-1LL:time)*gr.a);
				if(GetDeadline(g,gr)>=time)break;
			}
			assert(erased<=g.a);
			g.a-=erased;
			g.y+=time*erased;
			g.executed=time-1LL;
//			printf("a become %d\n",g.a);
			const Gap &gr=GAP[RIGT[g.id]];
			g.deadline=GetDeadline(g,gr);
			S.insert(g);
			if(LEFT[g.id]==g.id)break;
			Gap &gl=GAP[LEFT[g.id]];
			S.erase(gl);
			gl.deadline=GetDeadline(gl,g);
			S.insert(gl);
		}
		vector<int>ans;
		for(const auto &g:S)ans.push_back(g.id);
		printf("%d\n",(int)ans.size());
		for(int i=0;i<(int)ans.size();i++)
		{
			if(i)putchar(' ');
			printf("%d",ans[i]+1);
		}
		puts("");
	}
	return 0;
}
