#include<cstdio>
#include<cstdlib>
#include<queue>
using namespace std;
int ans;
char S[1000];
bool norewrite;
struct node
{
	int s;
	node *ch[2];
	node()
	{
		s=-1;
		ch[0]=ch[1]=NULL;
	}
	void push(int a,int b)
	{
		//printf("%c",S[b]);
		switch(S[b])
		{
			case ')':
				{
					if(s!=-1) norewrite=false;
					s=a;
					return;
				}
			case 'L':
				{
					if(ch[0]==NULL) ch[0]=new node();
					ch[0]->push(a,b+1);
				}break;
			case 'R':
				{
					if(ch[1]==NULL) ch[1]=new node();
					ch[1]->push(a,b+1);
				}break;
		}
	}
	bool iscomplete()
	{
		if(s==-1) return false;
		if(ch[0]==NULL)
		{
			if(ch[1]==NULL) return true;
			return ch[1]->iscomplete();
		}
		else
		{
			if(ch[1]==NULL) return ch[0]->iscomplete();
			return ch[0]->iscomplete()&&ch[1]->iscomplete();
		}
	}
	/*void print()
	{
		if(ans) printf(" ");
		ans++;
		printf("%d",s);
		if(ch[0]!=NULL) ch[0]->print();
		if(ch[1]!=NULL) ch[1]->print();
	}*/
};
bool isnum(char a)
{
	return a>='0'&&a<='9';
}
int main()
{
	norewrite=true;
	node *a=new node();
	while(scanf("%s",S)==1)
	{
		int n=0,i=0;
		while(!isnum(S[i])&&S[i]) i++;
		while(isnum(S[i])&&S[i])
		{
			n*=10;
			n+=S[i]-'0';
			i++;
		}
		while(S[i]!=','&&S[i]) i++;
		while(S[i]==','&&S[i]) i++;
		if(!S[i])
		{
			if(norewrite&&a->iscomplete())
			{
				ans=0;
				queue<node> q;
				if(a!=NULL) q.push(*a);
				while(!q.empty())
				{
					node tmp=q.front();
					q.pop();
					if(ans) printf(" ");
					ans++;
					printf("%d",tmp.s);
					if(tmp.ch[0]) q.push(*tmp.ch[0]);
					if(tmp.ch[1]) q.push(*tmp.ch[1]);
				}
				printf("\n");
			}
			else printf("not complete\n");
			a=new node();
			norewrite=true;
		}
		else a->push(n,i);
	}
	return 0;
}
