const int BUFSIZE=20<<20;//20MB
char Buf[BUFSIZE+1],*buf=Buf;
//fread(Buf,1,BUFSIZE,stdin); 在读入之前写这句话  任何整数
template<class T>
void scan(T&a){
    int sgn=1;
    for(a=0;*buf<'0'||*buf>'9';buf++)if(*buf=='-')sgn=-1;
    while(*buf>='0'&&*buf<='9'){a=a*10+(*buf-'0');buf++;}
    a*=sgn;
}