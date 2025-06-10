
/*
  Amesis Project & FreakDoctor
    ^ ^    		   """"  
  =( '')=  		   Ø-Ø"
  ( ")_( ")   	    ""
                
   https://github.com/AmesisProject/002-Amesis-Throttle_To_ThrottleBody_Arduino
   
   
Youtube   : https://www.youtube.com/channel/UCCexVZN3UYSep2lsj2jVjdg?sub_confirmation=1
GitHub    : https://github.com/AmesisProject
			https://github.com/freakdoctor
Discord   : https://discord.gg/vRAybmd3hk
FaceBook  : https://www.facebook.com/amesis.pro.5
Instagram : https://www.instagram.com/?hl=fr
  
  licence OpenSource CC-BY-NC-SA
  licence OpenSource non comercialisable, modifiable en citant le propriétaire AmesisProject avec l'un des liens ci dessus

NomDuProjet : Speeduino_Bosch_electronic_throttle_body
Version     : v1.0 28/05/2021
  


  Hardware Connections:
  -Throttle Input 0:        Pin A0
  -TPS 0:                   Pin A1

  -VNH7070AS H-Bridge Enable A: Pin 9
  -VNH7070AS H-Bridge Input 1:  Pin 8
  -VNH7070AS H-Bridge Input 2:  Pin 11
*/

//Pins assignments
#define pinI1 8
#define pinI2 9
#define speedPin 6

//PID Library
#include <PID_v1.h>

int minTps = 0;       //---------------NEW---------------
int maxTps = 0;       //---------------NEW---------------
int sensorValue = 0;  //---------------NEW---------------

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, 1, 0, 0, DIRECT);

void setup()
{
  //Set PWM frequency to 31.37255 kHz
  TCCR1B = TCCR1B & 0b11111000 | 0x01;

  Input = 0;
  Setpoint = 0;
  myPID.SetMode(AUTOMATIC); // PID Mode
  pinMode(pinI1, OUTPUT); //VNH7070AS H-Bridge Input 1
  pinMode(pinI2, OUTPUT); //VNH7070AS H-Bridge Input 2
  pinMode(speedPin, OUTPUT); //VNH7070AS H-Bridge Enable
  digitalWrite(pinI2, LOW); //VNH7070AS H-Bridge Input 2
  digitalWrite(pinI1, HIGH); //VNH7070AS H-Bridge Input 1
  Serial.begin(9600);


  //Auto Calibration TPS
  while (millis() < 1000) {             //---------------NEW---------------
    sensorValue = analogRead(1);        //---------------NEW---------------
    // record the minimum sensor value  //---------------NEW---------------
    minTps = sensorValue;               //---------------NEW---------------
  }                                     //---------------NEW---------------
  while (millis() < 2500) {             //---------------NEW---------------
    sensorValue = analogRead(1);        //---------------NEW---------------
    analogWrite(speedPin, 255);         //---------------NEW---------------
    // record the maximum sensor value  //---------------NEW---------------
    maxTps = sensorValue;               //---------------NEW---------------
  }                                     //---------------NEW---------------
  if (millis() >  2500) {               //---------------NEW---------------
    analogWrite(speedPin, 0);           //---------------NEW---------------
  }                                     //---------------NEW---------------
}
void loop()
{
  //Uncomment to tune the PID loop
  /*
    float Kp = mapfloat(analogRead(4), 0, 1023, 0, 5);
    Serial.print(Kp, DEC);
    Serial.print("  ");
    float Ki = mapfloat(analogRead(5), 0, 1023, 0, 5);
    Serial.print(Ki, DEC);
    Serial.print("  ");
    myPID.SetTunings(Kp, Ki, 0.00);
  */

  //digitalWrite(LEDPin, LOW);

  //PID Loop tunings
  myPID.SetTunings(0.15, 2.00, 0.00);
  //myPID.SetTunings(0.80, 0.20, 0.01);

  //int TPS1 = constrain(analogRead(1), 161, 963);  //Range: 161 - 963
  int TPS1 = constrain(analogRead(1), minTps, maxTps);  //Range: autocalibrated min and max values  //---------------NEW---------------

  //PID Input from TPS
  //Input = map(constrain(TPS1, 161, 963), 161, 963, 0, 180);
  Input = map(constrain(TPS1, minTps, maxTps), minTps, maxTps, 0, 180); //---------------NEW---------------

  int Pedal0 = map(constrain(analogRead(0), 70, 470), 70, 470, 0, 180);  //Range: 70 - 470


  //PID Setpoint from Throttle Pedal
  Setpoint = Pedal0;
  //Set throttle to 0
  if (Setpoint <= 5)
  {
    analogWrite(speedPin, 0);
  }
  else
  {
    myPID.Compute();
    analogWrite(speedPin, Output);
  }
  /*
    Serial.print(diff0, DEC);
    Serial.print("  ");
    Serial.print(diff1, DEC);
    Serial.print("  ");
    Serial.print(TPS0, DEC);
    Serial.print("  ");
    Serial.print(TPS1, DEC);
    Serial.print("  ");
    Serial.print(Pedal0, DEC);
    Serial.print("  ");
    Serial.print(Pedal1, DEC);
    Serial.print("  ");
    Serial.print(Input, DEC);
    Serial.print("  ");
    Serial.print(Setpoint, DEC);
    Serial.print("  ");
    Serial.println(Output, DEC);
  */
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
