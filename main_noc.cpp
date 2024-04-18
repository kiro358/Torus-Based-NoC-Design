// main.cpp
#include "systemc.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "packet.h"
#include "source.h"
#include "sink.h"
#include "router.h"


int sc_main(int argc, char *argv[])
{
	sc_signal<packet> si_source[4];
	sc_signal<packet> si_input[4];
	sc_signal<packet> si_zero[16];
	sc_signal<packet> si_sink[4];
	sc_signal<packet> si_output[4];
	sc_signal<bool>  si_ack_src[4],si_ack_ou[4];
	sc_signal<bool>  si_ack_sink[4],si_ack_in[4];
	sc_signal<bool>  si_ack_zero[16];
	sc_signal<sc_uint<4> >  id0,id1,id2,id3;
	sc_clock s_clock("S_CLOCK", 125, SC_NS, 0.5, 0.0, SC_NS); // source clock
	sc_clock r_clock("R_CLOCK", 5, SC_NS, 0.5, 10.0, SC_NS);	// router clock
	sc_clock d_clock("D_CLOCK", 5, SC_NS, 0.5, 10.0, SC_NS);	// destination clock
	
	// Module instiatiations follow
	// Note that modules can be connected by hooking up ports 
	// to signals by name or by using a positional notation
	source source0("source0");
	source0(si_source[0], id0, si_ack_src[0], s_clock);
	//need codes
	//need codes
	//need codes


	router router0("router0");
	// hooking up signals to ports by name
	router0.in0(si_source[0]);
	router0.in2(si_input[0]);
	router0.in3(si_input[3]);
	router0.in1(si_zero[0]);
	router0.in4(si_zero[1]);

	router0.router_id(id0);

	router0.out0(si_sink[0]);
	router0.out2(si_output[0]);
	router0.out3(si_output[3]);
	router0.out1(si_zero[2]);
	router0.out4(si_zero[3]);

	router0.inack0(si_ack_sink[0]);
	router0.inack2(si_ack_in[0]);
	router0.inack3(si_ack_in[3]);
	router0.inack1(si_ack_zero[0]);
	router0.inack4(si_ack_zero[1]);

	router0.outack0(si_ack_src[0]);
	router0.outack2(si_ack_ou[0]);
	router0.outack3(si_ack_ou[3]);
	router0.outack1(si_ack_zero[2]);
	router0.outack4(si_ack_zero[3]);

	router0.rclk(r_clock);

	router router1("router1");
	// hooking up signals to ports by name
	router1.in0(si_source[1]);
	router1.in2(si_zero[4]);
	router1.in3(si_input[1]);
	router1.in4(si_output[0]);
	router1.in1(si_zero[5]);

	router1.router_id(id1);

	router1.out0(si_sink[1]);
	router1.out2(si_zero[6]);
	router1.out3(si_output[1]);
	router1.out4(si_input[0]);
	router1.out1(si_zero[7]);

	router1.inack0(si_ack_sink[1]);
	router1.inack2(si_ack_zero[4]);
	router1.inack3(si_ack_in[1]);
	router1.inack4(si_ack_ou[0]);
	router1.inack1(si_ack_zero[5]);

	router1.outack0(si_ack_src[1]);
	router1.outack2(si_ack_zero[6]);
	router1.outack3(si_ack_ou[1]);
	router1.outack4(si_ack_in[0]);
	router1.outack1(si_ack_zero[7]);

	router1.rclk(r_clock);
	//need 64 code statement


  	//need codes
	sink sink1("sink1");
	sink1(si_sink[1], si_ack_sink[1], id1, d_clock);
	//need codes
	//need codes

//sc_start(0, SC_NS);
  // tracing:
	// trace file creation
	sc_trace_file *tf = sc_create_vcd_trace_file("graph");
	// External Signals
	sc_trace(tf, s_clock.signal(), "s_clock");
	sc_trace(tf, d_clock.signal(), "d_clock");
	sc_trace(tf, si_source[0], "si_source[0]");
	sc_trace(tf, si_source[0], "si_source[1]");
	//need codes
	//need codes
	sc_trace(tf, si_source[0], "si_sink[0]");
	sc_trace(tf, si_source[0], "si_sink[1]");
	//need codes
	//need codes
	
	id0.write(0);
	id1.write(1);
	//need codes
	//need codes

	cout << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << endl << " 1X2 mesh NOC simulator containing 2 5x5 Wormhole router " << endl;
	cout << "-------------------------------------------------------------------------------" << endl;
	cout << "This is the simulation of a 1x2 Wormhole router.  " << endl; 
	cout << "We assume the router has 5 input/output ports, with 4 buffers per input port " << endl;
	cout << "and each flit has 21 bits width " << endl;
	cout << "  Press \"Return\" key to start the simulation..." << endl << endl;

	getchar();
	sc_start(10*125+124); // during [(10*125)+124] ns 10 packets will be sent and received 

	sc_close_vcd_trace_file(tf);

	cout << endl << endl << "-------------------------------------------------------------------------------" << endl;
	cout << "End of switch operation..." << endl;
	cout << "Total number of packets sent: " <<  source0.pkt_snt<< endl;//need codes to be added
	cout << "Total number of packets received: " <<  sink1.pkt_recv<< endl;//need codes to be added
	cout << "-------------------------------------------------------------------------------" << endl;
    cout << "  Press \"Return\" key to end the simulation..." << endl << endl;
	getchar();
  return 0;

}

