#include<cstdio>
#include<cstdlib>
#include<vector>
using namespace std;
char S1[100000],S2[100000];
vector<int> v1,v2;//v1:M->R->L,v2:R->M->L
int n1,n2;
struct node
{
	int v,mom,sumv,leaf;//mom:first turn left point on the way to root
	node *ch[2];
	node(int mom):mom(mom)
	{
		v=-1;
		ch[0]=ch[1]=NULL;
	}
	void scan()
	{
		//v2:[left][right][main]
		//v1:[left][main][right]
		v=sumv=leaf=v2[n2];
		n2--;
		if(n2<0) return;
		//v2:[left:[left][right][main]][right:[left][right][main]]
		//v1:[left][main][right]
		if(v1[n1]==v)//no right
		{
			//v2:[left:[left][right][main]]
			//v1:[left:[left][main][right]][main]
			n1--;
			if(n1<0||v1[n1]==mom)//no left
			{
				return;
			}
			//v2:[left:[left][right][main]]
			//v1:[left:[left][main][right]]
			ch[0]=new node(mom);
			ch[0]->scan();
			sumv+=ch[0]->sumv;
			leaf=ch[0]->leaf;
			return;
		}
		//v2:[left:[left][right][main]][right:[left][right][main]]
		//v1:[left][main][right:[left][main][right]]
		ch[1]=new node(v);
		ch[1]->scan();
		//n1==this
		//v2:[left:[left][right][main]]
		//v1:[left][main]
		n1--;
		if(n1<0||n2<0||v1[n1]==mom)//no left
		{
			sumv+=ch[1]->sumv;
			leaf=ch[1]->leaf;
			return;
		}
		//v2:[left:[left][right][main]]
		//v1:[left:[left][main][right]]
		ch[0]=new node(mom);
		ch[0]->scan();
		if(ch[0]->sumv<ch[1]->sumv)
		{
			sumv+=ch[0]->sumv;
			leaf=ch[0]->leaf;
		}
		else
		{
			sumv+=ch[1]->sumv;
			leaf=ch[1]->leaf;
		}
	}
	void print(int a)
	{
		if(a==0) printf(" %d",v);
		if(ch[0]) ch[0]->print(a);
		if(a==1) printf(" %d",v);
		if(ch[1]) ch[1]->print(a);
		if(a==2) printf(" %d",v);
	}
};
bool isnum(char a){return a>='0'&&a<='9';}
int main()
{
	while(fgets(S1,100000,stdin)&&fgets(S2,100000,stdin))
	{
		v1.clear();
		v2.clear();
		int n=0;
		while(S1[n]&&!isnum(S1[n])) n++;
		while(S1[n])
		{
			v1.push_back(0);
			while(S1[n]&&isnum(S1[n]))
			{
				v1[v1.size()-1]*=10;
				v1[v1.size()-1]+=S1[n]-'0';
				n++;
			}
			while(S1[n]&&!isnum(S1[n])) n++;
		}n=0;
		while(S2[n]&&!isnum(S2[n])) n++;
		while(S2[n])
		{
			v2.push_back(0);
			while(S2[n]&&isnum(S2[n]))
			{
				v2[v2.size()-1]*=10;
				v2[v2.size()-1]+=S2[n]-'0';
				n++;
			}
			while(S2[n]&&!isnum(S2[n])) n++;
		}
		//for(int i=0;i<v2.size();i++) printf(" %d\n",v2[i]);printf("\n");
		n1=n2=v1.size()-1;
		node *a=new node(-1);
		a->scan();
		//a->print(0);printf("\n");
		//a->print(1);printf("\n");
		//a->print(2);printf("\n");
		printf("%d\n",a->leaf);
	}
	return 0;
}
