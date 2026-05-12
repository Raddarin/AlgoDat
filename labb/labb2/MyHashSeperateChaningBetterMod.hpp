#include <functional>
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
    int index = keyhash(key_in) & (size - 1);
    for (KeyValPair &node : bucket_list[index]) {
      if (node.key == key_in) {
        return node.val;
      }
    }
    return V();
  }
  void put(K new_key, V new_val) {
    int index = keyhash(new_key) & (size - 1);
    for (KeyValPair &node : bucket_list[index]) {
      if (node.key == new_key) {
        node.val = new_val;
        return;
      }
    }
    bucket_list[index].push_back({new_key, new_val});
    elements++;
    if ((float)elements / size > 0.5) {
      size = size << 1;
      reyhash();
    }
  }

  bool remove(K key_in) {
    int index = keyhash(key_in) & (size - 1);
    std::vector<KeyValPair> &chain = bucket_list[index];

    for (auto node = chain.begin(); node != chain.end(); ++node) {
      if (node->key == key_in) {
        chain.erase(node);
        elements--;
        if ((float)elements / size < 0.25) {
          size = size >> 1;
          reyhash();
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
  ~MyHash() = default;

private:
  int size;
  int elements;
  std::vector<std::vector<KeyValPair>> bucket_list;
  size_t keyhash(const K &key) const { return std::hash<K>{}(key); }
  void reyhash() {
    std::vector<KeyValPair> temp_list = getAll();
    bucket_list.clear();
    elements = 0;
    bucket_list.resize(size);
    for (KeyValPair node : temp_list) {
      put(node.key, node.val);
    }
  }
};
