/*
 * PWList.cpp
 *
 *  Created on: 01/03/2012
 *      Author: MathiasGS
 */

#include "TimeDartPWList.hpp"

namespace VerifyTAPN {
namespace DiscreteVerification {

bool TimeDartPWHashMap::Add(TAPN::TimedArcPetriNet* tapn, NonStrictMarkingBase* marking, int youngest, WaitingDart* parent, int upper){
	discoveredMarkings++;
	TimeDartList& m = markings_storage[marking->HashKey()];
	for(TimeDartList::const_iterator iter = m.begin();
			iter != m.end();
			iter++){
		if((*iter)->getBase()->equals(*marking)){
				bool inWaiting = (*iter)->getWaiting() < (*iter)->getPassed();

				(*iter)->setWaiting(min((*iter)->getWaiting(),youngest));

				if((*iter)->getWaiting() < (*iter)->getPassed() && !inWaiting){
					waiting_list->Add((*iter)->getBase(),(*iter));
                                        if(this->trace){
                                            ((ReachabilityTraceableDart*)(*iter))->trace = new TraceDart((*iter), parent, youngest, upper, marking->generatedBy);
                                        }
				}

			delete marking;

			return false;
		}
	}

	TimeDartBase* dart = new TimeDartBase(marking, youngest, INT_MAX);
        stored++;
	m.push_back(dart);
        if(this->trace){
            ((ReachabilityTraceableDart*)dart)->trace = new TraceDart(dart, parent, youngest, upper, marking->generatedBy);
        }
	waiting_list->Add(dart->getBase(), dart);
	return true;
}

TimeDartBase* TimeDartPWHashMap::GetNextUnexplored(){
	return waiting_list->Pop();
}

bool TimeDartPWPData::Add(TAPN::TimedArcPetriNet* tapn, NonStrictMarkingBase* marking, int youngest, WaitingDart* parent, int upper){
	discoveredMarkings++;
        PData<TimeDartBase>::Result res = passed.Add(marking);

        if(!res.isNew){
            TimeDartBase* t = res.encoding.GetMetaData();
            bool inWaiting = t->getWaiting() < t->getPassed();
            t->setWaiting(min(t->getWaiting(),youngest));

            if(t->getWaiting() < t->getPassed() && !inWaiting){
                    waiting_list->Add(marking, new EncodingPointer<TimeDartBase>(res.encoding, res.pos));
 //               waiting_list->Add(t->getBase(), t);
            }
            return false;
        }

	TimeDartBase* dart = new TimeDartBase(marking, youngest, INT_MAX);
        stored++;
        res.encoding.SetMetaData(dart);
	waiting_list->Add(marking, new EncodingPointer<TimeDartBase>(res.encoding, res.pos));
//        waiting_list->Add(dart->getBase(), dart);
	return true;
}

TimeDartBase* TimeDartPWPData::GetNextUnexplored(){
  
    EncodingPointer<TimeDartBase>* p = waiting_list->Pop();
    NonStrictMarkingBase* m = passed.EnumerateDecode(*p);
    TimeDartBase* dart = p->encoding.GetMetaData();
    dart->setBase(m);
    
    p->encoding.Release();
    delete p;
    return dart;
}


TimeDartPWHashMap::~TimeDartPWHashMap() {
	// TODO Auto-generated destructor stub
}

std::ostream& operator<<(std::ostream& out, TimeDartPWHashMap& x){
	out << "Passed and waiting:" << std::endl;
	for(TimeDartPWHashMap::HashMap::iterator iter = x.markings_storage.begin(); iter != x.markings_storage.end(); iter++){
		for(TimeDartPWHashMap::TimeDartList::iterator m_iter = iter->second.begin(); m_iter != iter->second.end(); m_iter++){
			out << "- "<< *m_iter << std::endl;
		}
	}
	out << "Waiting:" << std::endl << x.waiting_list;
	return out;
}

} /* namespace DiscreteVerification */
} /* namespace VerifyTAPN */
