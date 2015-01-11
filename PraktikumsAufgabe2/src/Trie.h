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


	bool empty() const{
		return root->empty();
	}



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
				cout<<newNode->getValue()<<"\t";
				current = static_cast<InnerNode *> (newNode);
			} else {
				current =  static_cast<InnerNode *> (check);
			}

		}
		if (current->getSon('$') == current) {
					Node * newLeaf = new Leaf(current, pair);
					current->insert(newLeaf);
					cout<<newLeaf->getValue()<<"\t";
					placeOfLeaf = iterator(newLeaf);

				}

		cout<<endl;
		return placeOfLeaf;

	}

	void erase(const key_type& value){
		iterator it = this->find(value);

		Node * current= (*it);
		InnerNode * NextInner = static_cast<InnerNode *>(current->getParent());
		NextInner->remove(current);

		delete current;

			while(NextInner->empty() && NextInner != root){
				InnerNode * Copy =  static_cast<InnerNode *>(NextInner->getParent());
				cout<<"nächster Value \t"<<NextInner->getValue()<<endl;
				Copy->remove(NextInner);
				delete NextInner;
				NextInner = Copy ;

			}
	}

	void clear(); // erase all
	iterator lower_bound(const key_type& testElement); // first element >= testElement
	iterator upper_bound(const key_type& testElement); // first element > testElement

	iterator find(const key_type& testElement) {

		iterator found = end();
		InnerNode * current = root;


		for(typename key_type::const_iterator it = testElement.begin();it != testElement.end();it++) {
			current = static_cast<InnerNode *> (current->getSon(*it));
			cout<<"werte \t"<<current->getValue()<<endl;

		}

		if (current != current->getSon('$')) {
			found = iterator(current->getSon('$'));
			cout<<"werte \t"<<current->getSon('$')->getValue()<<endl;
		}

		return found;
	} // first element == testElement

	iterator begin(){
		InnerNode current = root;
		while(root->getLeft()){
			current = current.getLeft();
		}
		return iterator(current);
	}; // returns end() if not found
	iterator end() {
		return iterator(root);
	}
	reverse_iterator rbegin();
	reverse_iterator rend();

	Trie() {
		root = new InnerNode(0, '0');
	}

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

//		void setParent(const Node* parent) {
//			this->parent = parent;
//		}

		E getValue() const {
			return value;
		}

//		void setValue(const E value) {
//			this->value = value;
//		}
//		virtual Node * getSon(const E)=0; //returns the Node which contains the searched value else this get back
//		virtual const T getData() const =0;	//returns the saved value
//		virtual void insert(Node * newSon) = 0; //for inserting a new Node
//		virtual bool empty()const  = 0;

	private:
		Node * parent;
		E value;
	};

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

		Node * getSon(const E searchedValue) {

			for (typename listsetting::iterator it = nodeList.begin();
					it != nodeList.end(); it++) {
				if (searchedValue == (*it)->getValue()) {
					return *it;
				}
			}
			return this;

		}

		Node * getLeft(){
			return *(nodeList.begin());
		}
		typename listsetting::iterator getRight(){
			cout<<nodeList.size();
//			if(nodeList.size()>2){
//			return ++(nodeList.begin());
//			}

				return nodeList.end();

		}

		bool empty() const{
			return nodeList.empty();
		}

		void remove(Node * node){
			nodeList.remove(node);

		}
	private:
		listsetting nodeList;

	};

	class Leaf: public Node {
	public:
		Leaf(Node * par, const value_type data) :
				Node(par, '$') {

			this->data = data.second;

		}

		const T  getData() const {
			return data;
		}


	private:

		T data;
	};

	class TrieIterator {
	public:
		friend class InnerNode;
		TrieIterator() {
			current = 0;
		}

		TrieIterator(Node * cur) :
				current(cur) {

		}
		Node * operator *() {
			return current;
		}
		iterator operator ++() {
			InnerNode * walkNode =  static_cast <InnerNode * >(current);

			//ist blatt
			if(current->getValue() == '$' ){
				current = current->getParent();
			}
			//hat rechte Nodes
			else if(walkNode->nodeList){
					current = current->getParent();


			}
			else if(currentIter != walkNode->getRight()){
				currentIter = walkNode->getRight();
					current = *currentIter ;
			}
//			else{
//				current= *(++(currentIter));
//			}



			cout<<"mal ein test für ++operator \t" << current->getValue() <<endl;
			return *this;
		}

	private:
		typename InnerNode::listsetting::iterator currentIter;
		Node * current;



	};

private:
	InnerNode * root;




};

} /* namespace PA2 */

#endif /* TRIE_H_ */
