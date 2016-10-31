#ifndef ARRAYLIST_H
#define ARRAYLIST_H
#include <math.h>   // log2 function

struct listArray
   {
       int row;                              // stores the list row position
       int col;                              // stores the list column position
       double val;                           // stores the list row/column value
       int pos;
       listArray();
       listArray(int a, int b, double c, int p);
   };

listArray::listArray()
{
    row = 0;
    col = 0;
    val = 0;
    pos = 0;
}

listArray::listArray(int a, int b, double c, int p)
{
    row = a;
    col = b;
    val = c;
    pos = p;
}

class BuildArray
{
private:
    int length;                                      // stores the length of the list
    int maxLen;                                      // stores the maximum size of the list
    int dimRow;                                      // stores the row position
    int dimCol;                                      // stores the column position
    double val;                                      // stores the value
    bool sortStatus;                                 // indicates whether the list is sorted or not
    int listSize;                                    // stores the number of items used in the array where ijv is not 0
    int firstOpen;
    int comparisonsCount;
    int swapCount;
    int bigO;
    
public:
    BuildArray();                                     // default constructor
    BuildArray(int a);                                // default constructor storing combined length
    ~BuildArray();                                    // destructor
    listArray* matrix;
    void setSortStatus(bool status);
    void setMaxLen(int n);                           // sets the max length of the array list
    void setLength(int n);                           // sets the length of the array list
    void setDims(int r, int c);                      // sets the value of the row dimension of matrix
    void calcMaxLen(string file);                    // function used to calculate max length of list
    void calcLength(string file);                    // function used to calculate length of list
    void calcMaxDims(string file);
    //void calcDims();
    void setItems(int n, int i, int j, double v, int p, listArray []);    // sets the row, column, and values
    void setListSize(int n);
    void setFirstOpen(int n);
    void updateValue(int n, double v, listArray[]);

    bool getSortStatus() const;
    int getMaxLen() const;                           // returns the max length of the list
    int getLength() const;                           // returns the length of the list
    int getRowDim() const;                           // returns the row dimension of the matrix
    int getColDim() const;                           // returns the column dimension of the matrix
    int getRow(int n, listArray[]);                               // returns the row position for elem-n
    int getCol(int n, listArray[]);                               // returns the column position for elem-n
    double getValue(int n, listArray[]);                          // returns the value at pos-ij for elem-n
    int getListSize();                               // returns the size of array list elements where not NULL
    int getFirstOpen();                               // returns the next open element where ij is 0
    
    void bubbleSort(int size, listArray[]);
    void quickSort(int left, int right, listArray[]);
    int partition(int left, int right, listArray[]);
    void setComparisonsCount(int n);
    int getComparisonsCount();
    void setSwapCount(int n);
    int getSwapCount();
    void setBigO(int n);
    int getBigO();
    void calcBigO(string sort);

    void makeArray(string, listArray[]);
    void makeDefault(int n, listArray[]);
    void nonRecursiveAdd(int, int);
    void printArray(listArray[]);
    void outputForward(string outfile, int r, int c, listArray []);
    
};

//============================================
// Default Constructor
//============================================
BuildArray::BuildArray()
{
    length = 0;
    maxLen = 0;
    listSize = 0;
    firstOpen = 0;
    //cout << "Matrix Created, element size = 1" << endl;
}

//============================================
// Default Constructor that accepts array
// length from 2 arrays, and adds them both
//============================================
BuildArray::BuildArray(int a)
{
    length = a;
    maxLen = a;
    //cout << "Matrix Created, element size = 1" << endl;
}

//============================================
// Destructor
//============================================
BuildArray::~BuildArray()
{
    //delete [] matrix;
    //cout << "Array List Object successfully destroyed" << endl;
}

//============================================
// setSortInd function accesses the private
// variable sortStatus and sets bool condition
//============================================
void BuildArray::setSortStatus(bool status)
{
    sortStatus = status;
}

