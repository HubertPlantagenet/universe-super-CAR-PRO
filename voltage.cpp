vol(int pin)
{
   //vol�������᷵��һ����ȷ��С�������λ�ĵ�ѹֵ�������ѹ��ΧΪ��0~25v��
   //pin is an analog in pin you choose��pin����ѡ���ģ������ڣ�
   //5����1024=0.00488    voltage=PWM*0.00488*5
   
   int box;
   float voltage;
   box=analogRead(pin);
   voltage=float(box)*0.00455*5;
   return voltage;

}