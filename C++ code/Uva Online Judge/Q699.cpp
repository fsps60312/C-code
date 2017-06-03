#include<cstdio>
#include<cstdlib>
#include<map>
using namespace std;
map<int,int> ans;
struct node
{
	int s,v;
	node *ch[2];
	node(int v):v(v)
	{
		s=0;
		ch[0]=ch[1]=NULL;
	}
	int scan()
	{
		scanf("%d",&s);
		if(s==-1) return 0;
		if(ans.find(v)==ans.end()) ans[v]=0;
		ans[v]+=s;
		//printf(" %d\n",ans[v]);
		ch[0]=new node(v-1);
		ch[0]->scan();
		ch[1]=new node(v+1);
		ch[1]->scan();
		return 1;
	}
};
int main()
{
	node* n=new node(0);
	int T=1;
	while(n->scan())
	{
		printf("Case %d:\n",T++);
		int j=0;
		for(map<int,int>::iterator i=ans.begin();i!=ans.end();i++)
		{
			if(j) printf(" ");
			printf("%d",i->second);
			j++;
		}
		printf("\n\n");
		ans.clear();
	}
	return 0;
}
