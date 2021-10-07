/* This is the TTrie.inc files to the templated TTrie class
 * that contains actual implementations to the public functions.
 * Shaopeng Zeng
 * Szeng 10
 * HW7
 */

#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include "TTrie.h"

template<typename DataType>
TTrie<DataType>::TTrie(const TTrie& rhs):is_end(false) {
  const TTrie<DataType>* temp_ptr = &rhs;
  copy(this, temp_ptr);
}

template<typename DataType>
TTrie<DataType>::~TTrie(void) {
  clear(this);
}

template<typename DataType>
TTrie<DataType>& TTrie<DataType>::operator=(const TTrie<DataType> &rhs) {
  clear(this);
  const TTrie<DataType>* temp_ptr = &rhs;
  copy(this, temp_ptr);
  return *this;
}

template<typename DataType>
TTrie<DataType>& TTrie<DataType>::operator+=(const std::vector<DataType> &sequence) {
  if (existed(sequence, this) == 0) {
    std::vector<DataType> temp_sequence = sequence;
    add(sequence, this, 1);
  }
  return *this;
}

template<typename DataType>
bool TTrie<DataType>::operator^(const std::vector<DataType> &sequence) const {
  if (existed(sequence, this) == 0) {
    return false;
  }
  else {
    return true;
  }
}

template<typename DataType>
bool TTrie<DataType>::operator==(const TTrie<DataType> &rhs) const {
  const TTrie<DataType>* temp_ptr = &rhs;
  if ((compare(this,temp_ptr)) + (compare(temp_ptr, this)) == 0) {
    return true;
  }
  else {
    return false;
  }
}

template<typename DataType>
std::ostream& operator<<(std::ostream &os, const TTrie<DataType> &ct) {
  // revise all other functions based on this
  std::stringstream ss;
  const TTrie<DataType>* temp_ptr = &ct;
  std::vector<DataType> empty_vec;
  ct.output(ss, temp_ptr, empty_vec);
  os << ss.str();
  return os;
}

template<typename DataType>
unsigned TTrie<DataType>::numChildren() const {
  unsigned count = 0;
  for (typename std::map<DataType, TTrie<DataType>*>::const_iterator ndIt = node.begin(); ndIt != node.end(); ndIt++) {
    count += 1;
  }
  return count;
}

template<typename DataType>
bool TTrie<DataType>::hasChild(const DataType &data) const {
  if ((node.count(data)) == 0) {
    return false;
  }
  else {
    return true;
  }
}

template<typename DataType>
bool TTrie<DataType>::hasChild() const {
  if(node.empty()) {
    return false;
  }
  else {
    return true;
  }
}

template<typename DataType>
const TTrie<DataType>* TTrie<DataType>::getChild(const DataType &data) const {
  if ((node.count(data)) == 0) {
    return nullptr;
  }
  else {
    typename std::map<DataType, TTrie<DataType>*>::const_iterator ndIt = node.find(data);
    return ndIt->second;
  }
}

template<typename DataType>
bool TTrie<DataType>::isEndpoint() const {
  return is_end;
}


template<typename DataType>
void TTrie<DataType>::add(std::vector<DataType> sequence, TTrie<DataType>* child_node, int mode) {
  // mode 0
  if (mode == 0) {
    if (sequence.size() > 0) {
      // create new nodes in the map
      TTrie<DataType>* temp_TTrie = new TTrie<DataType>();
      child_node->node[sequence[0]] = temp_TTrie;
      sequence.erase(sequence.begin());
      if (sequence.size() == 0) {
	temp_TTrie->is_end = true;
      }
      else {
	add(sequence, temp_TTrie, 0);
      }
    }
  }
  //mode1 1 searches for nodes to be added
  if (mode == 1) {
    if (child_node->node.count(sequence[0]) == 1) {
      typename std::map<DataType, TTrie<DataType>*>::iterator ndIt = child_node->node.find(sequence[0]);
      // if the whole sequence existed in the TTrie
      if (sequence.size() == 1 && !ndIt->second->isEndpoint()) {
	ndIt->second->is_end = true;
      }
      else {
	sequence.erase(sequence.begin());
	add(sequence, ndIt->second, 1);
      }
    }
    else {
      add(sequence, child_node, 0);
    }
  }
}


template<typename DataType>
int TTrie<DataType>::existed(std::vector<DataType> sequence, const TTrie<DataType>* child_node) const {
  int judgement = 0;
  // base case
  if (sequence.size() == 0) {
    if (child_node->isEndpoint()) {
      return 1;
    }
    else {
      return 0;
    }
  }
  // recursive case
  else {
    // if the first element of vector existed
    if (child_node->node.count(sequence[0]) == 1) {
      typename std::map<DataType, TTrie<DataType>*>::const_iterator ndIt = child_node->node.find(sequence[0]);
      sequence.erase(sequence.begin());
      // check next element
      judgement += existed(sequence, ndIt->second);
    }
    else{
      return 0;
    }
  }
  return judgement;
}

template<typename DataType>
void TTrie<DataType>::clear(TTrie<DataType>* children_node) {
  for (typename std::map<DataType, TTrie<DataType>*>::iterator ndIt = children_node->node.begin(); ndIt != children_node->node.end();) {
    delete ndIt->second;
    ndIt = children_node->node.erase(ndIt);
  }
}

template<typename DataType>
void TTrie<DataType>::copy(TTrie<DataType>* child_node_1, const TTrie<DataType>* child_node_2) {
  child_node_1->is_end = child_node_2->is_end;
  for (typename std::map<DataType, TTrie<DataType>*>::const_iterator ndIt = child_node_2->node.cbegin(); ndIt != child_node_2->node.cend(); ndIt++) {
    TTrie<DataType>* temp_Ttr = new TTrie<DataType>(*(ndIt->second));
    child_node_1->node[ndIt->first] = temp_Ttr;
    child_node_1->is_end = child_node_2->isEndpoint();
  }
}

template<typename DataType>
int TTrie<DataType>::compare(const TTrie<DataType>* child_node_1, const TTrie<DataType>* child_node_2) const {
  int judgement = 0;
  // check size() equality
  if (child_node_1->node.size() == child_node_2->node.size()) {
    for (typename std::map<DataType, TTrie<DataType>*>::const_iterator ndIt = child_node_1->node.cbegin(); ndIt != child_node_1->node.cend(); ndIt++) {
      if ((child_node_2->node.count(ndIt->first)) == 0) {
	return 1;
	break;
      }
      else {
	typename std::map<DataType, TTrie<DataType>*>::const_iterator ndIt2 = child_node_2->node.find(ndIt->first);
	if (ndIt->second->is_end != ndIt2->second->is_end) {// check each endpoint status
	  return 1;
	  break;
	}
	else {
	  judgement += compare(ndIt->second, ndIt2->second);
	}
      }
    }
  }
  else {
    return 1;
  }
  return judgement;
}

template<typename DataType>
void TTrie<DataType>::output(std::stringstream& ss,const TTrie<DataType>* node, std::vector<DataType> sequence) const {
  if (node->isEndpoint()) {
    for (int i = 0; i < (int)sequence.size() - 1; i++) {
      ss << sequence[i];
      ss << "-";
    }
    ss << sequence[sequence.size()-1];
    ss << "\n";
  }
  for (typename std::map<DataType, TTrie<DataType>*>::const_iterator ndIt = node->node.cbegin(); ndIt != node->node.cend(); ndIt++) {
    std::vector<DataType> updated_sequence = sequence;
    updated_sequence.push_back(ndIt->first);
    output(ss, ndIt->second, updated_sequence);
  }
}
