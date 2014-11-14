#ifndef Robo_h
#define Robo_h

#include <Servo.h>

#define MOTOR_LEFT_PIN      6
#define MOTOR_RIGHT_PIN     5
#define ULTRASSONIC_PIN     4
#define ARM_HAND_PIN        11
#define ARM_PULSE_PIN       9
#define ARM_HEIGHT_PIN      3
#define ARM_ROT_PIN         10
#define LINE_FINDER_PIN     13

class Manipulador
{
public:
    void inicializa();
    void setAbertura(int value);
    void setRotPulso(int value);
    void setAltura(int value);
    void setRotacao(int value);
private:
    Servo mao;
    Servo pulso;
    Servo altura;
    Servo rotacao;
};

class Motor
{
public:
  void inicializa();
  void stop();
  void walk(int left, int right);
private:
  Servo motorLeft;
  Servo motorRight;
};

class Ultrassonic
{
public:
  int read();
};

class Linefinder
{
public:
  int read();
};

class Autonomy
{
public:
  void lineFollow();
  void lineCatch();
  void avoidObstacle();
};

class Robo
{
public:
  Motor motor;
  Ultrassonic ultrassonic;
  Linefinder linefinder;
  Manipulador manipulador;
  Autonomy autonomy;
  void inicializa();
};

#endif
