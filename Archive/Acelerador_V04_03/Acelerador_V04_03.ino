#include <PID_v1.h>
//Declarando as Variaveis

//Pedal Acelerador
const int pin_ACL01 = A0;           // Pino de entrada analógica do potenciômetro pino 6
const int pin_ACL02 = A1;           // Pino de entrada analógica do potenciômetro pino 4
      int LeituraPedal = 0;         // le o valor do potenciômetro digital de 0 a 1023
      int ValorPedal = 0;           // valor entre 0 e 100% convertido 0 a 1023 em 0 a 100%

//Corpo de Borboleta
const int pin_TPS01 = A2;           // Pino de entrada analógica do potenciômetro tps pino 4
const int pin_TPS02 = A3;           // Pino de entrada analógica do potenciômetro tps pino 1
      int LeituraTPS = 0;           // le o valor do potenciômetro digital de 0 a 1023
      int ValorTPS = 0;             // valor entre 0 e 100% convertido 0 a 1023 em 0 a 100%
      
//Ponte H L298N// (O módulo L298N é um módulo de energia para alimentar o motor DC porque o arduino não fornece energia para meus controles)
      int pin_ENA = 3;              // Portas de controle de velocidade do motor
      int pin_IN01 = 4;             // Portas de controle do motor A no sentido horário
      int pin_IN02 = 2;             // Portas de controle do motor B no sentido anti-horário

// Valores Corpo de Borboleta
const int TPS_MIN = 166;
const int TPS_MAX = 953;

//Valores Acelerador
const int ACL_MIN = 0;
const int ACL_MAX = 1023;

//Motor PWM
const int PWM_MAX = 190;
const int PWM_MIN = 80;

int throttleRest; //Posição normalizada de repouso do acelerador

//PID Control variables
double kP = 2;
double kI = 0;
double kD = 0;

//Define the PID controller
double Input, Output, SetPoint;
PID throttlePID(&Input, &Output, &SetPoint, kP, kI, kD, DIRECT);


void setup()
{

  //Determine pot value with throttle at rest 
  throttleRest = map(constrain(analogRead(pin_TPS01), TPS_MIN, TPS_MAX), TPS_MIN, TPS_MAX, 0, 255);
  
  //Enable PID control
  throttlePID.SetMode(AUTOMATIC);
  
  pinMode(pin_ACL01,  INPUT);
  pinMode(pin_ACL02,  INPUT);
  pinMode(pin_TPS01,  INPUT);
  pinMode(pin_TPS02,  INPUT);
  pinMode(pin_IN01,   OUTPUT);
  pinMode(pin_IN02,   OUTPUT);
  pinMode(pin_ENA,    OUTPUT);
    
  Serial.begin(9600);
}
  
void loop()
{
//_______________________________________________________________________________________
//Leitura do Pedal

    LeituraPedal = analogRead(pin_ACL01);             //Leitura do valor potencimetro
    ValorPedal = map(LeituraPedal,ACL_MIN, ACL_MAX, 0 ,100);   // Função de escala "map": os 74 e 474 são o valor do meu pedal, pode ser que outro pedal e valores diferentes, para encontrá-los substituam os valores "PedaleValeur = map (Pedale, X, Y, 0, 100); " X e Y por X = 0 e Y = 1023 e controlar seu início / fim de sua pedalada, você encontrará seu próprio X e Y

    Serial.print("A posicao do pedal esta em = ");    // Enviamos as informações para a porta serial do console do arduino
    Serial.print(ValorPedal);                         // Retorna o valor da variável na porta serial
    Serial.print("%  ");                              // Valor referente ao acionamento
 //----------------------------------------------------------------------------------------
 
 //________________________________________________________________________________________
 //Leitura do TPS

    LeituraTPS = analogRead(pin_TPS01);               //Leitura do valor potencimetro
    ValorTPS = map(LeituraTPS,TPS_MIN, TPS_MAX, 0 ,100);      // Função de escala "map": os 74 e 474 são o valor do meu pedal, pode ser que outro pedal e valores diferentes, para encontrá-los substituam os valores "PedaleValeur = map (Pedale, X, Y, 0, 100); " X e Y por X = 0 e Y = 1023 e controlar seu início / fim de sua pedalada, você encontrará seu próprio X e Y

    Serial.print("A posicao da borboleta esta em = ");// Enviamos as informações para a porta serial do console do arduino
    Serial.print(ValorTPS);                           // Retorna o valor da variável na porta serial
    Serial.println("%");                              // Valor referente ao acionamento
 //-----------------------------------------------------------------------------------------
 
 //Nova Formula

  //Open throttle if pedal position > throttle position
  if (SetPoint > Input) {
    digitalWrite(pin_IN01, HIGH);
    digitalWrite(pin_IN02, LOW);
  //Close throttle
  } else if (SetPoint < throttleRest && Input <= throttleRest) {
      digitalWrite(pin_IN01, LOW);
      digitalWrite(pin_IN02, HIGH);
  //Return throttle to resting position 
  } else {
    digitalWrite(pin_IN01, LOW);
    digitalWrite(pin_IN02, LOW);
  }
                                                                      
  // Read throttle position 
  Input = map(constrain(analogRead(pin_TPS01), TPS_MIN, TPS_MAX), TPS_MIN, TPS_MAX, 0, 1023);
  
  // Read pedal sensor position 
  SetPoint = map(constrain(analogRead(pin_ACL01), ACL_MIN, ACL_MAX), ACL_MIN, ACL_MAX, 0, 1023);

  //Go PID, Go!
  throttlePID.Compute();

  // Map PID output to motor PWM range 
  Output = map(Output, 0, 255, PWM_MIN, PWM_MAX);
  analogWrite(pin_ENA, Output);

    

}
