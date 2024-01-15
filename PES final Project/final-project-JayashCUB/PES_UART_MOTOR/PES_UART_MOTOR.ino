// DC motor 1 control
#define P1A 2 // define pin 2 as for P1A
#define P2A 7 // define pin 7 as for P2A
#define EN12 8 // define pin 8 as for 1,2EN enable

void setup() {
  // Start serial communication with 38400 baud rate
  Serial.begin(38400, SERIAL_8O2);
   pinMode(P1A, OUTPUT);// define pin as OUTPUT for P1A
  pinMode(P2A, OUTPUT);// define pin as OUTPUT for P2A
  pinMode(EN12, OUTPUT);// define pin as OUTPUT for 1,2EN
}

void loop() {
  static String receivedString = "";

  // Check if data is available to read
  while (Serial.available() > 0) {
    // Read the incoming byte
    char receivedByte = Serial.read();
    
    // print the received data
    Serial.print(receivedByte);

    // Check if the received character is a digit
    if (isdigit(receivedByte)) {
      // Accumulate the digit to the string
      receivedString += receivedByte;
    } 
    }
      
      if (receivedString.length() > 0) {
        int receivedInteger = receivedString.toInt();
        //print the received integer
        Serial.print(" Received Integer: ");
        Serial.println(receivedInteger);
        if(receivedInteger < 10)
        {
            //motor off
            digitalWrite(EN12 ,LOW);// Disable 1A and 2A
            delay(50);
        }
        else if(receivedInteger > 10 && receivedInteger < 40)
        {
            //motor clkwise
            digitalWrite(EN12 ,HIGH);// Enable 1A and 2A     
            digitalWrite(P1A,LOW);// send + or HIGH singal to P1A
            digitalWrite(P2A,HIGH);// send - or LOW singal to P2A 
            delay(50);
        }
        else if(receivedInteger > 40)
        {
            //motor anti-clkwise
            digitalWrite(EN12 ,HIGH);// Enable 1A and 2A     
            digitalWrite(P1A,HIGH);// send + or HIGH singal to P1A
            digitalWrite(P2A,LOW);// send - or LOW singal to P2A 
            delay(50);
        }        
      }
      // Reset the string for the next integer
      receivedString = "";
  delay(10);
}
