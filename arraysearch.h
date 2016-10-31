#ifndef ARRAYSEARCH
#define ARRAYSEARCH
#include "arraybuild.h"

class ArraySearch : public BuildArray
{
private:

public:
    ArraySearch();
    ArraySearch(int a);
    ~ArraySearch();
    void testPrint();
    void checkSorted();
    bool binaryRowSearch(int tmpRow);
    double binarySearch(int tmpRow, int tmpCol) const;
    double linearSearch(int n, int last, int tmpRow, int tmpCol);
    double seqSearch(int tmpRow, int tmpCol);
    void setLinearSkips(int found);
    int getLinearSkips();
    
    int linearSkips;
};

ArraySearch::ArraySearch()
{
    
}

ArraySearch::ArraySearch(int a)
{
    setLength(a);
    setMaxLen(a);
}

ArraySearch::~ArraySearch()
{
    
}

//=========================================
// binarySearch function
// used if both lists are sorted
//=========================================
bool ArraySearch::binaryRowSearch(int tmpCol)
{
    int first = 0;
    int last = getLength() - 1;
    int mid = 0;
    bool found = false;
    
    while (first <= last && !found)
    {
        mid = (first + last) / 2;
        
        if (tmpCol > matrix[mid].row)
        {
            first = mid + 1;
        }
        else if (tmpCol < matrix[mid].row)
        {
            last = mid - 1;
        }
        else
        {
            //cout << "Row " << tmpCol << " matches " << matrix[mid].row << " found at position " << mid << "\n" << endl;
            found = true;
        }
    }
    return found;
}

//=========================================
// binarySearch function
// used if both lists are sorted
//=========================================
double ArraySearch::binarySearch(int tmpRow, int tmpCol) const
{
    int first = 0;
    int last = getLength() - 1;
    int mid = 0;
    double x = 0;
    bool found = false;
    
    while (first <= last && !found)
    {
        mid = (first + last) / 2;
        
        if (matrix[mid].row == tmpRow && matrix[mid].col == tmpCol)
        {
            found = true;
            return matrix[mid].val;
        }
        else if (matrix[mid].row > tmpRow)
        {
            last = mid - 1;
        }
        else if (matrix[mid].row < tmpRow)
        {
            first = mid + 1;
        }
        else if (matrix[mid].row == tmpRow)
        {
            if (matrix[mid].col < tmpCol)
            {
                first = mid + 1;
            }
            else
            {
                last = mid - 1;
            }
        }
    }
    
    return x;
}


//=========================================
// linearSearch function
// used if either list is unordered
//=========================================
double ArraySearch::linearSearch(int n, int last, int tmpRow, int tmpCol)
{
    int found = 0;
    double x = 0;
    
    while (n < last)
    {
        if (matrix[n].row == 0 && matrix[n].col == 0)
        {
            //cout << "bad row,col combination ... " << endl;
        }
        else
        {
            //cout << "good row,col check, test if passed row,col are equal to element ... " << endl;
            if (matrix[n].row == tmpRow && matrix[n].col == tmpCol)
            {
                //cout << "row,col are equal to element ... " << endl;
                found++;
                x += matrix[n].val;
            }
            else
            {
                //cout << "row,col not equal to element, exit if condition ... " << endl;
            }
        }
        //cout << "increment to next nth position ... \n" << endl;
        n++;
        
    }

    setLinearSkips(found);
    return x;
    
}

//=============================================
// seqSearch function sequentially searchs the
// matrix list for the same row and column
//=============================================
double ArraySearch::seqSearch(int tmpRow, int tmpCol)
{
    bool found = false;
    double x = 0;
    int n = 0;
    int last = getLength();
    
    while (n < last && !found)
    {
        if (matrix[n].row == tmpRow && matrix[n].col == tmpCol)
        {
            found = true;
            x = matrix[n].val;
            n++;
        }
        else
        {
            found = false;
            n++;
        }
        
    }
    
    return x;
}

//=============================================
// setLinearSkips void function
//=============================================
void ArraySearch::setLinearSkips(int found)
{
    linearSkips = found;
}

int ArraySearch::getLinearSkips()
{
    return linearSkips;
}


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
    setSortStatus(checkSort);
}

void ArraySearch::testPrint()
{
    cout << "you've reached the testPrint function via inheritence" << endl;
}




#endif // ARRAYSEARCH
