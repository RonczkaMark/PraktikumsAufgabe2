/*
 * Trie.h
 *
 *  Created on: 08.01.2015
 *      Author: Stefan
 */

#ifndef TRIE_H_
#define TRIE_H_

#include <utility>
#include <list>

namespace PA2 {

using namespace std;

template<class T, class E = char>

class Trie {



public:
	class TrieIterator;


	typedef basic_string<E> key_type; // string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;
	typedef TrieIterator iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	bool empty() const;


iterator insert(const value_type & pair) {
		Node * current = root;
		key_type wort = pair.first;
		iterator placeOfLeaf;

		for (typename key_type::iterator it = wort.begin(); it != wort.end();
				it++) {
			Node * check = current->getSon(*it);

				if (it == --wort.end()) {
					Node * newLeaf = new Leaf(current,pair);
					current->insert(newLeaf);
					placeOfLeaf =iterator(newLeaf);

				}
				else if (current == check) {
					Node * newNode = new InnerNode(current,*it);
					current->insert(newNode);
					current = newNode;
				}
				else{
					current =check;
				}

			}

		return placeOfLeaf;


	}

	void erase(const key_type& value);

	void clear(); // erase all
	iterator lower_bound(const key_type& testElement); // first element >= testElement
	iterator upper_bound(const key_type& testElement); // first element > testElement
	iterator find(const key_type& testElement); // first element == testElement
	iterator begin(); // returns end() if not found
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();




	Trie(){
		root = new InnerNode(0,'0');
	}




	class Node {
	public:

		Node(Node * par,E val) :
				value(val), parent(par) {

		}
		;
		virtual ~Node(){}

		Node* getParent() const {
			return parent;
		}

//		void setParent(const Node* parent) {
//			this->parent = parent;
//		}

		E getValue() const {
			return value;
		}

//		void setValue(const E value) {
//			this->value = value;
//		}
		virtual Node * getSon(const E)=0; //returns the Node which contains the searched value else this get back
		virtual const T * getData()const  =0;	//returns the saved value
		virtual void insert(Node * newSon) = 0; //for inserting a new Node

	private:
		Node * parent;
		E value;
	};

	class InnerNode: public Node {

	public:
		typedef std::list<Node *> listsetting;

		InnerNode(Node * par =0,E val ='0') :
				Node(par,val) {
		}
		~InnerNode() {
		}

		void insert(Node * newSon) {
			if (nodeList.empty()) {
				nodeList.push_front(newSon);
			} else {

				typename listsetting::iterator inSort;
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

		Node * getSon(const E searchedValue){

			for (typename listsetting::iterator it = nodeList.begin();
					it != nodeList.end(); it++) {
				if (searchedValue == (*it)->getValue()) {
					return *it;
				}
			}
			return this;

		}

		bool empty() {
			return nodeList.empty();
		}
		const T * getData()const{
			return NULL;
		}

	private:
		listsetting nodeList;

	};

	class Leaf:public Node{
	public:
		Leaf(Node * par,const value_type data):Node(par,'$'){

			this->data = & data.second;

		}
		Node * getSon(const E searchedValue){
			return this;
		}

		const T * getData()const{
			return data;
		}
		void insert(Node * newSon) {}


	private:

		const T * data;
	};

	class TrieIterator {
	public :
		TrieIterator(){
			current = 0;
		}

		TrieIterator(Node * cur):current(cur){

		}
		Node * operator * (){
			return current;
		}
		iterator operator ++(){
			current = current->getParent();
			return *this;
		}

	private:
		Node * current;

	};


	private:
	Node * root;
};

} /* namespace PA2 */

#endif /* TRIE_H_ */
