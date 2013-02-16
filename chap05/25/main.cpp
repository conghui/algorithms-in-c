#include <vector>
#include <iostream>
#include <string>

using namespace std;
void print(const vector<string> &v);
vector<string> matrix(int n);

int main(void)
{
    vector<string> v = matrix(4);
    print(v);
    return 0;
}

void print(const vector<string> &v)
{
    size_t i;

    for (i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }

    cout << "The total size is: " << v.size() << endl;
}

vector<string> matrix(int n)
{
    vector<string> ret;
    vector<string> newret;

    if (n == 1) {
        ret.push_back("0");
        ret.push_back("1");
        return ret;
    }

    ret = matrix(n-1);

    for (size_t i = 0; i < ret.size(); i++) {
        newret.push_back(ret[i] + "0");
        newret.push_back(ret[i] + "1");
    }

    return newret;
}
