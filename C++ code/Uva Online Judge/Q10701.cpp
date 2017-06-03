#include<cstdio>
#include<cstdlib>
int n,n1,n2;
char S1[53],S2[53];
struct node
{
	char s;
	node *ch[2];
	node()
	{
		s=0;
		ch[0]=ch[1]=NULL;
	}
	void scan()
	{
		//printf("%c",S1[n1]);
		s=S1[n1];
		n1++;
		if(S2[n2]==s)
		{
			n2++;
			return;
		}
		if(!S1[n1]) return;
		ch[0]=new node();
		//printf("%d",n1);
		ch[0]->scan();
		if(S2[n2])
		ch[1]=new node();
		//printf("%d",n1);
		ch[1]->scan();
	}
	void print(int a)
	{
		if(a==0) printf("%c",s);
		if(ch[0]) ch[0]->print(a);
		if(a==1) printf("%c",s);
		if(ch[1]) ch[1]->print(a);
		if(a==2) printf("%c",s);
	}
};
int C;
int main()
{
	scanf("%d",&C);
	while(C--)
	{
		scanf("%d%s%s",&n,S1,S2);
		n1=n2=0;
		node *a=new node();
		a->scan();
		a->print(0);
		printf("\n");
		a->print(1);
		printf("\n");
		a->print(2);
		printf("\n");
		//printf("\n%s %s\n",S1,S2);
	}
	return 0;
}
