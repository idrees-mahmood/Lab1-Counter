#include "Vcounter.h"
#include "verilated.h"
#include <verilated_vcd_c.h>


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

    // intialise simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    bool count_pause = false;
    // run simulation for many clock cycles
    for (i = 0; i < 300; i++)
    {

        // dump variables into VCD file and toggle clock
        for (clk = 0; clk < 2; clk++)
        {
            tfp->dump(2 * i + clk);
            if (i < 9 || i > 12)
            {
                top->clk = !top->clk;
            }
            else
            {
                top->clk = top->clk;
            }
            top->eval();
        }
        top->rst = (i < 2) | (i == 15);
        top->en = (i > 4);
        if (Verilated::gotFinish())
            exit(0);
    }
    tfp->close();
    exit(0);
}