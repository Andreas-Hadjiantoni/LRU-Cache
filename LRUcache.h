
#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <iostream>
#include <vector>
#include <unordered_map>

template <class K, class V>
class LRU_Cache {
public:
  LRU_Cache(int capacity, V defaultValue);
  V get(K key);
  void put(K key, V value);

private:
  typedef struct node{
    node* next;
    node* prev;
    K key;

    node(K k);
    node(K k, node* nextNode, node* prevNode);
  } node;

  int size;
  node* head;
  node* tail;
  V def;

  std::unordered_map<K, node*> nodePointers;
  std::unordered_map<K, V> cache;

  // Assumes that key exists
  void removeKey( K key );
};

#include "LRUcache.cpp"

#endif
