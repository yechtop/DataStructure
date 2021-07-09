#include <iostream>
#include <string>

using namespace std;

int getStrIndex(string subStr, string str) {
    for (int i = 0; i < str.length() - subStr.length() + 1; ++i) {
        int j = 0;
        for (j = 0; j < subStr.length(); ++j) {
            if (str[i + j] != subStr[j])
                break;
        }
        if (j == subStr.length())
            return i;
    }
    return -1;
}

void buildNext(string str, int *next) {
    // 计算 next 数组
    next[0] = 0;
    for (int i = 1; i < str.length(); ++i) {
        int prevNext = next[i - 1];
        //如果当前字符和上一个字符的 next 位置相等，则直接加一就好
        if (str[i] == str[prevNext]) {
            next[i] = prevNext + 1;
        } else {
            //如果不等的话，就获取前一位置的 next
            int firstNext = prevNext > 0 ? (next[prevNext - 1]) : 0;
            next[i] = (str[firstNext] == str[i]) ? (firstNext + 1) : 0;
        }
    }
}

void buildNextPro(string str, int *next) {
    // 计算 next 数组
    int i = 1, now = 0;
    next[0] = 0;
    while (i < str.length()) {
        if (str[i] == str[now]) {
            next[i++] = ++now;
        } else if (now != 0) {
            //这种情况说明上一个位置是存在 next 的，则直接跳转到 next 位置去比较
            now = next[now - 1];
        } else {
            // 这种情况说明上一个位置不能处理，同时 now = 0
            // 说明已经比较过了 str[i] 和 str[0]，直接跳转到下一个就好
            next[i++] = 0;
        }
    }
}

int getStrIndexByKMP(string subStr, string str) {
    int next[subStr.length()];
    buildNextPro(subStr, next);
    int tar = 0, pos = 0;
    while (tar < str.length()) {
        if (subStr[pos] == str[tar]) {
            tar++;
            pos++;
            if (pos == subStr.length()) {
                return (tar - pos);
            }
        } else if (pos != 0) {
            pos = next[pos - 1];
        } else {
            tar++;
        }
    }
    return -1;
}

int main() {
    //0 0 0 1 2 0 0 0 1 2 3 4 5 3
    string a = "aaaaaaaaaa";
    int next[a.length()];
    buildNext(a, next);
    for (int i = 0; i < 10; ++i) {
        std::cout << next[i] << " ";
    }
}
