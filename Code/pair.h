/*
 * pair.h
 *
 *  Created on: 23.12.2014
 *      Author: Stefan
 */

#ifndef PAIR_H_
#define PAIR_H_


#include "String"
#include "iostream"
#include "Node.h"
namespace PA2 {

template<class string,class T>
class pair : public Node{
public:
	pair(Node parent,string key,T value):Node(parent){
		this->key = key;
		this->value = value;
	};
	virtual ~pair(){
	};
	string getKey() const {
		return key;
	}

	void setKey(string key) {
		this->key = key;
	}

	;

private:
	T value;
	//mal den key mit gespeichert
	string key;

};

} /* namespace PA2 */

#endif /* PAIR_H_ */
