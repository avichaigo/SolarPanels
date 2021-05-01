#include <EEPROM.h>
#include <Servo.h>

Servo myservo;

int sensor1 = A1;
int sensor2 = A0;
int calswitch = 2;

int val1;
int val2;

int pos = 0;
int error;
int state;

void setup()
{
    pinMode(sensor1, INPUT);
    pinMode(sensor2, INPUT);
    pinMode(calswitch, INPUT);

    myservo.attach(10);
    myservo.attach(9);
}

void loop()
{
    // Button that reset servos
    if (digitalRead(calswitch) == 0){
        myservo.detach();
        delay(1000);
        myservo.attach(10);
        myservo.attach(9);
    }else{
        val1 = analogRead(sensor1);
        val2 = analogRead(sensor2);

        state = EEPROM.read(1);
        error = EEPROM.read(0);

        if (state == 0){
            val1 = val1 - error;
        }
        else{
            val2 = val2 - error;
        }
        if (val1 - val2 > 4){
            myservo.write(pos--);
            delay(10);
        }
        else if (val2 - val1 > 4){
            myservo.write(pos++);
            delay(10);
        }
        else{
            myservo.write(pos);
        }
        if (pos > 90){
            pos = 90;
        }
        else if (pos < 0){
            pos = 0;
        }
    }
}
