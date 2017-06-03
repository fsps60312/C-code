#include<cstdio>
#include<cstdlib>
#include<map>
#include<string>
using namespace std;
char S[101];
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
		if(a==')') now++;
		else if(a=='(') now--;
		a++;
	}while(now>0);
	return a;
}
int cal(int a,int b)
{
	while(S[b]==' ') b--;
	int n1,n2;
	char o;
	if(S[b]==')')
	{
		int c=b;
		b=next(b);
		n2=cal(b+2,c-1);
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
		if(M.find(s)==M.end()) M[s]=newpair(0,0);
		n2=M[s].x;
	}
	if(S[b]=='_')
	{
		n2*=-1;
		b--;
	}
	while(b>=a&&S[b]==' ') b--;
	if(b<a) return n2;
	o=S[b];b--;
	while(S[b]==' ') b--;
	n1=cal(a,b);
	switch(o)
	{
		case'+':return n1+n2;
		case'-':return n1-n2;
		case'*':return n1*n2;
		case'/':return n1/n2;
		default:
		{
			int c=b;
			while(isupper(S[b])) b--;
			string s;
			s.assign(S,b+1,c-b);
			M[s].x=n2;
		}
	}
}
int main()
{
	freopen("in.txt","r",stdin);
	while(fgets(S,101,stdin))
	{
		if(S[0]=='#'&&S[1]==0) break;
		n=-1;while(S[++n]&&S[n]!='\n');
		cal(0,n-1);
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
