#include<vector>
#include<sstream>
#include<iostream>
using namespace std;
//字符串分割，来自https://segmentfault.com/a/1190000002483483
vector<string>& split(const string& str, char delim, vector<string>& elems, bool skip_empty = true) {
    istringstream iss(str);
    for (string item; getline(iss, item, delim); )
        if (skip_empty && item.empty()) continue;
        else elems.push_back(item);
    return elems;
}//字符串转数字
double stringToNum(const string& str)
{
    istringstream iss(str);
    double num;
    iss >> num;
    return num;
}

//类定义
class Matrix
{
private:
    vector<vector<double>> matrix;
    int row, line;
public:
    static int count;
    Matrix(string shit = "0")
    {
        vector<string> str_1;
        split(shit, '|', str_1);
        row = str_1.size();
        for (auto i = str_1.begin(); i < str_1.end(); i++)
        {
            vector<string> str_3;
            split(*i, ' ', str_3);
            vector<double> fuck;
            for (auto i = str_3.begin(); i < str_3.end(); i++)
            {
                fuck.push_back(stringToNum(*i));
            }
            matrix.push_back(fuck);
            line = fuck.size();
        }
        count++;
    }
    Matrix& loadMatrix(string shit)
    {
        matrix.clear();
        vector<string> str_1;
        split(shit, '|', str_1);
        row = str_1.size();
        for (auto i = str_1.begin(); i < str_1.end(); i++)
        {
            vector<string> str_3;
            split(*i, ',', str_3);
            vector<double> fuck;
            for (auto i = str_3.begin(); i < str_3.end(); i++)
            {
                fuck.push_back(stringToNum(*i));
            }
            matrix.push_back(fuck);
            line = fuck.size();
        }
        return *this;
    };
    Matrix(const Matrix& T)
    {
        matrix = T.matrix;
        row = T.row;
        line = T.line;
    }
    Matrix& operator=(const Matrix& T)
    {
        if (this != &T)
        {
            matrix = T.matrix;
            row = T.row;
            line = T.line;
        }
        return *this;
    }
    Matrix operator+(const Matrix& T)
    {
        Matrix tmp;
        tmp.matrix.clear();
        if (row == T.row && line == T.line)
        {
            tmp.row = T.row;
            tmp.line = T.line;
            for (int i = 0; i < row; i++)
            {
                vector<double> shit;
                for (int j = 0; j < line; j++)
                {
                    shit.push_back(matrix[i][j] + T.matrix[i][j]);
                }
                tmp.matrix.push_back(shit);
            }
        }
        else
        {
            cout << "不符合规则" << endl;
        }
        return tmp;
    };
    friend std::ostream& operator<<(ostream& os, Matrix& T);
    friend std::istream& operator>>(istream& is, Matrix& T);
    friend Matrix operator-(const Matrix& rhs, const Matrix& lhs);
    double SetMatrix(int m, int n, double num)
    {
        matrix[m][n] = num;
    };
    ~Matrix() {};

};
//计数器
int Matrix:: count = 0;
Matrix operator-(const Matrix& rhs, const Matrix& lhs)
{
    Matrix tmp;
    tmp.matrix.clear();
    if (lhs.row == rhs.row && rhs.line == lhs.line)
    {
        tmp.row = rhs.row;
        tmp.line = rhs.line;
        for (int i = 0; i < tmp.row; i++)
        {
            vector<double> shit;
            for (int j = 0; j < tmp.line; j++)
            {
                shit.push_back(rhs.matrix[i][j] - lhs.matrix[i][j]);
            }
            tmp.matrix.push_back(shit);
        }
    }
    else
    {
        cout << "不符合规则" << endl;
    }
    return tmp;
};
std::ostream& operator<<(ostream& os, Matrix& T)
{
    for (int i = 0; i < T.row; i++)
    {
        for (int j = 0; j < T.line; j++)
        {
            os << T.matrix[i][j] << " ";
        }
        os << endl;
    }
    return os;
}
std::istream& operator>>(istream& is, Matrix& T)
{
    string str;
    is >> str;
    T.loadMatrix(str);
    return is;
}
int main()
{
    Matrix shit("1 2 3 4|5 6 7 8|");
    Matrix shit_2("3 4 5 6|7 8 9 10|");
    Matrix shit_3;
    shit_3=shit+shit_2;
    cout << shit_3;
    shit_3=shit-shit_2;
    cout<<shit_3;
    cin>>shit_3;
    cout<<shit_3;

}
