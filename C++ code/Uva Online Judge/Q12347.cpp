#include<cstdio>
#include<cstdlib>
int S[10001],n=-1,n1=0;
struct node
{
	int v,Max;
	node *ch[2];
	node(int Max):Max(Max){ch[0]=ch[1]=NULL;}
	void scan()
	{
		v=S[n1];
		n1++;
		if(n1==n) return;
		if(S[n1]<v)
		{
			ch[0]=new node(v);
			ch[0]->scan();
			if(n1==n) return;
		}
		if(S[n1]<Max&&S[n1]>v)
		{
			ch[1]=new node(Max);
			ch[1]->scan();
		}
	}
	void print()
	{
		if(ch[0]) ch[0]->print();
		if(ch[1]) ch[1]->print();
		printf("%d\n",v);
	}
};
int main()
{
	//freopen("in.txt","r",stdin);
	while(scanf("%d",&S[++n])==1);
	node *a=new node(2147483647);
	a->scan();
	if(n>0) a->print();
	//printf("done\n");
	return 0;
}
