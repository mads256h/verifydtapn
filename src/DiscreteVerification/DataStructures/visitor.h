/* 
 * File:   visitor.h
 * Author: Peter G. Jensen
 *
 * Created on 16 June 2015, 23:15
 */

#ifndef VISITOR_H
#define	VISITOR_H

#include <stdint.h>

namespace pgj
{
    template<typename T>
    class ptriepointer;
    
    template<typename T>
    class visitor_t
    {
    public:
        virtual bool back(uint32_t index) = 0;
        virtual bool set(uint32_t index, bool value) = 0;
        virtual bool set_remainder(uint32_t index, ptriepointer<T> pointer) = 0;
    };
}


#endif	/* VISITOR_H */

