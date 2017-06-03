#include<cstdio>
#include<cassert>
#include<string>
#include<set>
#include<vector>
using namespace std;
const char NAME_SYMBOL='a';
//inline void bssert(const bool valid){if(!valid)for(;;);}
template<class T>struct MyMap
{
	T data[520];
	MyMap<T>(){}
//	inline void clear(){}
//	inline int Id(const char a)const{return 'A'<=a&&a<='Z'?a-'A':a-'a'+26;}
	T &operator[](const int &s)
	{
//		if(s.size()!=2)for(;;);
		return data[s];
	}
	const T &operator[](const int &s)const
	{
//		if(s.size()!=2)for(;;);
		return data[s];
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
vector<int>NAMES;
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
inline string ReadStringName(int &cur)
{
	while(cur<(int)S.size()&&!IsDigitOrLetter(S[cur])&&!IsSymbol(S[cur]))cur++;
	assert(cur<(int)S.size());//return "";
//	puts(S.c_str()+cur);
	if(ReadName_CHECK)assert(ReadName_ISVALID[cur]);
	assert(IsDigitOrLetter(S[cur]));
	string ans="";
	while(IsDigitOrLetter(S[cur]))ans+=S[cur],cur++;
	return ans;
}
inline int ReadName(int &cur)
{
	assert(NAMES[cur]!=-1);
	return NAMES[cur++];
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
		assert(S[cur]=='{'||S[cur]=='(');
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
		if(ReadName(cur)==-2)
		{
			assert(SkipBlanks(cur)=='(');
			++cur;
			assert(IsDigitOrLetter(S[cur]));
//			puts("b");
			ReadName(cur);
			assert(SkipBlanks(cur)==')');
			++cur;
			SkipOneStatement(cur);
			SkipBlanks(cur);
			int c1=cur;
//			puts("a");
//			printf("%s\n%s\n",S.c_str(),S.c_str()+cur);
			assert(IsDigitOrLetter(S[c1])&&ReadName(c1)==-3);
//			puts("b");
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
					assert(S[cur]==S[cur+1]);
					cur+=2;
					ans=cur;
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
		ans=cur;
		return;
	}
}
struct Function
{
	int NAME;
	MyMap<int>PARAMETERS;
	int LOC,PARAMETERS_SIZE;
	Function(){}
	Function(int &cur)
	{
//		puts(S.c_str()+cur);
		if(cur==(int)S.size()){LOC=-1;return;}
		assert(IsDigitOrLetter(S[cur]));
//		puts("c");
		NAME=ReadName(cur);
//		printf("NAME=%d\n",NAME);
//		assert(NAME.size()==2);
		assert(MoveToNextSymbol(cur)=='(');
//		PARAMETERS.clear();
		PARAMETERS_SIZE=0;
		for(int cnt=0;MoveToNextSymbol(cur)!=')';cnt++)
		{
			++cur;
			if(S[cur]==')')break;
//			puts("d");
			const int &n=ReadName(cur);
//			assert(n.size()<=2);
			PARAMETERS[n]=cnt;
			PARAMETERS_SIZE=cnt+1;
		}
		assert(S[cur]==')');
		++cur;
		LOC=cur;
		SkipOneStatement(cur);
	}
	inline bool GetValue(const int &parameter_name,const int parameters)const
	{
//		assert(parameter_name.size()==2);
		return (parameters&(1<<PARAMETERS[parameter_name]))>0;
	}
	inline void AddValue(const int &parameter_name,int &parameters)const
	{
//		assert(parameter_name.size()==2);
		parameters|=1<<PARAMETERS[parameter_name];
	}
	inline void SubValue(const int &parameter_name,int &parameters)const
	{
//		assert(parameter_name.size()==2);
		parameters&=~(1<<PARAMETERS[parameter_name]);
	}
	inline void SetValue(const int &parameter_name,int &parameters,const bool value)const
	{
		if(value)AddValue(parameter_name,parameters);
		else SubValue(parameter_name,parameters);
	}
};
MyMap<Function>FUNCTIONS;
MyMap<MyArray>DDD;
vector<int>ET[20*(1<<15)],EF[20*(1<<15)];
int NAME_ID[20*(1<<15)];
//bool Ddd(const Function &f,const int parameters,const int kase);
void ExecuteSucceed(const Function &f,int cur,int &parameters,const int id)
{
	assert(id<20*(1<<15));
//	printf("cur=%d\n",cur);
//	static int ExecuteSucceedc=0;
//	if(ExecuteSucceedc++%1000==0)printf("ExecuteSucceed=%d\n",ExecuteSucceedc);
//	static int ddd=0;
//	if(ddd++%1000==0)printf("ddd=%d\n",ddd);
	if(IsDigitOrLetter(SkipBlanks(cur)))
	{
		const int &name=ReadName(cur);
		if(name==-2)
		{
//			puts("a");
			assert(SkipBlanks(cur)=='(');
			++cur;
			const int &p=ReadName(cur);
			assert(SkipBlanks(cur)==')');
			++cur;
			const bool value=f.GetValue(p,parameters);
//			puts("b");
			if(value)ExecuteSucceed(f,cur,parameters,id);//return false;
			SkipOneStatement(cur);
			SkipBlanks(cur);
			int c1=cur;
//			puts("a");
//			printf("%s\n%s\n",S.c_str(),S.c_str()+cur);
			assert(IsDigitOrLetter(S[c1])&&ReadName(c1)==-3);
//			puts("b");
			{
				cur=c1;
				if(!value)ExecuteSucceed(f,cur,parameters,id);//return false;
				SkipOneStatement(cur);
			}
			return;
		}
		else
		{
			assert(name>=0);
//			if(name.size()!=2)printf("name=%s\n",name.c_str());
//			assert(name.size()==2);
			switch(SkipBlanks(cur))
			{
				case'+':f.AddValue(name,parameters),assert(S[cur]==S[cur+1]),cur+=2;return;
				case'-':f.SubValue(name,parameters),assert(S[cur]==S[cur+1]),cur+=2;return;
				case'(':
				{
					const Function &nxtf=FUNCTIONS[name];
					int nxtparameters=0,cnt=0;
					for(;MoveToNextSymbol(cur)!=')';cnt++)
					{
						++cur;
						if(S[cur]==')')break;
						if(f.GetValue(ReadName(cur),parameters))nxtparameters|=1<<cnt;
					}
					assert(cnt==nxtf.PARAMETERS_SIZE);
					assert(S[cur]==')');
					++cur;
					const int nxtid=(NAME_ID[nxtf.NAME]<<15)+nxtparameters;
					ET[id].push_back(nxtid);
					EF[nxtid].push_back(id);
					return;
//					return !Ddd(nxtf,nxtparameters,kase);
				}
				default:printf("error=%c\n%s\n",S[cur],S.c_str()+cur);assert(0);return;
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
			ExecuteSucceed(f,cur,parameters,id);//return false;
			SkipOneStatement(cur);
		}
		return;
	}
	assert(0);//return false;
}
//set<int>DEBUG;
void Ddd(const Function &f,int parameters)
{
//	static int Dddc=0;
//	if(Dddc++%1000==0)printf("Ddd=%d\n",Dddc);
//	printf("In function: %d(",f.NAME);
//	for(int i=0;i<(int)f.PARAMETERS_SIZE;i++)
//	{
//		if(i)putchar(',');
//		printf("%d",(parameters>>i)&1);
//	}
//	puts(")");
//	static int ccc=0;
//	if(ccc++%1000==0)printf("ccc=%d\n",ccc);
//	if(DDD[f.NAME][parameters]!=-1)return DDD[f.NAME][parameters]==kase;
//	assert(DEBUG.find(parameters)==DEBUG.end());
//	DEBUG.insert(parameters);
//	DDD[f.NAME][parameters]=kase;
	ExecuteSucceed(f,f.LOC,parameters,(NAME_ID[f.NAME]<<15)+parameters);
}
void DfsVeryMuch()
{
//	static int DfsVeryMuchc=0;
//	if(DfsVeryMuchc++%1000==0)printf("DfsVeryMuch=%d\n",DfsVeryMuchc);
	int cur=0;
//	FUNCTIONS.clear();
//	puts("a");
	vector<Function>fff;
	set<int>named;
	for(Function f=Function(cur);f.LOC!=-1;f=Function(cur))
	{
		assert(named.find(f.NAME)==named.end());
		named.insert(f.NAME);
		fff.push_back(f);
//		assert(f.NAME.size()==2);
		FUNCTIONS[f.NAME]=f;
	}
//	assert(!fff.empty());
//	puts("c");
//	DDD.clear();
	for(int i=0;i<(int)fff.size();i++)NAME_ID[fff[i].NAME]=i;
	for(const auto &f:fff)
	{
		for(int p=0;p<(1<<f.PARAMETERS_SIZE);p++)Ddd(f,p);//return true;
	}
//	return false;
}
#include<map>
#include<queue>
int main()
{
//	freopen("in.txt","r",stdin);
	freopen("recursion.in","r",stdin);
	freopen("recursion.out","w",stdout);
	S.clear();
	for(char c;(c=(char)getchar())!=EOF;)if(IsDigitOrLetter(c)||IsSymbol(c)||true)S+=c;
	vector<char>w;
	for(char c='A';c<='Z';c++)w.push_back(c);
	for(char c='a';c<='z';c++)w.push_back(c);
	map<string,int>replace;
	for(int i=0,cnt=0;i<(int)S.size();)
	{
		if(IsDigitOrLetter(S[i]))
		{
			const string &s=ReadStringName(i);
			if(s!="if"&&s!="else")
			{
//	puts("a");
				assert(cnt<520);
//				printf("cnt=%d,%d\n",cnt,(int)replace.size());
				if(replace.find(s)==replace.end())replace[s]=cnt,DDD[cnt]=MyArray(),cnt++;
//				puts("b");
			}
		}
		else i++;
	}
	string t;
	NAMES.clear();
	for(int i=0;i<(int)S.size();)
	{
		if(IsDigitOrLetter(S[i]))
		{
			assert(i==0||!IsDigitOrLetter(S[i-1]));
//			printf("aaaaaaaaaaaaaaaaaaaaa=%c\n",S[i]);
			const string &s=ReadStringName(i);
			if(s=="if")t+='i',NAMES.push_back(-2);
			else if(s=="else")t+='e',NAMES.push_back(-3);
			else
			{
//				printf("s=%s\n",s.c_str());
				t+=NAME_SYMBOL;
				const auto &it=replace.find(s);
//				printf("s=%s\n%s\n**********************\n",s.c_str(),S.c_str()+i);
				assert(it!=replace.end());
				NAMES.push_back(it->second);
//	puts((S+"\n********************\n").c_str());
			}
			assert(i==(int)S.size()||!IsDigitOrLetter(S[i]));
		}
		else if(IsSymbol(S[i]))t+=S[i++],NAMES.push_back(-1);
		else i++;
	}
	S=t;
	assert(NAMES.size()==S.size());
//	puts("a");
//	puts("zzzzzzzzzzzzzz");
//	printf("%s\n",S.c_str());
	SkipOneStatement_DP.resize(S.size(),-1);
//	SkipBlanks_DP.resize(S.size(),-1);
	MoveToNextSymbol_DP.resize(S.size(),-1);
	MoveToCorrespondingBracket_DP.resize(S.size(),-1);
//	assert(S.size()<500);
//	puts("start");
//	puts("b");
	for(int i=0;i<20*(1<<15);i++)ET[i].clear(),EF[i].clear();
//	puts("a");
	DfsVeryMuch();
//	puts("b");
	queue<int>q;
	for(int i=0;i<20*(1<<15);i++)if(ET[i].empty())q.push(i);
	while(!q.empty())
	{
		const int u=q.front();q.pop();
		for(const int nxt:EF[u])
		{
			ET[nxt].pop_back();
			if(ET[nxt].empty())q.push(nxt);
		}
	}
	for(int i=0;i<20*(1<<15);i++)if(!ET[i].empty())
	{
		puts("YES");
		return 0;
	}
	puts("NO");
	return 0;
}
