/************************************************************/
/* 快速读入，比getchar()快很多(Tested 2 times)
 * 最开始的时候init()一次，然后再调用readint()
 */
const int MAXSIZE = 50000007;
char buf[MAXSIZE];
ll bufpos;

void init(){
	buf[fread(buf,1,MAXSIZE,stdin)]='\0';
	bufpos=0;
}

inline int readint(){
	bool isneg;
	int val=0;
	for(;!isdigit(buf[bufpos]) && buf[bufpos]!='-';bufpos++);
	bufpos+=(isneg=buf[bufpos]=='-');
	for(;isdigit(buf[bufpos]);bufpos++)
		val=val*10+buf[bufpos]-'0';
	return isneg?-val:val;
}
/************************************************************/
