#include "ritos.h" //RITOS: Real Internet Time Operation Sansystem

volatile int a = 1000, b = 3000;
int statemachine=0;

Ritos tarefa1;
void thread1() {
  a--; 
  
  if ( a <= 0 && statemachine==0) {
   Serial.println("Interrupt thread 1!");
   
   a=1500; //1500ms
   statemachine=1;
  }

  if ( a <= 0 && statemachine==1) {   
   Serial.println("thread 1 again!");
   
   a=2000; 
   statemachine=2;
  }

   if ( a <= 0 && statemachine==2) {   
   Serial.println("thread 1 again again!");
   
   a=1700; 
   statemachine=0;
  }
}


Ritos tarefa2;
void thread2() {
  b--; 
  if ( b <= 0 ) {
   
  Serial.println("Interrupcao thread 2!");
  b=4300; 
  }
}

void setup() {
  Serial.begin(115200);

  // Criar threads concorrentes
  tarefa1.task(thread1);  
  tarefa2.task(thread2);

}

void loop() {}
