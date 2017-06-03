#include<cstdio>
#include<cstdlib>
#include<string>
#include<map>
#include<vector>
using namespace std;
int n,m,ans,T,vis[25][25];//from, now at: to where
char char1[100],char2[100];
string name1,name2;
map<string,int> inde;
map<int,string> namecollect;
vector<int> group[25];
int parent[25];
bool call[25][25];
map<int,int> A;//state, ans
void showbit(int a)
{
	for(int i=0;i<n;i++)
	{
		printf("%d",a%2);
		a/=2;
	}
}
void searchdown(int a,int b,int c)//from, now at, meeted
{
	c|=(1<<b);
	if(c==parent[b]) return;
	parent[b]|=c;
	//showbit(parent[b]);printf(" %d\n",b);
	for(int i=0;i<n;i++)
	{
		if(call[b][i])
		{
			searchdown(a,i,parent[b]);
		}
	}
}
int main()
{
	//freopen("in.txt","r",stdin);
	T=1;
	while(scanf("%d%d",&n,&m)==2)
	{
		if(n==0&&m==0) break;
		inde.clear();
		namecollect.clear();
		A.clear();
		ans=0;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				call[i][j]=false;
				vis[i][j]=-1;
			}
			group[i].clear();
			parent[i]=0;
		}
		for(int i=0;i<m;i++)
		{
			scanf("%s%s",char1,char2);
			name1=char1;
			name2=char2;
			if(inde.find(name1)==inde.end())
			{
				inde[name1]=inde.size()-1;
				namecollect[inde.size()-1]=name1;
			}
			if(inde.find(name2)==inde.end())
			{
				inde[name2]=inde.size()-1;
				namecollect[inde.size()-1]=name2;
			}
			call[inde[name1]][inde[name2]]=true;
		}
		for(int i=0;i<n;i++)
		{
			//printf("%d %d\n",n,i);
			searchdown(i,i,0);
		}
		for(int i=0;i<n;i++)
		{
			if(A.find(parent[i])==A.end())
			{
				A[parent[i]]=A.size()-1;
				ans++;
			}
			group[A[parent[i]]].push_back(i);
		}
		if(T>1) printf("\n");
		printf("Calling circles for data set %d:\n",T++);
		for(int i=0;i<ans;i++)
		{
			printf("%s",namecollect[group[i][0]].c_str());
			for(int j=1;j<group[i].size();j++)
			{
				printf(", %s",namecollect[group[i][j]].c_str());
			}
			printf("\n");
		}
	}
	return 0;
}
