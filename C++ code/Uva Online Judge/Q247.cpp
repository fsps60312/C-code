#include<cstdio>
#include<cstdlib>
#include<string>
#include<map>
#include<vector>
using namespace std;
char char1[100],char2[100];
string name1,name2;
map<string,int> inde;
map<int,string> namecollect;
bool call[25][25];
vector<int> group[25];
int n,m,ans;
bool vis[25][25];//from, visited inde
bool grouped[25];
bool searchcircle(int a,int b,int c)
{
	if(vis[a][b]) return true;
	vis[a][b]=true;
	bool insamegroup=false;
	bool circled=false;
	for(int i=0;i<n;i++)
	{
		if(call[b][i])
		{
			insamegroup=searchcircle(a,i,c);
			if(insamegroup)
			{
				circled=true;
				if(!grouped[i]) group[c].push_back(i);
				grouped[i]=true;
			}
		}
	}
	if(circled)
	{
		if(!grouped[b]) group[c].push_back(b);
		grouped[b]=true;
		return true;
	}
	else if(a==b)
	{
		if(!grouped[b]) group[c].push_back(b);
		grouped[b]=true;
		//ans++;
	}
	return false;
}
int main()
{
	freopen("in.txt","r",stdin);
	int T=1;
	while(scanf("%d%d",&n,&m)==2)
	{
		if(n==0&&m==0) break;
		inde.clear();
		namecollect.clear();
		ans=0;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				call[i][j]=false;
				vis[i][j]=false;
			}
			group[i].clear();
			grouped[i]=false;
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
			if(!grouped[i])
			{
				searchcircle(i,i,ans);
				ans++;
			}
		}
		printf("Calling circles for data set %d:%d\n",T++,ans);
		for(int i=0;i<ans;i++)
		{
			for(int j=0;j<group[i].size();j++)
			{
				printf("%s ",namecollect[group[i][j]].c_str());
			}
			printf("\n");
		}
	}
	return 0;
}
