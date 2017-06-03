#include<cstdio>
#include<vector>
using namespace std;
int T,N,T1[500],T2[500],TO[500];
struct Student
{
	int stature;
	char sex[2];
	char music[101];
	char sport[101];
	void show()
	{
		printf("%d %s %s %s\n",stature,sex,music,sport);
	}
};
vector<Student> BOY,GIRL;
vector<int> RD[500];
int abs(int a){return a>=0?a:-a;}
bool strcmp(char *a,char *b)
{
	while(1)
	{
		if((*a)!=(*b))return false;
		else if((*a)==0&&(*b)==0)return true;
		a++,b++;
	}
}
bool couple(Student a,Student b)
{
	if(abs(a.stature-b.stature)>40)return false;
	//if(a.sex[0]==b.sex[0])return false;
	if(!strcmp(a.music,b.music))return false;
	if(strcmp(a.sport,b.sport))return false;
	return true;
}
bool check_paired(int u)
{
	if(T1[u])return false;
	T1[u]=1;
	for(int i=0;i<RD[u].size();i++)
	{
		int &j=RD[u][i];
		if(T2[j])continue;
		T2[j]=1;
		if(TO[j]==-1||check_paired(TO[j]))
		{
			TO[j]=u;
			return true;
		}
	}
	return false;
}
int main()
{
	freopen("inn.txt","r",stdin);
	//freopen("out.txt","w",stdout); 
	scanf("%d",&T);
	while(T--)
	{
		//printf("Case %d\n",T);
		scanf("%d",&N);
		BOY.clear(),GIRL.clear();
		for(int i=0;i<N;i++)
		{
			Student a;
			scanf("%d%s%s%s",&a.stature,a.sex,a.music,a.sport);
			if(a.sex[0]=='M')BOY.push_back(a);
			else GIRL.push_back(a);
		}
		for(int i=0;i<BOY.size();i++)
		{
			RD[i].clear();
			T1[i]=0;
		}
		for(int i=0;i<GIRL.size();i++)
		{
			TO[i]=-1;
			T2[i]=0;
		}
		for(int i=0;i<BOY.size();i++)
		{
			for(int j=0;j<GIRL.size();j++)
			{
				if(couple(BOY[i],GIRL[j]))
				{
					RD[i].push_back(j);
					BOY[i].show();
					GIRL[j].show();
				}
			}
		}
		int edge_find=0;
		for(int i=0;i<BOY.size();i++)
		{
			if(check_paired(i))edge_find++;
		}
		printf("%d\n",N-edge_find);
	}
}
