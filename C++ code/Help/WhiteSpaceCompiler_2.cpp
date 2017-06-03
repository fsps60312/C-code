#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<map>
#include<cassert>
#define debug(...) printf(__VA_ARGS__)
char TRASH[10000];
//#define debug(...) sprintf(TRASH,__VA_ARGS__)
using namespace std;
vector<char>CODE;
struct Stack
{
	vector<int>s;
	void clear(){s.clear();}
	int &operator[](const int idx){assert(idx>=0);assert(idx<size());return s[idx];}
	int size()const{return s.size();}
	int &top(){assert(size()>=1);return (*this)[size()-1];}
	void push(const int v){s.push_back(v);}
	void copy(const int i){push((*this)[i]);}
	void remove(const int i){s.erase(s.begin()+i);}
	int pop(){int ans=top();s.pop_back();return ans;}
	void SwapTop(){assert(size()>=2),swap((*this)[size()-1],(*this)[size()-2]);}
}STK,CURSOR;
map<int,int>MEMORY,LABEL;
char Front()
{
	assert(CURSOR.top()<(int)CODE.size());
	char ans=CODE[CURSOR.top()++];
	static int cnt=0;
	debug("command %d\n",cnt++);
	return ans;
}
int GetInt()
{
	int ans=0;
	for(char c;(c=Front())!='\n';)ans<<=1,ans+=(c=='\t');
	return ans;
}
char *GetType(const char c)
{
	if(c=='\t')return (char*)"T";
	if(c=='\n')return (char*)"L";
	if(c==' ')return (char*)"S";
	assert(0);
	return (char*)"";
}
void StackOperation()
{
	debug("StackOperation\n");
	const char first=Front();
	debug("first=%s\n",GetType(first));
	if(first==' ')STK.push(GetInt());
	else if(first=='\t')
	{
		const char second=Front();
		debug("second=%s\n",GetType(second));
		if(second==' ')STK.copy(GetInt());
		else if(second=='\n')STK.remove(GetInt());
		else assert(0);
	}
	else if(first=='\n')
	{
		const char second=Front();
		debug("second=%s\n",GetType(second));
		if(second==' ')STK.push(STK.top());
		else if(second=='\t')STK.SwapTop();
		else if(second=='\n')STK.pop();
		else assert(0);
	}
	else assert(0);
}
void ArithmOperation()
{
	debug("ArithmOperation\n");
	const char first=Front(),second=Front();
	const int b=STK.pop(),a=STK.pop();
	if(first==' ')
	{
		if(second==' ')STK.push(a+b);
		else if(second=='\t')STK.push(a-b);
		else if(second=='\n')STK.push(a*b);
		else assert(0);
	}
	else if(first=='\t')
	{
		if(second==' ')STK.push(a/b);
		else if(second=='\t')STK.push(a%b);
		else assert(0);
	}
	else assert(0);
}
void SetValue(const int i,const int v){MEMORY[i]=v;debug("setting index=%d, value=%d\n",i,v);}
int GetValue(const int i){const auto it=MEMORY.find(i);debug("getting index=%d\n",i);assert(it!=MEMORY.end());return it->second;}
void AccumulateOperation()
{
	debug("AccumulateOperation\n");
	const char command=Front();
	if(command==' ')
	{
		const int value=STK.pop(),mem=STK.pop();
		SetValue(mem,value);
	}
	else if(command=='\t')
	{
		const int mem=STK.pop();
		STK.push(GetValue(mem));
	}
	else assert(0);
}
void InputOutputOperation()
{
	debug("InputOutputOperation\n");
	const char first=Front(),second=Front();
	if(first==' ')
	{
		if(second==' ')printf("%c",(char)STK.top());
		else if(second=='\t')printf("%d",STK.top());
		else assert(0);
	}
	else if(first=='\t')
	{
		if(second==' '){char c;scanf("%c",&c);SetValue(STK.pop(),(int)c);}
		else if(second=='\t'){int v;scanf("%d",&v);SetValue(STK.pop(),v);}
		else assert(0);
	}
	else assert(0);
}
void SetLabel(const int l,const int c){LABEL[l]=c;debug("setting label=%d, value=%d\n",l,c);}
int GetLabel(const int l){const auto it=LABEL.find(l);debug("getting label=%d\n",l);assert(it!=LABEL.end());return it->second;}
#include<cstdlib>
void ExitProgram(const int exitvalue)
{
	puts("\n**********\n");
	printf("In main data stack: (size = %d)\n",STK.size());
	for(int i=0;i<STK.size();i++)printf("level %d: %d\n",i,STK[i]);
	puts("");
	printf("In calling stack: (size = %d)\n",CURSOR.size());
	for(int i=0;i<CURSOR.size();i++)printf("level %d: %d\n",i,CURSOR[i]);
	puts("");
	printf("Used position: (size = %d)\n",(int)MEMORY.size());
	for(const auto &it:MEMORY)printf("index = %d, value = %d\n",it.first,it.second);
	puts("");
	printf("Used label: (size = %d)\n",(int)LABEL.size());
	for(const auto &it:LABEL)printf("index = %d, label = %d\n",it.first,it.second);
	puts("");
	system("pause");
	exit(exitvalue);
}
void ControlOperation()
{
	debug("ControlOperation\n");
	const char first=Front(),second=Front();
	debug("first=%s,second=%s\n",GetType(first),GetType(second));
	if(first==' ')
	{
		if(second==' ')SetLabel(GetInt(),CURSOR.top());
		else if(second=='\t')CURSOR.push(GetLabel(GetInt()));
		else if(second=='\n')CURSOR.top()=GetLabel(GetInt());
		else assert(0);
	}
	else if(first=='\t')
	{
		if(second==' '){if(STK.top()==0)CURSOR.top()=GetLabel(GetInt());}
		else if(second=='\t'){if(STK.top()<0)CURSOR.top()=GetLabel(GetInt());}
		else if(second=='\n')CURSOR.pop();
		else assert(0);
	}
	else if(first=='\n')
	{
		if(second=='\n')ExitProgram(0);
		else assert(0&&"Not Implemented");
	}
	else assert(0&&"Not Implemented");
}
int main()
{
	FILE *in=fopen("whileab.ws","r");
	CURSOR.clear(),CODE.clear();
	for(char c;(fscanf(in,"%c",&c))==1;)if(c==' '||c=='\t'||c=='\n')CODE.push_back(c);
	CURSOR.push(0);
	for(;;)
	{
		const char first=Front();
		if(first==' ')StackOperation();
		else if(first=='\t')
		{
			const char second=Front();
			if(second==' ')ArithmOperation();
			else if(second=='\t')AccumulateOperation();
			else if(second=='\n')InputOutputOperation();
			else assert(0);
		}
		else if(first=='\n')ControlOperation();
		else assert(0);
	}
	return 0;
}
