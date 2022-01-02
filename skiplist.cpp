//
// Created by Yusuf Pisan on 4/26/18.
//

#include <cassert>
#include <climits>
#include <cstdlib>
#include <iostream>

#include "skiplist.h"

using namespace std;

ostream &operator<<(ostream &out, const SkipList &skip) {
  for (int d = skip.maxLevel - 1; d >= 0; d--) {
    out << d << ": ";
    auto *curr = skip.head->forward[d];
    if (curr != skip.tail) {
      out << curr->value;
      curr = curr->forward[d];
    }
    while (curr != nullptr && curr != skip.tail) {
      out << "-->" << curr->value;
      curr = curr->forward[d];
    }
    out << endl;
  }
  return out;
}

SNode::SNode(int value) : value{value} {}

// // how many forward/backward pointers it has
// int SNode::height() const { return 0; }

// // increase the number of forward/backward pointers it has
// void SNode::increaseHeight() {}

SkipList::SkipList(int maxLevel, int probability)
    : maxLevel{maxLevel}, probability{probability} {
  assert(maxLevel > 0 && probability >= 0 && probability < 100);
  head = new SNode(INT_MIN);
  tail = new SNode(INT_MAX);
  for (int i = 0; i < maxLevel; i++) {
    head->forward.push_back(tail);
    tail->backward.push_back(head);
  }
}

bool SkipList::shouldInsertAtHigher() const {
  return rand() % 100 < probability;
}

bool SkipList::add(const vector<int> &values) {
  bool result = false;
  // NOLINTNEXTLINE
  for (int value = 0; value < values.size(); value++) {
    result = add(values[value]);
  }
  return result;
}

bool SkipList::add(int value) {

  // check if duplicate
  SNode *temp = containsSNode(value);
  if (temp != nullptr) {
    return false;
  }

  // create node
  auto *insertedNode = new SNode(value);
  insertedNode->forward.push_back(nullptr);
  insertedNode->backward.push_back(nullptr);

  while (insertedNode->forward.size() < maxLevel && shouldInsertAtHigher()) {
    insertedNode->forward.push_back(nullptr);
    insertedNode->backward.push_back(nullptr);
  }

  SNode *iter = head;
  for (int level = maxLevel - 1; level >= 0; level--) {
    while (iter->forward[level] != tail &&
           iter->forward[level]->value < value) {
      iter = iter->forward[level];
    }

    if (level < insertedNode->forward.size()) {
      // Connect iter with insertedNode, connect inserted_column with nextIter
      SNode *nextIter = iter->forward[level];
      iter->forward[level] = insertedNode;
      nextIter->backward[level] = insertedNode;
      insertedNode->backward[level] = iter;
      insertedNode->forward[level] = nextIter;
    }
  }
  return true;
}

SkipList::~SkipList() {
  for (int d = maxLevel - 1; d >= 0; d--) {
    SNode* currNode = head -> forward[d];
    SNode* nextNode = nullptr;
    while(currNode != tail) {
      nextNode = currNode -> forward[d];
      remove(currNode->value);
      currNode = nextNode;
    }
  }
  // need to delete individual nodes
  delete head;
  delete tail;
}

bool SkipList::remove(int data) {
  // check if the value is existed
  SNode *erasedNode = containsSNode(data);
  if (erasedNode == nullptr || erasedNode == tail ||
      erasedNode->value != data) {
    return false;
  }
  // check to remove
  SNode *iter = head;
  for (int level = maxLevel - 1; level >= 0; level--) {
    while (iter->forward[level] != tail &&
           iter->forward[level]->value <= data) {
      iter = iter->forward[level];
    }
    if (iter == erasedNode) {
      // Connect previousIter with nextIter
      SNode *previousIter = iter->backward[level],
            *nextIter = iter->forward[level];
      previousIter->forward[level] = nextIter;
      nextIter->backward[level] = previousIter;
    }
  }
  delete erasedNode;
  return true;
}

// get the node that would be before this data
// at level-0
// vector<SNode *> SkipList::getBeforeNodes(int data) const {
//   vector<SNode *> v(maxLevel);
//   return v;
// }

SNode *SkipList::containsSNode(int data) const {
  SNode *iter = head;
  for (int level = maxLevel - 1; level >= 0; level--) {
    while (iter->forward[level] != tail && iter->forward[level]->value < data) {
      iter = iter->forward[level];
    }
  }
  if (iter->forward[0]->value == data) {
    return iter->forward[0];
  }
  return nullptr;
}

bool SkipList::contains(int data) const {
  SNode *iter = head;
  for (int level = maxLevel - 1; level >= 0; level--) {
    while (iter->forward[level] != tail && iter->forward[level]->value < data) {
      iter = iter->forward[level];
    }
  }
  return iter->forward[0]->value == data;
}

// void SkipList::connect2AtLevel(SNode *a, SNode *b, int level) {}

// void SkipList::connect3AtLevel(SNode *a, SNode *b, SNode *c, int level) {}