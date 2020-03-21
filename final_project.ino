
#include <SoftwareSerial.h>
SoftwareSerial gps(8,7); // RX, TX

//String str="";
/*char str[70];
String gpsString="";

char *test="$GPGGA";
*/
String latitude="no range";
String longitude="no range";
String check_latitude="12.87";
String check_longitude="74.93";

 boolean present_flag=0;
int temp=0,i,count=0;
boolean gps_status=0;
float test;
double k;
String inString = "";    

String firstVal, secondVal, thirdVal, forthVal, fifthVal, sixthVal, seventhVal, eighthVal;
   

void setup() 
{
   pinMode(LED_BUILTIN, OUTPUT);
 Serial.begin(9600);
  gps.begin(9600);

  gsm_init();

  Serial.println("AT+CNMI=2,2,0,0,0");
   Serial.println("gps module testing");

 get_gps();
  delay(2000);
 
    Serial.println("gps module working");
 
  Serial.println("system ready");
     digitalWrite(LED_BUILTIN, LOW);    
  temp=0;
}

void loop()
{
  serialEvent();
  if(temp)
  {
 get_gps();
 tracking();
  }
}

void serialEvent()
{
  while(Serial.available())
  {
    if(Serial.find("Get Attendence"))
    {
      temp=1;
      break;
    }
    else
    temp=0;
  }
}

void gsm_init()
{
  
  boolean at_flag=1;
  while(at_flag)
  {
    Serial.println("AT");
    while(Serial.available()>0)
    {
      if(Serial.find("OK"))
      at_flag=0;
    }
    
    delay(1000);
  }

  
  boolean echo_flag=1;
  while(echo_flag)
  {
    Serial.println("ATE0");
    while(Serial.available()>0)
    {
      if(Serial.find("OK"))
      echo_flag=0;
    }
    delay(1000);
  }

  
 
  boolean net_flag=1;
  while(net_flag)
  {
    Serial.println("AT+CPIN?");
    while(Serial.available()>0)
    {
      if(Serial.find("+CPIN: READY"))
      net_flag=0;
    }
    delay(1000);
  }

}

void get_gps()
{
    Serial.println("Start listening for GPS Shield...");
while (gps.available() > 0) 
  {
    inString = gps.readString();
      
    
    for (int i = 0; i < inString.length(); i++) 
    {
      if (inString.substring(i, i+1) == "*")
      {
        firstVal = inString.substring(1, i);
        secondVal = inString.substring(i+1);
        //Serial.println("Latitude: " + (firstVal) + ", second: " + (secondVal)); 
      }
    }

    for (int i = 0; i < secondVal.length(); i++) 
    {
      if (secondVal.substring(i, i+1) == "%")
      {
        thirdVal = secondVal.substring(0, i);
        forthVal = secondVal.substring(i+1);
        //Serial.println("Longitude: " + (thirdVal) + ", forth: " + (forthVal));    
      }
    }

    for (int i = 0; i < forthVal.length(); i++) 
    {
      if (forthVal.substring(i, i+1) == "@")
      {
        fifthVal = forthVal.substring(0, i);
        sixthVal = forthVal.substring(i+1);
        //Serial.println("Accuracy: " + (fifthVal) + ", sixth: " + (sixthVal));    
        //test = fifthVal.toFloat();
      }
    }

    for (int i = 0; i < sixthVal.length(); i++) 
    {
      if (sixthVal.substring(i, i+1) == "#")
      {
        seventhVal = sixthVal.substring(0, i);
        eighthVal = sixthVal.substring(i+1);
        //Serial.println("Time: " + (seventhVal) + ", eighth: " + (eighthVal));    
      }
    }
    
  //  Serial.println("Latitude: " + (firstVal) + ",    Longitude: " + (thirdVal) + ",    Accuracy: " + (fifthVal) + ",    Time: " + (seventhVal)); 
    //Serial.println(test, 5);


  
   latitude=firstVal.substring(0,5);
   longitude=thirdVal.substring(0,5);

   if((latitude==check_latitude)&&(longitude==check_longitude))
   present_flag=1;
   

 Serial.println(latitude);
   Serial.println(longitude);


//if((firstVal==latitude)&&(thirdVal==longitude))
  //present_flag=1;
 
}
}

void init_sms()
{
  Serial.println("AT+CMGF=1");
  delay(400);
  Serial.println("AT+CMGS=\"+918217886101\"");   // use your 10 digit cell no. here
  delay(400);
}

void send_data(String message)
{
  Serial.println(message);
  delay(200);
}

void send_sms()
{
  Serial.write(26);
}



void tracking()
{
 
   init_sms();
   


  if(present_flag)
   Serial.print("Student is Present");

  else
   Serial.print("Student is Absent");
    send_sms();

    
}
