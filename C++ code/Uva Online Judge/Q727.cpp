#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
char in[1000000];
int T;
vector<char> v;
int next(int a)
{
	if(v[a]!='(') return -1;
	int now=0;
	do
	{
		if(v[a]=='(') now++;
		else if(v[a]==')') now--;
		a++;
	}while(now>0);
	return a;
}
bool iso(char a)
{
	switch(a)
	{
		case'+':
		case'-':
		case'*':
		case'/':
			return true;
	}
	return false;
}
bool isnum(char a)
{
	return a>='0'&&a<='9';
}
void show(int a,int b)
{
	for(int i=a;i<=b;i++) printf("%c",v[i]);printf("\n");
}
struct node
{
	int o,n1,n2;//o is index of operator
	node *ch[2];
	node(int a,int b)
	{
		//show(a,b);
		ch[0]=ch[1]=NULL;
		o=-1;
		if(a==b)
		{
			n1=n2=a;
			return;
		}
		n1=a,n2=b;
		if(isnum(v[a])&&v[a+1]=='(')
		{
			ch[0]=new node(a,a);
			int c=a+1,d=b;
			while(next(c)==d+1) c++,d--;
			ch[1]=new node(c,d);
			return;
		}
		if(v[a]=='(')
		{
			int i=next(a);
			if(i<=b&&!iso(v[i]))
			{
				int c=a,d=i-1;;
				while(next(c)==d+1) c++,d--;
				ch[0]=new node(c,d);
				c=i,d=b;
				while(next(c)==d+1) c++,d--;
				ch[1]=new node(c,d);
				return;
			}
		}
		for(int i=a;i<=b;i++)
		{
			while(i<=b&&v[i]=='(')
			{
				i=next(i);
			}
			if(i>b) break;
			switch(v[i])
			{
				case'+':
				case'-':
					{
						o=i;
						int c=a,d=i-1;
						while(next(c)==d+1) c++,d--;
						ch[0]=new node(c,d);
						c=i+1,d=b;
						while(next(c)==d+1) c++,d--;
						ch[1]=new node(c,d);
						return;
					}
			}
		}
		for(int i=a;i<=b;i++)
		{
			while(i<=b&&v[i]=='(')
			{
				i=next(i);
			}
			if(i>b) break;
			switch(v[i])
			{
				case'*':
				case'/':
					{
						o=i;
						int c=a,d=i-1;
						while(next(c)==d+1) c++,d--;
						ch[0]=new node(c,d);
						c=i+1,d=b;
						while(next(c)==d+1) c++,d--;
						ch[1]=new node(c,d);
						return;
					}
			}
		}
		printf("error\n");
		ch[0]=new node(a,a);
		ch[1]=new node(a+1,b);
	}
	void print()
	{
		//printf("\n%d %d\n",n1,n2);
		if(n1==n2)
		{
			printf("%c",v[n1]);
			return;
		}
		ch[1]->print();
		ch[0]->print();
		if(o!=-1) printf("%c",v[o]);
	}
};
int main()
{
	//freopen("in.txt","r",stdin);
	fgets(in,1000000,stdin);
	sscanf(in,"%d",&T);
	//printf("%d\n",T);
	int t=0;
	fgets(in,1000000,stdin);
	while(T--)
	{
		char c;
		while(fgets(in,1000000,stdin)&&in[0]!='\n') v.push_back(in[0]);
		if(t++) printf("\n");
		if(v.size())
		{
			int c=0,d=v.size()-1;
			for(int i=0;i<=(d-c)/2;i++)
			{
				char b=v[c+i];
				v[c+i]=v[d-i];
				v[d-i]=b;
			}
			for(int i=0;i<=d;i++)
			{
				if(v[i]=='(') v[i]=')';
				else if(v[i]==')') v[i]='(';
			}
			while(next(c)==d+1) c++,d--;
			node *a=new node(c,d);
			a->print();
		}
		printf("\n");
		v.clear();
	}
	return 0;
}
