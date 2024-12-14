#ifndef ReadMatrix_h
#define ReadMatrix_h

/// @brief 
/// @param ptr  - pointer_array[ARR_SIZE] || ARR_SIZE = rowCount * colCount
/// @param rowCount - how many rows in total
/// @param rowList - DI/DO pins for rows
/// @param colCount - how many columns in total
/// @param colList - DI/DO pins for columns
/// @return 
bool ReadMatrix(int ptr[], int rowCount, int rowList[], int colCount, int colList[]);
/*
\\ ReadMatrix(int pointer[])
\\\
\\
*/
#endif