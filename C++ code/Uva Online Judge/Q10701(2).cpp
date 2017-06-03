#include<cstdio>
#include<cstdlib>
int n,n1,n2;
char S1[53],S2[53];
struct node
{
	char s,momc;
	node *ch[2];
	node(char momc):momc(momc)
	{
		s=0;
		ch[0]=ch[1]=NULL;
	}
	void scan()
	{
		//printf("%c",S1[n1]);
		s=S1[n1];//n1==this
		n1++;
		if(!S1[n1]) return;
		//n1==right||left(if no right, then n2 must==this)
		if(S2[n2]==s)//no right
		{
			n2++;
			if(!S2[n2]) return;
			//n2==mom||left(else)
			if(S2[n2]==momc) return;
			ch[1]=new node(momc);
			ch[1]->scan();
			return;
		}
		ch[0]=new node(s);
		ch[0]->scan();
		if(!S1[n1]) return;
		//n2 must==this
		n2++;
		if(!S2[n2]) return;
		if(S2[n2]!=momc)//has right
		{
			ch[1]=new node(momc);
			ch[1]->scan();
		}
		return;
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
		node *a=new node(0);
		a->scan();
		/*a->print(0);
		printf("\n");
		a->print(1);
		printf("\n");*/
		a->print(2);
		printf("\n");
		//printf("\n%s %s\n",S1,S2);
	}
	return 0;
}
