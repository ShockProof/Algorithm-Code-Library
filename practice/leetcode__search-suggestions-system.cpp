/**
 * Problem Link:
 * https://leetcode.com/problems/search-suggestions-system/
 **/

#include <iostream>
#include <vector>
using namespace std;

vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
  return {};
}

int main() {
  vector<string> products = {"mobile","mouse","moneypot","monitor","mousepad"};
  string searchWord = "mouse";

  vector<vector<string>> output = suggestedProducts(products, searchWord);

  vector<vector<string>> desiredOutput = {
    {"mobile","moneypot","monitor"},
    {"mobile","moneypot","monitor"},
    {"mouse","mousepad"},
    {"mouse","mousepad"},
    {"mouse","mousepad"},
  };

  cout << ((output == desiredOutput) ? "Acceppted" : "Wrong Answer") << endl;

  return 0;
}
