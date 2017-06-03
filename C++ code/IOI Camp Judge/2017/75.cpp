#include <bits/stdc++.h>
using namespace std;
long long ANS;
void ERROR(const string &s) {
  fprintf(stderr, "ERROR: %s\n", s.c_str());
  exit(1);
}

void WA(const string &s = "") {
//	return;
  puts("WA");
  if (s != "") printf("%s\n", s.c_str());
  return;
  exit(0);
}

void AC(const string &s = "") {
  puts("AC");
  if (s != "") printf("%s\n", s.c_str());
  printf("ANS=%lld\n",ANS);
  exit(0);
}

struct Checker {
  string f_user_out;
  int T, n;
  char buf[64] = {};
  unsigned ala;

  void init(int argc, char **argv) {
    if(argc <= 2) ERROR("USAGE: ./judge user_code user_out");
    f_user_out=argv[2];
//    f_user_out.open(argv[2]); // only need <user_out>
//    printf("argv[2]=%s\n",argv[2]);
  }

  int readint() {
    string s=f_user_out;
    if(s.length() == 0 || s.length() > 10) WA("Too long.");
//    if (!f_user_out.good()) WA("Not good.");
    int val = 0;
    for(auto c: s)
      if(c > '9' || c < '0') WA("Digits only.");
      else val = val * 10 + c - '0';
    return val;
  }
  void log(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buf+strlen(buf), fmt, ap);
    va_end(ap);
  }
  void check() {
    T = 1;
    if(T != 1)
	{
		WA("Invalid T.");//10
		return;
	}
    log("OK: T=1\n");//8
    n = readint();
    log("OK: valid n\n");//12
    alalala();
    if(ala == 0)
	{
		WA("Nice try, but I'll never let you AC!"); // ^_^
		return;
	}
//  	unsigned pre_ala=ala;

    log("Checking if alalala(%d) equals 0...", n);//33+n
//    printf("%u %u\n",pre_ala,ala);
    if(ala) {
      log("You bad.");
      WA(buf);
	  return;
    }
    else {
      log("<3");
      AC(buf);
    }
  }

  void alalala() {
    ala = 0;
    unsigned piv = 0xdeadbeef;
    for(int i = 0; i < 32; i++) {
      if(n & (1u << i)) ala ^= piv;
      ala <<= 1;
    }
  }
};
int main(){
	int argc=3;
	char *argv[3];
//	argv[0];
//	argv[1];
	argv[2]=new char[100];
	for(unsigned i=2;i<128;i+=2)
	{
		unsigned v=i;
		unsigned n=0;
		for(int i=31;i>=0;i--)
		{
			assert(!(v&1));
			v>>=1;
			if(v&1)n+=((unsigned)1)<<i,v^=0xdeadbeef;
		}
		ANS=n;
		printf("ans=%lld\n",ANS);
		sprintf(argv[2],"%lld",ANS);
		Checker checker;
		checker.init(argc, argv);
		checker.check();
	}
  return 0;
} 
