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
	const value_type test("blablafuckingbla", "testasdf");
	cout << test.second << "ende" << endl;

	typedef typename Trie<tree_type>::TrieIterator testIterator;

	testIterator testIter1 = trie.insert(test);

	cout << "test iteration $ \t" << (*testIter1)->getValue() << endl;
	cout << "\n\n test ob leaf geht test \t "
			<< static_cast<typename Trie<tree_type>::Leaf *>((static_cast<typename Trie<
					tree_type>::InnerNode *>(*(++testIter1))->getSon('$')))->getData()
			<< endl;

	const basic_string<char> testString = "blablafuckingbla";
	testIter1 = trie.find(testString);
	cout << "test $" << (*testIter1)->getValue() << endl;
	cout << "test if the find mehtod is working right result test\t"
			<< static_cast<typename Trie<tree_type>::Leaf *>(*testIter1)->getData()
			<< endl;

	trie.erase(testString);
	cout<< "test the erease method \t"<< trie.empty();


	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}

