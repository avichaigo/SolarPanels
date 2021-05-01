#include <EEPROM.h>
#include <Servo.h>
#define PRESSED 0

Servo servo_9;
Servo servo_10;

int sensor0 = 0;
int sensor1 = 0;
int kill_button = 2;

int pos_9 = 0;
int pos_10 = 0;

void setup()
{
    pinMode(sensor0, INPUT);
    pinMode(sensor1, INPUT);
    pinMode(kill_button, INPUT);

    servo_9.attach(9);
    servo_10.attach(10);
}

void fix_pos(int *pos){
    if(*pos > 90){
        *pos = 90;
    }else if(*pos < 0){
        *pos = 0;
    }
}

void loop()
{
    // Button that reset servos
    if (digitalRead(kill_button) == PRESSED){
        servo_9.detach();
        servo_10.detach();
        delay(1000);
        servo_9.attach(9);
        servo_10.attach(10);
    }else{
        sensor0 = analogRead(A0);
        sensor1 = analogRead(A1);
        
        if (sensor0 > sensor1){
            servo_9.write(pos_9--);
            servo_10.write(pos_10++);
            delay(10);
        }
        else if (sensor0 < sensor1){
            servo_9.write(pos_9++);
            servo_10.write(pos_10--);
            delay(10);
        }
        fix_pos(&pos_9);
        fix_pos(&pos_10);
    }
}
