
//https://github.com/MartyMacGyver/PMS7003-on-Particle/blob/master/pms7003-photon-demo-1/pms7003-photon-demo-1.ino
//https://www.taiwaniot.com.tw/shop/module-sensor/%E7%A9%BA%E6%B0%A3%E7%B2%89%E5%A1%B5-pm2-5/%E6%94%80%E8%97%A4-g7-pms7003-pm1-0-pm2-5-pm10-%E7%B2%89%E5%A1%B5%E6%BF%83%E5%BA%A6%E6%84%9F%E6%B8%AC%E5%99%A8/

#include <SoftwareSerial.h>
#define START_1 0x42
#define START_2 0x4d

#define DATA_LENGTH_H        0
#define DATA_LENGTH_L        1
#define PM1_0_CF1_H          2
#define PM1_0_CF1_L          3
#define PM2_5_CF1_H          4
#define PM2_5_CF1_L          5
#define PM10_CF1_H           6
#define PM10_CF1_L           7
#define PM1_0_ATMOSPHERE_H   8
#define PM1_0_ATMOSPHERE_L   9
#define PM2_5_ATMOSPHERE_H   10
#define PM2_5_ATMOSPHERE_L   11
#define PM10_ATMOSPHERE_H    12
#define PM10_ATMOSPHERE_L    13
#define UM0_3_H              14
#define UM0_3_L              15
#define UM0_5_H              16
#define UM0_5_L              17
#define UM1_0_H              18
#define UM1_0_L              19
#define UM2_5_H              20
#define UM2_5_L              21
#define UM5_0_H              22
#define UM5_0_L              23
#define UM10_H               24
#define UM10_L               25
#define VERSION              26
#define ERROR_CODE           27
#define CHECKSUM             29


unsigned char chrRecv;
byte bytCount = 0;
int PIN_tx= A15;
int PIN_rx = A14;
//int PIN_tx= 11;
//int PIN_rx = 10;
SoftwareSerial myPMS7003(PIN_tx, PIN_rx); 

void setup() {
  Serial.begin(9600);
  Serial.println("PM7003 Reader Ready to go");

  myPMS7003.begin(9600);
}
int count=0;
void loop() {
   unsigned char chrData[30];
   count++;
   if (myPMS7003.available())
   {
        chrRecv = myPMS7003.read();
        
        if (chrRecv == START_1 && bytCount == 0)  bytCount = 1;
        if (chrRecv == START_2 && bytCount == 1)  bytCount = 2;
  
        if (bytCount == 2)
        {
           bytCount = 0;
           
           for(int i = 0; i < 30; i++)
           {
              chrData[i] = myPMS7003.read();
              //Serial.print(String(chrData[i], HEX));
              //Serial.print("-");
           } // end for(bytCount = 0; bytCount < 30; bytCount++)
           //Serial.println("");
           ShowTitle(chrData);
           ShowPM_ATMO(chrData);
           //ShowPM_CF(chrData);
           ShowPM_Count(chrData);
           Serial.print("[COUNT]");Serial.println(count);
           count=0;
           //Serial.print("PM 1.0 Atmosphere = ");
           //Serial.println(GetPM_Data(chrData, PM1_0_ATMOSPHERE_H, PM1_0_ATMOSPHERE_L));
           //Serial.print("PM 2.5 Atmosphere = ");
           //Serial.println(GetPM_Data(chrData, PM2_5_ATMOSPHERE_H, PM2_5_ATMOSPHERE_L));
           //Serial.print("PM 10 Atmosphere = ");
           //Serial.println(GetPM_Data(chrData, PM10_ATMOSPHERE_H, PM10_ATMOSPHERE_L));
  
           delay(1000); //sleep 5 seconds
        }
      }

}

unsigned int GetPM_Data(unsigned char chrSrc[], byte bytHigh, byte bytLow)
{
   return (chrSrc[bytHigh] << 8) + chrSrc[bytLow];
}

void ShowTitle(unsigned char chrData[])
{
         Serial.println("===================================================");
         Serial.print("Data Length = ");
         Serial.print((unsigned int) (chrData[DATA_LENGTH_H] << 8) + chrData[DATA_LENGTH_L]);
         Serial.print(", Device Version = ");
         Serial.print((unsigned int) chrData[VERSION]);
         Serial.print(" (Src=");  Serial.print(chrData[VERSION]);   Serial.print(" HEX="); Serial.print(String(chrData[VERSION], HEX));
         Serial.print("), Error Code = ");
         Serial.println((unsigned int) chrData[ERROR_CODE]);
         Serial.println("");
}

void ShowPM_ATMO(unsigned char chrData[])
{
   Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
   Serial.println("                   Atmosphere (ug/m^3)");
   Serial.println("  PM 1.0     PM 2.5     PM 10");
   Serial.println("---------------------------------------------------");
   Serial.print("  ");
   Serial.print(GetPM_Data(chrData, PM1_0_ATMOSPHERE_H, PM1_0_ATMOSPHERE_L));
   Serial.print("          ");
   Serial.print(GetPM_Data(chrData, PM2_5_ATMOSPHERE_H, PM2_5_ATMOSPHERE_L));
   Serial.print("          ");
   Serial.println(GetPM_Data(chrData, PM10_ATMOSPHERE_H, PM10_ATMOSPHERE_L));
   Serial.println("");
}

void ShowPM_CF(unsigned char chrData[])
{
   Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
   Serial.println("                   CF = 1 (ug/m^3)");
   Serial.println("  PM 1.0     PM 2.5     PM 10");
   Serial.println("---------------------------------------------------");
   Serial.print("  ");
   Serial.print(GetPM_Data(chrData, PM1_0_CF1_H, PM1_0_CF1_L));
   Serial.print("          ");
   Serial.print(GetPM_Data(chrData, PM2_5_CF1_H, PM2_5_CF1_L));
   Serial.print("          ");
   Serial.println(GetPM_Data(chrData, PM10_CF1_H, PM10_CF1_L));
   Serial.println("");
}

void ShowPM_Count(unsigned char chrData[])
{
   Serial.println("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
   Serial.println("                   Dusty Count");
   Serial.println("  >um0.3     >0.5um     >1.0um     >2.5um     >5.0um     >10um");
   Serial.println("--------------------------------------------------------------");
   Serial.print("  ");
   Serial.print(GetPM_Data(chrData, UM0_3_H, UM0_3_L));
   Serial.print("        ");
   Serial.print(GetPM_Data(chrData, UM0_5_H, UM0_5_L));
   Serial.print("        ");
   Serial.print(GetPM_Data(chrData, UM1_0_H, UM1_0_L));
   Serial.print("        ");
   Serial.print(GetPM_Data(chrData, UM2_5_H, UM2_5_L));
   Serial.print("        ");
   Serial.print(GetPM_Data(chrData, UM5_0_H, UM5_0_L));
   Serial.print("        ");
   Serial.print(GetPM_Data(chrData, UM10_H, UM10_L));
   Serial.print("        ");
   
   Serial.println("");
}
