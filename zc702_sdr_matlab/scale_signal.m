function [i_out, q_out] = scale_signal1(i_in, q_in)
%Converts i and q samples to max values in 16 or 32 bit environment
% for maximum precision in output stage of DAC chain

    depth = 16;
    %depth = 32;
    
    i_max = max(max(abs(i_in)));
    q_max = max(max(abs(q_in)));
    maxVal = max(i_max,q_max);
    mult = (2.^depth)/maxVal;
    i_out = mult*i_in;
    q_out = mult*q_in;
    assignin('base','i_out1',i_out);
    assignin('base','q_out1',q_out);
end