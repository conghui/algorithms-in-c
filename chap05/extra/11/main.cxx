#include <iostream>
#include <string>

using namespace std;
string repeatString(const string &str, size_t n);

int main(void)
{
    cout << repeatString("Hello", 3) << endl;
    return 0;
}


string repeatString(const string &str, size_t n)
{
    if (n == 0) {
        return "";
    }

    return repeatString(str, n-1) + str;
}
