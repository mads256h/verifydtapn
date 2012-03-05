/*
 * PWList.cpp
 *
 *  Created on: 01/03/2012
 *      Author: MathiasGS
 */

#include "PWList.hpp"
#include "NonStrictMarking.hpp"
#include "WaitingList.hpp"

namespace VerifyTAPN {
namespace DiscreteVerification {

PWList::PWList() {
	// TODO Auto-generated constructor stub

}

void PWList::Add(const NonStrictMarking& marking){
	if(markings_storage[marking.HashKey()].equals(marking)){
		markings_storage[marking.HashKey()] = marking;
		waiting_list.Add(marking);
	}
}

const NonStrictMarking& PWList::GetNextUnexplored(){
	//const NonStrictMarking& next = waiting_list.Next();
	//return next;

	return waiting_list.Next();
}

PWList::~PWList() {
	// TODO Auto-generated destructor stub
}

} /* namespace DiscreteVerification */
} /* namespace VerifyTAPN */