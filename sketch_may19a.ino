// Libraries
#include <Servo.h>      // servo-motors lead up.
#include <Ultrasonic.h> // PING sensor lead up.

// objects definition
Servo myservo; // my own servo object

// variables and constants definition
int in1 = 6;                   // motor 1, 1st pin
int in2 = 7;                   // motor 1, 2nd pin
int in3 = 8;                   // motor 2, 1st pin
int in4 = 9;                   // motor 2, 2nd pin
//int motorDireito = 2;               // motor 1, PWM pin to speed control
//int motorEsquerdo = 5;              // motor 2, PWM pin to speed control
//int Velocidade1 = 180;          // MotorEsquerdo
//int Velocidade2 = 140;          // MotorDireito
int distLimite = 50;           // distancia do robo em centimetors
int tempoGiro = 50;            //tempo em milisegundos que a roda gira para virar o carrinho

int pinR = 3;   //receptor do ultrasonico
int pinE = 4;   //emissor do ultrasonico

/**
 * Os valores dos angulos
 * do servo do ultrasonico
 */
int servoDireita = 30;   //quanto mais proximo de zero mais para a direita vira
int servoEsquerda = 150;  // quanto maior mais para a esquerda vira
int servoMeio = 80;       // Angulo do meio

Ultrasonic ultrasonic(pinE, pinR);


//Executa somente quando a placa é ligada
void setup(){
  Serial.begin(9600);          // serial communication initialization, just for debug
  myservo.attach(13);          // attach servo motor to pin 13
//  pinMode(motorDireito, OUTPUT);    // motor pins definition
//  pinMode(motorEsquerdo, OUTPUT);
  pinMode(in1, OUTPUT);  // inicializa o pino 6 como saida
  pinMode(in2, OUTPUT);  // inicializa o pino 7 como saida
  pinMode(in3, OUTPUT);  // inicializa o pino 8 como saida
  pinMode(in4, OUTPUT);  // inicializa o pino 9 como saida
}

//Executa esta acao repetidamente até a placa ser desligada
void loop() { 
  andar();
}

void andar(){
//Caso a distancia lida pelo ultrasonico seja MAIOR que o limite de distancia configurado ele anda pra frente
  if(ultrasonic.read()>distLimite){
    paraFrente();
  }else{
//Caso o espaço a frente seja MENOR que o limite de distancia configurado ele para o motor, le o ambiente e decide para onde virar
    pararMotor();
    int lado = lerAmbiente();
    if(lado ==1){
      virarDireita();
    }else if(lado==2){
      virarEsquerda();
    }
  }
}

// forward
void paraFrente(){                   
  Serial.println("andando para frente");               
//  analogWrite(motorEsquerdo, Velocidade1); 
//  analogWrite(motorDireito, Velocidade2);
  //Roda direita
  digitalWrite(in1, LOW);          
  digitalWrite(in2, HIGH);
  //Roda esquerda
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void pararMotor(){
  Serial.println("Motor parado"); 
  //Roda direita
  digitalWrite(in1, LOW);            
  digitalWrite(in2, LOW);
  //Roda esquerda
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

/**
* vira o ultrasonico para os dois lados lendo qual dos dois tem mais espaço
*/
int lerAmbiente(){
  Serial.println("Lendo ambiente"); 
   int angulo = 0; 
   int direita = lerDireita();
   int esquerda = lerEsquerda();
   if(direita>=esquerda){
    angulo = 1;
   }else{
    angulo = 2;
   }
   return angulo;// 1 = direita tem mais espaço 2 = esquerda tem mais espaço
}

/**
 * metodo retorna a distancia lida pelo ultrasonico ao virar o servo para a direita
 */
int lerDireita(){
   int leitura=0;
   myservo.write(servoDireita);
   delay(500);
   leitura = ultrasonic.read();
   myservo.write(servoMeio);
   delay(500); 
   return leitura; 
}

/**
 * metodo retorna a distancia lida pelo ultrasonico ao virar o servo para a esquerda
 */
int lerEsquerda(){
   int leitura=0;
   myservo.write(servoEsquerda);
   delay(500);
   leitura = ultrasonic.read();
   myservo.write(servoMeio); 
   delay(500);
   return leitura; 
}

void virarEsquerda(){
  Serial.println("Virando esquerda");
  //Roda direita
  digitalWrite(in1, LOW);            
  digitalWrite(in2, HIGH);
  //Roda esquerda
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(tempoGiro);
}

void virarDireita(){                   
  Serial.println("Virando direita");    
  //Roda direita
  digitalWrite(in1, HIGH);            
  digitalWrite(in2, LOW);
  //Roda esquerda
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(tempoGiro);
}
