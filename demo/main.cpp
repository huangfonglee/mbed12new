#include "mbed.h"

#define CENTER_BASE 1500

BufferedSerial pc(USBTX, USBRX);
DigitalIn encoder(D10);
PwmOut servo(D11);

Timer t;
Ticker encoder_ticker;
Thread t2;

volatile int steps;
volatile int last;

void servo_control(int speed) {
   if (speed > 200)       speed = 200;
   else if (speed < -200) speed = -200;

   servo=(CENTER_BASE + speed)/20000.0f;
}

void encoder_control() {
   int value = encoder;
   if(!last && value) steps++;
   last = value;
}

void rota(){
   while(1) {
      servo_control(-23.234);
      //wait_us(5);
      ThisThread::sleep_for(5000ms);
      servo_control(41.545);
      ThisThread::sleep_for(5000ms);
      //wait_us(5);
   }
}


int main() {

   pc.set_baud(9600);

   encoder_ticker.attach(&encoder_control, .01);

   servo.period_ms(20);
   
   t2.start(rota);

   while(1) {

   //TODO: revise this value according to your result


   steps = 0;
   t.reset();
   t.start();

   ThisThread::sleep_for(2000ms);
   //wait_us(3);

   float time = t.read();

   printf("%1.3f\r\n", (float) steps * 6.5 * 3.14 / 32 / time);

   }
}