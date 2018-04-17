clear all;
close all;

acqSize=15000;

delete(instrfind)
s=serial('/dev/tty.usbmodem3565641','BaudRate',57600); %start serial port to arduino
% s.ReadAsyncMode = 'continuous';
fopen(s); %open port



%Gyroscope statistics
Offset=[-3.6982,-3.3570,-2.5909]';
var=[(0.5647/180*pi)^2 (0.5674/180*pi)^2 (0.5394/180*pi)^2]';
%var=[(0.7698/180*pi)^2 (0.4925/180*pi)^2 (0.5144/180*pi)^2]';

%Acquisition variables
GyroRate=zeros(3,acqSize);
Acc=zeros(3,acqSize);
Magn=zeros(3,acqSize);
Angles=zeros(3,acqSize);
AccF=zeros(3,acqSize);
MagnF=zeros(3,acqSize);
mu=zeros(1,acqSize);
dqnorm=zeros(1,acqSize);
dq=zeros(4,acqSize);

qUpdate=zeros(4,acqSize);
%Initial quaternion values
qUpdate(:,1)=[1 0 0 0]';

%Observation vector
qOsserv=zeros(4,acqSize);
qOsserv(:,1)=[1 0 0 0]';

%----KALMAN MATRIXES
Q1=[var(1,1)+var(2,1)+var(3,1) -var(1,1)+var(2,1)-var(3,1) -var(1,1)-var(2,1)+var(3,1) var(1,1)-var(2,1)-var(3,1)];
Q2=[-var(1,1)+var(2,1)-var(3,1) var(1,1)+var(2,1)+var(3,1) var(1,1)-var(2,1)-var(3,1) -var(1,1)-var(2,1)+var(3,1)];
Q3=[-var(1,1)-var(2,1)+var(3,1) var(1,1)-var(2,1)-var(3,1) var(1,1)+var(2,1)+var(3,1) -var(1,1)+var(2,1)-var(3,1)];
Q4=[var(1,1)-var(2,1)-var(3,1) -var(1,1)+var(2,1)-var(3,1) -var(1,1)+var(2,1)-var(3,1) var(1,1)+var(2,1)+var(3,1)];
Qmatrix=[Q1;Q2;Q3;Q4];

H=eye(4,4);

sigmaR=[0.01 0.01 0.01 0.01]';
R=[sigmaR(1,1) 0 0 0;0 sigmaR(2,1) 0 0;0 0 sigmaR(3,1) 0;0 0 0 sigmaR(4,1)];

qPredicted=zeros(4,acqSize);
%qPredicted(:,1)=[0.5 0.5 0.5 0.5]';
qPredicted(:,1)=[1 0 0 0]';
P_Update=eye(4,4)*2;
%----------
t=[0];

i=1;
dt=0;

[bAcc,aAcc] = butter(3,0.0075,'low');
[bMagn,aMagn] = butter(2,0.06,'low');


magnF_Length=13;
accF_Length=13;

 while (s.Status == 'open')
     
 u = udp('127.0.0.1',7400); 
 fopen(u); 
 


while(i<=acqSize)

C=fscanf(s);
    arr = regexp(C, '?', 'split')
    arr = str2double(arr);
    
     if(s.Status ~= 'open')
       break;
     end
        

    oscsend(u,'/q','fff', arr(2), arr(3), arr(4) );
%     oscsend(u,'/q','ffff', qUpdate(1,i), qUpdate(2,i), qUpdate(3,i), qUpdate(4,i) );
    
    %END KALMAN FILTERING
    i=i+1;
end
break;
fclose(u)
fclose(s);
delete(s);
clear s;
 end

 figure;
    subplot(3,1,1);plot(t,Acc(1,:),'b',t,AccF(1,:),'r',t,Magn(1,:),'g',t,MagnF(1,:),'c');legend('AccX','AccFX','MagnX','MagnFX');grid;
    subplot(3,1,2);plot(t,Acc(2,:),'b',t,AccF(2,:),'r',t,Magn(2,:),'g',t,MagnF(2,:),'c');legend('AcY','AccFY','MagnY','MagnFY');grid;
    subplot(3,1,3);plot(t,Acc(3,:),'b',t,AccF(3,:),'r',t,Magn(3,:),'g',t,MagnF(3,:),'c');legend('AccZ','AccFZ','MagnZ','MagnFZ');grid;


figure;
    subplot(4,1,1);plot(t,qOsserv(1,1:acqSize));grid;legend('q0 Observed');
    subplot(4,1,2);plot(t,qOsserv(2,1:acqSize));grid;legend('q1 Observed');
    subplot(4,1,3);plot(t,qOsserv(3,1:acqSize));grid;legend('q2 Observed');
    subplot(4,1,4);plot(t,qOsserv(4,1:acqSize));grid;legend('q3 Observed');

figure;
    subplot(4,1,1);plot(t,qUpdate(1,1:acqSize));hold on;plot(t,qOsserv(1,1:acqSize),'r');grid;legend('q0 Estimated','q0 Observed');xlabel('time (sec)');ylabel('Quaternion value');
    subplot(4,1,2);plot(t,qUpdate(2,1:acqSize));hold on;plot(t,qOsserv(2,1:acqSize),'r');grid;legend('q1 Estimated','q1 Observed');xlabel('time (sec)');ylabel('Quaternion value');
    subplot(4,1,3);plot(t,qUpdate(3,1:acqSize));hold on;plot(t,qOsserv(3,1:acqSize),'r');grid;legend('q2 Estimated','q2 Observed');xlabel('time (sec)');ylabel('Quaternion value');
    subplot(4,1,4);plot(t,qUpdate(4,1:acqSize));hold on;plot(t,qOsserv(4,1:acqSize),'r');grid;legend('q3 Estimated','q3 Observed');xlabel('time (sec)');ylabel('Quaternion value');    
    
figure;
    subplot(3,1,1);plot(t,Angles(1,1:acqSize));grid;legend('Roll');xlabel('time (sec)');ylabel('Angle (deg)');
    subplot(3,1,2);plot(t,Angles(2,1:acqSize));grid;legend('Pitch');xlabel('time (sec)');ylabel('Angle (deg)');
    subplot(3,1,3);plot(t,Angles(3,1:acqSize));grid;legend('Yaw');xlabel('time (sec)');ylabel('Angle (deg)');
    
    
    
    