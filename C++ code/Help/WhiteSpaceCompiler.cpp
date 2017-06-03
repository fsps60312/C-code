#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
#include<map>
#include<cassert>
//#define debug(...) printf(__VA_ARGS__)
char TRASH[10000];
#define debug(...) sprintf(TRASH,__VA_ARGS__)
using namespace std;
queue<char>CODE;
struct Stack
{
	vector<int>s;
	int size()const{return s.size();}
	int top()const{assert(size()>=1);return s[size()-1];}
	void push(const int v){s.push_back(v);}
	void copy(const int i){push(s[i]);}
	void remove(const int i){s.erase(s.begin()+i);}
	int pop(){int ans=top();s.pop_back();return ans;}
	void SwapTop(){assert(size()>=2),swap(s[size()-1],s[size()-2]);}
}STK;
map<int,int>MEMORY;
char Front()
{
	assert(!CODE.empty());
	char ans=CODE.front();
	CODE.pop();
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
void StackOperation()
{
	debug("StackOperation\n");
	const char first=Front();
	if(first==' ')STK.push(GetInt());
	else if(first=='\t')
	{
		const char second=Front();
		if(second==' ')STK.copy(GetInt());
		else if(second=='\n')STK.remove(GetInt());
		else assert(0);
	}
	else if(first=='\n')
	{
		const char second=Front();
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
	const int b=STK.pop(),a=STK.top();
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
void ControlOperation()
{
	const char first=Front(),second=Front();
	if(first=='\n')
	{
		if(second=='\n')exit(0);
		else assert(0&&"Not Implemented");
	}
	else assert(0&&"Not Implemented");
}
int main()
{
	FILE *in=fopen("AB.ws","r");
	for(char c;(fscanf(in,"%c",&c))==1;)if(c==' '||c=='\t'||c=='\n')CODE.push(c);
	while(!CODE.empty())
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
