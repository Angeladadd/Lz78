//contributed by Chenge Sun
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
int idx=0;
int number=0;
int maxNum=9000;
struct Node{
    int index;
    char *code;
};
Node *List;
void doubleSpace()
{
    Node *tmp = List;
    List = new Node[2*maxNum];
    for (int i=0;i<maxNum;i++)
    {
        List[i].index=tmp[i].index;
        List[i].code=new char[strlen(tmp[i].code)+1];
        strcpy(List[i].code, tmp[i].code);
    }
}
int str_to_num(char *str,int len)
{
    int ans=0;
    int base=1;
    while(len)
    {
        ans += (str[len-1]-'0')*base;
        len--;
        base *=10;
    }
    return ans;
}
int main()
{
    List = new Node[maxNum];
    ifstream infile("LZ78Encoding.txt");
    ofstream outfile("LZ78decoding.txt");
    char ch;
    if(infile.fail()) cout<<"open error"<<endl;
    infile.get(ch);
    while(ch != '@')
    {
        number ++;
        //if(number>maxNum) doubleSpace();
        char tmpstr[20];
        int tmplen=0;
        while(ch!=' ' && ch !='@')
        {
            if(ch!='\r')
            {
            tmpstr[tmplen]=ch;
            tmplen++;
            }
            if(ch!= '@' )infile.get(ch);
        }
        //空格有两种情况，一种是编码中的空格，一种是分隔符，这时我们要根据空格后面是不是还是空格来判断是不是分隔符
        if(ch == ' ') infile.get(ch);//读空格后面的一个字符
        if(ch==' ')//空格后面还是空格，证明上一个空格应该被写进去，但是这个空格是分隔符所以不要了
        {
            tmpstr[tmplen]= ' ';
            tmplen++;
            infile.get(ch);
        }//剩下一种情况分别有数字和EOF两种情况，我们就交给下一轮处理
        
        List[idx].index=str_to_num(tmpstr,tmplen-1)-1;//如果是0设成-1以此类推
        if(List[idx].index == -1)
        {
            List[idx].code = new char[2];
            List[idx].code[0] = tmpstr[tmplen-1];
            List[idx].code[1] = '\0';
        }
        else{
            int codelen = strlen(List[List[idx].index].code);
            List[idx].code = new char[codelen+2];
            strcpy(List[idx].code, List[List[idx].index].code);
            List[idx].code[codelen] = tmpstr[tmplen-1];
            List[idx].code[codelen+1] = '\0';
        }
        outfile<<List[idx].code;
        idx ++;
    }
    infile.close();
    outfile.close();
    return 0;
}
