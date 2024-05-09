//
//  full_adder.h
//  FULLADDER
//
//  Created by Behrad Niazmand on 7/19/14.
//  Copyright (c) 2014 Behrad Niazmand. All rights reserved.
//

#include <iostream>
#include "systemc.h"

SC_MODULE (encoder)
{
    sc_in <sc_uint<2> > input;
    sc_in <bool> enable;
    
    sc_out <sc_uint<4> > output;
    
    void proc_encoder();
    
    SC_CTOR (encoder)
    {
        SC_METHOD (proc_encoder);
        sensitive << input << enable;
    }
};
