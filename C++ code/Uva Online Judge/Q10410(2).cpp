#include<cstdio>
#include<cstdlib>
int index[1001],reind[1001],v2[1001],order[1001],depth[1001],n1,n;
struct node
{
	int v;
	node *ch[2];
	node(){v=-1;}
	void scan(int dep)
	{
		if(n1>n) return;
		if(depth[n1]!=dep) return;
		v=reind[n1];
		n1++;
		ch[0]=new node();
		ch[0]->scan(dep+1);
		ch[1]=new node();
		ch[1]->scan(dep+1);
	}
	void print()
	{
		if(v==-1) return;
		printf("%d:",v);
		if(ch[0]->v!=-1) printf(" %d",ch[0]->v);
		if(ch[1]->v!=-1) printf(" %d",ch[1]->v);
		printf("\n");
		ch[0]->print();
		ch[1]->print();
	}
};
int main()
{
	freopen("in.txt","r",stdin);
	depth[0]=v2[0]=0;
	while(scanf("%d",&n)==1)
	{
		for(int i=1,j;i<=n;i++)
		{
			depth[i]=i;
			scanf("%d",&j);
			index[j]=i;
			reind[i]=j;
		}
		for(int i=1,j;i<=n;i++)
		{
			scanf("%d",&j);
			v2[i]=index[j];
			order[index[j]]=i;
		}
		for(int i=1;i<=n;i++)
		{
			int j=order[i];//index of v2
			//printf(" %d",v2[j]);
			if(depth[i]>depth[i-1]+1) depth[i]=depth[i-1]+1;
			if(j+1<n)
			{
				//depth[v2[j]] should <= depth[v2[j+1]]
				if(depth[v2[j]]>depth[v2[j+1]]) depth[v2[j]]=depth[v2[j+1]];
				if(depth[v2[j+1]]>depth[v2[j]]+1) depth[v2[j+1]]=depth[v2[j]]+1;
			}
		}//printf("\n");
		for(int i=1;i<=n;i++) printf(" %d",reind[i]);printf(" reind\n");
		for(int i=1;i<=n;i++) printf(" %d",index[i]);printf(" index\n");
		for(int i=1;i<=n;i++) printf(" %d",depth[i]);printf(" depth\n");
		for(int i=1;i<=n;i++) printf(" %d",v2[i]);printf(" v2\n");
		for(int i=1;i<=n;i++) printf(" %d",order[i]);printf(" order\n");
		n1=1;
		node *a=new node();
		a->scan(1);
		a->print();
	} 
	return 0;
}
