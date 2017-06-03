#include<cstdio>
#include<cstdlib>
#include<vector>
#include<map>
using namespace std;
vector<int> connect[30];
vector<int> group[30];
bool grouped[30];
int start,strict,T,n,m;
double mom;
map<vector<int>,double> state;
void dfs(int a,int b)
{
	if(grouped[a]) return;
	grouped[a]=true;
	if(a==1) start=b;
	group[b].push_back(a);
	for(int i=0;i<connect[a].size();i++)
	{
		dfs(connect[a][i],b);
	}
}
vector<int> range(vector<int> a)
{
	for(int i=0,j,k;i<a.size();i++)//sort
	{
		for(k=i,j=i+1;j<a.size();j++)
		{
			if(a[j]<a[k]) k=j;
		}
		j=a[k];
		a[k]=a[i];
		a[i]=j;
	}
	return a;
}
void showvector(vector<int> a)
{
	printf("vector:");
	for(int i=0;i<a.size();i++) printf("%d ",a[i]);printf("\n");
}
double dfs(vector<int> a,int path)
{//{2,3}=(1/6){2,3}+(2/6){3}+(3/6){2}+1
//(5/6){2,3}=(2/6){3}+(3/6){2}+1
	if(a.size()==0) return 0;//0 step
	if(state.find(a)!=state.end()) return state[a];
	int b=n;//chance to stay
	for(int i=0;i<a.size();i++) b-=a[i];
	b--;
	//(b/mom)*(this)=(for all x)a-a[x]+1
	double ans=1;
	for(int i=0,j;i<a.size();i++)
	{
		j=a[i];
		a[i]=a[a.size()-1];
		a.pop_back();
		a=range(a);
		//showvector(a);
		//printf("%llf\n",dfs(a,path+1));
		ans+=dfs(a,path+1)*j/mom;
		a.push_back(j);
		a=range(a);
	}
	state[a]=ans*mom/(mom-b);
	return state[a];
}
int main()
{
	//freopen("in.txt","r",stdin);
	scanf("%d",&T);
	for(int t=1;t<=T;t++)
	{
		scanf("%d%d",&n,&m);
		for(int i=0;i<=n;i++)
		{
			connect[i].clear();
			group[i].clear();
			grouped[i]=false;
		}
		for(int i=0;i<m;i++)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			connect[a].push_back(b);
			connect[b].push_back(a);
		}
		strict=0;
		start=-1;
		for(int i=1;i<=n;i++)
		{
			if(!grouped[i])
			{
				dfs(i,strict);
				strict++;
			}
		}
		mom=n-1;
		state.clear();
		vector<int> tmp;
		tmp.clear(); 
		for(int i=0;i<strict;i++)
		{
			if(i!=start) tmp.push_back(group[i].size());
		}
		tmp=range(tmp);
		//printf("%d %d\n",start,strict);
		//showvector(tmp);
		//printf("%llf\n",dfs(tmp,0));
		double ans=dfs(tmp,0);
		printf("Case %d: %.6lf\n",t,ans);
	}
	return 0;
}
