/* This is the CTrie.cpp fike that implements 
 * most of the public functions in CTrie class 
 * that stores character sequences.
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
#include "CTrie.h"


CTrie::CTrie(const CTrie& rhs) : CTrie() {
  const CTrie* temp_ptr = &rhs;
  copy(this, temp_ptr);
  
}


CTrie::~CTrie() {
  clear(this);
}


CTrie& CTrie::operator=(const CTrie &rhs) {
  clear(this);
  const CTrie* temp_ptr = &rhs;
  copy(this, temp_ptr);
  return *this;
}


CTrie& CTrie::operator+=(const std::string &word) {
  if (existed(word, this) == 0) {
    std::string temp_str = word;
    add(word, this, 1);
  }
  return *this;
}


bool CTrie::operator^(const std::string &word) const {
  if (existed(word, this) == 0) {
    return false;
  }
  else {
    return true;
  }
}

bool CTrie::operator==(const CTrie &rhs) const {
  const CTrie* temp_ptr = &rhs;
  // double check both sides
  if ((compare(this,temp_ptr)) + (compare(temp_ptr, this)) == 0) {
    return true;
  }
  else {
    return false;
  }
}

std::ostream& operator<<(std::ostream &os, const CTrie &ct) {
  // revise all other functions based on this
  std::stringstream ss;
  const CTrie* temp_ptr = &ct;
  ct.output(ss, temp_ptr, "");
  os << ss.str();
  return os;
}


unsigned CTrie::numChildren() const {
  unsigned count = 0;
  for (std::map<char, CTrie*>::const_iterator ndIt = node.begin(); ndIt != node.end(); ndIt++) {
    count += 1;
  }
  return count;
}

bool CTrie::hasChild(char character) const {
  if ((node.count(character)) == 0) {
    return false;
  }
  else {
    return true;
  }
}

bool CTrie::hasChild() const {
  if(node.empty()) {
    return false;
  }
  else {
    return true;
  }
}

const CTrie* CTrie::getChild(char character) const {
  if ((node.count(character)) == 0) {
    return nullptr;
  }
  else {
    std::map<char, CTrie*>::const_iterator ndIt = node.find(character);
    return ndIt->second;
  }
}

bool CTrie::isEndpoint() const {
  return is_end;
}

int CTrie::existed(std::string word, const CTrie* child_node) const {
  int judgement = 0;
  // base case
  if (word.length() == 0) {
    if (child_node->isEndpoint()) {
      return 1;
    }
    else {
      return 0;
    }
  }
  // recursive case
  else {
    // if the first char of the string existed
    if (child_node->node.count(word[0]) == 1) {
      std::map<char, CTrie*>::const_iterator ndIt = child_node->node.find(word[0]);
      // check the next character of the string
      judgement += existed(word.erase(0,1), ndIt->second);
    }
    else{
      return 0; // signify mismatch
    }
  }
  return judgement;   
}

void CTrie::add(std::string word, CTrie* child_node, int mode) {
  // mode 0
  if (mode == 0) {
    if (word.length() > 0) {
      CTrie* temp_CTrie = new CTrie();
      // create new values in the map
      child_node->node[word[0]] = temp_CTrie;
      std::string str = word.erase(0,1);
      if (str.length() == 0) {
	// assigning endpoint
	temp_CTrie->is_end = true;
      }
      else {
	add(str, temp_CTrie, 0);
      }
    }
  }
  //model 1 searches for nodes to be added
  if (mode == 1) {
    if (child_node->node.count(word[0]) == 1) {
      std::map<char, CTrie*>::iterator ndIt = child_node->node.find(word[0]);
      // if the whole sequence existed in the Tree
      if (word.length() == 1 && !ndIt->second->isEndpoint()) {
	ndIt->second->is_end = true;
      }
      else {
	add(word.erase(0,1), ndIt->second, 1);
      }
    }
    // if no matches, starting creating new node in mode 0
    else {
      add(word, child_node, 0);
    }
  }
}


void CTrie::clear(CTrie* children_node) {
  for (std::map<char, CTrie*>::iterator ndIt = children_node->node.begin(); ndIt != children_node->node.end();) {
    delete ndIt->second;
    ndIt = children_node->node.erase(ndIt);
  }
}

void CTrie::copy(CTrie* child_node_1, const CTrie* child_node_2) {
  child_node_1->is_end = child_node_2->is_end;
  for (std::map<char, CTrie*>::const_iterator ndIt = child_node_2->node.cbegin(); ndIt != child_node_2->node.cend(); ndIt++) {
    CTrie* temp_Ctr = new CTrie(*(ndIt->second));
    child_node_1->node[ndIt->first] = temp_Ctr;
    child_node_1->is_end = child_node_2->isEndpoint();

  }
}

int CTrie::compare(const CTrie* child_node_1, const CTrie* child_node_2) const {
  int judgement = 0;
  // check size() equality
  if (child_node_1->node.size() == child_node_2->node.size()) {
    for (std::map<char, CTrie*>::const_iterator ndIt = child_node_1->node.cbegin(); ndIt != child_node_1->node.cend(); ndIt++) {
      if ((child_node_2->node.count(ndIt->first)) == 0) {
	return 1;
	break;
      }
      else {
	std::map<char, CTrie*>::const_iterator ndIt2 = child_node_2->node.find(ndIt->first);
	// check each endpoint status
	if (ndIt->second->is_end != ndIt2->second->is_end) {
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

void CTrie::output(std::stringstream& ss,const CTrie* node, std::string str) const {
  if (node->isEndpoint()) {
    ss << str;
    ss << "\n";
  }
  for (std::map<char, CTrie*>::const_iterator ndIt = node->node.cbegin(); ndIt != node->node.cend(); ndIt++) {
    std::string updated_str = str + (ndIt->first);
    output(ss, ndIt->second, updated_str);
  }
}
