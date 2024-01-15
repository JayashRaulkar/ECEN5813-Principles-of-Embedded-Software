// DC motor 1 control
#define P1A 2 // define pin 2 as for P1A
#define P2A 7 // define pin 7 as for P2A
#define EN12 8 // define pin 8 as for 1,2EN enable

void setup() {
  pinMode(P1A, OUTPUT);// define pin as OUTPUT for P1A
  pinMode(P2A, OUTPUT);// define pin as OUTPUT for P2A
  pinMode(EN12, OUTPUT);// define pin as OUTPUT for 1,2EN
}

void loop() {
        
   //motor clkwise
   digitalWrite(EN12 ,HIGH);// Enable 1A and 2A     
   digitalWrite(P1A,LOW);// send + or HIGH singal to P1A
   digitalWrite(P2A,HIGH);// send - or LOW singal to P2A 
   delay(500);

   //motor clkwise
   digitalWrite(EN12 ,LOW);// Disable 1A and 2A 
   delay(500);
        
   //motor anti-clkwise
   digitalWrite(EN12 ,HIGH);// Enable 1A and 2A     
   digitalWrite(P1A,HIGH);// send + or HIGH singal to P1A
   digitalWrite(P2A,LOW);// send - or LOW singal to P2A 
   delay(500);
        
}
