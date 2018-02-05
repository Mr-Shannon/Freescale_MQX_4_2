                          Iperf - RTCS version
                          --------------------

1.1 Introduction
----------------
Iperf is a tool to measure maximum TCP and UDP bandwidth, allowing the tuning of 
various parameters and UDP characteristics. Iperf reports bandwidth, 
delay jitter, datagram loss.

1.2 Version
-----------
This is ported version of Iperf 3.0b4. Please note, that this version of Iperf 
is compatible only with 3.0b4! Iperf will not work with version 2 and older. Compatible precompiled Windows version is available in iperf_PC directory.

1.3 Running the application
---------------------------
1) Prepare your evaluation board according to the "MQX Getting started" document.
   Pay special attention to correct jumper settings.
2) Connect your PC to the evaluation board using a serial cable.
3) Connect the evaluation board and your PC to same Ethernet network. 
   Change board or computer IP address if necessary.
4) Start Terminal application on your PC.
   Set serial port settings to 115200 baud rate, no parity and 8 bits.
5) Compile all required libraries (BSP, PSP, SHELL, RTCS).
6) Compile, load and run the application. Following message should show up in 
   the terminal window:

    Shell (build: Mar 25 2014)
    Copyright (c) 2013 Freescale Semiconductor;
    shell>
    shell>

7) To run Iperf, execute "iperf" command with appropriate options listed below.


1.4 Establishing connection between board and PC
------------------------------------------------
This is example how to create iperf server on PC and start TCP bandwidth measurement using board as a client.

a)Open command line on PC and navigate to directory containing PC version of iperf using cd command. For example:

	cd c:\Freescale\4.2.0\rtcs\examples\iperf\iperf_PC

Then type:

	iperf -s [-6]

This will start iperf server on your PC. Use -6 option only with IPv6.

b)In serial terminal type:

	iperf -c <computer_ip_addres> [-6]

This will connect board to PC with <computer_ip_addres> and start measurement.
 
Note: To use IPv6 rather than IPv4, please use -6 option both on server and client.


1.5 Usage
---------
For detaled info please refer to iperf website: https://iperf.fr/

iperf [-s|-c host] [options]
iperf [-h|--help]  [-v|--version]

Client/Server:

              -f  [kmgKMG]  format to report: Kbits, Mbits, KBytes, MBytes
              -i  #         seconds between periodic bandwidth reports
              -l  #[KMG]    length of buffer to read or write (default 8 KB)
              -m            print TCP maximum segment size (MTU - TCP/IP header)
              -p  #         server port to listen on/connect to
              -u            use UDP rather than TCP
              -w  #[KMG]    TCP window size (socket buffer size)
              -M  #         set TCP maximum segment size (MTU - 40 bytes)
              -N            set TCP no delay, disabling Nagle's Algorithm
              -T            Output detailed TCP info
              -v            print version information and quit
              -V            more verbose output
              -6            use IPv6 rather than IPv4

Server specific:

              -s            run in server mode

Client specific:

               -b  #[KMG]    for UDP, bandwidth to send at in bits/sec
                             (default 1 Mbit/sec, implies -u)
               -c  <host>    run in client mode, connecting to <host>
               -n  #[KMG]    number of bytes to transmit (instead of -t)
               -t  #         time in seconds to transmit for (default 10 secs)
               -P  #         number of parallel client threads to run
               -R            reverse mode

Miscellaneous:

               -h            print this message and quit


1.6 Default Example Configuration
---------------------------------

  - Listen port number  5201
  - Device IPv4 addres  192.168.0.22
  - Device IPv6 addres  fe80::200:5eff:fea8:16
  - UDP packet size     1450 bytes (1 packet per ethernet frame)
  - TCP packet size     2048 bytes
  - Socket size         4096 bytes
  - UDP badwidth limit  1Mbit/s
  - Buffer size         2048 bytes
  - Time to transmit    10s

1.7 RTCS limitations
--------------------
 - For simplicity longopt command options were removed.
 - Number of maximum paralel streams was limited to 5.


1.8 Known issues
----------------
 - There is a bug on PC version in multi socket connection on udp. Selecting
   more than one paralel stream will cause crash.

 - UDP Client (TX) bandwidth limit function has bug on PC. TX bandwidth is limited to 
   1 Mbit/s.

                    Iperf - PC version
                    ------------------

2.1 Description
---------------
Windows version of Iperf 3.0b4. You can use it to connect your PC to 
your board and start measurement. This version is avalible either in GUI or 
command line version. 


2.2 Instalation
---------------
PC version of Iperf can be downloaded from here:

http://www.softpedia.com/get/Network-Tools/Bandwidth-Tools/Iperf3-Cygwin-GUI.shtml

To install, please extract downloaded zip file.
Note: If you use GUI version, ensure that you have Java JRE 1.5+ installed. 


2.3 Iperf command line version usage(recomanded)
------------------------------------------------
Open command line and navigate to iperf3.exe using cd command:

   cd C:\<your_install_path>\iperf3cygwingui-3.0b4-03\bin
   
Then you can start measurement using iperf3 command with appropriate options.
For example:

   iperf3 -c <board_ipaddress>
   
This will start Iperf in client mode and connect to board with <board_ipaddress>.      


2.4 Iperf GUI version usage
---------------------------
To run GUI version please do following:

- Windows users
  run following script: iperf3cygwingui.bat
  
- Linux or OS X users
  run following script: iperf3cygwingui.sh
  
Then application window should appear. To start measurement, choose either server 
or client mode, enter your board ip address and other required parameters and press 
"Run Iperf3" button on the right. 
