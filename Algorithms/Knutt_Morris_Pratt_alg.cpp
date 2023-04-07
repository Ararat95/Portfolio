#include <iostream>
#include <string>
#include <vector>

void Knutt_alg(const std::string&, const std::string&);
void get_lps(const std::string&, const int, std::vector<int>&);
int main() {

    std::string pattern;
    std::string text;
    std::cout << "input text you need to check" << std::endl;
    getline(std::cin, text);
    std::cout << "type pattern you need to find" << std::endl;
    getline(std::cin, pattern);
    Knutt_alg(text, pattern);

    return 0;
}

void Knutt_alg(const std::string& text, const std::string& pattern) {
    const int pat_size = pattern.size();
    const int text_size = text.size();
    std::vector<int> lps(pat_size, 0);
    get_lps(pattern, pat_size, lps);
    for (int i = 0, j = 0; (text_size - i) > (pat_size - j);) {
        if (text[i] == pattern[j]) {
            ++i, ++j;
        }
        if(j == pat_size) {
            std::cout << "Pattern found at index: " << i - j << std::endl;
            j = lps[j - 1];
        }
        else if (i < text_size && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                ++i;
            }
        }
    }
}

void get_lps(const std::string& pattern, const int size, std::vector<int>& lps) {
    int len = 0;
    
    for (int key = 1; key < size;) {
        if (pattern[key] == pattern[len]) {
            ++len;
            lps[key] = len;
            ++key;
        }
        else {
            if(len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[key] = len;
                ++key;
            }
        }
    }
}