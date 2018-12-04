vol(int pin)
{
   //vol函数将会返回一个精确到小数点后两位的电压值，所测电压范围为（0~25v）
   //pin is an analog in pin you choose（pin是你选择的模拟输入口）
   //5处以1024=0.00488    voltage=PWM*0.00488*5
   
   int box;
   float voltage;
   box=analogRead(pin);
   voltage=float(box)*0.00455*5;
   return voltage;

}