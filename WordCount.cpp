#include <iostream>
#include <io.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>
using namespace std;
#define maxlan 300
#define maxsize 300
struct choice
{
    bool c,w;//选择参数
};

class cow{
private:
    int cn;//字符数量
    int wn;//词数
    struct choice opt;
public:
    cow()
	{
        cn=wn=0;
        opt.c=opt.w=false;
    };
    void cncheck(FILE*fp);//字符检索 
    void wncheck(FILE*fp);//单词检索 
    void ListFiles(string path,string mode);
    void Work(char*filename);
    void Choose(int argc,char*argv[]);
};

bool IsCharacter(char ch)//回车空格换行 
{
    if(ch=='\t'||ch==' '||ch=='\n')
		return false;
    else 
		return true;
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


void cow::cncheck(FILE *fp)//字符 
{
    char flag=0;int count=0;
    while(!feof(fp)){
        flag=fgetc(fp);
        if(IsCharacter(flag))
            count++;
    }
    cn=count-1;
    cout<<"字符数： "<<cn<<endl;
    rewind(fp);
    return;
}

void cow::wncheck(FILE*fp)//词 
{
    int len;//每行的字符数
    int count=0;
    char str[maxsize];
    while(!feof(fp))
	{
        fgets(str,maxsize,fp);
        len=strlen(str);
        for(int i=0;i<len;i++)
        {
            if(IsCharacter_(str[i]))
			{
                if(i==0||!IsCharacter_(str[i-1]))
                    count++;
            }
        }
    }
    wn=count;
    cout<<"单词数："<<wn<<endl;
    rewind(fp);
    return;
}

void cow::Work(char *filename) //运行
{
    FILE *fp=fopen(filename,"r");
    if(opt.c== true)
    	cncheck(fp);
    if(opt.w== true)
        wncheck(fp);
}
void cow::ListFiles(string path,string mode)//处理 
{
    _finddata_t file;//查找 
    intptr_t HANDLE;
    string Onepath = path + mode;//递归头 
    HANDLE = _findfirst(Onepath.c_str(), &file);
    do { 
        {
            cout << file.name << " " << endl;
            FILE *fp=fopen(&file.name[0],"r");
            if(opt.c== true){
                cncheck(fp);
            }
            if(opt.w== true){
                wncheck(fp);
            }
            cout<<"------------------------------"<<endl;
        }
    } while (_findnext(HANDLE, &file) == 0);
    _findclose(HANDLE);
}

void cow::Choose(int argc,char*argv[])//选择
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
    char filename[maxlan];
    strcpy(filename,argv[argc-1]);
    cow filefp;
    filefp.Choose(argc,argv);
    filefp.Work(filename);
    return 0;
}
