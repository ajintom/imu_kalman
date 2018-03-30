delete(instrfind)
s=serial('/dev/tty.usbmodem3565641','BaudRate',57600); %start serial port to arduino
s.ReadAsyncMode = 'continuous';
fopen(s); %open port
 while (s.Status == 'open')
   C=fscanf(s);
   arr = regexp(C, '?', 'split')
     if(s.Status ~= 'open')
       break;
     end
   end