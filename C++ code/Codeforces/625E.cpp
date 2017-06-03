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
	int x,a,deadline;
	Gap(){}
	Gap(const int _id,const int _x,const int _a,const int _d):id(_id),x(_x),a(_a),deadline(_d){}
	bool operator<(const Gap &g)const{return deadline!=g.deadline?deadline<g.deadline:id<g.id;}
};
int GetDeadline(const int p1,const int p2,const int a1,const int a2)
{
	if(a1<=a2)return INF;
	return (p2-p1-1)/(a1-a2);
}
int N,M,LEFT[100000],RIGT[100000];
Gap GAP[100000];
set<Gap>S;
int main()
{
	freopen("in.txt","r",stdin);
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
			const Frog &f1=frog[i],&f2=frog[(i+1)%N];
			GAP[f1.id]=Gap(f1.id,f1.p,f1.a,GetDeadline(f1.p,i==N-1?f2.p+M:f2.p,f1.a,f2.a));
			S.insert(GAP[f1.id]);
			printf("id=%d\n",f1.id+1);
			RIGT[f1.id]=f2.id;
			LEFT[f2.id]=f1.id;
		}
		for(LL time=0LL;;)
		{
			Gap &g=GAP[S.begin()->id];
			if(g.deadline==INF)break;
			S.erase(*S.begin());
			time=g.deadline+1LL;
			printf("frog=%d,a=%d\n",g.id+1,g.a);
			for(;RIGT[g.id]!=g.id;)
			{
				const int nxt=RIGT[g.id];
				printf("erase(%d)\n",nxt+1);
				RIGT[LEFT[nxt]]=RIGT[nxt];
				LEFT[RIGT[nxt]]=LEFT[nxt];
				S.erase(GAP[nxt]),g.a=max(0,g.a-1);
				const Gap &gr=GAP[RIGT[g.id]];
				if(g.x+time*g.a<(gr.x<=g.x?gr.x+M:gr.x)+(time-1LL)*gr.a)break;
			}
			printf("a become %d\n",g.a);
			const Gap &gr=GAP[RIGT[g.id]];
			g.deadline=GetDeadline(g.x,gr.x<=g.x?gr.x+M:gr.x,g.a,gr.a);
			S.insert(g);
			if(LEFT[g.id]==g.id)break;
			Gap &gl=GAP[LEFT[g.id]];
			S.erase(gl);
			gl.deadline=GetDeadline(gl.x,g.x<=gl.x?g.x+M:g.x,gl.a,g.a);
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
