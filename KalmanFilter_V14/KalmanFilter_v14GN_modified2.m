clear all;
close all;

acqSize=8500;

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
 

%Bring up the filters
while(i<=accF_Length+4)
    if(i>1)
        dt = toc(t0);
        t=[t t(length(t))+dt];
    end
    
    t0 = tic;

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

    
    Acc(:,i)=Acc(:,i)/norm(Acc(:,i));
    Magn(:,i)=Magn(:,i)/norm(Magn(:,i));
    if(i<=accF_Length)
        AccF(:,i)=MyFilter(bAcc,aAcc,Acc(:,:));
    else
        AccF(:,i)=MyFilter(bAcc,aAcc,Acc(:,i-accF_Length:i));
    end
    if(i<=magnF_Length)
        MagnF(:,i)=MyFilter(bMagn,aMagn,Magn(:,:));
    else
        MagnF(:,i)=MyFilter(bMagn,aMagn,Magn(:,i-magnF_Length:i));
    end
    MagnF(:,i)=MagnF(:,i)/norm(MagnF(:,i));
    AccF(:,i)=AccF(:,i)/norm(AccF(:,i));
    i=i+1;
    qPredicted(:,i)=[0.5 0.5 0.5 0.5]';
    qUpdate(:,i)=qPredicted(:,i);
    qOsserv(:,i)=qPredicted(:,i);
  
end



while(i<=acqSize)
    if(i>2)
        dt = toc(t0);
        t=[t t(length(t))+dt];
    end
    %dt=0.015;
    %----Acquisition
        t0 = tic;

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
    
    GyroRate(1,i)=(GyroRate(1,i)+GyroRate(1,i-1))/2;
    GyroRate(2,i)=(GyroRate(2,i)+GyroRate(2,i-1))/2;
    GyroRate(3,i)=(GyroRate(3,i)+GyroRate(3,i-1))/2;
    
    %Normalization and filtering
    Acc(:,i)=Acc(:,i)/norm(Acc(:,i));
    Magn(:,i)=Magn(:,i)/norm(Magn(:,i));
    
    AccF(:,i)=MyFilter(bAcc,aAcc,Acc(:,i-accF_Length:i));
    MagnF(:,i)=MyFilter(bMagn,aMagn,Magn(:,i-magnF_Length:i));
    
    MagnF(:,i)=MagnF(:,i)/norm(MagnF(:,i));
    AccF(:,i)=AccF(:,i)/norm(AccF(:,i));
    %----End Acquisition
    
    %OBSERVATION COMPUTING
    
    %Gradient Descent
    dq(:,i)=0.5*(QuaternionProduct(qUpdate(:,i-1),[0 GyroRate(1,i) GyroRate(2,i) GyroRate(3,i)]'));
    dqnorm(1,i)=norm(dq(:,i));
    mu(1,i)=10*dqnorm(1,i)*dt;
    qOsserv(:,i)=GradientDescent(AccF(:,i),MagnF(:,i),qOsserv(:,i-1),mu(1,i));
    qOsserv(:,i)=qOsserv(:,i)/norm(qOsserv(:,i));
    
    oscsend(u,'/q','ffff', qOsserv(1,i), qOsserv(2,i), qOsserv(3,i), qOsserv(4,i) );
    
    %END OSSERVATION COMPUTING
    
    %KALMAN FILTERING
    const=dt/2;
    %F matrix computing
    F1=[1 -const*GyroRate(1,i) -const*GyroRate(2,i) -const*GyroRate(3,i)];
    F2=[const*GyroRate(1,i) 1 const*GyroRate(3,i) -const*GyroRate(2,i)];
    F3=[const*GyroRate(2,i) -const*GyroRate(3,i) 1 const*GyroRate(1,i)];
    F4=[-const*GyroRate(3,i) const*GyroRate(2,i) -const*GyroRate(1,i) 1];
    
    F=[F1;F2;F3;F4];
    qPredicted(:,i)=F*qUpdate(:,i-1);
    
    Q=Qmatrix;
    
    P_Predicted=F*P_Update*F'+Q;
    
    K=P_Predicted*H'*(H*P_Predicted*H'+R)^-1;
    qUpdate(:,i)=qPredicted(:,i)+K*(qOsserv(:,i)-H*qPredicted(:,i));
    qUpdate(:,i)=qUpdate(:,i)/norm(qUpdate(:,i));
    
    P_Update=(eye(4,4)-K*H)*P_Predicted;
    Angles(:,i)=GetAnglesFromQuaternion(qUpdate(:,i));
    
    %END KALMAN FILTERING
    i=i+1;
end
break;
fclose(u)
fclose(s);
delete(s);
clear s;
 end

    