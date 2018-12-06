package telecontrol;

import java.io.OutputStream;
import java.util.Enumeration;
import java.util.TooManyListenersException;
import java.io.IOException;
import java.io.InputStream;

import gnu.io.CommPortIdentifier;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import gnu.io.UnsupportedCommOperationException;

public class ReanderAndSender implements Runnable,SerialPortEventListener{
	private SerialPort port;
	private CommPortIdentifier portIdentifier;
	private Enumeration<CommPortIdentifier> portList;
	private InputStream inputStream;
	private OutputStream outputStream;
	
	private int delay = 500; //过快会造成串口运作异常
	
	public void sendData(String str) throws IOException
	{
		outputStream.write(str.getBytes("utf-8"));
		run();
	}
	
	@SuppressWarnings("unchecked")//unchecked warnings
	public void getPortList()
	{
		portList = CommPortIdentifier.getPortIdentifiers();
		while(portList.hasMoreElements()){
			portIdentifier = (CommPortIdentifier)portList.nextElement();
			System.out.println(portIdentifier.getName()+"	"+portIdentifier.getPortType());
		}
	}
	

	@SuppressWarnings("unchecked")
	public void selectComm(String name,int params,String serialName) throws IOException,UnsupportedCommOperationException, PortInUseException, TooManyListenersException
	{
		portList = CommPortIdentifier.getPortIdentifiers();
		while(portList.hasMoreElements()) {
			portIdentifier = portList.nextElement();
			if(portIdentifier.getName().equals(name)) {
				port = (SerialPort)portIdentifier.open(serialName,delay);
				port.addEventListener(this);
                // 设置可监听
                port.notifyOnDataAvailable(true);
                // 设置串口通信参数
                // 波特率，数据位，停止位，校验方式
                port.setSerialPortParams(params, 
                        SerialPort.DATABITS_8, 
                        SerialPort.STOPBITS_1,
                        SerialPort.PARITY_NONE);
                outputStream = port.getOutputStream();
                inputStream = port.getInputStream();
                System.out.println("SerialPort "+port.getName()+" ready!");
			}
		}
	}
	
	public void CloseSerialPort()
	{
		System.out.println("Closing port: "+port.getName());
		try {
			inputStream.close();
			outputStream.close();
			port.notifyOnDataAvailable(false);
		
			port.removeEventListener();
		
			port.close();
		} catch (Exception e) {
			System.out.println("Did you open any ports?");
			e.printStackTrace();
		}
		System.out.println("All Closed");
	}
	
	@Override
	public void serialEvent(SerialPortEvent event) 
	{
		// TODO Auto-generated method stub
		switch (event.getEventType()) {//以下都是一些可能出现的事件
        case SerialPortEvent.BI:
        case SerialPortEvent.OE:
        case SerialPortEvent.FE:
        case SerialPortEvent.PE:
        case SerialPortEvent.CD:
        case SerialPortEvent.CTS:
        case SerialPortEvent.DSR:
        case SerialPortEvent.RI:
        case SerialPortEvent.OUTPUT_BUFFER_EMPTY:
            break;
        case SerialPortEvent.DATA_AVAILABLE: // 
        	byte[] readBuffer = new byte[1024];
        	try {
        	while (inputStream.available() > 0) {
        			inputStream.read(readBuffer);
        			}
        		System.out.println(new String(readBuffer,"utf-8"));
        	} catch (Exception e) {
        		e.printStackTrace();
        	}
        default:
            break;
    }   
	}
	@Override
	public void run() {
		try{Thread.sleep(delay);}
		catch(Exception e) {e.printStackTrace();}
	}
}
