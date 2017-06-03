#include<cstdio>
#include<cstdlib>
#include<string>
#include<map>
#include<vector>
#include<queue>
using namespace std;
int R,PRE[500][500],HEAD[500],NEXT[10000],VELO[10000],TO[10000],NSZ;
map<string,int> CITYIDX;
map<int,string> CITYNAME;
int getidx(string name)
{
	if(CITYIDX.find(name)!=CITYIDX.end())return CITYIDX[name];
	int sz=CITYIDX.size();
	CITYIDX[name]=sz;
	CITYNAME[sz]=name;
	for(int i=0;i<500;i++)PRE[sz][i]=-1;
	HEAD[sz]=-1;
	return sz;
}
void dfsprint(int u,int cn)
{
	if(PRE[u][cn]==-1)
	{
		printf("%s",CITYNAME[u].c_str());
		return;
	}
	dfsprint(PRE[u][cn],cn-1);
	printf(" %s",CITYNAME[u].c_str());
}
void solve(int sp,int ep)
{
	queue<int> q;
	q.push(sp),q.push(0),q.push(0);
	int u,v,cn;
	bool found=false;
	while(!q.empty()&&!found)
	{
		u=q.front();q.pop();
		v=q.front();q.pop();
		cn=q.front();q.pop();
		for(int ti=HEAD[u];ti!=-1;ti=NEXT[ti])
		{
			int j=TO[ti];
			if(j==sp||v>VELO[ti]||PRE[j][cn+1]!=-1)continue;
			//if(CITYNAME[u]=="g")printf(" g:%s",CITYNAME[j].c_str());
			//if(CITYNAME[u]=="z")printf(" z:%s",CITYNAME[j].c_str());
			PRE[j][cn+1]=u;
			if(j==ep)
			{
				u=j,v=VELO[ti],cn++;
				found=true;
				dfsprint(ep,cn);
				printf("\n");
				return;
			}
			q.push(j),q.push(VELO[ti]),q.push(cn+1);
		}
	}
	printf("No valid route.\n");
}
bool needexchange(int a,int b)
{
	return TO[a]>TO[b]||(TO[a]==TO[b]&&VELO[a]>VELO[b]);
}
void addside(int from,int to,int v)
{
	NEXT[NSZ]=HEAD[from];
	HEAD[from]=NSZ;
	TO[NSZ]=to;
	VELO[NSZ]=v;
	int i=NSZ;
	while(NEXT[i]!=-1&&needexchange(i,NEXT[i]))
	{
		int &a=i,&b=NEXT[i];
		TO[a]^=TO[b]^=TO[a]^=TO[b];
		VELO[a]^=VELO[b]^=VELO[a]^=VELO[b];
		i=NEXT[i];
	}
	NSZ++;
}
int main()
{
	freopen("inn.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int kase=0;
	while(scanf("%d",&R)==1)
	{
		NSZ=0;
		if(kase++)printf("\n");
		CITYIDX.clear(),CITYNAME.clear();
		char tcity1[31],tcity2[31];
		while(R--)
		{
			int v;
			scanf("%s%s%d",tcity1,tcity2,&v);
			int a=getidx((string)tcity1),b=getidx((string)tcity2);
			addside(a,b,v);
			addside(b,a,v);
		}
		scanf("%s%s",tcity1,tcity2);
		//printf("\n");for(int ti=HEAD[getidx("g")];ti!=-1;ti=NEXT[ti])printf(" %s",CITYNAME[TO[ti]].c_str());printf("\n");
		solve(getidx((string)tcity1),getidx((string)tcity2));
	}
	return 0;
}
