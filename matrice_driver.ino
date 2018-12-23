#include "LedControl.h" //  need the library
#include "LiquidCrystal.h"
#define V0_PIN 9
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
#define TBUT 8
#define FBUT 13
LedControl lc = LedControl(12, 11, 10, 1);
int score;
int lvl, result;
/*Clasa Number ne va retine numerele in binar si va face operatiile aferente.*/
class Number
{
  private:
    bool binary[8];
  public:
    Number();
    Number(const Number &No);
    Number operator=(const Number &No);
    bool operator==(const Number &No);
    bool* getBinary();
    void setBinary(bool b[8]);
};
Number::Number()
{
  for(int i = 0; i<8; i++)
    binary[i] = 0;
}
Number::Number(const Number &No)
{
  for(int i = 0; i<8; i++)
    binary[i] = No.binary[i];
}
Number Number::operator=(const Number &No)
{
  for(int i = 0; i<8; i++)
    binary[i] = No.binary[i];
   return (*this);
}
bool Number::operator==(const Number &No)
{
  for(int i = 0; i<8; i++)
    if(binary[i]!=No.binary[i])
      return false;
   return true;
}
bool* Number::getBinary()
{
  return binary;
}
void Number::setBinary(bool b[8])
{
  for(int i = 0; i<8; i++)
    binary[i] = b[i];
  return;
}
/*Afiseaza pe matricea de leduri numarul in baza 2*/
void displayNo(int line, int number)
{
   int  powerValue = 128;
   for(int power = 7; power>=0;power--)
  {
    if(number>=powerValue)
    {
      number -= powerValue;
      lc.setLed(0,power,line,true);
    }
    powerValue = powerValue / 2;
  }
}
/*Transforamere din baza 10 in baza 2, fara sa modificam parametrul primit, ci prin returnarea unui obiect de tip Number*/
Number makeBinary(int number)
{
  Number res;
  bool aux[8];
  for(int i = 0; i < 8; i++)
    aux[i] = 0;
  int  powerValue = 128;
   for(int power = 7; power>=0;power--)
  {
    if(number>=powerValue)
    {
      number -= powerValue;
      aux[power] = 1;
    }
    powerValue = powerValue / 2;
  }
  res.setBinary(aux);
  return res;
}
/*Urmatoarele functii afiseaza pe matricea de leduri semne corspunzatoare in functie de situatia in care ne aflam*/
void plus()
{
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);
  lc.setLed(0,4,1,true);
  lc.setLed(0,4,3,true);
}
void minus()
{
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,2,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,2,true);
}
void multiply()
{
  lc.setLed(0,3,1,true);
  lc.setLed(0,5,1,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,3,3,true);
  lc.setLed(0,5,3,true);
}
void divide()
{
  lc.setLed(0,3,1,true);
  lc.setLed(0,4,2,true);
  lc.setLed(0,5,3,true);
}
void ok()
{
  lc.clearDisplay(0);
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,3,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,5,3,true);
  lc.setLed(0,6,2,true);
  lc.setLed(0,7,1,true);
}
void notOk()
{
  lc.clearDisplay(0);
  lc.setLed(0,2,2,true);
  lc.setLed(0,3,3,true);
  lc.setLed(0,4,4,true);
  lc.setLed(0,5,5,true);
  lc.setLed(0,6,6,true);
  lc.setLed(0,3,5,true);
  lc.setLed(0,2,6,true);
  lc.setLed(0,5,3,true);
  lc.setLed(0,6,2,true);
}
Number resultBinary,goodResult;/*resultatul introdus de utilizator in binar, rezultatul in binar calculat de program dupa generarea aleatoare a doua numere*/
/*Utilizatorul introduce nivelul dorit*/
int setLevel()
{
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Select level: ");
  int level = 0;
  bool selected = false;
  int tButtonState, fButtonState;
  while(selected == false)
  {
    lcd.setCursor(1,1);
    lcd.print(level);
    fButtonState = digitalRead(FBUT);
    tButtonState = digitalRead(TBUT);
    if(fButtonState == true && tButtonState == true)
      selected = 1;
    int changeValue = 0;
    while(fButtonState == true && level>0)
    {
      fButtonState = digitalRead(FBUT);
      changeValue = -1;
    }
    while(tButtonState == true && level<10)
    {
      tButtonState = digitalRead(TBUT);
      changeValue = 1;
    }
    level += changeValue;
    unsigned long delayMillis = millis() + 100;
    while(delayMillis > millis());
  }
  lcd.print("START!");
  unsigned long currentMillis = millis();
  unsigned long delayMillis = currentMillis + 300;
  while(currentMillis < delayMillis)
    currentMillis = millis();
  return level;
}
/*Generam doua numere la intamplare si un semn intre ele, in functie de nivelul ales de utilizator*/
Number generate()
{
  randomSeed(millis());
  int firstNo, secondNo, sign = random(0,3), result;
  if(sign == 0)//PLUS
  {
    
    firstNo = random(1,lvl);
    secondNo = random(1,lvl-firstNo);
    displayNo(0, firstNo);
    plus();
    displayNo(4, secondNo);
    result = firstNo + secondNo;
  }
  else if(sign == 1)//MINUS
  {
    firstNo = random(2,lvl);
    secondNo = random(1, firstNo);
    displayNo(0,firstNo);
    minus();
    displayNo(4,secondNo);
    result = firstNo - secondNo;
  }
  else if(sign == 2)//MULTIPLY
  {
    firstNo = random(1,lvl/2);
    secondNo = random(1,lvl/firstNo);
    displayNo(0,firstNo);
    multiply();
    displayNo(4, secondNo);
    result = firstNo * secondNo;
  }
  else//DIVIDE
  {
    firstNo = random(1,lvl);
    secondNo = random(2,lvl+1);
    while(firstNo%secondNo !=0);
      secondNo--;
    displayNo(0,firstNo);
    divide();
    displayNo(4,secondNo);
    result = firstNo / secondNo;
  }
  goodResult = makeBinary(result);
  return goodResult;
}
/*Preluam numarul introdus de utilizator*/
Number getInput()
{
  int tButtonState,fButtonState;
  bool addT;
  bool aux[8] = {0,0,0,0,0,0,0,0};
  for(int j = 0; j<8;j++)
  {
    tButtonState = fButtonState = 0;
    while(tButtonState == 0 && fButtonState == 0)
    {
      tButtonState = digitalRead(TBUT);
      fButtonState = digitalRead(FBUT);
    }
    addT = false;
    if(tButtonState == 1)
    {
      unsigned long endMillis = millis() + 50;
      while(millis()<endMillis);
      if(tButtonState == 1)
        while(tButtonState==1)
        {
          tButtonState = digitalRead(TBUT);
          Serial.println(tButtonState);
          addT = true;
        }
    }
    if(addT == true)
    {
      lc.setLed(0,j,6,true);
      aux[j] = true;
    }
    int currentMillis = millis();
    int delayMillis = currentMillis + 300;
    while(currentMillis < delayMillis)
      currentMillis = millis();
  }
  resultBinary.setBinary(aux);
  return resultBinary;
}
void setup()
{
  // the zero refers to the MAX7219 number, it is zero for 1 chip
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 2); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  pinMode(TBUT, INPUT);
  pinMode(FBUT, INPUT);
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(1,0);   
  Serial.begin(9600);
  pinMode(V0_PIN, OUTPUT); 
  analogWrite(V0_PIN, 90);
  randomSeed(A0);
}
int hp, passedLevels;
bool aux[8];
/*Functia care stabileste conditiile initiale dupa incheierea fiecarui joc(cand utilizatorul nu mai are vieti)*/
void startSet()
{
  lvl = setLevel();
  hp = 3;
  for(int i = 0; i<8; i++)
    aux[i] = 0;
  goodResult.setBinary(aux);
  resultBinary.setBinary(aux);
  passedLevels = 0;
}
bool reset = 1;/*retinem cand trebuie sa resetam conditiile initiale*/
void loop()
{
    if(reset == 1)
    {
      startSet();
      reset = 0;
    }
    if(hp>0)
    {
      int generateTime = 0, inputTime = 0;
      lcd.clear();
      lcd.print("Health Points: ");
      lcd.print(hp);
      lcd.setCursor(1,2);
      lcd.print("Score: ");
      score = lvl* passedLevels+(int)(generateTime-inputTime)/1000;
      lcd.print(lvl* passedLevels+(int)(generateTime-inputTime)/1000);
      goodResult = generate();
      generateTime = millis();
      resultBinary = getInput();
      inputTime = millis();
      if(resultBinary == goodResult)
      {
        ok();
        passedLevels++;
      }
       else
       {
        notOk();
        hp--;
       }
      unsigned long currentMillis = millis();
      unsigned long delayMillis = currentMillis + 1000;
      while(currentMillis < delayMillis)
        currentMillis = millis();
      lc.clearDisplay(0);
      lcd.clear();
      lcd.print("Try again!");
    } 
    else if(hp == 0)
    {
      lcd.setCursor(1,1);
      lcd.print("Your score: ");
      lcd.print(score);
      while(digitalRead(TBUT) == 0 && digitalRead(FBUT) ==0);
      reset = 1;
    }
    lc.clearDisplay(0);
}
