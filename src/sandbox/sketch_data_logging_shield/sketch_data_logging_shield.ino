                 #include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;
tmElements_t clockTime;
void initClock(){ 
  if (!RTC.read(clockTime)) {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }    
  }
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
void readClock(){  

  if (RTC.read(clockTime)) {
    Serial.print("Ok, Time = ");
    print2digits(clockTime.Hour);
    Serial.write(':');
    print2digits(clockTime.Minute);
    Serial.write(':');
    print2digits(clockTime.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(clockTime.Day);
    Serial.write('/');
    Serial.print(clockTime.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(clockTime.Year));
    Serial.println();
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
}
void setup() {
  Serial.begin(9600);
  
  initClock();
  
//writeClock();

}

void loop() {

  
  readClock();
  
}


tmElements_t writeClockTime;
bool getTime4WriteClock(const char *str){
  int Hour, Min, Sec;
  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  writeClockTime.Hour = Hour;
  writeClockTime.Minute = Min;
  writeClockTime.Second = Sec;
  return true;
}
bool getDate4WriteClock(const char *str){
  const char *monthName[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
  };  
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  writeClockTime.Day = Day;
  writeClockTime.Month = monthIndex + 1;
  writeClockTime.Year = CalendarYrToTm(Year);
  return true;
}
void writeClock(){  
  bool parse=false;
  bool config=false;

  // get the date and time the compiler was run
  if (getDate4WriteClock(__DATE__) && getTime4WriteClock(__TIME__)) {
    parse = true;
    // and configure the RTC with this info
    if (RTC.write(writeClockTime)) {
      config = true;
    }
  } 
  while (!Serial) ; // wait for Arduino Serial Monitor
  delay(200);
  if (parse && config) {
    Serial.print("DS1307 configured Time=");
    Serial.print(__TIME__);
    Serial.print(", Date=");
    Serial.println(__DATE__);
  } else if (parse) {
    Serial.println("DS1307 Communication Error :-{");
    Serial.println("Please check your circuitry");
  } else {
    Serial.print("Could not parse info from the compiler, Time=\"");
    Serial.print(__TIME__);
    Serial.print("\", Date=\"");
    Serial.print(__DATE__);
    Serial.println("\"");
  }  
}

bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}
