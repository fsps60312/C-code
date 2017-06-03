#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
int T,N,M,Q,Y[100000];
struct State
{
	int y,x,h;
	State(){}
	State(const int &_y,const int &_x,const int &_h):y(_y),x(_x),h(_h){}
	bool operator<(const State &s)const{return h<s.h;}
};
vector<State>S;
int DJ[1000000];
int FindDJ(const int &a){return DJ[a]==a?a:(DJ[a]=FindDJ(DJ[a]));}
bool Merge(const int &a,const int &b)
{
	static int i,j;
	if((i=FindDJ(a))==(j=FindDJ(b)))return false;
	DJ[i]=j;
	return true;
}
bool VIS[1000][1000];
int main()
{
	while(scanf("%d",&T)==1)
	{
		while(T--)
		{
			scanf("%d%d",&N,&M);
			S.clear();
			for(int i=0;i<N;i++)for(int j=0;j<M;j++)
			{
				VIS[i][j]=false;
				static int v;scanf("%d",&v);
				S.push_back(State(i,j,v));
			}
			sort(S.begin(),S.end());
			scanf("%d",&Q);
			for(int i=0;i<Q;i++)scanf("%d",&Y[i]);
			for(int i=N*M-1;i>=0;i--)DJ[i]=i;
			int cnt=0;
			vector<int>ans;
			for(int i=N*M-1;Q--;)
			{
				for(;i>=0&&S[i].h>Y[Q];i--)
				{
					cnt++;
					const State &s=S[i];
					if(s.x&&VIS[s.y][s.x-1]&&Merge(s.y*M+s.x,s.y*M+(s.x-1)))cnt--;
					if(s.y&&VIS[s.y-1][s.x]&&Merge(s.y*M+s.x,(s.y-1)*M+s.x))cnt--;
					if(s.x+1<M&&VIS[s.y][s.x+1]&&Merge(s.y*M+s.x,s.y*M+(s.x+1)))cnt--;
					if(s.y+1<N&&VIS[s.y+1][s.x]&&Merge(s.y*M+s.x,(s.y+1)*M+s.x))cnt--;
					VIS[s.y][s.x]=true;
				}
				ans.push_back(cnt);
			}
			for(int i=ans.size()-1;i>=0;i--)
			{
//				if(i<ans.size()-1)printf(" ");
				printf("%d ",ans[i]);
			}
			puts("");
		}
	}
	return 0;
}
