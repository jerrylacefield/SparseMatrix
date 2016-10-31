#ifndef SORTARRAY
#define SORTARRAY
#include "arraybuild.h"

class SortArray : public BuildArray
{
private:
    bool isSorted;  //stores boolean condition if list is sorted or not
public:
    void checkSorted();
    void setSortInd(bool ind);
    bool getSortInd() const;
    
};

//============================================
// setSortInd function accesses the private
// variable sortedList and sets the indicator
//============================================
void SortArray::setSortInd(bool ind)
{
    isSorted = ind;
}

//==============================================
// getSortInd function access the value of the
// boolean sortedList variable
//==============================================
bool SortArray::getSortInd() const
{
    return sortedList;
}


//============================================
// checkSorted function reads the array and
// determines if currently sorted ascending
//============================================
void ArraySearch::checkSorted()
{
    int i = 0;
    bool checkSort = true;
    int length = getListSize();
    
    //cout << "List Length = " << length << endl;
    
    //cout << "Initialized Sort Indicator = " << checkSort << endl;
    
    while (checkSort == true && i < length - 1)
    {
        //cout << "Checking List Item " << i + 1 << " less than item " << i << " ... " << endl;
        //cout << "Checking if Row(n+1) less than Row(n) ... " << endl;
        if (matrix[i+1].row < matrix[i].row)
        {
            //cout << "Row Less Than Check Result: True " << matrix[i+1].row << " lt " << matrix[i].row << "\n" << endl;
            checkSort = false;  //Sort Indicator now set to False
        }
        else
        {
            //cout << "Row Less Than Check Result: False" << matrix[i+1].row << " nlt " << matrix[i].row << endl;
            //cout << "Checking if Row(n+1) equal to Row(n) ... " << endl;
            if (matrix[i+1].row == matrix[i].row)
            {
                //cout << "Row Equality Check Result: True" << matrix[i+1].col << " eq " << matrix[i].col << endl;
                //cout << "Checking if Col(n+1) less than Col(n) ... " << endl;
                if (matrix[i+1].col < matrix[i].col)
                {
                    //cout << "Column Check Result: True" << matrix[i+1].col << " lt " << matrix[i].col << "\n" << endl;
                    checkSort = false;  //Sort Indicator now set to False
                }
                else
                {
                    //cout << "Column Check Result: False" << matrix[i+1].col << " gt " << matrix[i].col << endl;
                    i++;
                }
            }
            else
            {
                i++;
            }
        }
    }
    
    //cout << "Final Sort Indicator = " << checkSort << endl;
    setSortInd(checkSort);
}

#endif // SORTARRAY
