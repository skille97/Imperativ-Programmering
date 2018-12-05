#include <Arduino.h>

struct player{
  char name[10];
  int reactionTimes[5];
  int averageReactionTimes;
};

const int numbersOfPlayer = 5;
struct player playerArray[numbersOfPlayer];


const int butUp = 3;
const int butDown = 4;

int menuID = 1;
int lastMenuID;

void waitRandomTime(){
  delay(random(500, 2000));
}
void waitUntilKeyPressed(){
  while(digitalRead(2)){}
}

int measuresReactionTime(){
  unsigned long startTime = 0;
  unsigned long stopTime = 0;
  digitalWrite(LED_BUILTIN, LOW);
  waitRandomTime();
  digitalWrite(LED_BUILTIN, HIGH);
  startTime = millis();
  waitUntilKeyPressed();
  stopTime = millis();
  Serial.println(stopTime - startTime);
  return stopTime - startTime;
}

void printReactionTime(int reactionTime){
  Serial.print("your reaction time is ");
  Serial.print(reactionTime);
  Serial.println(" milliseconds");
}

void singleplayer(){
  int reactionTime = measuresReactionTime();
  printReactionTime(reactionTime);
  delay(500);
}

void definePlayerArray(player playerArray[]) {
  for(int i = 0; i != numbersOfPlayer; i++){
    sprintf(playerArray[i].name, "player %d", i);
  }
}

void printPlayers(player playerArray[]) {
  for(int i = 0; i != numbersOfPlayer; i++){
    Serial.println(playerArray[i].name);
  }
}

void ReactionTimeMultiplayer(struct player *player){
  for(int i = 0; i != 5; i++){
    player->reactionTimes[i] = measuresReactionTime();
  }
}

void Multiplayer() {
  definePlayerArray(playerArray);
  ReactionTimeMultiplayer(&playerArray[0]);
  printPlayers(playerArray);
}

void printMenu(int menuID){

  switch(menuID){
    case 1:
      if(menuID != lastMenuID){
        Serial.println("Single player");
      }
      if(!digitalRead(2)){
        singleplayer();
      }
      break;
    case 2:
      if(menuID != lastMenuID){
        Serial.println("Multiplayer");
      }
      if(!digitalRead(2)){
        Multiplayer();
      }
      break;
    case 3:
      if(menuID != lastMenuID){
        Serial.println("Scores");
      }
      if(!digitalRead(2)){
      }
      break;
  }
  lastMenuID = menuID;
}

void menu(){
  if(!digitalRead(butDown)){
    if(menuID <= 1){
      menuID = 1;
    }
    else {
      menuID--;
    }
  }
  if(!digitalRead(butUp)){
    if(menuID >= 3){
      menuID = 3;
    }
    else{
      menuID++;
    }
  }
  //Serial.println(menuID);
  printMenu(menuID);
  delay(250);
}


void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(butUp, INPUT_PULLUP);
  pinMode(butDown, INPUT_PULLUP);

  pinMode(13, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  menu();
}




void turnOnLED();
void registerStartTime();
void waitUntilKeyPressed();
void registerStopTime();
void calcReactionTime();
void presentResult();
