#include "Robo.h"
#include <Arduino.h>

Robo *_this;

void Manipulador::inicializa(){
    mao.attach(ARM_HAND_PIN);
    pulso.attach(ARM_PULSE_PIN);
    altura.attach(ARM_HEIGHT_PIN);
   // rotacao.attach(ARM_ROT_PIN);
}

void Manipulador::setAbertura(int value){
    mao.write(value);
}

void Manipulador::setRotPulso(int value){
    pulso.write(value);
}

void Manipulador::setAltura(int value){
    altura.write(value);
}

void Manipulador::setRotacao(int value){
    rotacao.write(value);
}

void Motor::inicializa()
{
    motorLeft.attach(MOTOR_LEFT_PIN);
    motorRight.attach(MOTOR_RIGHT_PIN);
}

void Motor::stop(){
    motorLeft.write(59);
    motorRight.write(73);
}

void Motor::walk(int left, int right){
        motorLeft.write(left);
        motorRight.write(right);
}

int Ultrassonic::read(){
    pinMode(ULTRASSONIC_PIN, OUTPUT);
	digitalWrite(ULTRASSONIC_PIN, LOW);
	delayMicroseconds(2);
	digitalWrite(ULTRASSONIC_PIN, HIGH);
	delayMicroseconds(5);
	digitalWrite(ULTRASSONIC_PIN,LOW);
	pinMode(ULTRASSONIC_PIN,INPUT);
	long duration = pulseIn(ULTRASSONIC_PIN,HIGH);
	return duration/29/2;
}

int Linefinder::read(){
    int a =  digitalRead(LINE_FINDER_PIN);
    return a;
}

void Robo::inicializa()
{
    motor.inicializa();
    manipulador.inicializa();
    _this = this;
}

void Autonomy::lineFollow(){
    if(_this->linefinder.read() == 1){
        _this->motor.walk(70,68);
    } else {
        _this->motor.walk(65,50);
    }
}

void Autonomy::lineCatch(){
    if(_this->ultrassonic.read() > 10){
        _this->autonomy.lineFollow();
        _this->manipulador.setAbertura(180);
        _this->manipulador.setAltura(150);
        _this->manipulador.setRotacao(0);
    } else {
        _this->motor.stop();
        _this->manipulador.setRotacao(95);
        delay(1500);
        _this->manipulador.setAbertura(20);
        _this->manipulador.setAltura(100);
        delay(500);
        _this->manipulador.setAltura(70);
        delay(500);
        _this->manipulador.setAbertura(75);
        delay(1000);
        _this->manipulador.setAltura(150);
        _this->manipulador.setRotacao(0);
        delay(1500);
        _this->manipulador.setAltura(70);
        _this->manipulador.setAbertura(20);
        delay(1500);
    }
}

void Autonomy::avoidObstacle(){
    if(_this->ultrassonic.read() > 15){
        _this->motor.walk(100,100);
    } else {
        _this->motor.walk(100,50);
        delay(100);
    }
}
