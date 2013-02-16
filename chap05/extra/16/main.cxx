#include <iostream>
#include <string>
#include <cctype>

using namespace std;
string disemvowel(const string &str);
string _disemvowel(const char *str, int a, int b);
bool isVowel(int c);

int main(void)
{
    string str = "aeiou12345iouea";
    string dis = disemvowel(str);
    cout << "The disemvowel of " << str << " is: " << dis << endl;
    return 0;
}

string disemvowel(const string &str)
{
    return _disemvowel(str.c_str(), 0, str.length() - 1);
}

string _disemvowel(const char *str, int a, int b)
{
    if (a == b) {
        string ret = "";

        if (!isVowel(str[a])) {
            ret += str[a];
        }

        return ret;
    }

    string ret = _disemvowel(str, a, b-1);

    if (!isVowel(str[b])) {
        ret += str[b];
    }

    return ret;
}

bool isVowel(int c)
{
    switch (tolower(c)) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
    }

    return false;
}

