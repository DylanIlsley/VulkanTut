#include <SimpleTimer.h>

SimpleTimer timer;
SimpleTimer LEDTimer;
SimpleTimer SerialTimer;

// Class to represent time variables
struct cTime{
  cTime(int hours, int minutes)
  {
    m_msecsSinceStartOfDay = hours * 3600000 + minutes * 60000;
  };

  cTime(long msecsSinceStartOfDay)
  {
    m_msecsSinceStartOfDay = msecsSinceStartOfDay;
  }

  cTime& operator++()
  {
    m_msecsSinceStartOfDay += 60000 ; // Add one minute to the time
    return *this;
  }

  bool operator>(cTime rhsTime)
  {
    return m_msecsSinceStartOfDay > rhsTime.m_msecsSinceStartOfDay;
  }

  bool operator<(cTime rhsTime)
  {
    return m_msecsSinceStartOfDay < rhsTime.m_msecsSinceStartOfDay;
  }

  bool operator>=(cTime rhsTime)
  {
    return m_msecsSinceStartOfDay >= rhsTime.m_msecsSinceStartOfDay;
  }

  bool operator<=(cTime rhsTime)
  {
    return m_msecsSinceStartOfDay <= rhsTime.m_msecsSinceStartOfDay;
  }

  String toString()
  {
    return String(m_msecsSinceStartOfDay);
  }

  int Hours()
  {
    return m_msecsSinceStartOfDay/3600000;
  }

  int Minutes()
  {
    return m_msecsSinceStartOfDay/60000;
  }

  void reset()
  {
    m_msecsSinceStartOfDay = 0;
  }
  
  long m_msecsSinceStartOfDay; //<The number of miliseconds since the start of day
};

// Time trackers
// Defaulted to zero so that it wont be on unless the pc has synced with it at least once since being on
cTime CurrentTime = cTime(0,0);
cTime StartTime = cTime(0,0);
cTime StopTime = cTime(0, 0);


//defs
bool OFF = HIGH;
bool ON = LOW;
long sec = 1000;
long minute = ((long)60) * sec; // multiple brackets since I'm not sure how casting will work on arduion
long hour = ((long)60) * minute;

// Relay pin is controlled with D10. The active wire is connected to Normally Open
int relay = 10;

bool relayState = OFF; // start off state so that if power goes off we don't ever have the light on longer than it should be




// swaps the state of the light
void SwapState(){
   // checking  whether the light should be turned on/off next hour
  ++CurrentTime;
  // Reset the time over 24 hours
  if (CurrentTime.Hours() >= 24)
      CurrentTime.reset();

  if (relayState == ON and CurrentTime >= StopTime){
        relayState = OFF;
  }

  else if (relayState == OFF and CurrentTime >= StartTime and CurrentTime < StopTime){
        relayState = ON;
  }

 digitalWrite(relay, relayState);
 
}

void ShowTime(){
 // int tempHours = NumberHoursInState;
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);       

  for (int i=0; i<CurrentTime.Hours(); ++i){
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
    
  }
 digitalWrite(LED_BUILTIN, LOW);// turn off till next display
}


void SerialHandler(){
   // Only do anything if serial is actually set up
   if(Serial.available()){
        String strCommand = Serial.readStringUntil('\n');
        if (strCommand == "SYN")
           SendParams();
        else if (strCommand)
          HandleCommand(strCommand);
  }
}

// Responsible for handling the commands given by the PC
void HandleCommand(String strCommand)
{
  // TODO: Create a splitting function to tidy up this code
  String strCurrentTime = getValue(strCommand, ',', 0);
  String strStartTime = getValue(strCommand,',', 1);
   // Find the position of strStartTime and then move past it.
   // NOTE: +1 to move past the delimiter
  String strStopTime = strCommand.substring(strCommand.indexOf(strStartTime) + strStartTime.length() + 1);

  
  StartTime = cTime(strStartTime.toInt());
  StopTime = cTime(strStopTime.toInt());
  CurrentTime = cTime(strCurrentTime.toInt());

  // Send the updated params so there is no delay
  SendParams();
}


void SendParams()
{
  // send with the current store for each variable
  String strReply  = CurrentTime.toString()  + ',' + StartTime.toString() + ',' + StopTime.toString() +  "\n";
  // Need to print time out again
  // Boomerang packet
  Serial.write(strReply.c_str(), strReply.length());
}


void setup() {
  // Pin for relay module set as output
  pinMode(relay, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Setup serial connection
  Serial.begin(9600);
   
  // always right off straight away so the light doesn't flicker
  digitalWrite(relay, relayState);

  // TODO: Can this be changed to be every minute instead? Would prevent the light from taking too long
  timer.setInterval(minute, SwapState); // have to write each hour since the maximum size it can take is less than 8 hours
 // LEDTimer.setInterval(20*sec, ShowTime);
  SerialTimer.setInterval(sec, SerialHandler);

  ShowTime();//want to show time straight away
}


void loop() {
    timer.run();
    LEDTimer.run();
    SerialTimer.run();
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {
    0, -1  };
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
      found++;
      strIndex[0] = strIndex[1]+1;
      strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