//============================================
// setMaxLen function used to store the max
// length of the sparse list for the file
//============================================
void BuildArray::setMaxLen(int n)
{
    maxLen = n;
}

//============================================
// setLength function used to store the length
// of the sparse list for the file read in
//============================================
void BuildArray::setLength(int n)
{
    length = n;
}

//============================================
// setRowDim function used to store the row
// dimension in dimRow variable
//============================================
void BuildArray::setDims(int r, int c)
{
    dimRow = r;
    dimCol = c;
}

//============================================
// calcLength function used to return the count
// of the number of lines in the sparse file
//=============================================
void BuildArray::calcMaxLen(string file)
{
    string str;
    ifstream ifs(file.c_str());
    int n = 0;
    
    while(getline(ifs, str))
    {
        if (!str.empty() && str.at(0) != '#')
        {
            n++;
        }
    }
    
    setMaxLen(n);
}

//=============================================
// calcMaxDim
//=============================================
void BuildArray::calcMaxDims(string file)
{
    string str;
    ifstream ifs(file.c_str());
    //int n = 0;
    int currMaxRow = 0;
    int currMaxCol = 0;
    
    while(getline(ifs, str))
    {
        if (!str.empty() && str.at(0) != '#')
        {
            stringstream ss(str.c_str());
            int a, b;
            double c;
            
            ss >> a;
            ss >> b;
            ss >> c;
            
//            cout << a << endl;
            if (a > currMaxRow)
                currMaxRow = a;
            
//            cout << b << endl;
            if (b > currMaxCol)
                currMaxCol = b;
        }
        
        //cout << "Current Max Row: " << currMaxRow << "\tCurrent Max Col: " << currMaxCol << endl;
    }
    
    setDims(currMaxRow, currMaxCol);
}

//=============================================
// calcLength function used to return the count
// of the number of lines in the sparse file
//=============================================
void BuildArray::calcLength(string file)
{
    string str;
    ifstream ifs(file.c_str());
    int n = 0;  // used to store number of loop iterations
    int d = 0;  // used to store number of lines skipped due to zero c-value
    
    while(getline(ifs, str))
    {
        if (!str.empty() && str.at(0) != '#')
        {
            stringstream ss(str.c_str());
            int a, b;
            double c;
            
            ss >> a;
            ss >> b;
            ss >> c;
            
            if (a > 0 && b > 0)
            {
                if (c == 0 && n == getMaxLen() - 1)
                {
                    n++;
                }
                else
                {
                    if (c == 0 && n < getMaxLen() - 1)
                    {
                        n++;
                        d++;
                    }
                    else
                    {
                        n++;
                    }
                }
            }
            else
            {
                //do nothing
            }
        }
    }
    
    setLength(n - d);   // set array-based list length equal to n-iterations minus d-iterations
}

//==============================================
// calcDims function searches for the max value
// of the row and column dimensions
//==============================================
//void BuildArray::calcDims()
//{
//    int i = 0;
//    int maxRow = 0;
//    int maxCol = 0;
//    
//    while (i < getLength())
//    {
//        if (matrix[i].row > maxRow)
//        {
//            maxRow = matrix[i].row;
//            i++;
//        }
//        else
//        {
//            i++;
//        }
//    }
//    
//    i = 0;
//    
//    while (i < getLength())
//    {
//        if (matrix[i].col > maxCol)
//        {
//            maxCol = matrix[i].col;
//            i++;
//        }
//        else
//        {
//            i++;
//        }
//    }
//    
//    setDims(maxRow, maxCol);
//    
//}

//==============================================
// setElement function used to set the row, col,
// and value at ij for the specified string
//==============================================
void BuildArray::setItems(int n, int i, int j, double v, int p, listArray neo[])
{
    //cout << "setting <" << i << ","<< j << ">" << v << " into position " << n << endl;
    
    neo[n].row = i;
    neo[n].col = j;
    neo[n].val = v;
    neo[n].pos = p;
    setListSize(n + 1);

}

