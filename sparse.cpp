#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"
#include "arraybuild.h"
#include "arraysearch.h"
//#include "arraysort.h"
using namespace std;

ArraySearch A;
ArraySearch B;
ArraySearch C;

//Function Prototypes
void callCalcMaxDims(string, string);               //process max dimension calculations for each matrix
void calcMatrixListSize();
void callMakeArray(string, string, listArray[], listArray[]);
void doSort(string sort, listArray[], listArray[]);
void doMultiply(string fileA, string fileB, listArray[]);
void openInFile(string);
void openOutFile(string);
bool isStringEmpty(string);
void convertSortBoolTest(bool, string);     //debugging function
bool isCompatible(int aj, int bi);          //Matrix Multiplication Compatability Test
void outputBigO(string sort, string fileA, string fileB);

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    string fileA = am.get("A");
    string fileB = am.get("B");
    string results = am.get("result");
    string oper = am.get("operation");
    string sort = am.get("sort");
    string stor = am.get("storage");
    
    callCalcMaxDims(fileA, fileB);  // calculate max dimensions for each sparse matrix file
    
    const int sizeA = A.getRowDim() * A.getColDim();
    const int sizeB = B.getRowDim() * B.getColDim();
    const int sizeC = A.getRowDim() * B.getColDim();
    
    // dynamic declaration of array of type listArray
    listArray *listA = new listArray[sizeA];
    listArray *listB = new listArray[sizeB];
    listArray *listC = new listArray[sizeC];
    
    callMakeArray(fileA, fileB, listA, listB);
    
    doSort(sort, listA, listB);
    
    doMultiply(fileA, fileB, listC);

    
    cout << "\nMultiplication Results" << endl;
    //C.printArray(listC);
    C.outputForward(results, A.getRowDim(), B.getColDim(), listC);
    
    outputBigO(sort, fileA, fileB);
    
    delete [] listA;
    delete [] listB;
    delete [] listC;
    
    return 0;

}

//=========================================
// callCalcMaxDims function calls the
// calcMaxDims member function for each
// object created
//=========================================
void callCalcMaxDims(string fileA, string fileB)
{
    A.calcMaxDims(fileA);
    B.calcMaxDims(fileB);
}

//=========================================
// callMakeArray function
//=========================================
void callMakeArray(string fileA, string fileB, listArray listA[], listArray listB[])
{
    A.makeArray(fileA, listA);
    B.makeArray(fileB, listB);
}

