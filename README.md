# QtNMEA
Qt NMEA Wrapper to show how to use libnmea-cpp

## How to Build

- You should build *libnmea-cpp* first via *libnmea-cpp/libnmea-cpp.sln* for x64 platform
- Now just open *QtNMEA.pro* file and press build

## How to Launch

This application supports 4 mode to launch:

- _Standalone mode_: application _has_ input field and sent it to self (command: QtNMEA.exe)
- _UDP Server mode_: application _has no_ input field and only receiving message (command: `QtNMEA.exe --server -i ip_address -p port`)
- _UDP Cleint mode_: application _has_ input field and only receiving message (command: `QtNMEA.exe --client -i ip_address -p port`)
- _COM Port mode_: application _has no_ input field and only receiving message (command: `QtNMEA.exe --com -i COMN`)
