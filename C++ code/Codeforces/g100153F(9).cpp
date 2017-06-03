#include<cstdio>
//#include<cassert>
#include<string>
#include<set>
#include<vector>
using namespace std;
//inline void bssert(const bool valid){if(!valid)for(;;);}
template<class T>struct MyMap
{
	T data[10][52];
	MyMap<T>(){}
//	inline void clear(){}
	inline int Id(const char a)const{return 'A'<=a&&a<='Z'?a-'A':a-'a'+26;}
	T &operator[](const string &s)
	{
//		if(s.size()!=2)for(;;);
		return data[Id(s[0])][Id(s[1])];
	}
	const T &operator[](const string &s)const
	{
//		if(s.size()!=2)for(;;);
		return data[Id(s[0])][Id(s[1])];
	}
};
struct MyArray
{
	int data[1<<15];
	MyArray()
	{
		for(int i=0;i<(1<<15);i++)data[i]=-1;
	}
	int &operator[](const int i){return data[i];}
	const int &operator[](const int i)const{return data[i];}
};
inline bool IsDigitOrLetter(const char c){return ('0'<=c&&c<='9')||('a'<=c&&c<='z')||('A'<=c&&c<='Z');}
inline bool IsSymbol(const char c){return c=='('||c==')'||c=='{'||c=='}'||c==','||c=='+'||c=='-';}
string S;
//vector<int>SkipBlanks_DP;
inline char SkipBlanks(int &cur)
{
	return S[cur];
//	int &ans=SkipBlanks_DP[cur];
//	if(ans!=-1)cur=ans;
//	else
//	{
//		while(!IsDigitOrLetter(S[cur])&&!IsSymbol(S[cur]))cur++;
//		ans=cur;
//	}
//	return S[cur];
}
bool ReadName_CHECK=false;
vector<bool>ReadName_ISVALID;
//#include<cassert>
inline string ReadName(int &cur)
{
	while(cur<(int)S.size()&&!IsDigitOrLetter(S[cur])&&!IsSymbol(S[cur]))cur++;
//	assert(cur<(int)S.size());//return "";
//	puts(S.c_str()+cur);
//	if(ReadName_CHECK)assert(ReadName_ISVALID[cur]);
//	assert(IsDigitOrLetter(S[cur]));
	string ans="";
	while(IsDigitOrLetter(S[cur]))ans+=S[cur],cur++;
	return ans;
}
vector<int>MoveToNextSymbol_DP;
inline char MoveToNextSymbol(int &cur)
{
	int &ans=MoveToNextSymbol_DP[cur];
	if(ans!=-1)cur=ans;
	else
	{
		while(!IsSymbol(S[cur]))cur++;
		ans=cur;
	}
	return S[cur];
}
vector<int>MoveToCorrespondingBracket_DP;
inline void MoveToCorrespondingBracket(int &cur)
{
	int &ans=MoveToCorrespondingBracket_DP[cur];
	if(ans!=-1){cur=ans;return;}
	else
	{
//		assert(S[cur]=='{'||S[cur]=='(');
		const char lc=S[cur],rc=(S[cur]=='{'?'}':')');
		for(int cnt=0;;)
		{
			if(S[cur]==lc)++cnt;
			if(S[cur]==rc)--cnt;
			if(cnt==0){ans=cur;return;}
			else ++cur;
		}
	}
}
vector<int>SkipOneStatement_DP;
void SkipOneStatement(int &cur)
{
	int &ans=SkipOneStatement_DP[cur];
	if(ans!=-1){cur=ans;return;}
//	static int eee=0;
//	if(eee++%1000==0)printf("eee=%d,%d\n",eee,(int)S.size());
	SkipBlanks(cur);
	if(IsDigitOrLetter(S[cur]))
	{
//		puts("a");
		if(ReadName(cur)=="if")
		{
//			assert(SkipBlanks(cur)=='(');
			++cur;
//			assert(IsDigitOrLetter(S[cur]));
//			puts("b");
			ReadName(cur);
//			assert(SkipBlanks(cur)==')');
			++cur;
			SkipOneStatement(cur);
			SkipBlanks(cur);
			int c1=cur;
			if(IsDigitOrLetter(S[c1])&&ReadName(c1)=="else")
			{
				cur=c1;
				SkipOneStatement(cur);
			}
			ans=cur;
		}
		else
		{
			switch(MoveToNextSymbol(cur))
			{
				case'(':
				{
					MoveToCorrespondingBracket(cur),++cur;
					ans=cur;
					return;
				}
				case'+':
				case'-':
				{
//					assert(S[cur]==S[cur+1]);
					cur+=2;
					ans=cur;
					return;
				}
//				default:assert(0);return;
			}
		}
	}
	else
	{
//		assert(S[cur]=='{');
		MoveToCorrespondingBracket(cur);
		++cur;
		ans=cur;
		return;
	}
}
//#include<cassert>
struct Function
{
	string NAME;
	MyMap<int>PARAMETERS;
	int LOC,PARAMETERS_SIZE;
	Function(){}
	Function(int &cur)
	{
		if(cur==(int)S.size()){LOC=-1;return;}
//		assert(IsDigitOrLetter(S[cur]));
//		puts("c");
		NAME=ReadName(cur);
//		assert(NAME.size()==2);
//		assert(MoveToNextSymbol(cur)=='(');
//		PARAMETERS.clear();
		PARAMETERS_SIZE=0;
		for(int cnt=0;MoveToNextSymbol(cur)!=')';cnt++)
		{
			++cur;
			if(S[cur]==')')break;
//			puts("d");
			const string &n=ReadName(cur);
//			assert(n.size()<=2);
			PARAMETERS[n]=cnt;
			PARAMETERS_SIZE=cnt+1;
		}
//		assert(S[cur]==')');
		++cur;
		LOC=cur;
		SkipOneStatement(cur);
	}
	inline bool GetValue(const string &parameter_name,const int parameters)const
	{
//		assert(parameter_name.size()==2);
		return (parameters&(1<<PARAMETERS[parameter_name]))>0;
	}
	inline void AddValue(const string &parameter_name,int &parameters)const
	{
//		assert(parameter_name.size()==2);
		parameters|=1<<PARAMETERS[parameter_name];
	}
	inline void SubValue(const string &parameter_name,int &parameters)const
	{
//		assert(parameter_name.size()==2);
		parameters&=~(1<<PARAMETERS[parameter_name]);
	}
	inline void SetValue(const string &parameter_name,int &parameters,const bool value)const
	{
		if(value)AddValue(parameter_name,parameters);
		else SubValue(parameter_name,parameters);
	}
};
MyMap<Function>FUNCTIONS;
MyMap<MyArray>DDD;
bool Ddd(const Function &f,const int parameters,const int kase);
bool ExecuteSucceed(const Function &f,int cur,int &parameters,const int kase)
{
//	static int ExecuteSucceedc=0;
//	if(ExecuteSucceedc++%1000==0)printf("ExecuteSucceed=%d\n",ExecuteSucceedc);
//	static int ddd=0;
//	if(ddd++%1000==0)printf("ddd=%d\n",ddd);
	if(IsDigitOrLetter(SkipBlanks(cur)))
	{
		const string &name=ReadName(cur);
		if(name=="if")
		{
//			puts("a");
//			assert(SkipBlanks(cur)=='(');
			++cur;
			const string &p=ReadName(cur);
//			assert(SkipBlanks(cur)==')');
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
//			if(name.size()!=2)printf("name=%s\n",name.c_str()); 
//			assert(name.size()==2);
			switch(SkipBlanks(cur))
			{
				case'+':f.AddValue(name,parameters),cur+=2;return true;
				case'-':f.SubValue(name,parameters),cur+=2;return true;
				case'(':
				{
					const Function &nxtf=FUNCTIONS[name];
					int nxtparameters=0;
					for(int cnt=0;MoveToNextSymbol(cur)!=')';cnt++)
					{
						++cur;
						if(S[cur]==')')break;
						if(f.GetValue(ReadName(cur),parameters))nxtparameters|=1<<cnt;
					}
//					assert(S[cur]==')');
					++cur;
					return !Ddd(nxtf,nxtparameters,kase);
				}
//				default:printf("error=%c\n%s\n",S[cur],S.c_str()+cur);assert(0);return false;
			}
		}
	}
	else
	{
//		printf("S[cur]=%c\n",SkipBlanks(cur));
//		puts("b");
//		printf("%s\n*************************\n",S.c_str()+cur);
//		assert(SkipBlanks(cur)=='{');
		for(++cur;SkipBlanks(cur)!='}';)
		{
			if(!ExecuteSucceed(f,cur,parameters,kase))return false;
			SkipOneStatement(cur);
		}
		return true;
	}
	return false;
}
//set<int>DEBUG;
bool Ddd(const Function &f,int parameters,const int kase)
{
//	static int Dddc=0;
//	if(Dddc++%1000==0)printf("Ddd=%d\n",Dddc);
//	printf("In function: %s(",f.NAME.c_str());
//	for(int i=0;i<(int)f.PARAMETERS_SIZE;i++)
//	{
//		if(i)putchar(',');
//		printf("%d",(parameters>>i)&1);
//	}
//	puts(")");
//	static int ccc=0;
//	if(ccc++%1000==0)printf("ccc=%d\n",ccc);
	if(DDD[f.NAME][parameters]!=-1)return DDD[f.NAME][parameters]==kase;
//	assert(DEBUG.find(parameters)==DEBUG.end());
//	DEBUG.insert(parameters);
	DDD[f.NAME][parameters]=kase;
	return !ExecuteSucceed(f,f.LOC,parameters,kase);
}
bool DfsVeryMuch()
{
//	static int DfsVeryMuchc=0;
//	if(DfsVeryMuchc++%1000==0)printf("DfsVeryMuch=%d\n",DfsVeryMuchc);
	int cur=0;
//	FUNCTIONS.clear();
	vector<Function>fff;
	for(Function f=Function(cur);f.LOC!=-1;f=Function(cur))
	{
		fff.push_back(f);
//		assert(f.NAME.size()==2);
		FUNCTIONS[f.NAME]=f;
	}
//	DDD.clear();
	int kase=0;
	for(const auto &f:fff)
	{
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
	for(int i=0,cnt=0;i<(int)S.size();)
	{
		if(IsDigitOrLetter(S[i]))
		{
			const string &s=ReadName(i);
			if(s!="if"&&s!="else")
			{
//	puts("a");
				string t;t=w[cnt/52];
				t+=w[cnt%52];
//				assert(cnt<52*10);
//				printf("cnt=%d,%d\n",cnt,(int)replace.size());
//				assert(t.size()==2);
				if(replace.find(s)==replace.end())replace[s]=t,cnt++,DDD[t]=MyArray();
//				puts("b");
			}
		}
		else i++;
	}
	string t;
	for(int i=0;i<(int)S.size();)
	{
		if(IsDigitOrLetter(S[i]))
		{
//			assert(i==0||!IsDigitOrLetter(S[i-1]));
//			printf("aaaaaaaaaaaaaaaaaaaaa=%c\n",S[i]);
			const string &s=ReadName(i);
			if(s!="if"&&s!="else")
			{
				const auto &it=replace.find(s);
//				printf("s=%s\n%s\n**********************\n",s.c_str(),S.c_str()+i);
//				assert(it!=replace.end());
				t+=it->second;
//	puts((S+"\n********************\n").c_str());
			}
			else t+=s;
//			assert(i==(int)S.size()||!IsDigitOrLetter(S[i]));
		}
		else t+=S[i++];
	}
	S=t;
	ReadName_ISVALID.resize(S.size(),false);
	ReadName_CHECK=true;
	for(int i=0,cnt=0;i<(int)S.size();cnt++)
	{
		if(IsDigitOrLetter(S[i]))
		{
			ReadName_ISVALID[i]=true;
			const string &s=ReadName(i);
//			if(s!="if"&&s!="else")assert(s.size()==2);
		}
		else i++;
	}
//	puts("zzzzzzzzzzzzzz");
//	printf("%s\n",S.c_str());
	SkipOneStatement_DP.resize(S.size(),-1);
//	SkipBlanks_DP.resize(S.size(),-1);
	MoveToNextSymbol_DP.resize(S.size(),-1);
	MoveToCorrespondingBracket_DP.resize(S.size(),-1);
//	assert(S.size()<500);
//	puts("start");
	puts(DfsVeryMuch()?"YES":"NO");
	return 0;
}
