package telecontrol;

import java.util.Scanner;

public class Operator {
	public static void main(String[] args){
		ReanderAndSender myAr = new ReanderAndSender();
		myAr.getPortList();
		Scanner sc = new Scanner(System.in);
		System.out.println("Whick one is UniverseSuperCarPRO?");
		String serialName = sc.nextLine();
		System.out.println("Baud rate?");
		int br = 9600;
		try{br = sc.nextInt();}catch(Exception e) {System.out.println("Please enter an intenger");}
		try {
			myAr.selectComm("Arduino", br, serialName);
		}catch(Exception e) {
			e.printStackTrace();
			System.exit(0);
			}
		System.out.println("Serial initialization:OK.");
		client myClient = new client(myAr);
		myClient.clientHandler();
	}
}
