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
    bool c,w;//ѡ�����
};

class Twc{
private:
    int num_of_characters;//�ַ�����
    int num_of_words;//����
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

bool IsCharacter(char ch)//�س��ո��� 
{
    if(ch=='\t'||ch==' '||ch=='\n')return false;
    else return true;
};

bool IsCharacter_(char ch)//��ĸ 
{
    if(ch>='0'&&ch<='9')
		return true;
    if(ch>='a'&&ch<='z')
		return true;
    if(ch>='A'&&ch<='Z')
		return true;
    return false;
};


void Twc::CalCharacters(FILE *fp)//�ַ� 
{
    char flag=0;int count=0;
    while(!feof(fp)){
        flag=fgetc(fp);
        if(IsCharacter(flag))
            count++;
    }
    num_of_characters=count-1;
    cout<<"�ַ����� "<<num_of_characters<<endl;
    rewind(fp);
    return;
}

void Twc::CalWords(FILE*fp)//�� 
{
    char str[bufsize];
    int len;//ÿ�е��ַ���
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
    cout<<"�������� "<<num_of_words<<endl;
    rewind(fp);
    return;
}

void Twc::Work(char *filename) {//���к���
    FILE *fp=fopen(filename,"r");
    if(opt.c== true){
        CalCharacters(fp);
    }
    if(opt.w== true){
        CalWords(fp);
    }
}
void Twc::ListFiles(string path,string mode)//���� 
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

void Twc::Choose(int argc,char*argv[])//ѡ��
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
