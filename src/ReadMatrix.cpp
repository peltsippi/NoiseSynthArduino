//#include "../include/ReadMatrix.h"
//#include "Arduino.h"
//#include "/home/timo/.arduino15/packages/arduino/hardware/avr/1.8.6/cores/arduino/Arduino.h"
//#include "../include/Arduino.h"


#ifdef UNIT_TEST
    #include "../mocks/digitalReadWriteMock.h"
#endif


bool ReadMatrix(int ptr[], int rowCount, int rowList[], int colCount, int colList[]) {
    
  /*
  How this works?
  First everything is set up as input_pullup (everything is 1)
  Then a column is switched to 0
  And all rows read to see if something changes to 0 -> button pressed
  
  */

  for (int col = 0; col < colCount; col++) {
    digitalWrite(colList[col], 0); //writing column low in order to read input_pullup
    //delay(20);
    for (int row = 0; row < rowCount; row++) {
      ptr[col * rowCount + row] = digitalRead(rowList[row]);
      //ptr[col * rowCount + row] = 1;
    }
    digitalWrite(colList[col], 1); //setting it back up

  }


    return HIGH;
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