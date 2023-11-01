#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"
#include <iostream>


int main(int argc, char **argv, char **env)
{
    int i = 0;
    int clk = 0;

    Verilated::commandArgs(argc, argv);
    // init top verilog instance
    Vcounter *top = new Vcounter;
    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC *tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    // init Vbuddy
    if (vbdOpen()!=1) return(-1);
    vbdHeader("Lab 1: Counter");

    // intialise simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    // run simulation for 300 clock periods

    for (i = 0; i<300; i++) {

        //dump variables into VCD file and toggle clock
        for (clk = 0; clk < 2; clk++) {
            tfp->dump(2*i+clk); // unit is in ps (periods)
            top->clk = !top->clk;
            top->eval();
        }
        
        std::cout << "count = " << int(top->count) << std::endl;
        // ++++ Send count value to vBuddy
        vbdPlot(int(top->count), 0, 255);
        vbdCycle(i+1);
        // ---- End of VBuddy output section

        // change input stimuli
        top -> rst = (i < 2) | (i == 15);
        top -> en = vbdFlag();
        if (Verilated::gotFinish())  exit(0);
    }

    vbdClose(); // close vBuddy prevents memory leaks
    tfp->close();
    exit(0);
}