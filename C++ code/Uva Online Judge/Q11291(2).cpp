#include<cstdio>
#include<cassert>
using namespace std;
char S[1000000];
int N,IDX;
bool Digit(const char c){return c>='0'&&c<='9';}
bool Valid(const char c){return c=='('||c=='.'||c=='-'||Digit(c);}
double GetDouble()
{
	assert(S[IDX++]=='.');
	double ans=0.0;
	for(double d=0.1;Digit(S[IDX]);ans+=d*(S[IDX]-'0'),IDX++,d*=0.1);
	return ans;
}
double GetValue()
{
	while(!Valid(S[IDX]))IDX++;
	double sign=1.0;
	if(S[IDX]=='-')sign=-1.0,IDX++;
	if(Digit(S[IDX]))
	{
//		puts("a");
		double ans=0.0;
		while(Digit(S[IDX]))ans*=10.0,ans+=S[IDX]-'0',IDX++;
		if(S[IDX]=='.')ans+=GetDouble();
		return ans*sign;
	}
	else if(S[IDX]=='.')return GetDouble()*sign;
	else
	{
		assert(sign==1.0);
		IDX++;
		double p=GetValue(),a=GetValue(),b=GetValue();
		return p*(a+b)+(1.0-p)*(a-b);
	}
}
int main()
{
//	freopen("in.txt","r",stdin);
	for(;;)
	{
		fgets(S,1000000,stdin);
		N=-1;while(S[++N])if(S[N]=='\n'){S[N]='\0';break;}
		if(S[0]=='('&&S[1]==')'&&N==2)break;
//		puts(S);
		IDX=0;
		printf("%.2f\n",GetValue());
	}
	return 0;
}
