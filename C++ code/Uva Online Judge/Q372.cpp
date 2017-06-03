#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
char str1[1000000],str2[1000000];
int n1,n2;
vector<int> in,pre;
struct node
{
	char v,mom;
	node *ch[2];
	node(char mom):mom(mom){ch[0]=ch[1]=NULL;}
	void scan()
	{
		v=pre[n1];
		n1++;if(n1==pre.size()) return;
		if(in[n2]==v)//left tree over
		{
			n2++;if(n2==in.size()) return;
			if(in[n2]==mom) return;//no right;
			ch[1]=new node(mom);
			ch[1]->scan();
			return;
		}
		ch[0]=new node(v);
		ch[0]->scan();
		//n2 must==v
		if(n1==pre.size()) return;
		n2++;if(n2==in.size()) return;
		if(in[n2]==mom) return;
		ch[1]=new node(mom);
		ch[1]->scan();
	}
	void print(int a)
	{
		if(a==0) printf(" %c",v);
		if(ch[0])ch[0]->print(a);
		if(a==1) printf(" %c",v);
		if(ch[1])ch[1]->print(a);
		if(a==2) printf(" %c",v);
	}
};
int main()
{
	//freopen("in.txt","r",stdin);
	fgets(str1,1000000,stdin);
	fgets(str2,1000000,stdin);
	n1=n2=-1;
	while(str1[++n1])if(str1[n1]!=' '&&str1[n1]!='\n') in.push_back(str1[n1]);
	while(str2[++n2])if(str2[n2]!=' '&&str2[n2]!='\n') pre.push_back(str2[n2]);
	//for(int i=0;i<in.size();i++) printf("%c",in[i]);printf("\n");
	//for(int i=0;i<pre.size();i++) printf("%c",pre[i]);printf("\n");
	n1=n2=0;
	node *a=new node(0);
	a->scan();
	printf("INFIX   =>");
	a->print(1);
	printf("\nPREFIX  =>");
	a->print(0);
	printf("\nPOSTFIX =>");
	a->print(2);
	printf("\n");
	return 0;
}
