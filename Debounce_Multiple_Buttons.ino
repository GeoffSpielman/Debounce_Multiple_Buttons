 /*
Taken mostly from https://www.arduino.cc/en/Tutorial/Debounce
Modified by Geoff Spielman on 2016-08-6.
*/

//breadboard setup
const int btn0 = 2;
const int btn1 = 3;
const int btn2 = 4;
const int btn3 = 5;
const int led0 = 8;  //red
const int led1 = 9;  //yellow
const int led2 = 10; //green
const int led3 = 11; //blue

int btn[] = {btn0, btn1, btn2, btn3};
int led[] = {led0, led1, led2, led3};


unsigned long prevChangeTime[] = {0, 0, 0, 0};
int prevButtonState[] = {0,0,0,0};
int buttonState[] = {0,0,0,0};
unsigned long debounceTime = 50;

void setup() {
 Serial.begin(9600);
 pinMode(btn0, INPUT);
 pinMode(btn1, INPUT);
 pinMode(btn2, INPUT);
 pinMode(btn3, INPUT);
 pinMode(led0, OUTPUT);
 pinMode(led1, OUTPUT);
 pinMode(led2, OUTPUT);
 pinMode(led3, OUTPUT);
}

void loop() {
  
  for (int i = 0; i < 4; i ++)
  {  
    //get the current state of the button
    int cur = digitalRead(btn[i]);
    
    //if the button state has changed, store the current time
    if (cur != prevButtonState[i])
      prevChangeTime[i] = millis();
  
    //if the button has been at this current state for longer than the debounce time (not noise)
    if ((millis() - prevChangeTime[i]) > debounceTime)
    {
      //if the leveled out button state is different than the last intended state
      if (cur != buttonState[i])
      {
        buttonState[i] = cur;
       
        //now that the new state has been confirmed, put your code here
        if (cur)
        {
          //button pressed down
          digitalWrite(led[i], HIGH);
        }
        else {
          //button released
          digitalWrite(led[i], LOW);
        }
      }
    }
    //overwrite previous with current for next interation of the loop
    prevButtonState[i] = cur;
  }
}
