#include <Tone.h>

byte columns[] = {34, 36, 38, 40, 42, 44, 46, 48};
byte rows[] = {22, 24, 26, 28, 30, 32};
byte tonePins[] = {9, 2, 6}; //pwm pins for tone output
//it seems that 4th tone is just not working.
// polyphone of 3 is good enouhg!

Tone tone1;
Tone tone2;
Tone tone3;
//Tone tone4;

//Tone *tones[4] = {&tone1, &tone2, &tone3, &tone4};
Tone *tones[3] = {&tone1, &tone2, &tone3};

struct Playing {
  int key_id;
  bool enabled;
};

Playing T1;
Playing T2;
Playing T3;
//Playing T4;

//Playing *sound[4] = {&T1, &T2, &T3, &T4};
Playing *sound[3] = {&T1, &T2, &T3};

int freqChart[] = {
0,0,0,0,437, 463, 
490, 519, 550, 583, 617, 654, 
693, 734, 778, 824, 873, 925, 
980, 1038, 1100, 1165, 1235, 1308, 
1390, 1468, 1556, 1648, 1746, 1850, 
1960, 2077, 2200, 2331, 2469, 2616, 
2772, 2937, 3111, 3296, 3492, 3700, 
3920, 4153, 4400, 4662, 4939, 5233
 }; //freq in Hz * 10

 /* 
 -, -, -, -, F, F#,
 G, G#, A, A#, H, C, 
 C#, D, D#, E, F, F#,
 + 5 additional rows
 ....
 */



/*
Note to self 4.7.2023: this grid probably now works, there are potential hw issues with the keyboard that needs further investigation...

pins (as 5.7.2023) - connected 1:1 linearly from keyboard pcb to arduino

base logic
rows -> input_pullup (22, 24, 26, 28, 30, 32)
columns -> output, high (34, 36, 38, 40, 42, 44, 46, 48)
and when reading, set output to low
...-> if key is pressed, row inputs drop to low
no keypress -> row reads high


      22    24    26    28    30    32
34 -  ?   , G0  , C#1 , G1  , C#2 , G2
36 -  C#3 , G3  , D1  , G#1 , D2  , G#2
38 -  D3  , G#3 , D#1 , A1  , D#2 , A2
40 -  D#3 , A3  , E1  , A#1 , E2  , A#2
42 -  E3  , A#3 , F1  , H1  , F2  , H2
44 -  F3  , H3  , F#1 , C2  , F#2 , C3
46 -  F#3 , C4  , ?   , ?   , ?   , ?     this is probably the one column with only 2 diodes?!?
48 -  ?   , ?   , ?   , ?   , ?   , ?

missing: F0, F#0, G#0, A0, A#0, H0, C1 - all from the beginning!
blanks: 11 pcs

this would translate to row 8 ?!?!?
Or then not, but that might be a start...

update: software bug, got rows & columns messed up...

    22    24    26    28    30    32
34                          F0    F#0
36  G0    G#0   A0    A#0   H0    C1 
38  C#1   D1    D#1   E1    F1    F#1
40  G1    G#1   A1    A#1   H1    C2
42  C#2   D2    D#2   E2    F2    F#2   
44  G2    G#2   A2    A#2   H2    C3
46  C#3   D3    D#3   E3    F3    F#3 
48  G3    G#3   A3    A#3   H3    C

8.7.2023 tested, all working!

*/

const int rowCount = sizeof(rows) / sizeof(rows[0]);
const int colCount = sizeof(columns) / sizeof(columns[0]);

const int toneCount = sizeof(tonePins) / sizeof(tonePins[0]);

byte keyMap[colCount][rowCount] = {0};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  //for (int i = 0; i < sizeof(tonePins) / sizeof(tonepins[0])) {

  //}
  for (int i = 0; i < toneCount; i++) {
    Serial.print("Enabling tone ");
    tones[i]->begin(tonePins[i]);
    Serial.print(i+1);
    Serial.print(" at pin ");
    Serial.println(tonePins[i]);
  }
  //tone1.begin(tonePins[0]);
  //tone2.begin(tonePins[1]);
  //tone3.begin(tonePins[2]);
  //tone4.begin(tonePins[3]);

  for (int i = 0; i < rowCount; i++) {
    Serial.print(rows[i]);
    Serial.println(" as input_pullup");
    pinMode(rows[i], INPUT_PULLUP);
  }

  for (int i = 0; i < colCount; i++) {
    Serial.print(columns[i]);
    Serial.println(" as output_high");
    pinMode(columns[i], OUTPUT);
    digitalWrite(columns[i], HIGH);
  }

 //   Serial.println("Column - Row1, Row2, Row3,... ");

}