//==============================================
// setSpotsUsed is a function used to store the
// count of elements that are currently occupied
//==============================================
void BuildArray::setListSize(int n)
{
    listSize = n;
}

//==============================================
// setNextOpen function stores the next open
// position for storage
//==============================================
void BuildArray::setFirstOpen(int n)
{
    firstOpen = n;
}

//==============================================
// updateValue function used to update value at
// the nth element
//==============================================
void BuildArray::updateValue(int n, double v, listArray neo[])
{
    neo[n].val = v;
}

//==============================================
// getRowDim returns the row dimension
//==============================================
int BuildArray::getRowDim() const
{
    return dimRow;
}

//==============================================
// getColDim returns the column dimension
//==============================================
int BuildArray::getColDim() const
{
    return dimCol;
}

//==============================================
// getItem function returns position value of
// row or column
//==============================================
int BuildArray::getRow(int n, listArray neo[])
{
    return neo[n].row;
}

//==============================================
// getItem function returns position value of
// row or column
//==============================================
int BuildArray::getCol(int n, listArray neo[])
{
    return neo[n].col;
}

//==============================================
// getValue function returns the value of the
// row and column returned
//==============================================
double BuildArray::getValue(int n, listArray neo[])
{
    return neo[n].val;
}

//==============================================
// getListSize function returns the number of
// elements utilized where not NULL
//==============================================
int BuildArray::getListSize()
{
    return listSize;
}

//==============================================
// getFirstOpen function returns the first open
// spot in the list
//==============================================
int BuildArray::getFirstOpen()
{
    return firstOpen;
}

//==============================================
// getLength function returns length integer
//==============================================
int BuildArray::getLength() const
{
    return length;
}

//==============================================
// getMaxLen function returns max length integer
//==============================================
int BuildArray::getMaxLen() const
{
    return maxLen;
}

//==============================================
// getSortInd function access the value of the
// boolean sortedList variable
//==============================================
bool BuildArray::getSortStatus() const
{
    return sortStatus;
}

//==============================================
// getNextOpen function returns the next open
// slot for storage
//==============================================

//====================================
// makeArray function
// reads in a file and streams each
// line to the data elements
//====================================
void BuildArray::makeArray(string file, listArray neo[])
{
    ifstream ifs;
    string str;
    calcMaxLen(file);
    calcLength(file);
    int rMax = getRowDim();
    int cMax = getColDim();
    
    int lewp = 0;

    ifs.open(file.c_str());
    while (getline(ifs, str))
    {
        if (!str.empty() && str.at(0) != '#')
        {
            stringstream ss(str.c_str());
            int r, c;
            double v;

            ss >> r;
            ss >> c;
            ss >> v;
            
            int p = (r * 100000) + c;
            
            //cout << a << " " << b << " " << c << endl;
            
            if (r > 0 && c > 0)
            {
                if (r == rMax && c == cMax)
                {
                    //cout << "Placing r,c,v " << r << "," << c << "," << v << " into the last position " << lewp << endl;
                    neo[lewp].row = r;
                    neo[lewp].col = c;
                    neo[lewp].val = v;
                    neo[lewp].pos = p;
                    setListSize(lewp + 1);
                    lewp++;
                }
                else if (v != 0)
                {
                    //cout << "Placing r,c,v " << r << "," << c << "," << v << " into position " << lewp << endl;
                    neo[lewp].row = r;
                    neo[lewp].col = c;
                    neo[lewp].val = v;
                    neo[lewp].pos = p;
                    setListSize(lewp + 1);
                    lewp++;
                }
                else
                {
                    
                }
            }
        }
        else
        {
            //skipping line
            //bad characters
        }
    }
    
    matrix = neo;
    
    ifs.close();
    
}

