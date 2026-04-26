#include "MyHash.hpp"
#include <iostream>
#include <string>

int main() {
  // std::unordered_map<std::string, int> d;
  MyHash<std::string, int> d;
  std::string word;
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  int i = 0;

  while (std::getline(std::cin, word)) {
    bool is_present = (d.get(word) != 0);
    bool remove_it = i % 16 == 0;

    if (is_present) {
      if (remove_it) {
        d.remove(word);
      } else {
        int count = d.get(word);
        d.put(word, count + 1);
      }
    } else if (!remove_it) {
      d.put(word, 1);
    }
    i++;
  }

  std::string best_word = "";
  int max_count = -1;

  for (auto const &[word, count] : d.getAll()) {
    if (count > max_count) {
      max_count = count;
      best_word = word;
    }
  }

  for (auto const &[this_word, this_count] : d.getAll()) {
    if (this_count == max_count && this_word < best_word) {
      best_word = this_word;
    }
  }
  std::cout << best_word << max_count;
}
