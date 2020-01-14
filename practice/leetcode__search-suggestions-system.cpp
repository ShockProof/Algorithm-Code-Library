/**
 * Problem Link:
 * https://leetcode.com/problems/search-suggestions-system/
 **/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TrieNode {
  int id[26];
  vector<int> ends;
  vector<int> suggestions;
};

vector<TrieNode> tree;

int addNode() {
  TrieNode tn = TrieNode();
  for (int i = 0 ; i < 26; i ++ ) tn.id[i] = -1;
  tn.ends = {};
  tn.suggestions = {};

  tree.push_back(tn);
  return tree.size() - 1;
};

int charId(char x) { return x-'a'; }

void insertInTrie(string &str, int inx) {
  int now = 0, strSize = str.size();
  for (int i = 0 ; i < strSize; i ++) {
    int cid = charId(str[i]);
    if (tree[now].id[cid] == -1) {
      tree[now].id[cid] = addNode();
    }
    now = tree[now].id[cid];
  }
  tree[now].ends.push_back(inx);
};

vector<int> dfs(int nodeIndex) {
  if(nodeIndex == -1) return {};

  TrieNode &node = tree[nodeIndex];

  node.suggestions = node.ends;

  for(int i = 0 ; i < 26; i ++) {
    vector<int> suggestions = dfs(node.id[i]);
    int j = 0;
    while(node.suggestions.size() < 3 && j < suggestions.size()) {
      node.suggestions.push_back(suggestions[j++]);
    }
  }

  return node.suggestions;
}

vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
  tree.clear();
  addNode(); /// root node at 0

  int productsSize = products.size();
  for(int i = 0; i < productsSize; i++) insertInTrie(products[i], i);

  dfs(0);

  vector<vector<string>> output = {};
  int searchWordSize = searchWord.size(), currentIndex = 0;
  for(int i = 0 ; i < searchWordSize; i ++) {
    output.push_back({});
    if (currentIndex != -1) currentIndex = tree[currentIndex].id[charId(searchWord[i])];
    if (currentIndex != -1) {
      for (auto j : tree[currentIndex].suggestions) {
        output[i].push_back(products[j]);
      }
    }
  }

  return output;
}

/// a simpler nlogn solution
vector<vector<string>> suggestedProductsNLOGN(vector<string>& products, string searchWord) {
  sort(products.begin(), products.end());

  auto prefixOf = [](string prefix, string s) -> bool {
    int prefixSize = prefix.size(), sSize = s.size();
    if (prefixSize > sSize) return false;
    for (int i = 0 ; i < prefix.size(); i ++) {
      if (prefix[i] != s[i]) return false;
    }
    return true;
  };

  vector<vector<string>> output = {};
  int x = 0, searchWordSize = searchWord.size(), productsSize = products.size();
  string build = "";
  for (int i = 0; i < searchWordSize; i ++) {
    output.push_back({});
    build.push_back(searchWord[i]);
    while(build > products[x] && x < productsSize) x ++;
    for (int j = x; j < productsSize; j ++) {
      if (prefixOf(build, products[j])) {
        output.back().push_back(products[j]);
      }
      if (output.back().size() == 3) break;
    }
  }
  return output;
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
