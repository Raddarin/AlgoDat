#include <stddef.h>
#include <vector>
template <typename K, typename V>

class MyHash {
public:
  struct KeyValPair {
    K key;
    V val;
  };

  MyHash() : size(1), elements(0) { bucket_list.resize(size); }

  V get(K key_in) {
    if (elements == 0) {
      return V();
    } else {
      int index = keyhash(key_in) % size;
      if (bucket_list[index].size == 1) {
        return bucket_list[index][0];
      } else {
        for (KeyValPair &node : bucket_list[index]) {
          if (node.key == key_in) {
            return node.val;
          }
        }
      }
    }
    return V();
  }

  void put(K new_key, V new_val) {
    int index = keyhash(new_key) % size;
    for (KeyValPair &node : bucket_list[index]) {
      if (node.key == new_key) {
        node.key = new_key;
      }
    }
    bucket_list[index].push_back({new_key, new_val});
    elements++;
    if ((float)elements / size > 0.5) {
      size = 2 * size;
      bucket_list.resize(size);
    }
  }

  bool remove(K key_in) {
    int index = keyhash(key_in) % size;
    std::vector<KeyValPair> &chain = bucket_list[index];

    for (KeyValPair &node = chain.begin(); node != chain.end(); ++node) {
      if (node.key == key_in) {
        chain.erase(node);
        elements--;
        if ((float)elements / size < 0.25) {
          size = size / 2;
          bucket_list.resize(size);
        }
        return true;
      }
    }
    return false;
  }
  std::vector<KeyValPair> getAll() const {
    std::vector<KeyValPair> all;
    for (const auto &bucket : bucket_list) {
      for (const auto &pair : bucket) {
        all.push_back(pair);
      }
    }
    return all;
  }
  MyHash(MyHash &&) = default;
  MyHash(const MyHash &) = default;
  MyHash &operator=(MyHash &&) = default;
  MyHash &operator=(const MyHash &) = default;
  ~MyHash();

private:
  int size;
  int elements;
  std::vector<std::vector<KeyValPair>> bucket_list;
};
