/* This is the templated class TTrie.h header files to the TTrie class
 * that involves the default constructors, private member
 * fields and private helper functions.
 * Shaopeng Zeng
 * Szeng 10
 * HW7
 */
#ifndef TTRIE_H
#define TTRIE_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

template< typename DataType>
class TTrie {
public:
  /**
   * Default Constructor.
   */
  TTrie(): is_end(false){}

  /**
   * Copy Constructor.
   * \param rhs A const reference to the input to copy.
   */
  TTrie(const TTrie& rhs);

  /**
   * Destructor.
   */
  ~TTrie();

  /**
   * Assignment operator.
   */
  TTrie& operator=(const TTrie<DataType> &rhs);

  /**
   * Overloaded addition/assignment operator to input a new vector into the TTrie.
   * \param sequence is the vector to insert into the trie
   * \return a reference to the TTrie object
   */
  TTrie& operator+=(const std::vector<DataType>& sequence);

  /**
   * Overloaded carat operator to check whether a given sequence exists in the object.
   * \param sequence is the sequence to find
   * \return true if the sequence is a member of the trie, false otherwise
   */
  bool operator^(const std::vector<DataType> &sequence) const;

  /**
   * Overloaded equality operator to check whether two TTrie objects are equal.
   * \param rhs A const reference to the TTrie object to compare.
   * \return true if the other object represents exactly the same set of sequences,
   *         false otherwise
   */
  bool operator==(const TTrie<DataType>& rhs) const;

  /**
   * \brief Overloaded output stream operator<< to print the sequences
   *        in the TTrie one per line, with values separated by '-'
   *        (hyphen) characters, in lexicographical order (note that if
   *        you use a map to represent links to children, a recursive
   *        traversal should allow you to generate the sequences in
   *        sorted order very easily)
   * \param os A reference to the output stream object
   * \param tt A constant reference to the input TTrie object
   * \return A reference to the output stream object
  */
  template< typename U>
  friend std::ostream& operator<<(std::ostream& os, const TTrie<U>& tt);

  /**
   * \return the number of children
   */
  unsigned numChildren() const;

  /**
   * \return true if there are any children, false otherwise
   */
  bool hasChild() const;

  /**
   * Check whether a child linked by a specific value exists.
   * \param value a value
   * \return true if there is a link to a child labeled with the value,
   *         false otherwise
   */
  bool hasChild(const DataType &value) const;

  /**
   * Get pointer to child node reachable via link labeled with
   * the specified value.
   * \param value a value
   * \return pointer to child node, or nullptr if there is no such child
   */
  const TTrie<DataType>* getChild(const DataType &value) const;

  /**
   * \return true if this node is an endpoint, false otherwise
   */
  bool isEndpoint() const; 

private:
  std::map<DataType, TTrie<DataType>*> node;
  bool is_end;
  
  /**
   * Check recursively whether the given sequence of dataType
   * can be represented in the Tree.
   * \return 1 if existed 0 otherwise
   */
  int existed(std::vector<DataType> sequence, const TTrie<DataType>* child_node) const;

  
  /*
   * add a particular vector of datatype sequence into the TTrie
   * recursively.There are two modes, 0 and 1.
   * Mode 0 is creating the new node in the child_node
   * Mode 1 is determines which child_node to be added
   * Mode 1 keeps searching for match and calls mode 0 to actually
   * add character and node.
   */
  void add(std::vector<DataType> sequence, TTrie<DataType>* child_node, int mode);
  

  /* 
   * delete all nodes recursively
   * \param children_node a pointer to TTrie
   */
  void clear(TTrie<DataType>* children_node);
  
  
  /*
   * copy all the information from child_node_2 to child_node_1 
   * \param child_node_1 the pointer to the TTrie to be copied to
   * \param child_node_2 the const pointer to the TTrie to be copied from
   */
  void copy(TTrie<DataType>* child_node_1, const TTrie<DataType>* child_node_2);

  /*
   * compare the Tree in child_node_1 with the Tree in child_node_2
   * \param child_node_1 the pointer to the first TTrie
   * \param child_node_2 the pointer to the second TTrie
   * \return 0 if every fields in child_node_1
   *  matches the information in child_node_2, and other positive integers otherwise
   */
  int compare(const TTrie<DataType>* child_node_1, const TTrie<DataType>* child_node_2) const;
  
  
  /*
   * outputs the each sequence of words in the given stringstream reference
   * \param ss reference to the stringstream
   * \param node the const pointer to the TTrie
   * \param str the string to be updated each time str is called 
   */
  void output(std::stringstream& ss,const TTrie<DataType>* node, std::vector<DataType> sequence) const;
  
};

#include "TTrie.inc"

#endif // TTRIE_H
