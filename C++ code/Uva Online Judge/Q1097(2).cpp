#include<cstdio>
#include<vector>
#include<map>
#include<cassert>
#include<algorithm>
#include<cmath>
#include<queue>
using namespace std;
void massert(bool valid){if(valid)return;for(;;)printf("E");}
const double PI=acos(-1.0);
const int INF=2147483647;
int V,E;
vector<int>AD[2704];
map<int,int>IDX;
bool VIS[2704];
int GetIdx(int a)
{
	if(IDX.find(a)==IDX.end())
	{
		int sz=IDX.size();
		AD[sz].clear();
		VIS[sz]=false;
		return IDX[a]=sz;
	}
	return IDX[a];
}
int CharId(char a){return a>='a'?a-'a':a-'A'+26;}
int StrId(char *str){return GetIdx(CharId(str[0])*52+CharId(str[1]));}
struct Point
{
	int id,x,y,h;
	Point(){}
	Point(int x,int y):x(x),y(y){}
	Point(char *str,int x,int y,int h):id(StrId(str)),x(x),y(y),h(h){}
}P[2704];
int IofMaxX()
{
	int x=-INF,ans=-1;
	for(int i=0;i<V;i++)
	{
		if(P[i].x>x)x=P[i].x,ans=i;
	}
	massert(ans!=-1);
	return ans;
}
struct Vector
{
	double x,y;
	Vector(double x,double y):x(x),y(y){}
	double Abs(){return sqrt(x*x+y*y);}
	double Angle()
	{
		double abs=Abs(),dx=x/abs,dy=y/abs;
		double ans=0.0;
		if(dx>0.0&&dy<0.0)
		{
			ans+=1.5*PI;
			static double tx,ty;
			tx=-dy,ty=dx;
			dx=tx,dy=ty;
		}
		else if(dx<0.0&&dy<0.0)
		{
			ans+=PI;
			dx=-dx,dy=-dy;
		}
		else if(dx<0.0&&dy>0.0)
		{
			ans+=0.5*PI;
			static double tx,ty;
			tx=dy,ty=-dx;
			dx=tx,dy=ty;
		}
		else if(dx==0.0)return dy>0.0?0.5*PI:1.5*PI;
		else if(dy==0.0)return dx>0.0?0.0:PI;
		if(dx<dy)return ans+acos(dx);
		else return ans+asin(dy);
	}
};
int NxtRim(int u,double &pre)
{
	int ans=-1;
	double angle=2.0*PI;
	for(int i=0;i<AD[u].size();i++)
	{
		int &j=AD[u][i];
		Vector tv=Vector(P[j].x-P[u].x,P[j].y-P[u].y);
		double ta=tv.Angle();
//		printf("%d to %d: %.4f\n",u,j,ta/PI*180.0);
		ta-=pre;
		if(ta<=0.0)ta+=2.0*PI;
		massert(ta>0.0&&ta<=2.0*PI);
		if(ta<angle)angle=ta,ans=j;
	}
	pre+=angle;
	if(pre>=2.0*PI)pre-=2.0*PI;
	massert(pre<2.0*PI&&pre>=0.0);
	pre+=PI;
	if(pre>=2.0*PI)pre-=2.0*PI;
//	printf("AD[%d].sz=%d\n",u,AD[u].size());
	massert(ans!=-1);
//	puts("b");
	return ans;
}
int Bfs(int s)
{
	queue<int>q;
	int ans=INF;
	q.push(s);
	while(!q.empty())
	{
		int u=q.front();q.pop();
		if(VIS[u]){ans=min(ans,P[u].h);continue;}
		VIS[u]=true;
		for(int i=0;i<AD[u].size();i++)q.push(AD[u][i]);
	}
	massert(ans!=INF);
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%d%d",&V,&E)==2&&(V||E))
	{
		IDX.clear();
		for(int i=0;i<V;i++)
		{
			static char tmp[3];
			static int x,y,h;
			scanf("%s%d%d%d",tmp,&x,&y,&h);
			P[i]=Point(tmp,x,y,h);
//			printf("Add v: %d\n",P[i].id);
		}
//		printf("IDX.sz=%d\n",IDX.size());
		massert(IDX.size()==V);
		for(int i=0;i<E;i++)
		{
			char s1[3],s2[3];
			scanf("%s%s",s1,s2);
			int i1=StrId(s1),i2=StrId(s2);
			AD[i1].push_back(i2);
			AD[i2].push_back(i1);
		}
		massert(IDX.size()==V);
		int start=IofMaxX();
		queue<int>q;
		q.push(start);
		double pre=1.5*PI;
//		printf("start=%d\n",start);
		int cnt=0;
		for(int u=NxtRim(start,pre);u!=start;u=NxtRim(u,pre))
		{
			q.push(u);
//			printf("u=%d,pre=%.4f\n",u,pre/PI*180);
			assert(cnt++<=V);
		}
		while(!q.empty())
		{
			int u=q.front();q.pop();
			if(VIS[u])continue;
			VIS[u]=true;
			for(int i=0;i<AD[u].size();i++)
			{
				int &j=AD[u][i];
				if(P[j].h<P[u].h)continue;
				q.push(j);
			}
		}
		vector<int>ans;
		for(int i=0;i<V;i++)
		{
			if(VIS[i])continue;
			ans.push_back(Bfs(i));
		}
		if(!ans.size())ans.push_back(0);
		else sort(ans.begin(),ans.end());
		static int kase=1;
		printf("Case %d:\n",kase++);
		for(int i=0;i<ans.size();i++)printf("  %d\n",ans[i]);
	}
	return 0;
}
