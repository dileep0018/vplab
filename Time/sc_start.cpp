#include <systemc.h>

SC_MODULE (some_block) {
  sc_in<bool>   clock;
  sc_in<sc_bit> data;
  sc_in<sc_bit> reset;
  sc_in<sc_bit> inv;
  sc_out<sc_bit> out;

  void body () {
    if (reset.read() == 1) {
      out = sc_bit(0);
    } else if (inv.read() == 1) {
      out = ~out.read();
    } else {
      out.write(data.read());
    }
  }
   
  SC_CTOR(some_block) {
    SC_METHOD(body);
      sensitive << clock.pos();
  }
};


SC_MODULE (signal_bind) {
  sc_in<bool> clock;

  sc_signal<sc_bit> data;
  sc_signal<sc_bit> reset;
  sc_signal<sc_bit> inv;
  sc_signal<sc_bit> out;
  some_block *block;

  void do_test() {
    while (true) {
      wait();
      cout << "@" << sc_time_stamp() <<" Starting test"<<endl;
      wait();
      wait();
      inv = sc_bit('0');
      data = sc_bit('0');
      cout << "@" << sc_time_stamp() <<" Driving 0 all inputs"<<endl;
      // Assert reset
      reset = sc_bit('1');
      cout << "@" << sc_time_stamp() <<" Asserting reset"<<endl;
      // Deassert reset
      wait();
      wait();
      reset = sc_bit('0');
      cout << "@" << sc_time_stamp() <<" De-Asserting reset"<<endl;
      // Assert data
      wait();
      wait();
      cout << "@" << sc_time_stamp() <<" Asserting data"<<endl;
      data = sc_bit('1');
      wait();
      wait();
      cout << "@" << sc_time_stamp() <<" Asserting inv"<<endl;
      inv = sc_bit('1');
      wait();
      wait();
      cout << "@" << sc_time_stamp() <<" De-Asserting inv"<<endl;
      inv = sc_bit('0');
      wait();
      wait();
      cout<<"Terminating Simulation"<<endl;
      sc_stop(); // sc_stop triggers end of simulation
    }
  }

  void monitor() {
    cout << "@" << sc_time_stamp() << " data :" << data 
      << " reset :" << reset << " inv :" 
      << inv << " out :" << out <<endl;
  }

  SC_CTOR(signal_bind) {
    block = new some_block("SOME_BLOCK");
    block->clock       (clock)  ;
    block->data        (data)   ;
    block->reset       (reset)  ;
    block->inv         (inv)    ;
    block->out         (out)    ;
                           
    SC_CTHREAD(do_test,clock.pos());
    SC_METHOD(monitor);
      sensitive << data << reset << inv << out;
  }
}; 

int sc_main (int argc, char* argv[]) {
  sc_clock clock ("my_clock",1,0.5);

  signal_bind  object("SIGNAL_BIND");
    object.clock (clock);
  sc_trace_file *wf = sc_create_vcd_trace_file("sc_start");
    sc_trace(wf, object.clock, "clock");
    sc_trace(wf, object.reset, "reset");
    sc_trace(wf, object.data, "data");
    sc_trace(wf, object.inv, "inv");
    sc_trace(wf, object.out, "out");
  sc_start(0,SC_NS); // First time called will init schedular
  sc_start(1,SC_NS); // Increment simulation by 1 time unit
  sc_start();  // Run the simulation till sc_stop is encountered
  // sc_start() is terminated and return to next startment after
  // encountering sc_stop()
  cout<<"Closing VCD File"<<endl;
  sc_close_vcd_trace_file(wf);
  return 0;// Terminate simulation
}
