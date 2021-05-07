#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <io.h>
#define bufsize 200
#define maxlen_filename 100
using namespace std;
struct Topt
{
    bool c,w;//选择参数
};

class Twc{
private:
    int num_of_characters;//字符数量
    int num_of_words;//词数
    struct Topt opt;
public:
    Twc(){
        num_of_characters=num_of_words=0;
        opt.c=opt.w=false;
    };
    void CalCharacters(FILE*fp);
    void CalWords(FILE*fp);
    void CalCodelines(FILE*fp);
    void ListFiles(string path,string mode);
    void Work(char*filename);
    void Choose(int argc,char*argv[]);
};

bool IsCharacter(char ch)//回车空格换行 
{
    if(ch=='\t'||ch==' '||ch=='\n')return false;
    else return true;
};

bool IsCharacter_(char ch)//字母 
{
    if(ch>='0'&&ch<='9')
		return true;
    if(ch>='a'&&ch<='z')
		return true;
    if(ch>='A'&&ch<='Z')
		return true;
    return false;
};


void Twc::CalCharacters(FILE *fp)//字符 
{
    char flag=0;int count=0;
    while(!feof(fp)){
        flag=fgetc(fp);
        if(IsCharacter(flag))
            count++;
    }
    num_of_characters=count-1;
    cout<<"字符数： "<<num_of_characters<<endl;
    rewind(fp);
    return;
}

void Twc::CalWords(FILE*fp)//词 
{
    char str[bufsize];
    int len;//每行的字符数
    int count=0;
    while(!feof(fp)){
        fgets(str,bufsize,fp);
        len=strlen(str);
        for(int i=0;i<len;i++)
        {
            if(IsCharacter_(str[i])){
                if(i==0||!IsCharacter_(str[i-1]))
                    count++;
            }
        }
    }
    num_of_words=count;
    cout<<"单词数： "<<num_of_words<<endl;
    rewind(fp);
    return;
}

void Twc::Work(char *filename) {//运行函数
    FILE *fp=fopen(filename,"r");
    if(opt.c== true){
        CalCharacters(fp);
    }
    if(opt.w== true){
        CalWords(fp);
    }
}
void Twc::ListFiles(string path,string mode)//处理 
{
    _finddata_t file;
    intptr_t HANDLE;
    string Onepath = path + mode;
    HANDLE = _findfirst(Onepath.c_str(), &file);
    do { 
        {
            cout << file.name << " " << endl;
            FILE *fp=fopen(&file.name[0],"r");
            if(opt.c== true){
                CalCharacters(fp);
            }
            if(opt.w== true){
                CalWords(fp);
            }
            cout<<"------------------------------"<<endl;
        }
    } while (_findnext(HANDLE, &file) == 0);
    _findclose(HANDLE);
}

void Twc::Choose(int argc,char*argv[])//选择
{
    for(int i=0;i<argc-1;i++){
        if(strcmp(argv[i],"-c")==0){
            opt.c=true;
        }
        if(strcmp(argv[i],"-w")==0){
            opt.w=true;
        }
    }
}
int main(int argc,char*argv[]){
    char filename[maxlen_filename];
    strcpy(filename,argv[argc-1]);
    Twc filefp;
    filefp.Choose(argc,argv);
    filefp.Work(filename);
    return 0;
}
