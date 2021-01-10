#if 1

  #define START_LISTENING 30000 //czas po ktorym otrzymujemy pierwszy pomiar z czujnika
  #define NOISE_TRSHLD 200      //granica dzwieku przy ktorej dostajemy powiadomienie
  #define BLYNK_PRINT Serial  
  #define ESP8266_BAUD 9600
  
  #include <ESP8266_Lib.h>
  #include <BlynkSimpleShieldEsp8266.h>  
  #include <SoftwareSerial.h>
  
  char auth[] = "zapytac mnie co tu wpisac";
  char ssid[] = "nazwa sieci";
  char pass[] = "haslo do wifi";

  SoftwareSerial EspSerial(2, 3); // RX, TX dla arduino

  ESP8266 wifi(&EspSerial);
  
  WidgetLED ledShot(V0);
  WidgetLED ledV(V1);
  //WidgetLED ledConnecting(V2);
  
  uint8_t ledVOn;
  uint32_t loudness;
  bool connection;
  
  BlynkTimer timer;
  
  void connectionStatus()
  {
    if(Blynk.connected() && (millis() >= START_LISTENING))
    {
      //ledConnecting.off();
      digitalWrite(9, LOW);
      connection = true;
    }
  }
  
  void Blink()
  {
    if(ledVOn == 0)
    {
      ledV.on();
      ledVOn = 1;
    }
    else
    {
      ledV.off();
      ledVOn = 0;
    }
    
    if(digitalRead(8) == LOW)
      digitalWrite(8, HIGH);
    else
      digitalWrite(8, LOW);
  
  }
  
  void emailMe()
  {
    if(millis() >= START_LISTENING)
    {
      loudness = analogRead(0);
      
      if (loudness > NOISE_TRSHLD)
      {
        //Blynk.email("themambamonster@gmail.com", "KSSR@22", "SHOT DETECTED");
        Blynk.notify("SHOT DETECTED");
        ledShot.on();
      }
      Serial.println("loudness: "); Serial.println(loudness);
    }
  }
  
  void setup()
  {
    digitalWrite(9, HIGH);
    
    // Debug console
    Serial.begin(9600);
  
    // Set ESP8266 baud rate
    EspSerial.begin(ESP8266_BAUD);
    delay(10);
  
    Blynk.begin(auth, wifi, ssid, pass);
    // You can also specify server:
    //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 80);
    //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);
    
    //ledConnecting.on();
    ledShot.off();
    ledVOn = 0;
  
    timer.setInterval(20L, emailMe);
    timer.setInterval(500L, Blink);
    if(connection == false)
    timer.setInterval(50L, connectionStatus);
  }
  
  void loop()
  {
    Blynk.run();
    timer.run();
  }

#else
// ----------------------------------------------- to sluzy do wysylania polecen AT do ESP8266 przez monitor portu szeregowego (normalnie nie jest kompilowane) -----------------------------------------------------
  #include <SoftwareSerial.h>
  
  SoftwareSerial mySerial(2, 3);  //RX,TX
  
  //  Arduino pin 2 (RX) to ESP8266 TX
  //  Arduino pin 3 to voltage divider then to ESP8266 RX
  //  Connect GND from the Arduiono to GND on the ESP8266
  //  Pull ESP8266 CH_PD HIGH
  
  // When a command is entered in to the serial monitor on the computer 
  // the Arduino will relay it to the ESP8266
  
   
  int LEDPIN = 13;
   
  void setup() 
  {
      pinMode(LEDPIN, OUTPUT);
   
      Serial.begin(115200);     // communication with the host computer
      //while (!Serial)   { ; }
   
      // Start the software serial for communication with the ESP8266
      mySerial.begin(115200);  
   
      Serial.println("");
      Serial.println("Remember to to set Both NL & CR in the serial monitor.");
      Serial.println("Ready");
      Serial.println("");    
  }
   
  void loop() 
  {
      // listen for communication from the ESP8266 and then write it to the serial monitor
      if ( mySerial.available() )   {  Serial.write( mySerial.read() );  }
   
      // listen for user input and send it to the ESP8266
      if ( Serial.available() )       {  mySerial.write( Serial.read() );  }
  }
  
#endif
