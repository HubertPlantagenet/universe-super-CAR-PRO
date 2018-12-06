package telecontrol;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;




public class Server{
	public final static int port = 38380;
	/*public static void main(String[] args){
		Server server = new Server();
		ServerSocket serverSK = null;
		try {
			serverSK = new ServerSocket(port);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		server.init(serverSK);  //Ҳ����ͨ���½��������һ�����󷽷�
	}*/
	public void init(ServerSocket serverSK) {  //��ʼ������
		Socket sk_1 = null;
		Socket sk_2 = null;
		try {
			sk_1 = serverSK.accept();
			System.out.println("The first client connected.");
			sk_2 = serverSK.accept();
			System.out.println("The second client connected.");
		}catch(Exception e) {e.printStackTrace();}
		//�ֱ�������client�Ķ�д����
		new Thread(new ServerHandler(sk_2,sk_1)).start();
		new Thread(new ServerHandler(sk_1,sk_2)).start();
	}
}

class ServerHandler implements Runnable{
	private Socket sk_1;
	private Socket sk_2;
	public ServerHandler(Socket sk_1 , Socket sk_2) {this.sk_1 = sk_1;this.sk_2 = sk_2;}
	@Override
	public void run() {
		PrintWriter pw = null;
		String str = new String();  //���ж���
		BufferedReader in = null;
		try {
			in = new BufferedReader(new InputStreamReader(sk_1.getInputStream()));
			pw = new PrintWriter(sk_2.getOutputStream());
		}catch(Exception e) {
			e.printStackTrace();
			System.exit(0);
			}
		try {
			while(str != null) {
				if(!str.equals("end connection")) {
					str = in.readLine();  //���ܷ���null
					System.out.println("Message from client:" + str);
					pw.println(str);
					pw.flush();
					System.out.println("Message sent sucessfully");
				}
				else	break;
			} 
			in.close();
			pw.close();
			//��ֹ�ظ�close
			if(sk_1 != null)
				sk_1.close();
			if(sk_2 != null)
				sk_2.close();
			}catch (IOException e) {
		}
	}
}
