#include <systemc.h>
#include "dff.h"
#include "driver.h"
#include "monitor.h"

int sc_main(int argc,char *argv[])
{
	sc_signal<bool>d,q,qbar;
	sc_clock clk("testclock",2,SC_NS,0.5);
	
	dff df("Dflip");
	df.d(d);
	df.q(q);
	df.qbar(qbar);
	df.clk(clk);
	
	driver drive("Driver");
	drive.d(d);
	drive.clk(clk);
	
	monitor mon("monitor");
	mon.d(d);
	mon.q(q);
	mon.qbar(qbar);
	mon.clk(clk);
	
	sc_trace_file *Tf;
	
	Tf=sc_create_vcd_trace_file("traces");
	sc_trace(Tf,d,"d");
	sc_trace(Tf,q,"q");
	sc_trace(Tf,qbar,"qbar");
	sc_trace(Tf,clk,"clk");
	sc_start(45,SC_NS);
	sc_close_vcd_trace_file(Tf);
	
	return 0;
}
