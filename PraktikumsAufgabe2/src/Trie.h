/*
 * Trie.h
 *
 *  Created on: 08.01.2015
 *      Author: Stefan Ronczka
 */

#ifndef TRIE_H_
#define TRIE_H_

#include <utility>
#include <list>
#include <stack>

namespace PA2 {

using namespace std;

template<class T, class E = char>

class Trie {

public:
	class TrieIterator;
	class InnerNode;

	typedef basic_string<E> key_type; // string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;
	typedef TrieIterator iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;

	bool empty() const {
		return root->empty();
	}
	//this method is inserting an new value pair

	iterator insert(const value_type & pair) {
		InnerNode * current = root;
		key_type wort = pair.first;
		iterator placeOfLeaf;

		for (typename key_type::iterator it = wort.begin(); it != wort.end();
				it++) {
			Node * check = current->getSon(*it);

			if (current->getValue() == check->getValue()) {
				Node * newNode = new InnerNode(current, *it);
				current->insert(newNode);
				cout << newNode->getValue() << "\t";
				current = static_cast<InnerNode *>(newNode);
			} else {
				current = static_cast<InnerNode *>(check);
			}

		}
		if (current->getSon('$') == current) {
			Node * newLeaf = new Leaf(current, pair);
			current->insert(newLeaf);
			cout << newLeaf->getValue() << "\t";
			placeOfLeaf = iterator(newLeaf);

		}

		cout << endl;
		return placeOfLeaf;

	}

	//this methode is erase the pair with the key_type
	void erase(const key_type& value) {
		iterator it = this->find(value);

		Node * current = (*it);
		InnerNode * NextInner = static_cast<InnerNode *>(current->getParent());
		NextInner->remove(current);

		delete current;

		while (NextInner->empty() && NextInner != root) {
			InnerNode * Copy = static_cast<InnerNode *>(NextInner->getParent());
			cout << "nächster Value \t" << NextInner->getValue() << endl;
			Copy->remove(NextInner);
			delete NextInner;
			NextInner = Copy;

		}
	}


	void clear(); // erase all
	iterator lower_bound(const key_type& testElement); // first element >= testElement
	iterator upper_bound(const key_type& testElement); // first element > testElement


	//find the pair with the key_type testelement
	iterator find(const key_type& testElement) {

		iterator found = end();
		InnerNode * current = root;

		//searches an node for each letter
		for (typename key_type::const_iterator it = testElement.begin();
				it != testElement.end(); it++) {

			current = static_cast<InnerNode *>(current->getSon(*it));
			cout << "werte \t" << current->getValue() << endl;

		}

		//test that the last is an leaf
		if (current != current->getSon('$')) {
			found = iterator(current->getSon('$'));
			cout << "werte \t" << current->getSon('$')->getValue() << endl;
		}

		return found;
	} // first element == testElement

	iterator begin() {
		//gives the lefttest node
		InnerNode * current = root;
		while (current->getLeft()->getValue() != '$') {
			current = static_cast<InnerNode *>(current->getLeft());
		}

		return iterator(current->getLeft());
	} // returns end() if not found
	//give the root
	iterator end() {
		return iterator(root);
	}

	Trie() {
		root = new InnerNode(0, '0');
	}

	//ABC for the tree Node structur
	class Node {
	public:

		Node(Node * par, E val) :
				value(val), parent(par) {

		}
		;
		virtual ~Node() {
		}

		Node* getParent() const {
			return parent;
		}


		E getValue() const {
			return value;
		}



	private:
		Node * parent;
		E value;
	};

	//the nodes contains an list of sub nodes
	class InnerNode: public Node {

	public:
		friend class TrieIterator;
		typedef std::list<Node *> listsetting;

		InnerNode(Node * par = 0, E val = '0') :
				Node(par, val) {
		}
		~InnerNode() {
		}

		void insert(Node * newSon) {
			typename listsetting::iterator inSort = nodeList.begin();
			if (nodeList.empty()) {
				nodeList.insert(inSort, newSon);
			} else {

				for (typename listsetting::iterator it = nodeList.begin();
						it != nodeList.end(); it++) {
					if (newSon->getValue() > (*it)->getValue()) {
						inSort = it;
						it = --nodeList.end();
					}
				}
				nodeList.insert(inSort, newSon);
			}
		}

		// searched an son in the list with the seachedValue return s this if nothing is found
		Node * getSon(const E searchedValue) {

			for (typename listsetting::iterator it = nodeList.begin();
					it != nodeList.end(); it++) {
				if (searchedValue == (*it)->getValue()) {
					return *it;
				}
			}
			return this;

		}

		//return the in the list left Node
		Node * getLeft() {
			return *(nodeList.begin());
		}

		//return s an right node if there is one
		//if not it return s itself
		Node * getRight() {
			if (nodeList.size() >= 2) {
				return *(++(nodeList.begin()));
			} else {
				return this;
			}
		}

		//should find an next right node if not it returns itself
		Node * getRight(Node * node) {
			if (node == 0) {
				return this;
			}
			return getSon(node->getValue());

		}
		// return true if the nodelist is empty
		bool empty() const {
			return nodeList.empty();
		}

		//removes the node s from the list
		void remove(Node * node) {
			nodeList.remove(node);

		}
	private:
		listsetting nodeList;

	};

	//sub class for the translation words or other template arg Es
	class Leaf: public Node {
	public:
		Leaf(Node * par, const value_type data) :
				Node(par, '$') {

			this->data = data.second;

		}


		//return the data
		const T getData() const {
			return data;
		}

	private:

		T data;
	};

	//should traverse through the tree
	class TrieIterator {
	public:
		friend class InnerNode;
		TrieIterator() {
			current = 0;
		}


		TrieIterator(Node * cur) :
				current(cur) {
//			Node * present =cur;
//			do {
//				Node * present = cur->getParent();
//				nodeStack.push_back(present);
//			} while (present);

		}
		//return the carried node
		Node * operator *() {
			return current;
		}
		iterator operator ++() {
			InnerNode * walkNode = static_cast<InnerNode *>(current);

			//ist blatt
//			if (current->getValue() == '$' || walkNode->getRight() == current) {
//
//				current = nodeStack.front();
//				nodeStack.pop_front();
//
//			}

			current = walkNode->getParent();
//
//			else if(nodeStack.front() == current->getParent()){
//				if(current != walkNode->getLeft()){
//					nodeStack.push_front(current);
//					current = walkNode->getLeft();
//
//				}




			cout << "mal ein test für ++operator \t" << current->getValue()
					<< endl;
			return *this;
		}

	private:
		typename InnerNode::listsetting::iterator currentIter;
		Node * current;
		list<Node *> nodeStack;
		Node * prevRight = NULL;

	};

private:

	//the node the tree starts with
	InnerNode * root;

};

} /* namespace PA2 */

#endif /* TRIE_H_ */
