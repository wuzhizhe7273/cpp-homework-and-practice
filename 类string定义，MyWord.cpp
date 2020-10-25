#include<iostream>
#include<cstring>
using namespace std;
class MyWord
{
private:
    char* data;
    int size;
public:
    MyWord(char* Word = "")
    {
        if (Word == nullptr)
        {
            data = new char[1];
            *data = '\0';
            size = 0;
        }
        else
        {
            int length = strlen(Word);
            data = new char(length + 1);
            strcpy(data, Word);
            size = length;
        }
    }
    MyWord(const MyWord& T) :data(new char[strlen(T.data + 1)])
    {
        strcpy(data, T.data);
        size = T.size;
    };
    MyWord& operator=(const MyWord& T)
    {
        if (this != &T)
        {
            delete[] data;
            data = new char[T.size + 1];
            strcpy(data,T.data);
            size = T.size;
        }
        return *this;
    };
    friend std::ostream& operator<<(std::ostream& os, const MyWord& obj);
    friend istream& operator>>(istream& is, MyWord& T);
    MyWord operator+(const MyWord& T)
    {
        MyWord tmp;
        delete tmp.data;
        tmp.data = new char[size + T.size + 1];
        strcpy(tmp.data, data);
        strcat(tmp.data, T.data);
        tmp.size = size + T.size;
        return tmp;
    }
    char* find(const char* needle)
    {
        return strstr(data, needle);
    }
    char* replace(char* detama, char* shit)
    {

        char* fuck_1;
        char* fuck_2;
        char* pos = find(detama);
        if (pos != NULL)
        {
            *pos = '\0';
            fuck_1 = new char[strlen(data)];
            strcpy(fuck_1, data);
            fuck_2 = new char[strlen(pos + 1)];
            strcpy(fuck_2, pos + strlen(detama));
            delete[] data;
            data = new char[strlen(fuck_1) + strlen(shit) + strlen(fuck_2) + 1];
            *data = '\0';
            strcat(strcat(strcat(data, fuck_1), shit), fuck_2);
            size = strlen(data);
            delete[] fuck_1;
            delete[] fuck_2;
            return data;
        }
        else
        {
            return NULL;
        }

    }
    MyWord replace_All(char* detama, char* shit)
    {
        while (replace(detama, shit) != NULL) {};
        return *this;
    }
    ~MyWord()
    {
        if (data != nullptr)
        {
            delete[] data;
        }
    }
};
std::ostream& operator<<(std::ostream& os, const MyWord& obj)
{
    os << obj.data;
    return os;
}
istream& operator>>(istream& is, MyWord& T)
{
    char tmp[1000];
    is >> tmp;
    T.size = strlen(tmp);
    delete[] T.data;
    T.data = new char[T.size + 1];
    strcpy(T.data, tmp);
    return is;
}
int main()
{
    MyWord shit("This is an ugly world!");
    shit.replace_All("This", "That");
    cout<<shit<<endl;
    MyWord shit_1("I hate it!");
    MyWord shit_2;
    shit_2=shit_1;
    cout<<shit_2<<endl;
    MyWord shit_3;
    cin>>shit_3;
    cout<<(shit_3+shit_1+shit);
}
