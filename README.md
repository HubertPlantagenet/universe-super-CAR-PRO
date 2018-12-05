# universe-super-CAR-PRO
## This is a robot car with gps,osd,wireless and many kinds of senors
### Telecontrol
> 通过网络与串口监视实现远程控制
* server类 与 client类 通过中介服务器实现通信
* serial类 用于读取串口信息与给串口发送命令

#### 使用的工具
* Socket
* RXTXcomm

#### RXTX-2.2win64安装方法
> For a JDK installation:
1. Copy RXTXcomm.jar ---> <JAVA_HOME>\jre\lib\ext
2. Copy rxtxSerial.dll ---> <JAVA_HOME>\jre\bin
3. Copy rxtxParallel.dll ---> <JAVA_HOME>\jre\bin
