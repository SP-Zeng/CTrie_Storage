/* This is the CTrie.h header files to the CTrie class 
 * that involves the default constructors, private member
 * fields and private helper functions.
 * Shaopeng Zeng
 * Szeng 10
 * HW7
 */

#ifndef CTRIE_H
#define CTRIE_H
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <iterator>

class CTrie {
public:
  /**
   * Default Constructor.
   */
  CTrie(): is_end(false){}

  /**
   * Copy Constructor.
   * \param rhs A const reference to the input to copy.
   */
  CTrie(const CTrie& rhs);

  /**
   * Destructor.
   */
  ~CTrie();

  /**
   * Assignment operator.
   */
  CTrie& operator=(const CTrie &rhs);

  /**
   * Overloaded addition/assignment operator to input a new string into the Trie.
   * \param word is the word to input into the operator.
   * \return a reference to the CTrie object
   */
  CTrie& operator+=(const std::string& word);

  /**
   * Overloaded carat operator to check whether a given word exists in the object.
   * \param word the word to find.
   * \return true if the word is a member of the trie, false otherwise
   */
  bool operator^(const std::string &word) const;

  /**
   * Overloaded equality operator to check whether two Trie objects are equal.
   * \param rhs A const reference to the CTrie object to compare.
   * \return true if the other object represents exactly the same set of words,
   *         false otherwise
   */
  bool operator==(const CTrie& rhs) const;

  /**
   * \brief Overloaded output stream operator<< to print the CTrie in 
   * this format a word by line in alphabetical order
   *   e.g. if we have a CTrie with three words 'johns', 'hopkins', 'university'
   *    it will print "hopkins\njohns\nuniversity\n"
   * \param os A reference to the output stream object
   * \param q A constant reference to the input CTrie object
   * \return A reference to the output stream object
  */
  friend std::ostream& operator<<(std::ostream& os, const CTrie& ct);

  /**
   * \return the number of children
   */
  unsigned numChildren() const;

  /**
   * \return true if there are any children, false otherwise
   */
  bool hasChild() const;

  /**
   * Check whether a child linked by a specific character exists.
   * \param character a character
   * \return true if there is a link to a child labeled with the character,
   *         false otherwise
   */
  bool hasChild(char character) const;

  /**
   * Get pointer to child node reachable via link labeled with
   * the specified character.
   * \param character a character
   * \return pointer to child node, or nullptr if there is no such child
   */
  const CTrie* getChild(char character) const;

  /**
   * \return true if this node is an endpoint, false otherwise
   */
  bool isEndpoint() const; 

private:
  std::map<char, CTrie*> node;
  bool is_end;

  /**
   * Check recursively whether the given word
   * can be represented in the Tree.
   * \param word a string of sequence, child_node pointer to CTrie 
   * \return 1 if existed 0 otherwise
   */
  int existed(std::string word, const CTrie* child_node) const;

  
  /*
   * add a particular sequence of word into the CTrie
   * recursively.There are two modes, 0 and 1.
   * Mode 0 is creating the new node in the child_node
   * Mode 1 is determines which child_node to be added
   * Mode 1 keeps searching for match and calls mode 0 to actually
   * add character and node.
   * \param word a string of sequence, child_node pointer to CTrie, mode mode of add
   */
  void add(std::string word, CTrie* child_node, int mode);

  
  /* 
   * delete all nodes recursively
   * children_node a pointer to CTrie
   */
  void clear(CTrie* children_node);

  
  /*
   * copy all the information from child_node_2 to child_node_1 
   * \param child_node_1 the pointer to the CTrie to be copied to
   * \param child_node_2 the const pointer to the CTrie to be copied from
   */
  void copy(CTrie* child_node_1, const CTrie* child_node_2);

  
  /*
   * compare the Tree in child_node_1 with the Tree in child_node_2
   * \param child_node_1 the pointer to the first CTrie
   * \param child_node_2 the pointer to the second CTrie
   * \return 0 if every fields in child_node_1
   *  matches the information in child_node_2, and other positive integers otherwise
   */
  int compare(const CTrie* child_node_1, const CTrie* child_node_2) const;

  
  /*
   * outputs the each sequence of words in the given stringstream reference
   * \param ss reference to the stringstream
   * \param node the const pointer to the CTrie
   * \param str the string to be updated each time str is called 
   */
  void output(std::stringstream& ss,const CTrie* node, std::string str) const;
  
  
};

#endif // CTRIE_H
