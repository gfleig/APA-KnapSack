#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct item{
    int C;
    int P;
};

struct tableItem{
    int value;
    int X;
};

int max(int a, int b)
{
    return a > b ? a : b;
}

std::vector <item> buildItemList(const char* filename, int& sackSize, int& numberOfItems)
{
    std::ifstream file;
    file.open(filename, std::ios::in);
    
    file >> numberOfItems;
    file >> sackSize;   

    std::vector <item> itemList;

    while(file.good())
    {
        struct item newItem;
        file >> newItem.P;
        file >> newItem.C;        

        itemList.push_back(newItem);        
    }

    file.close(); 
    
    return itemList;    
}

void knapSack(const int sackSize, const int numberOfItems, const std::vector <item> itemList)
{
    struct tableItem table[sackSize + 1][numberOfItems + 1];

    for(int i = 0; i < numberOfItems + 1; ++i)      //inicializa primeira linha com 0
    {
        table[0][i].value = 0;
        table[0][i].X = 0;
    }
    for(int i = 0; i < sackSize + 1; ++i)           //inicializa ultima coluna com 0
    {
        table[i][numberOfItems].value = 0;
        table[i][numberOfItems].X = 0;
    }

    for(int i = numberOfItems - 1; i >= 0; --i)
    {
        for(int M = 1; M <= sackSize; ++M)
        {   
            int Coord = M - itemList[i+1].P;
            
            int tableValue;
            if(Coord < 0) 
            {                
                tableValue = itemList[i+1].C;
            }      
            else
            {
                tableValue = table[Coord][i + 1].value + itemList[i+1].C;
            }     

            //finds max(table[M][i+1].value , table[M - itemList[i].P][i + 1].value + itemList[i].C)
            if(table[M][i+1].value > tableValue)
            {
                table[M][i].value = table[M][i+1].value;
                table[M][i].X = 0;
            }
            else
            {
                table[M][i].value = tableValue;
                table[M][i].X = 1;
            }
        }        
    }

    std::cout << table[sackSize][0].value << std::endl;
}

int main()
{
    int sackSize, numberOfItems;
    std::vector <item> itemList = buildItemList("instancias/mochila01.txt", sackSize, numberOfItems);
    
    knapSack(sackSize, numberOfItems, itemList);

    return 0;
}