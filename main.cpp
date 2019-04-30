#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

const int USERS = 2;
String user;
int id;

const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char customKey;
int cont[USERS] = {3, 3}; //Contador de intentos de los usuarios

const byte ROWS = 4;
const byte COLS = 4;

const int contras[USERS] = { 1234, 4321};

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {A0, A1, 13, 12};
byte colPins[COLS] = {11, 10, 9, 8};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

int introducePass();

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("User: ");
  lcd.setCursor(0,1);
  lcd.print("Pass: ");
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("User: ");
  lcd.setCursor(0,1);
  lcd.print("Pass: ");
  lcd.setCursor(6, 0);
  customKey = customKeypad.getKey(); // Identificador del usuario.
  id = int(customKey) - 48;
   if (customKey){


       if(customKey == '1' ){
         user = "Simon";
    //     Serial.print("Bienvenido " + user);
    //     Serial.print(id);
       } else if(customKey == '2'){
         user = "Alberto";

       } else{
         user = "No recon.";
       }


  lcd.print(user);

int bo = introducePass();
lcd.clear();
lcd.setCursor(0, 0);
if(bo == 1){
  lcd.print("BIENVENIDO! :D");
  delay(1000);
  cont[id-1] = 3;
} else{
  cont[id-1] = cont[id-1]-1;
  lcd.print("INCORRECTO! >:(");
  lcd.setCursor(0, 1);
  int c = cont[id-1];
  lcd.print("Int. rest: ");
  lcd.setCursor(11, 1);
  lcd.print(c);
  delay(1000);
}

//     Serial.println(customKey);
}
   delay(200);
}

int introducePass(){
  int res;
//  int i = 0; // posicion del digito en el array pass
  int k = 6; // posicion del lcd donde se imprime el digito
  int pass = 0;

  while(pass<999){
    char ck = customKeypad.getKey();
    if(ck){
      int j = int(ck) - 48;
      Serial.print(j);
      pass = pass * 10 + j;
      lcd.setCursor(k, 1);
      k++;
      lcd.print("*");
      delay(500);
    }
  }
  if(pass == contras[id-1]){
    res = 1;
  } else{
    res = 0;
  }
//  Serial.println(pass);
//  Serial.println(id);
  return res;
}
