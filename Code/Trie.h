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
public:
	typedef std::basic_string<E> key_type; // string=basic_string<char>
	typedef pair<const key_type, T> value_type;
	typedef T mapped_type;
//	typedef ... iterator;
//	typedef std::reverse_iterator<iterator> reverse_iterator;

	bool empty() const;
//	iterator insert(const value_type &);
	void erase(const key_type& value);

	Trie(){};

private:
	 class InnerNode : public  Node{
		typedef std::list<Node *, std::allocator<E> > nodeList;

	public:
		 InnerNode(T value) {
			this->value = value;
		}

		void addSon(Node * newSon) {
			nodePointerList.insert(newSon);
		};
		Node * getNext(){
			typename nodeList::iterator it = nodePointerList.begin();
			it ++;
			return *it;
		};

	private:
		T value;
		nodeList nodePointerList;
	};


};

} /* namespace PA2 */

#endif /* TRIE_H_ */
