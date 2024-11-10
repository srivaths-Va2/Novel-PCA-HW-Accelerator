/*
The module computes the normalized form of the vector
*/

module vector_normalizer#(
    parameter N = 4,
    parameter WIDTH = 16
)(
    input clk,
    input rst,
    input [(N * WIDTH) - 1 : 0] vector,
    output reg [WIDTH - 1 : 0] norm
    );
    
    // intermediate signals
    reg[2 * WIDTH : 0] sum_squares;
    integer i;
    
    // main loop to calculate sum_squares
    always@(posedge clk or posedge rst)
        begin
            if(rst == 1'b1)
                begin
                    sum_squares <= 0;
                    norm <= 0;
                end
            
            else
                begin
                    sum_squares = 0;
                    for(i = 0; i < N; i = i + 1)
                        begin
                            sum_squares = sum_squares + (vector[i * WIDTH +: WIDTH] * vector[i * WIDTH +: WIDTH]);
                        end
                end
             // need to add square root calculator for sum_squares signal
             norm <= sum_squares;
        end
endmodule
