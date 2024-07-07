//#include "../include/ReadMatrix.h"


int* ReadMatrix(int rowCount, int rowList[], int colCount, int colList[]) {
    
    int *arr = (int*) malloc(sizeof(int[rowCount][colCount]));

    return (int*) arr;
    
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