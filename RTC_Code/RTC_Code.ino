//..........................................** REAL TIME COMMUNICATION WITH IoT & MORSE CODE INTERPRETER **.................................................................................................
//................................................................$ PART 1 $..................................................................................

#include<ESP8266WiFi.h>
#include<FirebaseArduino.h>
//#include<ArduinoJson.h>


unsigned long signal_len, t1, t2;      //time for which button is pressed
#define inputPin D7                    //input pin for push button 1
#define spacePin D3                   //input pin for push button 2
#define ledPin D2                     //output pin for LED
#define buzzerpin D1                   //output pin for buzzer

String code = "";                                                             //string in which one alphabet is stored
int i = 0;
int code_strength = 0;                                                      //for differentiating letters(4) and numbers(5).
#define FIREBASE_HOST "postman-99991.firebaseio.com"                         // the project name address from firebase id
#define FIREBASE_AUTH "ODx9GP58daGUiyYiHYIwq1nhSJjvYb6RxlVkzbYU"             // the secret key generated from firebase
#define WIFI_SSID "Abhijeet"                                                 //WiFi Name
#define WIFI_PASSWORD "123456789"                                           //WiFi Password
String text = "";                                                           //string in which actual message is stored
int count = 0;                                                              //to find String length and store it to remove last character


//..............................................................$ PART 2 $..............................................................................
//..................................................................................................................................................

char readio()                                                                //To read digital signal as dot or dash
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

//............................................................$ PART 3 $.........................................................................................
//..................................................................................................................................................

void convertor()                        //Used to convert morse code to its corresponding letter and number
{
  code_strength = code.length();
  Serial.print("code mass: ");
  Serial.println(code_strength);


  static String letters[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-",
                             ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "E"
                            };
  static String numbers[] =  {"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "E"   };

  int i = 0;

  if (code_strength <= 4)                //if code strength is less than or equal to 4 its is a letter
  {
    while (letters[i] != "E")  //loop for comparing input code with letters array
    {
      if (letters[i] == code)
      {
        text += char('A' + i);
        Serial.println(text);
        Firebase.setString("Message", text);            //To send text message to firebase
        delay(500);
        break;
      }
      i++;
    }
    if (letters[i] == "E")
    {
      Serial.println("<Wrong input>");  //if input code doesn't match any letter, error
      text = "";
    }
    code = "";                            //reset code to blank string
  }
  else if (code_strength == 5)
  { //if code strength is 5 it is a number.
    while (numbers[i] != "E")  //loop for comparing input code with letters array
    {
      if (numbers[i] == code)
      {
        text += char('0' + i);
        Serial.println(text);
        Firebase.setString("Message", text);            //To send text message to firebase
        delay(500);
        break;
      }
      i++;
    }
    if (numbers[i] == "E")
    {
      Serial.println("<Wrong input>");  //if input code doesn't match any letter, error
      text = "";
    }
    code = "";                            //reset code to blank string
  }
  else {
    Serial.println("<Wrong input>");  //if input code doesn't match any letter, error
    text = "";
    code = "";
  }
}

//.........................................................$ PART 4 $.........................................................................................
//..................................................................................................................................................

void spaces()                                                                //to convert code from Button 2, into space or backspace
{
  if (code == ".")
  {
    Serial.println("Backspace");
    count = text.length();
    count = count - 1;
    text.remove(count);                             //To remove last letter (basically works as backspace)
    Serial.println(text);
    Firebase.setString("Message", text);            //To send text message to firebase
    delay(500);
    code = "";                            //reset code to blank string

  }
  else if (code == "-")
  {
    Serial.println("Space");
    text += " ";                                    //To add a space to text
    Serial.println(text);
    Firebase.setString("Message", text);            //To send text message to firebase
    delay(500);
    code = "";                            //reset code to blank string
  }
  else {
    Serial.println("wrong input");
    code = "";                            //reset code to blank string
  }
}

//.........................................................$ PART 5 $.........................................................................................
//..................................................................................................................................................

void setup() {
  Serial.begin(115200);
  pinMode(inputPin, INPUT_PULLUP); //internal pullup resistor is used to simplify the circuit
  pinMode(spacePin, INPUT_PULLUP); //internal pullup resistor is used to simplify the circuit
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerpin, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP ADDRESS is : ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase
  Firebase.setString("Message", "");                                         //send initial string of status
}

//...........................................................$ PART 6 $.......................................................................................
//..................................................................................................................................................

void loop()
{
  if (digitalRead(spacePin) == LOW)                       //Button 2 is HIGH i.e code will be space or backspace
  {
    Serial.println("Button 2");
NextDahDit:
    while (digitalRead(spacePin) == HIGH) {
      ESP.wdtFeed(); //To feed watchdog timer before it bites
    }
    t1 = millis();                            //time at button press
    digitalWrite(ledPin, HIGH);               //LED on while button pressed
    tone(buzzerpin, 2500);                    //buzz at particular frequency
    while (digitalRead(spacePin) == LOW) {
      ESP.wdtFeed();
    }
    t2 = millis();                            //time at button release
    digitalWrite(ledPin, LOW);                //LED off on button release
    noTone(buzzerpin);                        //To stop buzz effect
    signal_len = t2 - t1;                     //time for which button is pressed
    if (signal_len > 50)                      //to account for switch debouncing
    {
      code += readio();                       //function to read dot or dash
    }
    while ((millis() - t2) < 500)           //if time between button press greater than 0.5sec, skip loop and go to next alphabet
    {
      if (digitalRead(spacePin) == LOW)
      {
        goto NextDahDit;
      }
    }
    spaces();
  }
  else if (digitalRead(inputPin) == LOW)                                  //Button 1 is HIGH i.e code will be letters or numbers
  {
    Serial.println("Button 1");
NextDotDash:
    while (digitalRead(inputPin) == HIGH) {
      ESP.wdtFeed(); //To feed watchdog timer before it bites
    }
    t1 = millis();                            //time at button press
    digitalWrite(ledPin, HIGH);               //LED on while button pressed
    tone(buzzerpin, 2500);                    //buzz at particular frequency
    while (digitalRead(inputPin) == LOW) {
      ESP.wdtFeed();
    }
    t2 = millis();                            //time at button release
    digitalWrite(ledPin, LOW);                //LED off on button release
    noTone(buzzerpin);                        //To stop buzz effect
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
  else
  {
    //Default
    //Serial.println("No button");
  }
}

//...........................................................## END OF CODE ##...................................................................................
//..................................................................................................................................................