//===========================================
// doSort function
//===========================================
void doSort(string sort, listArray listA[], listArray listB[])
{
    if (sort == "nsquared")
    {
        A.calcBigO(sort);
        B.calcBigO(sort);
        
        // I'm feeling "bubbly" about this sort of thing
        cout << "\n ... Entering Quick Sort Function ... \n" << endl;
        cout << "Pre-Quick Sort Condition List A" << endl;
        cout << "++++++++++++++++++++++++++++++++++\n" << endl;
        A.printArray(listA);
        cout << "++++++++++++++++++++++++++++++++++\n" << endl;
        
        A.bubbleSort(A.getListSize(), listA);   // bubble sorting list A
        
        cout << "Post-Quick Sort Condition" << endl;
        cout << "++++++++++++++++++++++++++++++++++\n" << endl;
        A.printArray(listA);
        cout << "++++++++++++++++++++++++++++++++++" << endl;
        cout << "Total Comparisons: \t" << A.getComparisonsCount() << endl;
        cout << "O(n^2) Analysis: \t" << A.getBigO() << endl;
        cout << "\nTotal Swaps: \t\t" << A.getSwapCount() << endl;
        
        cout << "\n ... Entering Quick Sort Function ... \n" << endl;
        cout << "Pre-Quick Sort Condition List B" << endl;
        cout << "++++++++++++++++++++++++++++++++++\n" << endl;
        B.printArray(listB);
        cout << "++++++++++++++++++++++++++++++++++\n" << endl;
        
        B.bubbleSort(B.getListSize(), listB);   // bubble sorting list B
        
        cout << "++++++++++++++++++++++++++++++++++\n" << endl;
        B.printArray(listB);
        cout << "++++++++++++++++++++++++++++++++++\n" << endl;
        cout << "Total Comparisons: \t" << B.getComparisonsCount() << endl;
        cout << "O(n^2) Analysis: \t" << B.getBigO() << endl;
        cout << "\nTotal Swaps: \t\t" << B.getSwapCount() << "\n" << endl;
        
    }
    else if (sort == "nlogn")
    {
        A.calcBigO(sort);
        B.calcBigO(sort);
        
        // Come on, we've got to be quick about this sort
        cout << "\n ... Entering Quick Sort Function ... \n" << endl;
        cout << "Pre-Quick Sort Condition List A" << endl;
        cout << "++++++++++++++++++++++++++++++++++\n" << endl;
        A.printArray(listA);
        cout << "++++++++++++++++++++++++++++++++++\n" << endl;
        
        A.quickSort(0, A.getListSize() - 1, listA);     // quick sort list A
        
        cout << "Post-Quick Sort Condition" << endl;
        cout << "++++++++++++++++++++++++++++++++++\n" << endl;
        A.printArray(listA);
        cout << "++++++++++++++++++++++++++++++++++" << endl;
        cout << "Total Comparisons: \t" << A.getComparisonsCount() << endl;
        cout << "O(nlogn) Analysis: \t" << A.getBigO() << endl;
        cout << "\nTotal Swaps: \t\t" << A.getSwapCount() << endl;
        
        cout << "\n ... Entering Quick Sort Function ... \n" << endl;
        cout << "Pre-Quick Sort Condition List B" << endl;
        cout << "++++++++++++++++++++++++++++++++++\n" << endl;
        B.printArray(listB);
        cout << "++++++++++++++++++++++++++++++++++\n" << endl;
        
        B.quickSort(0, B.getListSize() - 1, listB);     // quick sort list B
        
        cout << "++++++++++++++++++++++++++++++++++\n" << endl;
        B.printArray(listB);
        cout << "++++++++++++++++++++++++++++++++++\n" << endl;
        cout << "Total Comparisons: \t" << B.getComparisonsCount() << endl;
        cout << "O(nlogn) Analysis: \t" << B.getBigO() << endl;
        cout << "\nTotal Swaps: \t\t" << B.getSwapCount() << "\n" << endl;
        
    }
    else
    {
        A.setSortStatus(false);
        B.setSortStatus(false);
    }
} //end callMakeArray

//=========================================
// doMultiply function
//=========================================
void doMultiply(string fileA, string fileB, listArray listC[])
{
    int iLoop = A.getRowDim();
    int jLoop = B.getColDim();
    int kLoop = A.getColDim();
    
    if (isCompatible(A.getColDim(),B.getRowDim()))
    {
        cout << "Matrix Compatability Check Status:  Passed" << endl;
        
        A.checkSorted();
        B.checkSorted();
        
        bool sortStatusA = A.getSortStatus();
        bool sortStatusB = B.getSortStatus();
        
        convertSortBoolTest(sortStatusA, fileA);
        convertSortBoolTest(sortStatusB, fileB);
        
        //
        if (sortStatusA && sortStatusB)
        {
            //iterating through Matrix A rows
            for (int i = 1; i < iLoop + 1; i++)
            {
                //iterating through Matrix B columns
                for (int j = 1; j < jLoop + 1; j++)
                {
                    double v = 0;
                    int iC = 0;
                    int jC = 0;
                    
                    //multiply values in positions ik & ki
                    for (int k = 1; k < kLoop + 1; k++)
                    {
                        v += (A.binarySearch(i, k) * B.binarySearch(k, j));
                        iC = i;
                        jC = j;
                    }
                    
                    //Throw the results of the sum of products into the array
                    //Append the SoP for the final position of SoP array
                    //
                    if (iC == A.getRowDim() && jC == B.getColDim())
                    {
                        int loc = C.getFirstOpen();
                        C.setItems(loc, iC, jC, v, (iC*100000)+jC, listC);
                        C.setFirstOpen(loc + 1);
                    }
                    //Append item into the array if sum of products is not zero
                    else if (v != 0)
                    {
                        int loc = C.getFirstOpen();
                        C.setItems(loc, iC, jC, v, (iC*100000)+jC, listC);
                        C.setFirstOpen(loc + 1);
                    }
                }
            }
        }
        else
        {
            cout << "Sort Test:\tFailed" << endl;
            cout << "Search Type:\tSequential" << endl;
            
            int lastA = A.getListSize();
            int lastB = B.getListSize();
            cout << "Last Element of A: " << lastA << endl;
            cout << "Last Element of B: " << lastB << endl;
            
            //iterating through Matrix A rows
            for (int i = 1; i < iLoop + 1; i++)
            {
                //iterating through Matrix B columns
                for (int j = 1; j < jLoop + 1; j++)
                {
                    double v = 0;
                    int iC = 0;
                    int jC = 0;
                    
                    //multiply values in positions ik & ki
                    for (int k = 1; k < kLoop + 1; k++)
                    {
                        v += (A.seqSearch(i, k) * B.seqSearch(k, j));
                        iC = i;
                        jC = j;
                    }
                    
                    //Throw the results of the sum of products into the array
                    //Append the SoP for the final position of SoP array
                    if (iC == A.getRowDim() && jC == B.getColDim())
                    {
                        int loc = C.getFirstOpen();
                        C.setItems(loc, iC, jC, v, (iC*100000)+jC, listC);
                        C.setFirstOpen(loc + 1);
                    }
                    //Append item into the array if sum of products is not zero
                    else if (v != 0)
                    {
                        int loc = C.getFirstOpen();
                        C.setItems(loc, iC, jC, v, (iC*100000)+jC, listC);
                        C.setFirstOpen(loc + 1);
                    }
                }
            }
        }
    }
    else
    {
        cout << "Sparse Matrices cannot be multipled ... exiting program" << endl;
        
    }
}

