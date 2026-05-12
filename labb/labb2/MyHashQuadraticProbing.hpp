#include <functional>
#include <stddef.h>
#include <vector>
template <typename K, typename V>

class MyHash {
  enum Status { EMPTY, OCCUPIED, DELETED };

public:
  struct KeyValPair {
    K key;
    V val;
    Status status = EMPTY;
  };

  MyHash() : size(1), elements(0) { bucket_list.resize(size); }

  V get(K key_in) {
    int start_index = keyhash(key_in) % size;
    for (size_t i = 0; i < size; ++i) {
      size_t index = (start_index + i * i) % size;

      if (bucket_list[index].status == EMPTY)
        break;
      if (bucket_list[index].status == OCCUPIED &&
          bucket_list[index].key == key_in) {
        return bucket_list[index].val;
      }
    }

    return V();
  }
  void put(K new_key, V new_val) {
    size_t start_index = keyhash(new_key) % size;
    if ((float)(elements + 1) / size > 0.4) {
      size *= 2;
      reyhash();
    }

    int first_deleted = -1;

    for (size_t i = 0; i < size; ++i) {
      size_t index = (start_index + i * i) % size;

      if (bucket_list[index].status == OCCUPIED &&
          bucket_list[index].key == new_key) {
        bucket_list[index].val = new_val;
        return;
      }

      if (bucket_list[index].status != OCCUPIED && first_deleted == -1) {
        first_deleted = index;
      }

      if (bucket_list[index].status == EMPTY)
        break;
    }

    if (first_deleted != -1) {
      bucket_list[first_deleted].key = new_key;
      bucket_list[first_deleted].val = new_val;
      bucket_list[first_deleted].status = OCCUPIED;
      elements++;
    }
  }
  bool remove(K key_in) {
    size_t start_index = keyhash(key_in) % size;
    for (size_t i = 0; i < size; ++i) {
      size_t index = (start_index + i * i) % size;

      if (bucket_list[index].status == EMPTY)
        break;

      if (bucket_list[index].status == OCCUPIED &&
          bucket_list[index].key == key_in) {
        bucket_list[index].status = DELETED;
        elements--;

        if (size < 0.125) {
          size = size / 2;
          reyhash();
        }

        return true;
      }
    }
    return false;
  }
  std::vector<KeyValPair> getAll() const {
    std::vector<KeyValPair> all;
    for (const auto &pair : bucket_list) {
      if (pair.status == OCCUPIED) {
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
  std::vector<KeyValPair> bucket_list;
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
