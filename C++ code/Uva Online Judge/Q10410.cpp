#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
int n,n1,n2;
vector<int> v1,v2;
bool vis[1001];
struct node
{
	int v;
	node *ch[2];
	node()
	{
		ch[0]=ch[1]=NULL;
	}
	void scan()
	{
		v=v1[n1];
		vis[v]=true;
		n1++;//n1 is left
		while(vis[v2[n2]]&&n2<v2.size()) n2++;
		if(n1==v1.size()||n2==v2.size()) return;
		//n2 is left, and n1 must == n2
		ch[0]=new node();
		ch[0]->scan();
	}
};
int main()
{
	while(scanf("%d",&n)==1)
	{
		v1.clear(),v2.clear();
		for(int i=1;i<=n;i++) vis[i]=false;
		for(int i=0,j;i<n;i++)
		{
			scanf("%d",&j);
			v1.push_back(j);
		}
		for(int i=0,j;i<n;i++)
		{
			scanf("%d",&j);
			v2.push_back(j);
		}
		n1=n2=0;
		node *a=new node();
		a->scan();
	}
}
