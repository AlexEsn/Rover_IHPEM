/*============= НАСТРОЙКИ =============*/
#define JOY_MAX 40 // рабочий ход джойстика (из приложения)
#define minDuty 10 // скорость, при которой мотор должен начинать крутится (обычно 25-50)
#define BRIGHTNESS 200
/*=============== ПИНЫ ===============*/

#define MOT_L1 3
#define MOT_L2 5
#define MOT_R1 10
#define MOT_R2 9
#define BT_TX 2
#define BT_RX 12
#define SPEAKER 13  // пин пищалки
#define STRIP_PIN 4 // пин ленты
#define NUMLEDS 6   // кол-во светодиодов

#include <SoftwareSerial.h>
SoftwareSerial BTserial(BT_TX, BT_RX); // TX, RX

#define COLOR_DEBTH 3
#include <microLED.h>
microLED<NUMLEDS, STRIP_PIN, MLED_NO_CLOCK, LED_WS2818, ORDER_GRB, CLI_AVER> strip;

boolean doneParsing, startParsing;
short dataX, dataY, motor_max = 255;
long long timer;
String string_convert;

void setup()
{

  Serial.begin(9600);
  BTserial.begin(9600);
  pinMode(MOT_L1, OUTPUT);
  pinMode(MOT_L2, OUTPUT);
  pinMode(MOT_R1, OUTPUT);
  pinMode(MOT_R2, OUTPUT);

  // Start with drivers off, motors coasting.
  digitalWrite(MOT_L1, LOW);
  digitalWrite(MOT_L2, LOW);
  digitalWrite(MOT_R1, LOW);
  digitalWrite(MOT_R2, LOW);

  strip.setBrightness(BRIGHTNESS);
  pinMode(SPEAKER, OUTPUT);
  randomSeed(analogRead(0));
}

void loop()
{
  parsing(); // функция парсинга
  if (doneParsing && dataX > JOY_MAX)
  {

    Serial.println(dataX);
    motor_max = dataX;
  }
  else if (doneParsing)
  {

    timer = millis();
    doneParsing = false;

    int joystickX = map((dataX), -JOY_MAX, JOY_MAX, -motor_max / 2, motor_max / 2); // сигнал по Х
    int joystickY = map((dataY), -JOY_MAX, JOY_MAX, -motor_max, motor_max);         // сигнал по Y

    int dutyR = joystickY - joystickX; // считаем сигнал для правого мотора
    int dutyL = joystickY + joystickX; // считаем сигнал для левого мотора

    dutyR = constrain(dutyR, -motor_max, motor_max); // ограничиваем значение для dutyR, на случай если dutyR > 255
    dutyL = constrain(dutyL, -motor_max, motor_max); // ограничиваем значение для dutyL, на случай если dutyL > 255

    rightMotor(dutyR);
    leftMotor(dutyL);
  }
  if (millis() - timer > 5000)
  {
    music();
    timer = millis();
  }
}

void music()
{

  int K = 2000;
  switch (random(1, 7))
  {

    case 1:
      phrase1();
      break;
    case 2:
      phrase2();
      break;
    case 3:
      phrase1();
      phrase2();
      break;
    case 4:
      phrase1();
      phrase2();
      phrase1();
      break;
    case 5:
      phrase1();
      phrase2();
      phrase1();
      phrase2();
      phrase1();
      break;
    case 6:
      phrase2();
      phrase1();
      phrase2();
      break;
  }

  for (int i = 0; i <= random(3, 9); i++)
  {

    printLed();
    tone(SPEAKER, K + random(-1700, 2000));
    delay(random(70, 170));
    strip.clear();
    noTone(SPEAKER);
    delay(random(0, 30));
  }

  noTone(SPEAKER);
}

void parsing()
{
  if (BTserial.available() > 0)
  { // если в буфере есть данные
    char incomingChar = BTserial.read(); // читаем из буфера
    if (startParsing)
    { // начать принятие пакетов
      if (incomingChar == ' ')
      { // принят пакет dataX
        dataX = string_convert.toInt(); // ковертируем принятый пакет в переменную
        string_convert = "";            // очищаем переменную пакета
      }
      else if (incomingChar == ';')
      { // принят пакет dataY
        dataY = string_convert.toInt(); // ковертируем принятый пакет в переменную
        string_convert = "";            // очищаем переменную пакета
        startParsing = false;           // закончить принятие пакетов
        doneParsing = true;             // парсинг окончен, можно переходить к движению
      }
      else
      {
        string_convert += incomingChar; // записываем принятые данные в переменную
      }
    }
    if (incomingChar == '$')
    { // начало парсинга
      startParsing = true; // начать принятие пакетов
    }
  }
}

void printLed()
{
  int num = random(0, 1530);
  switch (random(1, 4))
  {
    case 1:
      strip.set(0, mWheel(num));
      strip.set(5, mWheel(num));
      break;
    case 2:
      strip.set(1, mWheel(num));
      strip.set(4, mWheel(num));
      break;
    case 3:
      strip.set(2, mWheel(num));
      strip.set(3, mWheel(num));
      break;
  }
  strip.show();
}

void rightMotor(size_t _speed)
{
  set_motor_pwm(_speed, MOT_R1, MOT_R2);
}

void leftMotor(size_t _speed)
{
  set_motor_pwm(_speed, MOT_L1, MOT_L2);
}

void set_motor_pwm(int pwm, int IN1_PIN, int IN2_PIN)
{
  if (pwm < 0)
  {
    analogWrite(IN1_PIN, -pwm);
    digitalWrite(IN2_PIN, LOW);
  }
  else
  { // stop or forward
    digitalWrite(IN1_PIN, LOW);
    analogWrite(IN2_PIN, pwm);
  }
}

void phrase1()
{

  int k = random(1000, 2000);
  printLed();
  for (int i = 0; i <= random(100, 2000); i++)
  {

    tone(SPEAKER, k + (-i * 2));
    delay(random(.9, 2));
  }
  strip.clear();
  for (int i = 0; i <= random(100, 1000); i++)
  {

    tone(SPEAKER, k + (i * 10));
    delay(random(.9, 2));
  }
}

void phrase2()
{

  int k = random(1000, 2000);
  printLed();
  for (int i = 0; i <= random(100, 2000); i++)
  {

    tone(SPEAKER, k + (i * 2));
    delay(random(.9, 2));
  }
  strip.clear();
  for (int i = 0; i <= random(100, 1000); i++)
  {

    tone(SPEAKER, k + (-i * 10));
    delay(random(.9, 2));
  }
}
