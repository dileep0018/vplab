#include "systemc.h"
#include <iostream>
#include <vector>
SC_MODULE(driver)
{
        int counter=0;
        //int<sc_bv> counter=0;
   	sc_out<bool> a1,b1;
        sc_time             t3;
        sc_in<bool> clk;

	void inputs()
	{	
	
	while(counter<4)
	   {
	     
		a1.write(counter & 0x01);
		b1.write(counter & 0x02);
	       
	        t3 = sc_time_stamp();
	        cout <<"Value of t3 "<< t3.to_string() << endl;
	         counter++;
	          wait();
	         }
		
	}
	
		SC_CTOR(driver)
		{
			SC_THREAD(inputs);
			sensitive <<clk.pos();
		}
};
