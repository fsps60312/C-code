#include<cstdio>
#include<cassert>
#include<map>
using namespace std;
typedef long long LL;
const LL MOD=1000000007LL;
LL N,H,W;
char COMMAND[500001];
LL Solve()
{
	LL up_bound=-1,down_bound=H,left_bound=-1,right_bound=W;
	LL y=0,x=0,miny=0,maxy=0,minx=0,maxx=0;
	map<LL,LL>up,down,left,right;
	LL ans=0LL;
	for(LL i=0;i<N;i++)
	{
		if(up_bound+1==down_bound||left_bound+1==right_bound)return ans;
		switch(COMMAND[i])
		{
			case'U':y--;break;
			case'D':y++;break;
			case'L':x--;break;
			case'R':x++;break;
			default:assert(0);break;
		}
		if(y<miny)miny=y,up[i+1]=y,up_bound++,(ans+=(i+1LL)*(right_bound-1LL-left_bound))%=MOD;
		if(y>maxy)maxy=y,down[i+1]=y,down_bound--,(ans+=(i+1LL)*(right_bound-1LL-left_bound))%=MOD;
		if(x<minx)minx=x,left[i+1]=x,left_bound++,(ans+=(i+1LL)*(down_bound-1LL-up_bound))%=MOD;
		if(x>maxx)maxx=x,right[i+1]=x,right_bound--,(ans+=(i+1LL)*(down_bound-1LL-up_bound))%=MOD;
	}
	if(x==0&&y==0)return -1;
//	const int dx=x,dy=y;
	while(!up.empty()&&y+(up.begin()->second)>=miny)up.erase(up.begin());
	while(!down.empty()&&y+(down.begin()->second)<=maxy)down.erase(down.begin());
	while(!left.empty()&&x+(left.begin()->second)>=minx)left.erase(left.begin());
	while(!right.empty()&&x+(right.begin()->second)<=maxx)right.erase(right.begin());
	map<LL,char>step;
	for(const auto &it:up)step[it.first]='U';
	for(const auto &it:down)step[it.first]='D';
	for(const auto &it:left)step[it.first]='L';
	for(const auto &it:right)step[it.first]='R';
	LL cost=0LL;
	while(up_bound+1<down_bound&&left_bound+1<right_bound)
	{
		cost+=N;
		for(const auto &it:step)
		{
			if(!(up_bound+1<down_bound&&left_bound+1<right_bound))break;
			switch(it.second)
			{
				case'U':up_bound++,(ans+=(cost+it.first)*(right_bound-1LL-left_bound))%=MOD;break;
				case'D':down_bound--,(ans+=(cost+it.first)*(right_bound-1LL-left_bound))%=MOD;break;
				case'L':left_bound++,(ans+=(cost+it.first)*(down_bound-1LL-up_bound))%=MOD;break;
				case'R':right_bound--,(ans+=(cost+it.first)*(down_bound-1LL-up_bound))%=MOD;break;
				default:assert(0);break;
			}
		}
	}
	return ans;
}
int main()
{
//	freopen("in.txt","r",stdin);
	while(scanf("%I64d%I64d%I64d",&N,&H,&W)==3)
	{
		scanf("%s",COMMAND);
		printf("%I64d\n",Solve());
		break;
	}
	return 0;
}
