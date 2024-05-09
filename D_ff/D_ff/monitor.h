#include <systemc.h>

SC_MODULE(monitor)
{
	sc_in<bool>d,q,qbar;
	sc_in<bool>clk;
	
	void mon()
	{
	
	cout<<"Inputs: "<<d <<"Output: "<<q <<qbar<<endl;	
	}
	
	SC_CTOR(monitor){
		SC_METHOD(mon);
			sensitive <<clk.pos();
	}

};