//===========================================
// makeDefault function builds an empty
// array list
//===========================================
void BuildArray::makeDefault(int n, listArray neo[])
{
    
    for (int count = 0; count < n; count++)
    {
        neo[count].row = 0;
        neo[count].col = 0;
        neo[count].val = 0;
        neo[count].pos = 0;
    }
    
    matrix = neo;
    
    setLength(n);
}

//===========================================
// bubbleSort
//===========================================
void BuildArray::bubbleSort(int size, listArray neo[])
{
//    bool swapped = false;
//    int n = 0;
    int loops = 0;
    int swaps = 0;
    
//    cout << "\n ... Entered Bubble Sort Function ... \n" << endl;
//    cout << "Pre-Bubble Sort Condition" << endl;
//    cout << "++++++++++++++++++++++++++++++++++\n" << endl;
//    printArray(neo);
//    cout << "++++++++++++++++++++++++++++++++++\n" << endl;
    
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (neo[j].row > neo[j + 1].row)
            {
                swap(neo[j],neo[j + 1]);
                swaps++;
                //else if(neo[j].row == neo[j + 1].row && )
            }
            else if (neo[j].row == neo[j + 1].row && neo[j].col > neo[j + 1].col)
            {
                swap(neo[j],neo[j + 1]);
                swaps++;
            }
            loops++;
        }
        
    }
    
//    cout << "BSF Swaps:\t" << swaps << endl;
//    cout << "BSF Compare:\t" << loops << endl;
    
//    cout << "Post-Bubble Sort Condition" << endl;
//    cout << "++++++++++++++++++++++++++++++++++\n" << endl;
//    printArray(neo);
//    cout << "++++++++++++++++++++++++++++++++++\n" << endl;
    
    cout << "... exiting bubble sort ... " << endl;
    
    setSwapCount(swaps);
    setComparisonsCount(loops);
    setSortStatus(true);
}

//===========================================
// quickSort
//===========================================
void BuildArray::quickSort(int left, int right, listArray neo[])
{
    //left should be the left-most element in array
    //right should be the right-most element in array
    
    int pivot;

    if (left < right)
    {
        pivot = partition(left, right, neo);
        quickSort(left, pivot - 1, neo);
        quickSort(pivot + 1, right, neo);
    }
    
    setSortStatus(true);
}

//===========================================
// quickSort partition (NEW)
//===========================================
int BuildArray::partition(int left, int right, listArray neo[])
{
    int index, smallIndex;
    int comps = getComparisonsCount();
    
    std::swap(neo[left], neo[(left + right) / 2]);
    
    int rowPivot = neo[left].row;
    int colPivot = neo[left].col;
    smallIndex = left;
    
    for (index = left + 1; index < right + 1; index++)
    {
        setComparisonsCount(comps++);
        if (neo[index].row < rowPivot)
        {
            smallIndex++;
            std::swap(neo[smallIndex], neo[index]);
        }
        else if (neo[index].row == rowPivot && neo[index].col < colPivot)
        {
            smallIndex++;
            swap(neo[smallIndex], neo[index]);
        }
        else
        {
            //do nothing
        }
    }
    
    swap (neo[left], neo[smallIndex]);
    
    return smallIndex;
}


/*
//===========================================
// quickSort partition
//===========================================
int BuildArray::partition_old(int left, int right, listArray neo[])
{
    int p = left;
    
    cout << "Comp # " << getComparisonsCount() << ", neo[left] = " << neo[left].row << "," << neo[left].col << "\tneo[p] = " << neo[(right - left) / 2].row << "," << neo[(right - left) / 2].col << endl;
    
    //swap the left most element with the middle element
    swap(neo[p],neo[(right - left) / 2]);
    
    
    int row = neo[left].row;
    int col = neo[left].col;
    int comps = getComparisonsCount();
    int swaps = getSwapCount();
    
    for (int i = left + 1; i < right + 1; i++)
    {
        setComparisonsCount(comps++);
        if (neo[i].row > row)
        {
            p++;
            swap(neo[i],neo[p]);
            setSwapCount(swaps++);
        }
        else if (neo[i].row == row && neo[i].col >= col)
        {
            p++;
            swap(neo[i],neo[p]);
            setSwapCount(swaps++);
        }
        else
        {
            
        }
    }
    
    swap(neo[p],neo[left]);
    //setComparisonsCount(comps++);
    setSwapCount(swaps++);
    
    return p;
}
*/

