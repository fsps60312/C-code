#include<cstdio>
#include<deque>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<list>
#include<ctime>
#include<cstdlib> 
using namespace std;
const int ARRAY_LENGTH=9000000;
const bool PAUSE_AFTER_CREATE=false;
struct LL{long long s[100];};
struct MyQueue
{
	vector<int>s;
	int l,r;
	void clear(){l=0,r=-1,s.clear();}
	void push(const int v){r++,s.push_back(v);}
	void pop(){l++;}
	bool empty(){return r<l;}
	int size(){return r-l+1;}
	int front(){return s[l];}
};
void Test_MyQueue()
{
	printf("MyQueue:       (%llu)",sizeof(MyQueue));
	clock_t start=clock();
	MyQueue*tmp=new MyQueue[ARRAY_LENGTH];
	printf(" %.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	if(PAUSE_AFTER_CREATE)system("pause");
	delete[]tmp;
}
void Test_list()
{
	printf("list:          (%llu,%llu)",sizeof(list<int>),sizeof(list<LL>));
	clock_t start=clock();
	list<int>*tmp=new list<int>[ARRAY_LENGTH];
	printf(" %.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	if(PAUSE_AFTER_CREATE)system("pause");
	delete[]tmp;
}
void Test_vector()
{
	printf("vector:        (%llu,%llu)",sizeof(vector<int>),sizeof(vector<LL>));
	clock_t start=clock();
	vector<int>*tmp=new vector<int>[ARRAY_LENGTH];
	printf(" %.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	if(PAUSE_AFTER_CREATE)system("pause");
	delete[]tmp;
}
void Test_priority_queue()
{
	printf("priority_queue:(%llu,%llu)",sizeof(priority_queue<int>),sizeof(priority_queue<LL>));
	clock_t start=clock();
	priority_queue<int>*tmp=new priority_queue<int>[ARRAY_LENGTH];
	printf(" %.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	if(PAUSE_AFTER_CREATE)system("pause");
	delete[]tmp;
}
void Test_set()
{
	printf("set:           (%llu,%llu)",sizeof(set<int>),sizeof(set<LL>));
	clock_t start=clock();
	set<int>*tmp=new set<int>[ARRAY_LENGTH];
	printf(" %.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	if(PAUSE_AFTER_CREATE)system("pause");
	delete[]tmp;
}
void Test_map()
{
	printf("map:           (%llu,%llu)",sizeof(map<int,int>),sizeof(map<LL,LL>));
	clock_t start=clock();
	map<int,int>*tmp=new map<int,int>[ARRAY_LENGTH];
	printf(" %.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	if(PAUSE_AFTER_CREATE)system("pause");
	delete[]tmp;
}
void Test_multiset()
{
	printf("multiset:      (%llu,%llu)",sizeof(multiset<int>),sizeof(multiset<LL>));
	clock_t start=clock();
	multiset<int>*tmp=new multiset<int>[ARRAY_LENGTH];
	printf(" %.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	if(PAUSE_AFTER_CREATE)system("pause");
	delete[]tmp;
}
void Test_multimap()
{
	printf("multimap:      (%llu,%llu)",sizeof(multimap<int,int>),sizeof(multimap<LL,LL>));
	clock_t start=clock();
	multimap<int,int>*tmp=new multimap<int,int>[ARRAY_LENGTH];
	printf(" %.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	if(PAUSE_AFTER_CREATE)system("pause");
	delete[]tmp;
}
void Test_deque()
{
	printf("deque:         (%llu,%llu)",sizeof(deque<int>),sizeof(deque<LL>));
	clock_t start=clock();
	deque<int>*tmp=new deque<int>[ARRAY_LENGTH];
	printf(" %.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	if(PAUSE_AFTER_CREATE)system("pause");
	delete[]tmp;
}
void Test_queue()
{
	printf("queue:         (%llu,%llu)",sizeof(queue<int>),sizeof(queue<LL>));
	clock_t start=clock();
	queue<int>*tmp=new queue<int>[ARRAY_LENGTH];
	printf(" %.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	if(PAUSE_AFTER_CREATE)system("pause");
	delete[]tmp;
}
void Test_stack()
{
	printf("stack:         (%llu,%llu)",sizeof(stack<int>),sizeof(stack<LL>));
	clock_t start=clock();
	stack<int>*tmp=new stack<int>[ARRAY_LENGTH];
	printf(" %.3f s\n",(double)(clock()-start)/CLOCKS_PER_SEC);
	if(PAUSE_AFTER_CREATE)system("pause");
	delete[]tmp;
}
int main()
{
	Test_MyQueue();
	Test_list();
	Test_vector();
	Test_priority_queue();
	Test_set();
	Test_map();
	Test_multiset();
	Test_multimap();
	Test_deque();
	Test_queue();
	Test_stack();
	return 0;
}
