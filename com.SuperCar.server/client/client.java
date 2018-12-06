package client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;  

public class client{
	public final static int port = 38380;
	public final static String serverIP = "149.28.18.99";
	//必须使用静态变量
	
	public static void main(String[] args) {
		clientHandler();
	}
	public static void clientHandler() { //不能在一个静态方法中引用该类中的另外一个静态方法
		try {
			Socket sk = new Socket(serverIP,port);
			System.out.println("Connected");
			//开启读写线程
			new Thread(new WriteHandler(sk)).start();
			new Thread(new ReadHandler(sk)).start();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.exit(0);  //发生异常时马上退出
		}
	}
}

/*处理
写操作的线程*/
class WriteHandler implements Runnable{
	public WriteHandler(Socket sk) {this.sk = sk;}//给线程传递Socket对象
	private Socket sk;
	@Override
	public void run() {
		PrintWriter pw = null;  //必须先声明，否则就要再同一个try中进行操作
		try {
			pw = new PrintWriter(sk.getOutputStream());
		}catch(Exception e) {e.printStackTrace();}
		BufferedReader reader = null;
		try {
			String str = new String();  //作判断用
			reader = new BufferedReader(new InputStreamReader(System.in));
			while(str != null) {
				if(!str.equals("end connection")  && !sk.isClosed()) {  //isClosed()判断sk是否被读线程关闭，end connection监测是否被主动关闭
					str = reader.readLine();  //被阻塞，无法判断sk是否关闭
					pw.println(str);
					pw.flush();  //清空已有的数据，告知输出流已经输入完毕
					System.out.println("\""+str+"\" sent successfully");
				}
				else	break;
			}
		}catch(Exception e) {e.printStackTrace();}
		try{
			pw.close();
			reader.close();
			sk.close();
		}catch(Exception e) {e.printStackTrace();}
	}
}

/*处理
读操作的线程*/
class ReadHandler implements Runnable{
	private Socket sk;
	public ReadHandler(Socket sk) {this.sk = sk;}
	@Override
	public void run() {
		BufferedReader in = null;
		try {
			in = new BufferedReader(new InputStreamReader(sk.getInputStream()));
		}catch(Exception e) {e.printStackTrace();}
		try {
			String str = new String();  //作判断用
			while(str != null) {
				str = in.readLine();  //若输出线程关闭Socket，调用此方法会引发异常
				if(!str.equals("end connection")) {
					System.out.println("Message from Server: " + str);
				}
				else {	
					System.out.println("Connection outage,press any key to exit");
					break;
				}
			}
			in.close();
		}catch(Exception e) {
			//e.printStackTrace();
		}
		finally {
			if(sk != null) {
				try {
					sk.close();
					} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}  //发生异常，表明输出线程已close掉Socket
			}
		}
	}
}