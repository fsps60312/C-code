#include<cstdio>
//#include<stack>
using namespace std;
char S[1000000];
int N,IDX;
int R[1000000];
bool Digit(const char c){return c>='0'&&c<='9';}
bool Valid(const char c){return c=='('||c=='.'||Digit(c);}
double GetValue(int l)
{
	while(Valid(S[l]))l++;
	double p;
	sscanf(S+l,"%lf",&p);
	if(S[l]!='(')return p;
	else
	{
		double a,b;
		while(S[l]!='(')l++;
		a=GetValue(l+1,R[l]-1);
		l=R[l];
		while(S[l])
	}
}
int main()
{
	while(scanf("%s",S)==1)
	{
		N=-1;while(S[++N])R[N]=-1;
		stack<int>stk;
		for(int i=0;i<N;i++)
		{
			if(S[i]=='(')stk.push(i);
			else if(S[i]==')')R[stk.top()]=i,stk.pop();
		}
		printf("%.2f\n",GetValue());
	}
	return 0;
}
