/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Date:   05/05/2019
 * Author: Jacob Kitchens
 * Email:  jak170430@utdallas.edu
 * Course: CS3377.502
 * Version: 1.0
 *
 * Description:
 * Modified example1.cc from Professor Perkins
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iomanip>
#include <string>


#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 18
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader {
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;  
};

const int maxRecordStringLength = 25;

class BinaryFileRecord {
public: 
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"R0", "a", "b", "c"};
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"R0", "a", "b", "c", "d", "e"};
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  char buffer[maxRecordStringLength];
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  ifstream binInFile ("cs3377.bin", ios::in | ios::binary);
  binInFile.read((char *) myHeader, sizeof(BinaryFileHeader));
  

  sprintf(buffer, "Magic: 0x%X", myHeader->magicNumber);
  setCDKMatrixCell(myMatrix, 1, 1, buffer);
  sprintf(buffer, "Version: %d", myHeader->versionNumber);
  setCDKMatrixCell(myMatrix, 1, 2, buffer);
  sprintf(buffer, "NumRecords: %d", myHeader->numRecords);
  setCDKMatrixCell(myMatrix, 1, 3, buffer);

  int i = 2;
  while (i < 6 || (binInFile.eof())) {
    BinaryFileRecord *myRecord = new BinaryFileRecord();
    binInFile.read((char*) myRecord, sizeof(BinaryFileRecord));
    
    sprintf(buffer, "strlen: %d", myRecord->strLength);
    setCDKMatrixCell(myMatrix, i, 1, buffer);
    setCDKMatrixCell(myMatrix, i, 2, myRecord->stringBuffer);
    i++;
  }
  
  binInFile.close();
  
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  while (!cin.get());


  // Cleanup screen
  endCDK();
}
