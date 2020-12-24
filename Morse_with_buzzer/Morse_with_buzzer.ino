#include<Ticker.h>
#include<ESP8266WiFi.h>
#include<FirebaseArduino.h>
#include<ArduinoJson.h>

int buzzer=13;
unsigned long signal_len,t1,t2;   //time for which button is pressed
int inputPin = 4;                 //input pin for push button
int ledPin = 16;                   //outpu pin for LED
String code = "";                 //string in which one alphabet is stored
int ButtonState1;
int ButtonState2;



void setup() {
   
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  Serial.begin(115200);
  pinMode(inputPin, INPUT); //internal pullup resistor is used to simplify the circuit
  pinMode(ledPin,OUTPUT);
}

void loop()
{
NextDotDash:
  ButtonState1 = digitalRead(inputPin);
  delay(500);
  while (ButtonState1 == HIGH) {ESP.wdtFeed();}
   tone(buzzer,2500);
  t1 = millis();     //time at button press
  digitalWrite(ledPin, HIGH);               //LED on while button pressed
  ButtonState2 = digitalRead(inputPin);
  delay(500);
  while (ButtonState2 == LOW) {ESP.wdtFeed();}
  t2 = millis(); 
  noTone(buzzer); //time at button release
  digitalWrite(ledPin, LOW);                //LED off on button release
  signal_len = t2 - t1;                     //time for which button is pressed
  if (signal_len > 50)                      //to account for switch debouncing
  {
    code += readio();                       //function to read dot or dash
  }
  while ((millis() - t2) < 500)           //if time between button press greater than 0.5sec, skip loop and go to next alphabet
  {     
    if (digitalRead(inputPin) == LOW)
    {
      goto NextDotDash;
    }
  }
  convertor();                          //function to decipher code into alphabet
}

char readio()
{
  if (signal_len < 600 && signal_len > 50)
  {
    return '.';                        //if button press less than 0.6sec, it is a dot
  }
  else if (signal_len > 600)
  {
    return '-';                        //if button press more than 0.6sec, it is a dash
  }
}

void convertor()
{
  static String letters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
                             ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "E"
                            };
  int i = 0;
  if (code == ".-.-.-")
  {
    Serial.print(".");        //for break
  }
  else
  {
    while (letters[i] != "E")  //loop for comparing input code with letters array
    {
      if (letters[i] == code)
      {
        Serial.print(char('A' + i));
        break;
      }
      i++;
    }
    if (letters[i] == "E")
    {
      Serial.println("<Wrong input>");  //if input code doesn't match any letter, error
    }
  }
  code = "";                            //reset code to blank string
}
