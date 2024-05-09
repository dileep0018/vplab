#include <systemc.h>

SC_MODULE(dff)
{
	sc_in<bool>d;
	sc_in<bool>clk;
	sc_out<bool>q,qbar;

	void compute(){
		q.write(d.read());
		qbar.write(!d.read());
	}
	SC_CTOR(dff){
	SC_METHOD(compute);
		sensitive<<clk.pos();
	}
};