//===========================================
// setBubbleSortCount
//===========================================
void BuildArray::setComparisonsCount(int n)
{
    comparisonsCount = n;
}

//===========================================
// getBubbleSortCount
//===========================================
int BuildArray::getComparisonsCount()
{
    return comparisonsCount;
}

//===========================================
// setBubbleSwaps
//===========================================
void BuildArray::setSwapCount(int n)
{
    swapCount = n;
}

//===========================================
// getBubbleSwaps
//===========================================
int BuildArray::getSwapCount()
{
    return swapCount;
}

//===========================================
// setBigO function
//===========================================
void BuildArray::setBigO(int n)
{
    bigO = n;
}

//===========================================
// getBigO function
//===========================================
int BuildArray::getBigO()
{
    return bigO;
}

//===========================================
// getBigO function
//===========================================
void BuildArray::calcBigO(string sort)
{
    int n = getListSize();
    
    if (sort == "nsquared")
    {
        
        setBigO(static_cast<int>(pow(static_cast<double>(n), 2)));
    }
    else if (sort == "nlogn")
    {
        double m = static_cast<double>(n);
        double nlogn = n * log2(m);
        cout << nlogn << endl;
        setBigO(nlogn);
    }
    else
    {
        cout << "no sort parameter provided" << endl;
    }
}


//===========================================
// printArray function prints contents of
// the array to the terminal
//===========================================
void BuildArray::printArray(listArray neo[])
{
    int index = 0;
    int length = getListSize();
    
    int rMax = getRowDim();
    int cMax = getColDim();
    
//    cout << rMax << " " << cMax << endl;
    
    cout << fixed << setprecision(2);
    
    cout << "============================" << endl;
    while (index < length)
    {
        
        if (neo[index].row == rMax && neo[index].col == cMax)
        {
//            cout << "Entering Last Item into list ... " << endl;
            cout << "Item " << index << ": " << neo[index].row << " " << neo[index].col << " " << neo[index].val << endl; //" (" << neo[index].pos << ")"  << endl;
        }
        else if (neo[index].val != 0)
        {
            cout << "Item " << index << ": " << neo[index].row << " " << neo[index].col << " " << neo[index].val << endl; //" (" << neo[index].pos << ")" << endl;
        }
        index++;
    }
    cout << "============================\nMatrix Length " << getLength() << endl;
    cout << "Matrix List Size " << getListSize() << "\n" <<endl;
}

//===========================================
// outputFoward function sends the contents
// of the results array to the specified file
//===========================================
void BuildArray::outputForward(string outfile, int rMax, int cMax, listArray neo[])
{
    int index = 0;
    int length = getListSize();
    
    ofstream ofs(outfile.c_str());
    ofs << fixed << setprecision(2);
    
    //std::cout << "writing to file ... " << length << " lines" << std::endl;
    
    //write the header to outfile
    //ofs << "### MATRIX C = A * B\n#" << endl;
    
    while (index < length)
    {
        if (neo[index].row == rMax && neo[index].col == cMax)
        {
            //std::cout << "out to line " << index << std::endl;
            ofs << neo[index].row << " " << neo[index].col << " " << neo[index].val << endl;
        }
        else if (neo[index].val != 0)
        {
            //std::cout << "outputing to line " << index << std::endl;
            ofs << neo[index].row << " " << neo[index].col << " " << neo[index].val << endl;
        }
        index++;
    }
    
    ofs.close();
}

#endif
