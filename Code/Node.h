/*
 * Node.h
 *
 *  Created on: 16.12.2014
 *      Author: Stefan
 */

#ifndef NODE_H_
#define NODE_H_
#include "string"

namespace PA2 {

template<class T>
class Node {
public:
	Node(Node * parent = 0) {
		this.parent = parent;
	}

	virtual ~Node();

private:
	Node * parent;
};

} /* namespace PA2 */

#endif /* NODE_H_ */
