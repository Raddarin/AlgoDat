#include <iostream>
#include <string>
#include <unordered_map>

int main() {
  std::unordered_map<std::string, int> d;
  std::string word;
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int i = 0;

  while (std::getline(std::cin, word)) {
    bool is_present = d.count(word);
    bool remove_it = i % 16 == 0;

    if (is_present) {
      if (remove_it) {
        d.erase(word);
      } else {
        int count = d[word];
        d[word] = count + 1;
      }
    } else if (!remove_it) {
      d[word] = 1;
    }
    i++;
  }

  std::string best_word = "";
  int max_count = -1;

  for (auto const &[word, count] : d) {
    if (count > max_count) {
      max_count = count;
      best_word = word;
    }
  }
  for (auto const &[this_word, this_count] : d) {
    if (this_count == max_count && this_word < best_word) {
      best_word = this_word;
    }
  }
  std::cout << best_word << max_count;
}
