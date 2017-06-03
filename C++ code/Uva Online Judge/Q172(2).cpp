#include<cstdio>
#include<cstdlib>
#include<map>
#include<string>
using namespace std;
char S[1000];
int n;
struct pairtype
{
	int x,y;
};
map<string,pairtype> M;
pairtype newpair(int a,int b)
{
	pairtype c;
	c.x=a,c.y=b;
	return c;
}
bool isnum(char a){return a>='0'&&a<='9';}
bool isupper(char a){return a>='A'&&a<='Z';}
int next(int a)
{
	int now=0;
	do
	{
		if(S[a]==')') now++;
		else if(S[a]=='(') now--;
		a--;
	}while(now>0);
	return a;
}
void show(int a,int b){for(int i=a;i<=b;i++)printf("%c",S[i]);printf("\n");}
int ttt=0;
int cal(int a,int b,int n3,char o1)
{
	//if(ttt++>10) return 0;
	//printf("n3=%c%d\t",o1,n3);show(a,b);
	while(S[b]==' ') b--;
	int n2;
	char o;
	if(S[b]==')')
	{
		int c=b;
		b=next(b);
		n2=cal(b+2,c-1,0,'+');
	}
	else if(isnum(S[b]))
	{
		int c=b;
		while(b>=a&&isnum(S[b])) b--;
		n2=0;
		for(int i=b+1;i<=c;i++)
		{
			n2*=10;
			n2+=S[i]-'0';
		}
	}
	else
	{
		int c=b;
		while(isupper(S[b])) b--;
		string s;
		s.assign(S,b+1,c-b);
		//printf("s is %s\n",s.c_str());
		if(M.find(s)==M.end()) M[s]=newpair(0,0);
		if(o1=='=') M[s].x=n3;
		n2=M[s].x;
	}
	if(S[b]=='_')
	{
		n2*=-1;
		b--;
	}
	switch(o1)
	{
		case'+':n2+=n3;break;
		case'-':n2-=n3;break;
		case'*':n2*=n3;break;
		case'/':n2/=n3;break;
	}
	while(b>=a&&S[b]==' ') b--;
	if(b<a)
	{
		return n2;
	}
	o=S[b];b--;
	while(S[b]==' ') b--;
	return cal(a,b,n2,o);
}
int main()
{
	//freopen("in.txt","r",stdin);
	while(fgets(S,1000,stdin))
	{
		ttt=0;
		//printf("\"%s\"\n",S);
		if(S[0]=='#')
		{
			//printf("break\n");
			break;
		}
		n=-1;while(S[++n]&&S[n]!='\n');
		cal(0,n-1,0,'+');
		int t=0;
		for(map<string,pairtype>::iterator i=M.begin();i!=M.end();i++)
		{
			pairtype j=i->second;
			if(j.x!=j.y)
			{
				M[i->first].y=j.x;
				if(t++) printf(", ");
				printf("%s = %d",i->first.c_str(),j.x);
			}
		}
		if(!t) printf("No Change\n");
		else printf("\n");
	}
	return 0;
}
