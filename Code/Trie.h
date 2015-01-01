/*
 * Trie.h
 *
 *  Created on: 02.12.2014
 *      Author: Sau
 */

#ifndef TRIE_H_
#define TRIE_H_

#include "String"
#include "iostream"
#include "list"
#include "memory"
#include "Node.h"
#include "pair.h"


namespace PA2 {


template<class T, class E = char>
class Trie {

	class TrieIterator;



public:
	typedef std::basic_string<E> key_type; // string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;
	typedef TrieIterator iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;

	bool empty() const{
		return (begin != end);

	};
	iterator insert(const value_type & value){

		key_type insertString = value.getKey();
		Node check;
		InnerNode current = father;
		for(int i = 0;i < insertString.length();i++){

		key_type subKey = insertString.substr(0,i);



		check=current.checkForExistingPath(subKey);

		if(current == check);
		InnerNode newNode = new InnerNode(current,subKey);
		}

	};
	void erase(const key_type& value);

	void clear(); // erase all
	 iterator lower_bound(const key_type& testElement); // first element >= testElement
	 iterator upper_bound(const key_type& testElement); // first element > testElement
	 iterator find(const key_type& testElement); // first element == testElement
	 iterator begin(){


	 }; // returns end() if not found
	 iterator end();
	 reverse_iterator rbegin();
	 reverse_iterator rend();

	Trie(){
		this->father = new InnerNode (0,"");
	};

private:

	 class InnerNode : public  Node{

		typedef std::list<Node *, std::allocator<E> > nodeList;

	public:
		 InnerNode(Node par,key_type value): Node(par){
			this->value = value;
			nodePointerList = nodeList();
		};


		void addSon(Node * newSon) {
			nodePointerList.insert(newSon);
		};

		Node getTheLeftElement(){
			return nodePointerList.first();
		};
		Node checkForExistingPath(key_type & path){
			typename nodeList::iterator it= nodePointerList.begin();
			Node target = this;
			while(*it != path){
				it++;

			}
			if(it == path){
				target = *it;
			}


			return target;
		}
		const key_type& getValue() const {
			return value;
		}

		void setValue(const key_type& value) {
			this->value = value;
		}

		;



	private:
		key_type value;
		nodeList nodePointerList;
	};


	class TrieIterator{
		 public:
		 TrieIterator(Node * cur):current(cur){

		 };
		 private:
		 Node & current;

		 //return the next Iterator walk throught the tree inorder
		 TrieIterator operator++(){

		 }

	};


	// variables

	InnerNode * father;


};

} /* namespace PA2 */

#endif /* TRIE_H_ */
