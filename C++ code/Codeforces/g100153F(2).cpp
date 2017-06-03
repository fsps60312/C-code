#include<cstdio>
#include<cassert>
#include<string>
#include<map>
#include<set>
using namespace std;
bool IsDigitOrLetter(const char c){return ('0'<=c&&c<='9')||('a'<=c&&c<='z')||('A'<=c&&c<='Z');}
bool IsSymbol(const char c){return c=='('||c==')'||c=='{'||c=='}'||c==','||c=='+'||c=='-';}
string S;
char SkipBlanks(int &cur){while(cur<(int)S.size()&&!IsDigitOrLetter(S[cur])&&!IsSymbol(S[cur]))cur++;assert(cur<(int)S.size());return S[cur];}
string ReadName(int &cur)
{
	while(cur<(int)S.size()&&!IsDigitOrLetter(S[cur])&&!IsSymbol(S[cur]))cur++;
	if(cur==(int)S.size())return "";
	string ans="";
	while(IsDigitOrLetter(S[cur]))ans+=S[cur],cur++;
	return ans;
}
char MoveToNextSymbol(int &cur)
{
	while(!IsSymbol(S[cur]))cur++;
	return S[cur];
}
void MoveToCorrespondingBracket(int &cur)
{
	assert(S[cur]=='{'||S[cur]=='(');
	const char lc=S[cur],rc=(S[cur]=='{'?'}':')');
	for(int cnt=0;;)
	{
		if(S[cur]==lc)++cnt;
		if(S[cur]==rc)--cnt;
		if(cnt==0)return;
		else ++cur;
	}
}
void SkipOneStatement(int &cur)
{
	SkipBlanks(cur);
	if(IsDigitOrLetter(S[cur]))
	{
		if(ReadName(cur)=="if")
		{
			assert(SkipBlanks(cur)=='(');
			++cur;
			ReadName(cur);
			assert(SkipBlanks(cur)==')');
			++cur;
			SkipOneStatement(cur);
			SkipBlanks(cur);
			int c1=cur;
			if(IsDigitOrLetter(S[c1])&&ReadName(c1)=="else")
			{
				cur=c1;
				SkipOneStatement(cur);
			}
		}
		else
		{
			switch(MoveToNextSymbol(cur))
			{
				case'(':
				{
					MoveToCorrespondingBracket(cur),++cur;
					return;
				}
				case'+':
				case'-':
				{
					cur+=2;
					return;
				}
				default:assert(0);return;
			}
		}
	}
	else
	{
		assert(S[cur]=='{');
		MoveToCorrespondingBracket(cur);
		++cur;
		return;
	}
}
struct Function
{
	string NAME;
	map<string,int>PARAMETERS;
	int LOC;
	Function(){}
	Function(int &cur)
	{
		NAME=ReadName(cur);
		if(NAME==""){LOC=-1;return;}
		assert(SkipBlanks(cur)=='(');
		PARAMETERS.clear();
		for(int cnt=0;MoveToNextSymbol(cur)!=')';cnt++)
		{
			++cur;
			PARAMETERS[ReadName(cur)]=cnt;
		}
		++cur;
		LOC=cur;
		SkipOneStatement(cur);
	}
	bool GetValue(const string &parameter_name,const int parameters)const
	{
		const auto &it=PARAMETERS.find(parameter_name);
		assert(it!=PARAMETERS.end());
		return (parameters&(1<<it->second))>0;
	}
	void AddValue(const string &parameter_name,int &parameters)const
	{
		const auto &it=PARAMETERS.find(parameter_name);
		assert(it!=PARAMETERS.end());
		parameters|=1<<it->second;
	}
	void SubValue(const string &parameter_name,int &parameters)const
	{
		const auto &it=PARAMETERS.find(parameter_name);
		assert(it!=PARAMETERS.end());
		parameters&=~(1<<it->second);
	}
	void SetValue(const string &parameter_name,int &parameters,const bool value)const
	{
		if(value)AddValue(parameter_name,parameters);
		else SubValue(parameter_name,parameters);
	}
};
map<string,Function>FUNCTIONS;
map<string,map<int,int> >DDD;
bool Ddd(const Function &f,const int parameters,const int kase);
bool ExecuteSucceed(const Function &f,int cur,int &parameters,const int kase)
{
	if(IsDigitOrLetter(SkipBlanks(cur)))
	{
		const string name=ReadName(cur);
		if(name=="if")
		{
//			puts("a");
			assert(SkipBlanks(cur)=='(');
			++cur;
			const string p=ReadName(cur);
			assert(SkipBlanks(cur)==')');
			++cur;
			const bool value=f.GetValue(p,parameters);
//			puts("b");
			if(value&&!ExecuteSucceed(f,cur,parameters,kase))return false;
			SkipOneStatement(cur);
			SkipBlanks(cur);
			int c1=cur;
			if(IsDigitOrLetter(S[c1])&&ReadName(c1)=="else")
			{
				cur=c1;
				if(!value&&!ExecuteSucceed(f,cur,parameters,kase))return false;
				SkipOneStatement(cur);
			}
			return true;
		}
		else
		{
			switch(SkipBlanks(cur))
			{
				case'+':f.AddValue(name,parameters),cur+=2;return true;
				case'-':f.SubValue(name,parameters),cur+=2;return true;
				case'(':
				{
					const auto &it=FUNCTIONS.find(name);
					assert(it!=FUNCTIONS.end());
					const Function &nxtf=it->second;
					int nxtparameters=0;
					for(int cnt=0;MoveToNextSymbol(cur)!=')';cnt++)
					{
						++cur;
						if(f.GetValue(ReadName(cur),parameters))nxtparameters|=1<<cnt;
					}
					++cur;
					return !Ddd(nxtf,nxtparameters,kase);
				}
				default:printf("error=%c\n%s\n",S[cur],S.c_str()+cur);assert(0);return false;
			}
		}
	}
	else
	{
//		printf("S[cur]=%c\n",SkipBlanks(cur));
//		puts("b");
//		printf("%s\n*************************\n",S.c_str()+cur);
		assert(SkipBlanks(cur)=='{');
		for(++cur;SkipBlanks(cur)!='}';)
		{
			if(!ExecuteSucceed(f,cur,parameters,kase))return false;
			SkipOneStatement(cur);
		}
		return true;
	}
	assert(0);return false;
}
bool Ddd(const Function &f,int parameters,const int kase)
{
//	printf("In function: %s(",f.NAME.c_str());
//	for(int i=0;i<(int)f.PARAMETERS.size();i++)
//	{
//		if(i)putchar(',');
//		printf("%d",(parameters>>i)&1);
//	}
//	puts(")");
	if(DDD[f.NAME].find(parameters)!=DDD[f.NAME].end())return DDD[f.NAME][parameters]==kase;
	DDD[f.NAME][parameters]=kase;
	return !ExecuteSucceed(f,f.LOC,parameters,kase);
}
bool DfsVeryMuch()
{
	int cur=0;
	FUNCTIONS.clear();
	for(Function f=Function(cur);f.LOC!=-1;f=Function(cur))
	{
		FUNCTIONS[f.NAME]=f;
	}
	DDD.clear();
	int kase=0;
	for(const auto &it:FUNCTIONS)
	{
		const Function &f=it.second;
		for(int p=0;p<(1<<f.PARAMETERS.size());p++)if(Ddd(f,p,kase++))return true;
	}
	return false;
}
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("recursion.in","r",stdin);
	freopen("recursion.out","w",stdout);
	S.clear();
	for(char c;(c=(char)getchar())!=EOF;)S+=c;
	puts(DfsVeryMuch()?"YES":"NO");
	return 0;
}
