#include <Wire.h>                 // usando a biblioteca Wire
#include <LiquidCrystal_I2C.h>    // usando a biblioteca LiquidCrystal I2C
LiquidCrystal_I2C lcd(0x27,16,2); // Configura endereço I2C 0x27 para um display com 16 caracteres e 2 linhas
int thisChar = 0 ;

#include <max6675.h>             // usando a biblioteca do circuito integrado MAX6675
 
/* Definições: GPIOs do Arduino utilizado na comunicação com o MAX6675 */ 

#define GPIO_SO       8 
#define GPIO_CS       9
#define GPIO_CLK      10


MAX6675 termopar(GPIO_CLK, GPIO_CS, GPIO_SO); // Criação de objeto para comunicação com termopar


int PWM_pin = 3; //Pino 3 digital

//Variaveis
float temperatura_lida = 0.0;
float setpoint_temperatura = 51;
float erro_pid = 0;
float erro_anterior = 0;
float tempo_decorido, tempo, tempo_prev;
int PID_valor = 0;



//PID constantes
int kp = 9.1;   int ki = 0.3;   int kd = 1.8;
int PID_p = 0;    int PID_i = 0;    int PID_d = 0;

void setup() {
  pinMode(PWM_pin,OUTPUT);
  TCCR2B = TCCR2B & B11111000 | 0x03;    // pino 3 com frequencia de 980.39 Hz
  tempo = millis(); 
  lcd.init();
  lcd.backlight();
}

void loop() {

  temperatura_lida = termopar.readCelsius();
  erro_pid = setpoint_temperatura - temperatura_lida; //Calculando o erro entre o valor setado e o valor lido pelo termopar
  PID_p = kp * erro_pid; //Calculando o valor de P
  if(-3 < erro_pid <3) //Calculando o valor de I num range entre +-3
  {
    PID_i = PID_i + (ki * erro_pid);
  }

  tempo_prev = tempo;                    
  tempo = millis();
  tempo_decorido = (tempo - tempo_prev) / 1000; 
  PID_d = kd*((erro_pid - erro_anterior)/tempo_decorido); //Calculando o valor de D
  
  PID_valor = PID_p + PID_i + PID_d; //Valor final será a soma de P + I + D

  
  if(PID_valor < 0) //  PWM no range entre 0 e 255
  {    PID_valor = 0;    }
  if(PID_valor > 255)  
  {    PID_valor = 255;  }

  analogWrite(PWM_pin,255-PID_valor); //Escrevendo o sinal PWM para o mosfet no pino 3~
  erro_anterior = erro_pid;
  delay(300);

  lcd.setCursor(0,0);
  lcd.print("CONTROLE PID TEMP");
  lcd.setCursor(0,1);
  lcd.print("S:");
  lcd.setCursor(2,1);
  lcd.print(temperatura_lida,1);
  lcd.setCursor(9,1);
  lcd.print("R:");
  lcd.setCursor(11,1);
  lcd.print(temperatura_lida,1);
}
