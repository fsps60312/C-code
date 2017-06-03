#include<cstdio>
#include<cstdlib>
#include<string>
#include<map>
#include<vector> 
using namespace std;
struct persontype
{
	int parent;
	int inde;
	int vis1;
	int vis2;
};
char char1[200],char2[200];
string name1,name2;
map<string,int> inde;
vector<persontype> S;
void printparent(int a)
{
	if(a==1) printf("parent\n");
	else
	{
		for(int i=3;i<=a;i++) printf("great ");
		printf("grand parent\n");
	}
}
void printchild(int a)
{
	if(a==1) printf("child\n");
	else
	{
		//printf("%d\n",a);
		for(int i=3;i<=a;i++) printf("great ");
		printf("grand child\n");
	}
}
void printcousin(int a,int b)
{
	printf("%d cousin",a-1);
	if(b>0) printf(" removed %d",b);
	printf("\n");
}
void showans(int a,int b)
{
	if(a==0)
	{
		//printf("%dparent\n",b);
		printparent(b);
		return;
	}
	if(b==0)
	{
		//printf("%dchild\n",a);
		printchild(a);
		return;
	}
	if(a==1&&b==1)
	{
		printf("sibling\n");
		return;
	}
	printcousin(a<b?a:b,a>b?a-b:b-a);//th,removed
}
int main()
{
	//freopen("in.txt","r",stdin);
	inde.clear();
	S.clear();
	while(scanf("%s%s",char1,char2)==2)
	{
		//printf("%s %s\n",char1,char2);
		name1=char1;
		name2=char2;
		if(name1=="no.child") break;
		if(inde.find(name1)==inde.end())
		{
			//printf("%d %d\n",inde.size(),S.size());
			inde[name1]=inde.size()-1;
			persontype i;
			i.inde=S.size();
			i.parent=-1;
			i.vis1=-1;
			S.push_back(i);
		}
		if(inde.find(name2)==inde.end())
		{
			//printf("%d %d\n",inde.size(),S.size());
			inde[name2]=inde.size()-1;
			persontype i;
			i.inde=S.size();
			i.parent=-1;
			i.vis1=-1;
			S.push_back(i);
		}
		S[inde[name1]].parent=inde[name2];
	}
	//for(int i=0;i<S.size();i++) printf("%d %d\n",i,S[i].parent);
	for(int T=0;scanf("%s%s",char1,char2)==2;T++)
	{
		//printf("%s %s\n",char1,char2);
		name1=char1;
		name2=char2;
		int a;
		if(inde.find(name1)!=inde.end()) a=inde[name1];
		else
		{
			printf("no relation\n");
			continue;
		}
		//printf("%d ",a);
		for(int i=0;a!=-1;i++)
		{
			S[a].vis1=T;
			S[a].vis2=i;
			a=S[a].parent; 
		}
		if(inde.find(name2)!=inde.end())a=inde[name2];
		else
		{
			printf("no relation\n");
			continue;
		}
		//printf("%d\n",a);
		bool printed=false;
		for(int i=0;a!=-1;i++)
		{
			if(S[a].vis1==T)
			{
				//printf("%d %d\n",S[a].vis2,i);
				showans(S[a].vis2,i);
				printed=true;
				break;
			}
			a=S[a].parent;
		}
		if(!printed) printf("no relation\n");
	}
	return 0;
}
