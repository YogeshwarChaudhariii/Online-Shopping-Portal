#include<iostream>
using namespace std;

class Items
{
    public:
    int ItemNo, Price;
    string ItemName;

    Items(int No, int p, string Iname)
    {
        ItemNo = No;
        Price = p;
        ItemName = Iname;
    }

    Items(Items &ItemObj)
    {
        this->ItemNo = ItemObj.ItemNo;
        this->Price = ItemObj.Price;
        this->ItemName = ItemObj.ItemName;
    }

    void Display()
    {
        cout<<"Item No: "<<ItemNo<<endl;
        cout<<"Item Name: "<<ItemName<<endl;
        cout<<"Item Price: "<<Price<<" Rs"<<endl;
    }

};

int main()
{
    Items iobj1(1, 20, "Samosa");
    Items iobj2(2, 25, "Kachori");
    Items iobj3(3, 15, "VadaPav");

    iobj1.Display();
    iobj2.Display();
    iobj3.Display();

    Items iobj4(iobj2);
    iobj4.Display();

    
    
    
    


    return 0;

}
