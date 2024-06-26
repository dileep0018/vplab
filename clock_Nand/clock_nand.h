#include "systemc.h"
SC_MODULE(andgate)
{
        sc_clock clk("TestClock",20,0.5,0,SC_NS,1);
	sc_in<bool> a1;
	sc_in<bool> b1;
	sc_out<bool> d1;
	void compute_and()
	{	
		d1.write(!(a1.read() &&  b1.read()));
	}
	SC_CTOR(andgate)
	{
		SC_METHOD(compute_and);
		sensitive <<a1 <<b1 <<clk;
	}
};
