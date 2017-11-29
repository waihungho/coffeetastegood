

//Request (This)
//A5 04 00 03 00 04 18 ED
//  Starting Address: 03
//Response
//A5 04 08 02 10 00 00 0A 21 00 00 F0 F5
//02 10 -> TDS = 528 / 10 = 52.8 ppm
//0A 21 -> Temperature = 2593 / 100 = 25.93 oC

// led to indicate that a communication error is present
#define connection_error_led 13

//////////////////// Port information ///////////////////
#define baud 9600
#define timeout 1000
#define polling 200 // the scan rate

// If the packets internal retry register matches
// the set retry count then communication is stopped
// on that packet. To re-enable the packet you must
// set the "connection" variable to true.
#define retry_count 20 

// used to toggle the receive/transmit pin on the driver
#define TxEnablePin 2 


                                    

// This is the easiest way to create new packets
// Add as many as you want. TOTAL_NO_OF_PACKETS
// is automatically updated.
enum
{
  PACKET1,
  //PACKET2,
  // leave this last entry
  TOTAL_NO_OF_PACKETS
};

// Create an array of Packets for modbus_update()
Packet packets[TOTAL_NO_OF_PACKETS];

// Create a packetPointer to access each packet
// individually. This is not required you can access
// the array explicitly. E.g. packets[PACKET1].id = 2;
// This does become tedious though...
packetPointer packet1 = &packets[PACKET1];
//packetPointer packet2 = &packets[PACKET2];

// The data from the PLC will be stored
// in the regs array
unsigned int regs[9];

void setup()
{
  // read 3 registers starting at address 0
  packet1->id = 0xA5; // A5
  packet1->function = 4;
//  packet1->address = 3;  // Starting Address
//  packet1->no_of_registers = 4;  // Request 6 registers

  packet1->address = 0;  // Starting Address
  packet1->no_of_registers = 1;  // Request 6 registers

  
  packet1->register_array = regs;
  
//  // write the 9 registers to the PLC starting at address 3
//  packet2->id = 2;
//  packet2->function = PRESET_MULTIPLE_REGISTERS;
//  packet2->address = 3;
//  packet2->no_of_registers = 9;
//  packet2->register_array = regs;
  
  // P.S. the register_array entries above can be different arrays


  delay(2000);
  
  // Initialize communication settings etc...
//  modbus_configure(baud, timeout, polling, retry_count, TxEnablePin, packets, TOTAL_NO_OF_PACKETS);
  //Serial.begin(9600, SERIAL_8E1);
  pinMode(connection_error_led, OUTPUT);

  pinMode(2, OUTPUT);
  
  Serial.begin(baud, SERIAL_8E1);
  //Serial.begin(baud);
    
  
}

void loop(){
    //Serial.println("Send Packet(BEGIN)");
    //Serial.flush();

    while (Serial.available()){
      Serial.read();
    }

    digitalWrite(2, HIGH);
    
//Request (This)
//A5 04 00 03 00 04 18 ED
//  Starting Address: 03
//Response
//A5 04 08 02 10 00 00 0A 21 00 00 F0 F5



    byte message[] = {0xA5, 0x04, 0x00, 0x03, 0x00, 0x04, 0x18, 0xED};
    Serial.write(message, sizeof(message));
//    Serial.write(0xA5);
//    Serial.write(0x04);
//    Serial.write(0x00);
//    Serial.write(0x03);
//    Serial.write(0x00);
//    Serial.write(0x04);
//    Serial.write(0x18);
//    Serial.write(0xED);
    Serial.flush();

    //Serial.println("Send Packet(END).");
//    Serial.flush();
    delay(1000);
    digitalWrite(2, LOW);
    int count=0;
    unsigned char frame[128];
    while (Serial.available()){
      frame[count++]=Serial.read();
    }
    Serial.println(String("Receive Packet[count]") + count);
    for (int i=0; i<count;i++){
      Serial.println(String("frame[i]") + i+":" + frame[i]);
      Serial.print (String("frame[i][HEX]") + i+":");
      Serial.println(frame[i],HEX);
      
    }
    unsigned int highBitTds = frame[3];
    unsigned int lowBitTds = frame[4];
    unsigned int highBitTemp = frame[7];
    unsigned int lowBitTemp = frame[8];
    Serial.println(String("[highBitTds]") + highBitTds + "[lowBitTds]" + lowBitTds  + "[highBitTemp]" + highBitTemp + "[lowBitTemp]" + lowBitTemp +".");
    unsigned int tds=highBitTds<<8 | lowBitTds;
    unsigned int temp =  highBitTemp<<8 | lowBitTemp;
    Serial.println(String("[tds]") + tds + "[temp]" + temp +".");
    
    delay(5000);
}

//
//void loop()
//{
//  unsigned int connection_status = modbus_update(packets);
//  Serial.println(String("TOTAL_NO_OF_PACKETS:") + TOTAL_NO_OF_PACKETS + "[connection_status]"+ connection_status +".");
//  if (connection_status != TOTAL_NO_OF_PACKETS)
//  {
//    digitalWrite(connection_error_led, HIGH);
//    // You could re-enable the connection by:
//    //packets[connection_status].connection = true;
//  }
//  else{
//    digitalWrite(connection_error_led, LOW);
//  }
//  
//  Serial.println(String("regs0:") + regs[0]);
//  Serial.println(String("regs1:") + regs[1]);
//  Serial.println(String("regs2:") + regs[2]);
//
//  delay(3000);
//  Serial.println("");
//    
//  // update the array with the counter data
////  regs[3] = packet1->requests;
////  regs[4] = packet1->successful_requests;
////  regs[5] = packet1->total_errors;
////  regs[6] = packet2->requests;
////  regs[7] = packet2->successful_requests;
////  regs[8] = packet2->total_errors; 
//}
