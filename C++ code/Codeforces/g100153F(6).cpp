#include<cstdio>
#include<cassert>
#include<string>
#include<utility>
#include<set>
using namespace std;
inline bool IsDigitOrLetter(const char c){return ('0'<=c&&c<='9')||('a'<=c&&c<='z')||('A'<=c&&c<='Z');}
inline bool IsSymbol(const char c){return c=='('||c==')'||c=='{'||c=='}'||c==','||c=='+'||c=='-';}
string S;
inline char SkipBlanks(int &cur){while(!IsDigitOrLetter(S[cur])&&!IsSymbol(S[cur]))cur++;return S[cur];}
inline string ReadName(int &cur)
{
	while(cur<(int)S.size()&&!IsDigitOrLetter(S[cur]))cur++;
	if(cur==(int)S.size())return "";
	string ans="";
	while(IsDigitOrLetter(S[cur]))ans+=S[cur],cur++;
	return ans;
}
inline char MoveToNextSymbol(int &cur)
{
	while(!IsSymbol(S[cur]))cur++;
	return S[cur];
}
inline void MoveToCorrespondingBracket(int &cur)
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
#include<map>
template<class T>struct MyMap
{
//	T data[10][52];
	map<string,T>data;
	MyMap<T>(){}
	inline void clear(){}
//	inline int Id(const char a)const{return 'A'<=a&&a<='Z'?a-'A':a-'a'+26;}
	T &operator[](const string &s)
	{
		return data[s];
		if(s.size()!=2)for(;;);
//		assert(s.size()==2);
//		return data[Id(s[0])][Id(s[1])];
	}
	const T &operator[](const string &s)const
	{
		const auto &it=data.find(s);
		static int none=T();
		if(it==data.end())return none;
		else return it->second;
		if(s.size()!=2)for(;;);
//		assert(s.size()==2);
//		return data[Id(s[0])][Id(s[1])];
	}
};
struct Function
{
	string NAME;
	MyMap<int>PARAMETERS;
	int PARAMETERS_SIZE;
	int LOC;
	Function(){PARAMETERS_SIZE=0;}
	Function(int &cur)
	{
		NAME=ReadName(cur);
		if(NAME==""){LOC=-1;return;}
		assert(SkipBlanks(cur)=='(');
		PARAMETERS.clear();
		PARAMETERS_SIZE=0;
		for(int cnt=0;MoveToNextSymbol(cur)!=')';cnt++)
		{
			++cur;
			PARAMETERS[ReadName(cur)]=cnt;
			PARAMETERS_SIZE=cnt+1;
		}
		++cur;
		LOC=cur;
		SkipOneStatement(cur);
	}
	inline bool GetValue(const string &parameter_name,const int parameters)const
	{
//		const auto &it=.find(parameter_name);
//		assert(it!=PARAMETERS.end());
		return (parameters&(1<<PARAMETERS[parameter_name]))>0;
	}
	inline void AddValue(const string &parameter_name,int &parameters)const
	{
//		const auto &it=PARAMETERS.find(parameter_name);
//		assert(it!=PARAMETERS.end());
		parameters|=1<<PARAMETERS[parameter_name];
	}
	inline void SubValue(const string &parameter_name,int &parameters)const
	{
//		const auto &it=PARAMETERS.find(parameter_name);
//		assert(it!=PARAMETERS.end());
		parameters&=~(1<<PARAMETERS[parameter_name]);
	}
	inline void SetValue(const string &parameter_name,int &parameters,const bool value)const
	{
		if(value)AddValue(parameter_name,parameters);
		else SubValue(parameter_name,parameters);
	}
};
MyMap<Function>FUNCTIONS;
template<class T>struct MyArray
{
	T data[1<<15];
	MyArray<T>()
	{
		for(int i=0;i<(1<<15);i++)data[i]=T(-1);
	}
	T &operator[](const int i){return data[i];}
	T &operator[](const int i)const{return data[i];}
};
MyMap<MyArray<int> >DDD;
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
//					const auto &it=FUNCTIONS.find(name);
//					assert(it!=FUNCTIONS.end());
					const Function &nxtf=FUNCTIONS[name];
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
	if(DDD[f.NAME][parameters]!=-1)return DDD[f.NAME][parameters]==kase;
	DDD[f.NAME][parameters]=kase;
	return !ExecuteSucceed(f,f.LOC,parameters,kase);
}
#include<vector>
bool DfsVeryMuch()
{
	int cur=0;
	FUNCTIONS.clear();
	vector<Function>fff;
	for(Function f=Function(cur);f.LOC!=-1;f=Function(cur))
	{
//		assert(FUNCTIONS.find(f.NAME)==FUNCTIONS.end());
		FUNCTIONS[f.NAME]=f;
		fff.push_back(f);
	}
	DDD.clear();
	int kase=0;
	for(const auto &f:fff)
	{
//		const Function &f=it.second;
		for(int p=0;p<(1<<f.PARAMETERS_SIZE);p++)if(Ddd(f,p,kase++))return true;
	}
	return false;
}
#include<map>
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("recursion.in","r",stdin);
	freopen("recursion.out","w",stdout);
	S.clear();
	for(char c;(c=(char)getchar())!=EOF;)if(IsDigitOrLetter(c)||IsSymbol(c))S+=c;
	vector<char>w;
	for(char c='A';c<='Z';c++)w.push_back(c);
	for(char c='a';c<='z';c++)w.push_back(c);
	map<string,string>replace;
	for(int i=0,cnt=0;i<(int)S.size();cnt++)
	{
		if(IsDigitOrLetter(S[i]))
		{
			string s=ReadName(i);
			if(s!="if"&&s!="else")
			{
				string t;t=w[cnt/52];
				t+=w[cnt%52];
//				if(cnt/52>=10)for(;;);//never happened
				if(replace.find(s)==replace.end())replace[s]=t,cnt++;
			}
		}
		else i++;
	}
	for(int i=0;i<(int)S.size();)
	{
		if(IsDigitOrLetter(S[i]))
		{
//			printf("aaaaaaaaaaaaaaaaaaaaa=%c\n",S[i]);
			int j=i;
			string s=ReadName(j);
			if(s!="if"&&s!="else")
			{
				const auto &it=replace.find(s);
//				printf("s=%s\n%s\n**********************\n",s.c_str(),S.c_str()+i);
				assert(it!=replace.end());
				string l=S.substr(0,i),r=S.substr(j,S.size()-j);
				assert(l.size()+s.size()+r.size()==S.size());
				S=l+it->second+r;
//	puts((S+"\n********************\n").c_str());
				i+=(int)it->second.size();
			}
			else i=j;
			assert(i==(int)S.size()||!IsDigitOrLetter(S[i]));
		}
		else i++;
	}
	puts(DfsVeryMuch()?"YES":"NO");
	return 0;
}
