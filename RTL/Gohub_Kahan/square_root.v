/*
This module is used in the computation of the square root
It employs the inbuilt Xilinx CORDIC style implementation of Square Root
*/

module square_root(
    input clk,
    input rst_b,
    input[31:0] in,
    output reg[23:0] y
    );
    
    // AXI interfaces
    wire s_axis_data_tvalid = 1'b1;
    wire m_axis_data_tvalid;
    
    // for debugging
    wire[31:0] sqrt_data_out;
    
    cordic_square_root root(
        .aclk(clk),
        .aresetn(rst_b),
        .s_axis_cartesian_tvalid(s_axis_data_tvalid),
        .s_axis_cartesian_tdata(in),
        .m_axis_dout_tvalid(m_axis_data_tvalid),
        .m_axis_dout_tdata(sqrt_data_out)
    );
    
    always@(posedge clk)
        begin
            if(m_axis_data_tvalid == 1'b0)
                begin
                    y <= sqrt_data_out;
                end
        end
    
endmodule
