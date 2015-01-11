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
	const value_type test("test", "test");
	cout << test.second << "ende" << endl;

	typedef typename Trie<tree_type>::TrieIterator testIterator;

	testIterator testIter1 = trie.insert(test);

	cout << "test iteration $ \t" << (*testIter1)->getValue() << endl;
	cout << "\n\n test ob leaf geht test \t "
			<< dynamic_cast<typename Trie<tree_type>::Leaf *>((dynamic_cast<typename Trie<
					tree_type>::InnerNode *>(*(++testIter1))->getSon('$')))->getData()
			<< endl;

	const basic_string<char> testString = "test";
	testIter1 = trie.find(testString);
	cout<<"test if the find mehtod is working right result test\t"<<dynamic_cast <typename Trie<tree_type>::Leaf *>((dynamic_cast<typename Trie<tree_type>::InnerNode * >(*testIter1)))->getData()<<endl;

					cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
					return 0;
				}

