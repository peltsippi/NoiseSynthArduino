//#include "../include/ReadMatrix.h"
//#include "Arduino.h"
//#include "/home/timo/.arduino15/packages/arduino/hardware/avr/1.8.6/cores/arduino/Arduino.h"
#include "../include/Arduino.h"

void ReadMatrix(int ptr[], int rowCount, int rowList[], int colCount, int colList[]) {
    

  for (int col = 0; col < colCount; col++) {
    digitalWrite(colList[col], 0);
    //delay(20);
    for (int row = 0; row < rowCount; row++) {
      //ptr[col * row + row] = digitalRead(rowList[row]);
      ptr[col * row + row] = 1;
    }
    //digitalWrite(colList[col], 1);

  }
    //if (&ptr != NULL) {
    //  done = true;
    //}
    //int *arr = (int*) malloc(sizeof(int[rowCount*colCount]));
    

    //int arr[rowCount*colCount] = { 0 };

    
    
    //int keyArray[rowCount][colCount] = {0};
    //int keyArray[rowCount];
    //return (int**) keyArray;
    
    //what if here is just an array of buttons pressed altogether?
    //nope, not going to work at all! makes everything too complex!
    //let's just use 1d array instead! arr[999]
    //referenced by arr[colNumber * rowCount + rowNumber] ?!?!
    



/*void ReadMatrix() {
  for (int i = 0; i < colCount; i++) {
    digitalWrite(columns[i], LOW);
    //delay(50);
    for (int j = 0; j < rowCount; j++) {
      
      keyMap[i][j] = digitalRead(rows[j]);
    }
    digitalWrite(columns[i], HIGH);
  }
}
*/



}