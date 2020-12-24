# Iot-Morse-code-interpreter
## Real time communication with Iot and Morse code interpreter

### Objective :

Our aim is to provide a proper instrument for partially paralyzed individuals who are not able to speak


### Abstract :

Morse code is a [character encoding](https://en.wikipedia.org/wiki/Character_encoding) scheme used in [telecommunication](https://en.wikipedia.org/wiki/Telecommunication) 
that encodes [text](https://en.wikipedia.org/wiki/Written_language) characters as standardized sequences of two different signal durations called _dots_ and _dashes.
![](RackMultipart20201224-4-4x3zja_html_1b75abf64ef31c76.png)

<img src="https://github.com/Amogh-Sadhu/Iot-Morse-code-interpreter/blob/main/International%20Morse%20Code%20Chart.png?raw=true" >

### Partially paralyzed :

Individuals who are not able to speak face a major problem in communicating with other peoples. They also want to speak and communicate like other peoples do. 
Usually this individuals have **tremors** ( **Tremor** is an involuntary, rhythmic muscle contraction leading to shaking movements in one or more parts of the body.
It is a common movement disorder that most often affects the hands ). Due to **tremor** this individuals are not able to work on keyboards like all of us do.
So to overcome this problem faced by this individuals we came up to an idea of using morse code for communicating with other people. As sending text messages is easy because
we will provide a single button for communication instead of keyboard. Learning morse code is easy you can also find a gaming app through which you can learn morse code. 
The converted message will be sent to an android app because nowadays people are more familiar with smart phones and android apps.
So in this way we are planning to work for betterment of disabled people because
most technology today is designed for the mass market. Unfortunately, this can mean that people with disabilities can be left behind. 
Developing communication tools like this is important, because for many people, it simply makes life livable.

### Execution:
We have made a morse code converter circuit using ESP8266 Nodemcu with 2 momentary push button, one buzzer, one LED.
- **Push Buttons** : The one push button is to feed the morse-code and other is for adding space and backspace purposes.
- **Buzzer and LED** : Buzzer and LED are for visual and audio indiction for the input. 

When the code is converted it is sent to a Realtime firebase database and from their the data is sent to an android app and presented to user in readable format.


<img src="https://github.com/Amogh-Sadhu/Iot-Morse-code-interpreter/blob/main/Connections.png?raw=true"  width="300">


### Future Scope :
1) We can make this system more compact using custom PCB instead of nodemcu esp8266 and fit it on wheel chair of disabled individuals and these wheel chairs would be made readily available in market.
2) We can also provide the communication app to users through playstore for android, iOS devices.
