//============================================================================
// Name        : PraktikumsAufgabe2.cpp
// Author      : Stefan Ronczka Sepp Mark
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "Trie.h"
#include <utility>
using namespace std;

using namespace PA2;

int main() {

	typedef string tree_type;
	typedef basic_string<char> key_type; // string=basic_string<char>
	typedef pair<const key_type, tree_type> value_type;

	Trie<tree_type> trie;
	const value_type test("abcd", "test1");
	const value_type test2("abcdef","test2");

	cout << test.second << "ende" << endl;

	typedef typename Trie<tree_type>::TrieIterator testIterator;

	testIterator testIter1 = trie.insert(test);
	testIterator testIter2 = trie.insert(test2);

	const basic_string<char> testString = "abcd";
	const basic_string<char> testString2 = "abcdef";

	testIter1 = trie.begin();
	cout<<"test2"<<static_cast<typename Trie<tree_type>::Leaf *>(*testIter1)->getData()<<endl;
	++testIter2;
	++testIter2;
	cout<<static_cast<typename Trie<tree_type>::InnerNode *>(*testIter2)->getLeft()->getValue();
	trie.erase(testString2);
	trie.find(testString);
	testIter1 = trie.begin();

	cout<<"test 1"<<static_cast<typename Trie<tree_type>::Leaf *>((*testIter1))->getData()<<endl;
	testIter1 =trie.insert(test2);
	cout<<"test 2"<<static_cast<typename Trie<tree_type>::Leaf *>((*testIter1))->getData()<<endl;

	++testIter1;
	++testIter1;
	++testIter1;
	++testIter1;









	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}

