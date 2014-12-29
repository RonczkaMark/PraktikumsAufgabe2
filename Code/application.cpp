/*
 * application.cpp
 *
 *  Created on: 29.12.2014
 *      Author: Stefan
 */



#include "Trie.h"
#include "pair.h"
#include "Node.h"
#include "iostream"
#include "string"


namespace PA2 {


int main(){

	std::string test ="";
	Trie <std::string> trie;

	typedef pair<std::string,std::string> GerEngPair;
	std::string wort= "wort";
	std::string word  ="word";
	Node father;
	GerEngPair testpair(father,wort,word);






	return 0;
}

} /* namespace PA2 */
