#include<cstdio>
#include<cstdlib>
#include<vector>
#include<string>
#include<map>
#include<queue>
const int MAXN=1000000;
using namespace std;
map<string,int> IDX;
map<int,string> NAME;
vector<int> LINK[MAXN];
int IN[MAXN],INSTED[MAXN],INSTIME_CNT,INSTIME[MAXN],EXPLICIT[MAXN];
bool cmpstr(char *a,char *b,int len){for(int i=0;i<len;i++)if(a[i]!=b[i])return false;return true;}
bool isempty(char a){return a==' '||a=='\n';}
void init(){IDX.clear();INSTIME_CNT=0;}
void init(int i)
{
	LINK[i].clear();
	IN[i]=INSTED[i]=0;
}
int I;
int getidx(char *str)
{
	while(isempty(str[I]))I++;
	//if(!str[I])return -1;
	char name[21];
	int j;
	for(j=0;str[I+j]&&!isempty(str[I+j]);j++)name[j]=str[I+j];
	name[j]=0;
	I+=j;
	while(isempty(str[I]))I++;
	if(IDX.find(name)!=IDX.end())return IDX[name];
	int sz=IDX.size();
	init(sz);
	IDX[name]=sz;
	NAME[sz]=name;
	return sz;
}
void adddepend(char *str)
{
	I=0;
	int u=getidx(str);
	while(str[I])
	{
		LINK[u].push_back(getidx(str));
	}
}
void install(int u,int ex)
{
	if(INSTED[u]){printf("   %s is already installed.\n",NAME[u].c_str());return;}
	for(int i=0;i<LINK[u].size();i++)
	{
		int j=LINK[u][i];
		//printf("%d->%d\n",u,j);
		IN[j]++;
		if(!INSTED[j])install(j,ex);
	}
	printf("   Installing %s\n",NAME[u].c_str());
	INSTED[u]=1;
	EXPLICIT[u]=ex;
	INSTIME[u]=INSTIME_CNT++;
}
void install(char *name){I=0;int u=getidx(name);install(u,u);}
struct RPair{int x,y;bool operator<(RPair a)const{return x<a.x;}};
void remove(int u)
{
	if(IN[u]){printf("   %s is still needed.\n",NAME[u].c_str());return;}
	if(!INSTED[u]){printf("   %s is not installed.\n",NAME[u].c_str());return;}
	printf("   Removing %s\n",NAME[u].c_str());
	INSTED[u]=0;
	priority_queue<RPair> q;
	for(int i=0;i<LINK[u].size();i++)
	{
		int j=LINK[u][i];
		IN[j]--;
		if(!IN[j]&&EXPLICIT[u]==EXPLICIT[j])q.push((RPair){INSTIME[j],j});
	}
	while(!q.empty())
	{
		RPair j=q.top();q.pop();
		remove(j.y);
	}
}
void remove(char *name){I=0;int u=getidx(name);remove(u);}
struct Pair{int x,y;bool operator<(Pair a)const{return x>a.x;}};
void list()
{
	priority_queue<Pair> q;
	for(int i=0;i<IDX.size();i++)
	{
		if(INSTED[i])q.push((Pair){INSTIME[i],i});
	}
	while(!q.empty())
	{
		Pair u=q.top();q.pop();
		printf("   %s\n",NAME[u.y].c_str());
	}
}
bool readline()
{
	char tstr[81];
	if(!fgets(tstr,81,stdin))return false;
	printf("%s",tstr);
	if(cmpstr(tstr,"END",3))init();
	else if(cmpstr(tstr,"DEPEND",6))adddepend(tstr+6);
	else if(cmpstr(tstr,"INSTALL",7))install(tstr+7);
	else if(cmpstr(tstr,"REMOVE",6))remove(tstr+6);
	else if(cmpstr(tstr,"LIST",4))list();
	return true;
}
int main()
{
	freopen("in.txt","r",stdin);
	init();
	while(readline());
	return 0;
}
