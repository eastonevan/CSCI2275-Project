#include<iostream>
#include<queue>
#include<stack>
#include<vector>

using namespace std;

/*===========
	Product
  ===========*/

struct Product
{
	string name;
	int price;
	int quantity;
};





/*===========
	Business
  ===========*/

class Business
{

};





/*===========
   Warehouse
  ===========*/

class Warehouse
{

};




/*===========
	Store
  ===========*/

class Store
{

};





/*===========
	Driver
  ===========*/

class Driver
{
public:

	void printMenu()
	{
		cout<<"1. Enter Business"<<endl;
		cout<<"2. Create Business"<<endl;
		cout<<"3. Delete Business"<<endl;
		cout<<"4. Quit"<<endl;

	}

	void runProgram()
	{
		
		while(true)
		{
			printMenu();
			int choice;
			cin>>choice;
			switch(choice)
			{
				case 1:
				{
					//Enter Business
					break;

				}
				case 2:
				{
					//Create Business
					break;

				}
				case 3:
				{
					//Delete Business
					break;

				}
				case 4:
				{
					//Quit;
					break;

				}
				default:
				{
					cout<<"Please choose a number between 1-4"<<endl;
					break;
				}
			}
		}



	}

};




/*===========
	Main
  ===========*/

int main()
{
	cout<<"evan edit"<<endl;
	cout<< "Test" << endl;
	cout<<"Max Edit"<<endl;
}