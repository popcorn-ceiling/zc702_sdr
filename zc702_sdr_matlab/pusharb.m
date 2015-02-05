function pusharb(radioSelection, idata, qdata)
idata = idata';
qdata = qdata';
% length(idata)
% idata(:,length(idata)) = [];
% length(idata)
% length(qdata)
% qdata(:,length(qdata)) = [];
% length(qdata)
% dan
chunksize = 20;
pause_t = .3;

%     !!!!!!!!!!!!!!!!!!!!!!
%     !!!! SO IMPORTANT !!!!
%     !!!!!!!!!!!!!!!!!!!!!!
% numChunks must be an integer value

numchunks = length(idata)/chunksize

% Open Connection at a specific address
t = tcpip('147.222.163.30', 8080); 
% Set size of receiving buffer, if needed. 
set(t, 'InputBufferSize', 10000);
set(t, 'OutputBufferSize', 300000);
fopen(t); 
% Transmit data to the server (or a request for data from the server).
freqInit = sprintf('0 %d %d', radioSelection, 913000000)
fprintf(t, freqInit);
dan = sprintf('2 %d %d %d', radioSelection, numchunks, chunksize)
fprintf(t, dan)
pause(pause_t) 
arbout = '';
while (get(t, 'BytesAvailable') > 0) 
    t.BytesAvailable;
    DataReceived = fscanf(t);
    arbout = strcat(arbout,DataReceived);
end

for j = 1:numchunks
    tempstr = sprintf('3 %d',j-1);
    for k=1:chunksize
        tempstr = strcat(tempstr, sprintf(' %d %d',idata(k+(j-1)*chunksize), qdata(k+(j-1)*chunksize)));
    end
    fprintf(t, tempstr);
    
    pause(pause_t) 
    arbout = '';
    while (get(t, 'BytesAvailable') > 0) 
        t.BytesAvailable; 
        DataReceived = fscanf(t);
        arbout = strcat(arbout,DataReceived);
    end
end

fclose(t); 
delete(t); 
clear t 

end