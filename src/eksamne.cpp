/*
Laurits Randers imprative programmings projekt

projektet er en variation af projekt forslag 2 – måling af reaktionstid

Der er implementeret et menu system, hvor man kan måle reaktionstid på en spiller eller 5 spillere. Scoren kan herefter printes ud og evt resettes til næste gang.
*/

#include <Arduino.h>

const int numbersOfPlayer = 3;
const int numbersOfTest = 3;

struct player{
  char name[10];
  int reactionTimes[numbersOfTest];
  int averageReactionTimes;
};


struct player playerArray[numbersOfPlayer];


const int butUp = 3;
const int butDown = 4;

int menuID = 1;
int lastMenuID = 0;

void waitRandomTime(){
  // Wait random time btween 500 and 2000 ms
  delay(random(500, 2000));
}

void waitUntilKeyPressed(){
  // Wait until Key 2 is pressed
  while(digitalRead(2)){}
}

int measuresReactionTime(){
  // Measure reaction time and retunes it
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
  // Prints reaction time to serial port

  Serial.print("your reaction time is ");
  Serial.print(reactionTime);
  Serial.println(" milliseconds");
}

void singleplayer(){
  // Measures reaction time and prints it out for single player
  // Waits 1000 ms before returning

  int reactionTime = measuresReactionTime();
  printReactionTime(reactionTime);
  delay(1000);
}

void definePlayerArray(player playerArray[]) {
  // Fill in names in playerArray

  for(int i = 0; i < numbersOfPlayer; i++){
    sprintf(playerArray[i].name, "player %d", i);
  }
}

void printPlayers(player playerArray[]) {
  // Prints player name and average reaction time on serial port
  for(int i = 0; i < numbersOfPlayer; i++){
    Serial.print(playerArray[i].name);
    Serial.print(" average reaction times is ");
    Serial.println(playerArray[i].averageReactionTimes);
  }
}

void ReactionTimeMultipleTimes(struct player *player){
  // Measure reaction time 5 times
  for(int i = 0; i < numbersOfTest; i++){
    Serial.print("Test ");
    Serial.println(i + 1);
    player->reactionTimes[i] = measuresReactionTime();
  }
}

void calculateaverage(player playerArray[]){
  // Calculate average reaction time for all players
  for(int i = 0; i < numbersOfPlayer; i++){
    int sum = 0;
    for(int j = 0; j < numbersOfTest; j++){
      sum += playerArray[i].reactionTimes[j];
    }
    playerArray[i].averageReactionTimes = sum/numbersOfTest;
  }
}

void multiplayer() {
  // Measure reaction time for the players
  Serial.println();
  Serial.println("you have selected multiplayer");
  definePlayerArray(playerArray);
  for(int i = 0; i < numbersOfPlayer; i++){
    delay(500);
    Serial.print("it is ");
    Serial.print(playerArray[i].name);
    Serial.println(" turn.");
    Serial.println("Press go to start");
    waitUntilKeyPressed();
    ReactionTimeMultipleTimes(&playerArray[i]);
  }
  Serial.println("All the test are done");
  calculateaverage(playerArray);
  delay(500);
}

void scores(){
  // Prints out reaction time for all players
  if(playerArray[0].averageReactionTimes == 0){
    Serial.println("no scores to show");
    return;
  }
  printPlayers(playerArray);
}

void reset() {
  // Empties PlayerArray filling it with Null
  memset(playerArray, 0, sizeof(playerArray));
  Serial.println("The scores have been reset");
}

void printMenu(int menuID){
  // Prints out menu items once
  // When key is pressed the function is called
  switch(menuID){
    case 1: // Single player
      if(menuID != lastMenuID){
        Serial.println(">Single player");
      }
      if(!digitalRead(2)){
        singleplayer();
      }
      break;

    case 2: // Multiplayer
      if(menuID != lastMenuID){
        Serial.println(">Multiplayer");
      }
      if(!digitalRead(2)){
        multiplayer();
      }
      break;

    case 3: // Scores
      if(menuID != lastMenuID){
        Serial.println(">Scores");
      }
      if(!digitalRead(2)){
        scores();
      }
      break;

    case 4: // Reset scores
      if(menuID != lastMenuID){
        Serial.println(">Reset scores");
        }
      if(!digitalRead(2)){
        reset();
      }
      break;
  }
  lastMenuID = menuID;
}

void menu(){
  // If Down button is pressed the menu ID is decreased and wrapped to 4 when decreased to 1
  // If Up button is pressed the menu ID is increased and wrapped to 4 when increased to 5
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

  printMenu(menuID);
  delay(250);
}


void setup() {
  // Defines pinModes of the IO and initialises serial communication
  pinMode(2, INPUT_PULLUP);
  pinMode(butUp, INPUT_PULLUP);
  pinMode(butDown, INPUT_PULLUP);

  pinMode(13, OUTPUT);

  Serial.begin(9600);
  Serial.println("welcome");

}

void loop() {
  // calls menu function
  menu();
}
