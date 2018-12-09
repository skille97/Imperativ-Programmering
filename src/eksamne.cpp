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
int lastMenuID = 0;

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
    Serial.print(playerArray[i].name);
    Serial.print(" average reaction times is ");
    Serial.println(playerArray[i].averageReactionTimes);
  }
}

void ReactionTimeMultipleTimes(struct player *player){
  for(int i = 0; i != 5; i++){
    Serial.print("Test ");
    Serial.println(i + 1);
    player->reactionTimes[i] = measuresReactionTime();
  }
}

void calculateaverage(player playerArray[]){
  for(int i = 0; i != numbersOfPlayer; i++){
    int sum = 0;
    for(int j = 0; j != 5; j++){
      sum += playerArray[i].reactionTimes[j];
    }
    playerArray[i].averageReactionTimes = sum/5;
  }
}

void multiplayer() {
  Serial.println();
  Serial.println("you have selected multiplayer");
  definePlayerArray(playerArray);
  for(int i = 0; i != 5; i++){
    delay(500);
    Serial.print("it is ");
    Serial.print(playerArray[i].name);
    Serial.println(" turn.");
    Serial.println("Press go to start");
    waitUntilKeyPressed();
    ReactionTimeMultipleTimes(&playerArray[i]);
  }
  Serial.println("all the Test are done");
  calculateaverage(playerArray);
  delay(500);
}

void scores(){
  printPlayers(playerArray);
}

void reset() {
  memset(playerArray, 0, sizeof(playerArray));
}

void printMenu(int menuID){

  switch(menuID){
    case 1:
      if(menuID != lastMenuID){
        Serial.println(">Single player");
      }
      if(!digitalRead(2)){
        singleplayer();
      }
      break;

    case 2:
      if(menuID != lastMenuID){
        Serial.println(">Multiplayer");
      }
      if(!digitalRead(2)){
        multiplayer();
      }
      break;

    case 3:
      if(menuID != lastMenuID){
        Serial.println(">Scores");
      }
      if(!digitalRead(2)){
        scores();
      }
      break;

    case 4:
      if(menuID != lastMenuID){
        Serial.println(">reset Scores");
        }
      if(!digitalRead(2)){
        reset();
      }
      break;
  }
  lastMenuID = menuID;
}

void menu(){
  if(!digitalRead(butDown)){
    if(menuID <= 1){
      menuID = 4;
    }
    else {
      menuID--;
    }
  }
  if(!digitalRead(butUp)){
    if(menuID >= 4){
      menuID = 1;
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
  Serial.println("welcome");

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