void PrintMatrix() {
  Serial.println("--------------------------");

  for (int i = 0; i < colCount; i++) {
    
    Serial.print(i+1);
    Serial.print(" -  ");
    for (int j = 0; j < rowCount; j++) {
      Serial.print(keyMap[i][j]);
      if (j < rowCount -1) {
        Serial.print(",");
      }
      
    }
    Serial.println("");

    
  }
  delay(1000);
}

int GetFirstFreeTone() {
  for (int i = 0; i < toneCount; i++) {
    if (!(sound[i]->enabled)) {
      return i;
    }
  }
  return -1;
}

int IsTonePlaying(int keyValue) {
  for (int i = 0; i < toneCount; i++) {
    if (sound[i]->key_id == keyValue) {
      return i;
    }
  }
  return -1;
}

void CheckReleasedKeys(){
  for (int i = 0; i < toneCount; i++) {
    if (sound[i]->enabled) {
      int secondArray = sound[i]->key_id % 6;
      int firstArray = (sound[i]->key_id - secondArray) / 6;
      if (keyMap[firstArray][secondArray] == 1) {
        Serial.print("Sound ");
        Serial.print(i+1);
        Serial.println(" released");
        tones[i]->stop();
        sound[i]->enabled = false;
      }
    }
  }
}

bool IsKeyPressed(int key_code) {
  for (int i = 0; i < toneCount; i ++) {
    if (sound[i]->enabled) {
      if (sound[i]->key_id == key_code) {
        return true;
      }
    }
  }
  return false;
}

int GetFreeTones() {
  int freeTones = 0;
  for (int i = 0; i < toneCount; i++) {
    if (!(sound[i]->enabled)) {
      freeTones++;
    }
  }
  return freeTones;
}

void ProcessTones() {
  int tonesFree = GetFreeTones;
  while (tonesFree > 0) { //proceed until all tones are populated
    for (int i = 0; i < colCount; i++) {
      for (int j = 0; j < rowCount; j++) {
        if (keyMap[i][j] == 0) {
          int keyValue = i * 6 + j;
          if (!(IsKeyPressed(keyValue))) {
            int firstIndex = GetFirstFreeTone();
            if (firstIndex > -1 ) { //new stuff only when there are free tones available
              PlayTone(firstIndex, keyValue);
              tonesFree--;
            }
          }
        }
      }
    }
    tonesFree = 0; //in case there are remaining tones free we need to break this while loop...
  }
}


void PlayTone(int soundNumber, int keyValue) {
  Serial.print("Playing key :");
  Serial.print(keyValue);
  Serial.print(" with tone :");
  Serial.println(soundNumber+1);
  sound[soundNumber]->enabled = true;
  sound[soundNumber]->key_id = keyValue;
  int toneFreq = freqChart[keyValue];
  toneFreq = toneFreq / 10;
  tones[soundNumber]->play(toneFreq);
}

void PlayMatrix() {
  //unsigned int timeStamp = millis(); //timestamp for delay calculation
  //int toneLength = 100; //tone length
  int currentPinNumber = 0; //output pin order number
  for (int i = 0; i < colCount; i++) {
    for (int j = 0; j < rowCount; j++) {
      //Serial.print("-");
      if (keyMap[i][j] == 0) {
        int keyValue = i * 6 + j;
        int toneFreq = freqChart[keyValue];
        
        toneFreq = toneFreq/10; //stored as *10, now it is taken back
        tones[currentPinNumber]->play(toneFreq);
        Serial.print("Playing tone with output");
        Serial.print(currentPinNumber+1);
        //todo: rewrite this tone -stuff to try to be something else and not only square wave?!?
        //tone(tonePins[currentPinNumber], toneFreq, toneLength);

        currentPinNumber++;
        if (currentPinNumber >= toneCount) { //this was the last pin, start from beginning
          currentPinNumber = 0;
        }

        
        
      }   
      Serial.println();
    }
    
    
  }

  for (int i = 0; i < 4; i++) {
    tones[i]->stop();
  }
  //int delayValue = toneLength - (millis() - timeStamp); //compensate delay based on how long executing this one lasts..
  //delay(delayValue);
}


void ReadMatrix() {
  for (int i = 0; i < colCount; i++) {
    digitalWrite(columns[i], LOW);
    //delay(50);
    for (int j = 0; j < rowCount; j++) {
      
      keyMap[i][j] = digitalRead(rows[j]);
    }
    digitalWrite(columns[i], HIGH);
  }
}

void loop() {
  ReadMatrix();
  CheckReleasedKeys();
  ProcessTones();
  //PlayMatrix(); //this gave pretty wild sound effects...
  //PrintMatrix();

}
