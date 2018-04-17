clear all;
close all;

acqSize=1000;

delete(instrfind)
s=serial('/dev/tty.usbmodem3565641','BaudRate',57600); %start serial port to arduino
% s.ReadAsyncMode = 'continuous';
fopen(s); %open port

%Gyroscope statistics
Offset=[-3.6982,-3.3570,-2.5909]';
var=[(0.7698/180*pi)^2 (0.4925/180*pi)^2 (0.5144/180*pi)^2]';

%Acquisition variables
GyroRate=zeros(3,acqSize);
Acc=zeros(3,acqSize);
Magn=zeros(3,acqSize);
Angles=zeros(3,acqSize);

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

sigmaR=[0.0001 0.0001 0.0001 0.0001]';
R=[sigmaR(1,1) 0 0 0;0 sigmaR(2,1) 0 0;0 0 sigmaR(3,1) 0;0 0 0 sigmaR(4,1)];

qPredicted=zeros(4,acqSize);
qPredicted(:,1)=[0.5 0.5 0.5 0.5]';
P_Update=eye(4,4)*0.01;
%----------
t=[0];

i=2;
dt=0;
[bAcc,aAcc] = butter(3,0.0075,'low');
[bMagn,aMagn] = butter(2,0.06,'low');

magnF_Length=13;
accF_Length=13;

 while (s.Status == 'open')

while(i<=acqSize)
%     if(i>2)
%         dt = toc(t0);
%         t=[t t(length(t))+dt];
%     end
%     %dt=0.015;
%         t0 = tic;

        %----------
%         pause(0.01)
        %---------
C=fscanf(s);
    arr = regexp(C, '?', 'split')
    arr = cell2mat(arr);
    
     if(s.Status ~= 'open')
       break;
     end
        
    Acc(1,i)=arr(1);
    Acc(2,i)=arr(2);
    Acc(3,i)=arr(3);
    Magn(1,i)=arr(4);
    Magn(2,i)=arr(5);
    Magn(3,i)=arr(6);
    GyroRate(1,i)=((arr(7)-Offset(1,1))/180)*pi;
    GyroRate(2,i)=((arr(8)-Offset(2,1))/180)*pi;
    GyroRate(3,i)=((arr(9)-Offset(3,1))/180)*pi;

    
    %Normalization
    Acc(:,i)=Acc(:,i)/norm(Acc(:,i));
    Magn(:,i)=Magn(:,i)/norm(Magn(:,i));
    %----End Acquisition
    
    %OBSERVATION COMPUTING
    %Gauss Newton step 
    %qOss=GaussNewtonMethod(qOsserv(2,i-1),qOsserv(3,i-1),qOsserv(4,i-1),qOsserv(1,i-1),Acc(:,i),Magn(:,i),Magn(:,2));
    %qOsserv(:,i)=[qOss(4,1); qOss(2:4,1)];
    
    %Gradient Descent
    dq=0.5*(QuaternionProduct(qOsserv(:,i-1),[0 GyroRate(1,i) GyroRate(2,i) GyroRate(3,i)]'));
    mu=10*norm(dq)*dt;
    qOsserv(:,i)=GradientDescent(Acc(:,i),Magn(:,i),qUpdate(:,i-1),mu);
    
    qOsserv(:,i)=qOsserv(:,i)/norm(qOsserv(:,i));
    %END OSSERVATION COMPUTING
    
    %KALMAN FILTERING
    
    %F matrix computing
    F1=[1 -dt/2*GyroRate(1,i) -dt/2*GyroRate(2,i) -dt/2*GyroRate(3,i)];
    F2=[dt/2*GyroRate(1,i) 1 dt/2*GyroRate(3,i) -dt/2*GyroRate(2,i)];
    F3=[dt/2*GyroRate(2,i) -dt/2*GyroRate(3,i) 1 dt/2*GyroRate(1,i)];
    F4=[-dt/2*GyroRate(3,i) dt/2*GyroRate(2,i) -dt/2*GyroRate(1,i) 1];
    
    F=[F1;F2;F3;F4];
    qPredicted(:,i)=F*qUpdate(:,i-1);
    
    Q=(dt/2)^2*Qmatrix;
    
    P_Predicted=F*P_Update*F'+Q;
    
    K=P_Predicted*H'*(H*P_Predicted*H'+R)^-1;
    
    qUpdate(:,i)=qPredicted(:,i)+K*(qOsserv(:,i)-H*qPredicted(:,i));
    
    P_Update=(eye(4,4)-K*H)*P_Predicted;
    Angles(:,i)=GetAnglesFromQuaternion(qUpdate(:,i));
    
    fprintf(s,'%i',i);
    %END KALMAN FILTERING
    i=i+1;
end
break;
fclose(s);
delete(s);
clear s;
 end
figure;
    subplot(4,1,1);plot(t,qOsserv(1,2:acqSize));grid;legend('q0 Observed');
    subplot(4,1,2);plot(t,qOsserv(2,2:acqSize));grid;legend('q1 Observed');
    subplot(4,1,3);plot(t,qOsserv(3,2:acqSize));grid;legend('q2 Observed');
    subplot(4,1,4);plot(t,qOsserv(4,2:acqSize));grid;legend('q3 Observed');

figure;
    subplot(4,1,1);plot(t,qUpdate(1,2:acqSize));grid;legend('q0 Estimated');
    subplot(4,1,2);plot(t,qUpdate(2,2:acqSize));grid;legend('q1 Estimated');
    subplot(4,1,3);plot(t,qUpdate(3,2:acqSize));grid;legend('q2 Estimated');
    subplot(4,1,4);plot(t,qUpdate(4,2:acqSize));grid;legend('q3 Estimated');
    
figure;
    subplot(3,1,1);plot(t,Angles(1,2:acqSize));grid;legend('Roll');
    subplot(3,1,2);plot(t,Angles(2,2:acqSize));grid;legend('Pitch');
    subplot(3,1,3);plot(t,Angles(3,2:acqSize));grid;legend('Yaw');


