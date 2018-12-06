package client;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;  

public class client{
	public final static int port = 38380;
	public final static String serverIP = "149.28.18.99";
	//����ʹ�þ�̬����
	
	public static void main(String[] args) {
		clientHandler();
	}
	public static void clientHandler() { //������һ����̬���������ø����е�����һ����̬����
		try {
			Socket sk = new Socket(serverIP,port);
			System.out.println("Connected");
			//������д�߳�
			new Thread(new WriteHandler(sk)).start();
			new Thread(new ReadHandler(sk)).start();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.exit(0);  //�����쳣ʱ�����˳�
		}
	}
}

/*����
д�������߳�*/
class WriteHandler implements Runnable{
	public WriteHandler(Socket sk) {this.sk = sk;}//���̴߳���Socket����
	private Socket sk;
	@Override
	public void run() {
		PrintWriter pw = null;  //�����������������Ҫ��ͬһ��try�н��в���
		try {
			pw = new PrintWriter(sk.getOutputStream());
		}catch(Exception e) {e.printStackTrace();}
		BufferedReader reader = null;
		try {
			String str = new String();  //���ж���
			reader = new BufferedReader(new InputStreamReader(System.in));
			while(str != null) {
				if(!str.equals("end connection")  && !sk.isClosed()) {  //isClosed()�ж�sk�Ƿ񱻶��̹߳رգ�end connection����Ƿ������ر�
					str = reader.readLine();  //���������޷��ж�sk�Ƿ�ر�
					pw.println(str);
					pw.flush();  //������е����ݣ���֪������Ѿ��������
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

/*����
���������߳�*/
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
			String str = new String();  //���ж���
			while(str != null) {
				str = in.readLine();  //������̹߳ر�Socket�����ô˷����������쳣
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
				}  //�����쳣����������߳���close��Socket
			}
		}
	}
}