//=========================================
// Function used to check if a string is
// empty before reading it to a function
//=========================================
bool isStringEmpty(string str)
{
   if (!str.empty())
   {
       return false;
   }
   else
   {
      cout << "empty file string provided" << endl;
      return true;
   }
}

//==========================================
// Function to open Input Matrix File      =
//==========================================
void openInFile(string fileStr)
{
   bool verifyStr;
   verifyStr = isStringEmpty(fileStr);

   if (!verifyStr)
   {
      ifstream ifs(fileStr.c_str());
      cout << "File opened successfully" << endl;
   }
   else
   {
      cout << "File not opened successfully ... closing program" << endl;
   }
}

//===========================================
// Function to open output matrix file      =
//===========================================
void openOutFile(string fileStr)
{
   ofstream ofs(fileStr.c_str());
}

//===========================================
// Function to convert boolean to string    =
// This function only serves debugging      =
//===========================================
void convertSortBoolTest(bool test, string file)
{
    
    string sortCondition;
    
    if (test)
    {
        sortCondition = "sorted";
    }
    else
    {
        sortCondition = "not sorted";
    }
    
    cout << "File " << file << " Sort Check: " << sortCondition << endl;
}

//===========================================
// Matrix Compatability Test                =
//===========================================
bool isCompatible(int aj, int bi)
{
    return (aj == bi);
}

//===========================================
// outputBigO function
//===========================================
void outputBigO(string sortAlgorithm, string fileA, string fileB)
{
    string bigO = "BigO.txt";
    ifstream fileExists(bigO);
    ofstream file;
    
    if (!fileExists)
    {
        fileExists.close();
        file.open( bigO.c_str(), ios::out);
        file << "Sparse List  Algorithm  #entries(n) countComparisons bigOcountComparisons\n";
        
        file << setw(11) << std::left << fileA << "  "
             << setw(13) << std::left << sortAlgorithm
             << setw(6) << std::right << A.getListSize() << ""
             << setw(16) << std::right << A.getComparisonsCount() << "  "
             << setw(16) << std::right << A.getBigO() << endl;
        
        file << setw(11) << std::left << fileB << "  "
             << setw(13) << std::left << sortAlgorithm
             << setw(6) << std::right << B.getListSize() << ""
             << setw(16) << std::right << B.getComparisonsCount() << "  "
             << setw(16) << std::right << B.getBigO() << endl;
    }
    else
    {
        file.open( bigO.c_str(), ios::app);
        
        file << setw(11) << std::left << fileA << "  "
             << setw(13) << std::left << sortAlgorithm
             << setw(6) << std::right << A.getListSize() << ""
             << setw(16) << std::right << A.getComparisonsCount() << "  "
             << setw(16) << std::right << A.getBigO() << endl;
        
        file << setw(11) << std::left << fileB << "  "
             << setw(13) << std::left << sortAlgorithm
             << setw(6) << std::right << B.getListSize() << ""
             << setw(16) << std::right << B.getComparisonsCount() << "  "
             << setw(16) << std::right << B.getBigO() << endl;
    }
    
    file.close();
    
}
