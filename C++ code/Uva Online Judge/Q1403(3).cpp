#include<cstdio>
#include<stack>
#include<cassert>
using namespace std;
const double EPS=1e-9;
char EQUATION[1000000];
int RBRACK[1000000];
bool Digit(const char c){return c>='0'&&c<='9';}
struct Node
{
	Node *ch[2];
	char o;
	double val;
	Node(){}
	Node(int l,int r):ch{NULL,NULL}
	{
		while(EQUATION[l]=='('&&RBRACK[l]==r)l++,r--;
		assert(EQUATION[l]!='('||RBRACK[l]<r);
		int result=0,loc=-1;
		for(int i=RBRACK[l]+1;i<=r;i=RBRACK[i+1]+1)
		{
			switch(EQUATION[i])
			{
				case'(':
				case')':printf("EQUATION[%d]=%c\n",i,EQUATION[i]),assert(0);break;
				case'+':
				case'-':
					if(result<2)result=2,loc=i;
					break;
				case'*':
				case'/':
					if(result<1)result=1,loc=i;
					break;
			}
		}
		if(result==0)ReadNumber(l,r);
		else
		{
			o=EQUATION[loc];
			ch[0]=new Node(l,loc-1);
			ch[1]=new Node(loc+1,r);
		}
	}
	void ReadNumber(const int l,const int r)
	{
		if(EQUATION[l]=='x')assert(l==r),o='x';
		else
		{
			o='d';
			val=0.0;
			int dotloc;
			for(dotloc=l;dotloc<=r&&EQUATION[dotloc]!='.';dotloc++);
			for(int i=l;i<dotloc;i++)
			{
				assert(Digit(EQUATION[i]));
				val=val*10.0+(EQUATION[i]-'0');
			}
			double tmp=0.1;
			for(int i=dotloc+1;i<=r;i++,tmp*=0.1)
			{
				assert(Digit(EQUATION[i]));
				val+=tmp*(EQUATION[i]-'0');
			}
		}
	}
	void Print()
	{
		switch(o)
		{
			case'+':case'-':case'*':case'/':
			{
				putchar('('),ch[0]->Print(),putchar(')');
				putchar(o);
				putchar('('),ch[1]->Print(),putchar(')');
			}break;
			case'x':putchar(o);break;
			case'd':printf("%.4f",val);break;
		}
	}
	double GetValue(const double &x)
	{
		switch(o)
		{
			case'x':return x;
			case'd':return val;
			case'+':return ch[0]->GetValue(x)+ch[1]->GetValue(x);
			case'-':return ch[0]->GetValue(x)-ch[1]->GetValue(x);
			case'*':return ch[0]->GetValue(x)*ch[1]->GetValue(x);
			case'/':return ch[0]->GetValue(x)/ch[1]->GetValue(x);
			default:assert(0);
		}
	}
}*NR,*NT;
double H,B;
int main()
{
	freopen("in.txt","r",stdin);
	while(scanf("%lf%lf",&H,&B)==2&&!(H==0&&B==0))
	{
		for(int type=0;type<=1;type++)
		{
			scanf("%s",&EQUATION);
			static int len;
			stack<int>stk;
			RBRACK[0]=-1;
			for(len=0;EQUATION[len];len++,RBRACK[len]=len-1)
			{
				switch(EQUATION[len])
				{
					case'(':stk.push(len);break;
					case')':RBRACK[stk.top()]=len;stk.pop();break;
				}
			}
			assert(stk.empty());
			(type==0?NR:NT)=new Node(0,len-1);
		}
//		NR->Print();putchar('\n');
//		NT->Print();putchar('\n');
//		puts("pass");
	}
	return 0;
}
