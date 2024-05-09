1. export SYSTEMC_HOME=/usr/local/systemc-2.3.3/
2. g++ -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -o hello hello.cpp -lsystemc -lm
3. ./hello 
4. gtkwave traces.vcd