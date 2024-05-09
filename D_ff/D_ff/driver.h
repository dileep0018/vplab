#include <systemc.h>

SC_MODULE(driver)
{
	sc_in<bool>clk;
	sc_out<bool>d;
	
	void inputs(){
		wait(5,SC_NS);
		d.write(false);
		wait(5,SC_NS);
		d.write(true);
	}
	
	SC_CTOR(driver){
		SC_THREAD(inputs);
		sensitive <<clk.pos();
	}
};
