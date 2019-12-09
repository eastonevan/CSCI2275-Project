#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include<string>

using namespace std;


/*===========
	Product
  ===========*/

struct Product
{
	string name;
	int price;
	int quantity;
	Product *left;
	Product *right;
	Product *parent;

	Product(string n, int p, int q)
	{
		name=n;
		price=p;
		quantity=q;
	}
};


/*===========
   Warehouse
  ===========*/

class Warehouse
{
private:
	Product *root;

public:
	Warehouse()
	{
		root=NULL;
	}

	~Warehouse()
	{
		destruct(root);
	}

	void destruct(Product* node)
	{
		if(node==NULL)
		{
			return;
		}

		destruct(node->left);
		delete node;
		destruct(node->right);

	}

	/*
	function: delete product
	purpouse: deletes a product node from warehouse BST
	return: void
	*/
	void deleteProduct(Product* tempNode)
	{
		if(tempNode->left==NULL&& tempNode->right==NULL)//this is if its leaf
		{
			if(tempNode==root)
			{
				root=NULL;
			}else if(tempNode->parent->left==tempNode)
			
			{
				tempNode->parent->left=NULL;
			}else{
				tempNode->parent->right=NULL;
			}

			delete tempNode;
			return;
		}else if(tempNode->left!=NULL&& tempNode->right!=NULL)//two children
		{
			Product *treeMin= tempNode->right;
			while(treeMin!=NULL)
			{
				treeMin=treeMin->left;
			}

			tempNode->name=treeMin->name;
			tempNode->price=treeMin->price;
			tempNode->quantity=treeMin->quantity;

			deleteProduct(treeMin);

		}else//one child
		{
			Product* child= NULL;

			if(tempNode->left==NULL)
			{
				child=tempNode->right;
			}else{
				child=tempNode->left;
			}

			if(tempNode==root)
			{
				root=child;
			}


			if(tempNode->parent->left==tempNode)//node being deleted is on left
			{
				child->parent=tempNode->parent;
				tempNode->parent->left=child;
			}else{
				child->parent=tempNode->parent;
				tempNode->parent->right=child;
			}

			delete tempNode;
			return;

		}
	}
	/*
	function: add product
	purpouse: adds to current inventory or creates new BST node 
	return void
	*/
	void addProduct(string name, int price, int quantity)
	{
		Product* temp= new Product(name, price, quantity);

		if(root==NULL)
		{
			root=temp;
			return;
		}else{
			Product* iter=root;
			Product* parent=NULL;

			while(iter!=NULL)
			{
				parent=iter;
				if(iter->name>temp->name)
				{
					iter=iter->left;
				}else{
					iter=iter->right;
				}
			}

			if(parent->name>temp->name)
			{
				parent->left=temp;
				temp->parent=parent;
			}else{
				parent->right=temp;
				temp->parent=parent;
			}
		}

	}
	/*
	function: product info
	purpouse: prints all inormation about the product 
	return void
	*/
	void productInfo(string product)
	{
		if(root==NULL)
		{
			cout<<"There are no products in the warehouse"<<endl;
			return;
		}

		Product* temp= searchWarehouse(root, product);

		if(temp==NULL)
		{
			cout<<"Product does not exist."<<endl;
			return;
		}else
		{
			cout<<"Name: "<<temp->name<<"\nPrice: "<<temp->price<<"\nQuantity: "<<temp->quantity<<endl;
			return;
		}

	}
	/*
	function print warehouse
	purpouse: prints all of the items in the warehouse
	returns: void
	*/
	void printWarehouse(Product* root)
	{
		if(root==NULL)
		{
			return;
		}
		printWarehouse(root->left);
		productInfo(root->name); 
		printWarehouse(root->right);
	}



	/*
	function search warehouse
	purpouse: helper function to traverse/ find nodes in BST
	returns: the product if found or null if node DNE
	*/
	Product* searchWarehouse(Product* node, string product)
	{
		if(node==NULL)
		{
			return NULL;
		}

		Product* temp= node;

		while(temp->name!=product)
		{
			if(temp->name < product)
			{
				temp=temp->right;
			}else {
				temp=temp->left;
			}

			if(temp==NULL)
			{
				return temp;
			}

		}
		return temp;
	}

	Product* getRoot()
	{
		return root;
	}



};




/*===========
	Stores
  ===========*/


struct storeNode
{
	string name;
	Warehouse sHouse;
	storeNode *next;

	storeNode(string n)
	{
		name=n;
		next=NULL;
	}

	void storeMenu()
	{
		while(true)
		{
			cout<<"====Available Products===="<<endl;
			sHouse.printWarehouse(sHouse.getRoot());
			cout<<"1. Buy product."<<endl;
			cout<<"2. Leave store."<<endl;


			int choice;
			cin>>choice;

			if(choice==1)
			{
				cout<<"Type the name of the product you want to buy."<<endl;

				cin.clear();
				cin.ignore();

				string pName;
				getline(cin, pName);
				cin.clear();

				Product* wanted= sHouse.searchWarehouse(sHouse.getRoot(), pName);

				cout<<"Enter the number you would like to buy."<<endl;
				string q;
				getline(cin, q);
				cin.clear();

				int qWanted=stoi(q);

				buyProduct(pName, qWanted);

			}else if(choice==2)
			{
				return;
			}else
			{
				cout<<"Please pick a number 1-2." <<endl;
			}

		}
	}



	/* 
	function: buyProduct
	purpose: decrements the quantity of the product in the storeNode's warehouse
	& increments the business's total profit
	returns: void
	*/
	
	void buyProduct(string pName, int qWanted)
	{
		Product *pWanted= sHouse.searchWarehouse(sHouse.getRoot(), pName);

		if(pWanted==NULL)
		{
			cout<<"Product not found."<<endl;
		}else{
			if(qWanted>0 && qWanted<=pWanted->quantity)
			{
				cout<<"buying"<<endl;
				pWanted->quantity-=qWanted;

				if(pWanted->quantity==0)
				{
					sHouse.deleteProduct(pWanted);
				}
			}else{
				cout<<"You either input an invalid shipping number, or there are not enough of that product"<<endl;
				return;
			}
		}
	}




};

class StoreLL
{
private:
	storeNode *head;
	storeNode *tail;

public:
	StoreLL()
	{
		head=NULL;
		tail=NULL;
	}

	/* 
	function: insertStore
	purpose: creates a new store and adds it to the end of the storeLL
	return void:
	*/

	void insertStore(string name)
	{
		storeNode *newNode= new storeNode(name);
		if(head==NULL)
		{
			head=newNode;
			tail=newNode;
		}else
		{
			tail->next=newNode;
			tail=newNode;
		}

	}

	/* 
	function: deleteStore
	purpose: deletes a store that either has no products, or if chosen to be deleted
	return void
	*/
	
	void deleteStore(string name)
	{
		storeNode* temp=head;
		int prevCount=0;

		if(temp==NULL)
		{
			cout<<"Store not found"<<endl;
			return;
		}

		while(temp!=NULL)
		{
			if(temp->name==name)
			{
				break;
			}
			temp=temp->next;
			prevCount++;
		}

		if(temp->name!=name)
		{
			cout<< "Store not found." << endl;
			return;
		}

		if(temp==head)
		{
			head=temp->next;
			delete temp;
		}else
		{
			storeNode* prev=head;
			for(int i=1; i<prevCount; i++)
			{
				prev=prev->next;
			}

			prev->next=temp->next;
			delete temp;
		}


	}

	/* 
	function: printStores
	purpose: prints the list of stores
	return void
	*/
	
	void printStores()
	{
		storeNode* temp=head;
		while(temp!=NULL)
		{
			cout<<temp->name<<endl;
			temp=temp->next;
		}
	}

	storeNode* findStore(string sName)
	{
		storeNode* iter= head;

		while(iter!=NULL)
		{
			if(iter->name==sName)
			{
				break;
			}
		}

		return iter;
	}



};




/*===========
	Business
  ===========*/

class Business
{
private: 
	string name;
	Warehouse bHouse;
	StoreLL stores;
public:
	Business()
	{
		name="";
	}

	Business(string n)
	{
		name=n;
	}
	/*
	function: addProduct
	purpose: adds a product to the Business's warehouse
	return void
	*/
	void addProduct(string product, int price, int quantity)
	{
		Product* check = bHouse.searchWarehouse(bHouse.getRoot(), name);

		if(check==NULL)
		{
			bHouse.addProduct(product, price, quantity);
			return;
		}

		if(check->name==product)
		{
			cout<<"This product already exists, what would you like to do?"<<endl;
			cout<<"1. Update price."<<endl;
			cout<<"2. Update quantity."<<endl;
			cout<<"3. Update both."<<endl;

			int choice;
			cin>>choice;

			switch(choice)
			{
				case 1:
				{
					cout<<"What would you like the new price to be?"<<endl;
					int newPrice;

					cin.clear();
					cin.ignore();

					cin>>newPrice;
					check->price=newPrice;
					break;
				}
				case 2:
				{
					cout<<"What would you like the new quantity to be?"<<endl;
					int newQuantity;

					cin.clear();
					cin.ignore();

					cin>>newQuantity;
					check->quantity=newQuantity;
					break;

				}
				case 3:
				{

					cin.clear();
					cin.ignore();

					cout<<"What would you like the new price to be?"<<endl;
					int newPrice;
					cin>>newPrice;

					cout<<"What would you like the new quantity to be?"<<endl;
					int newQuantity;
					cin>>newQuantity;

					check->price=newPrice;
					check->quantity=newQuantity;
					break;

				}
				default:
				{
					cout<<"Invalid input, product not updated."<<endl;
					break;
				}
			}
			return;
		}

		
	}

	/*
	function: deleteProduct
	purpose: deletes a product from the Business's warehouse
	return void
	*/
	void deleteProduct(string product)
	{

		Product* check= bHouse.searchWarehouse(bHouse.getRoot(), product);
		if(check==NULL)
		{
			cout<<"This product does not exist."<<endl;
			return;
		}

		bHouse.deleteProduct(check);
	}

	/*
	function: checkBInventory
	purpose: prints the info of a product in the Business's warehouse
	return void
	*/
	void checkBInventory(string product)
	{
		Product* temp= bHouse.searchWarehouse(bHouse.getRoot(), product);

		if(temp==NULL)
		{
			cout<<"This product does not exist."<<endl;
			return;
		}

		bHouse.productInfo(temp->name);

	}

	/*
	function: shipProduct
	purpose: ships a selected number of a product to a store in the Business's StoreLL
	return void
	*/
	void shipProduct(string product, int numShipped, string storeName)
	{
		Product* ship= bHouse.searchWarehouse(bHouse.getRoot(), product);

		if(ship==NULL)
		{
			cout<<"Product not found."<<endl;
			return;
		}

		if(numShipped>0 && numShipped<= ship->quantity)
		{
			
			storeNode *check= stores.findStore(storeName);

			if(check==NULL)
			{
				cout<<"This store does not exist."<<endl;
				return;
			}else{
				ship->quantity-=numShipped;
				check->sHouse.addProduct(ship->name, ship->price, numShipped);

				if(ship->quantity==0)
				{
					bHouse.deleteProduct(ship);
				}
			}

		}else
		{
			cout<<"You either input an invalid shipping number, or there are not enough of that product"<<endl;
			return;
		}

	}

	/*
	function: businessMenu
	purpose: runs the certain business's menu and all of its own features
	return void
	*/
	void businessMenu()
	{
		while(true)
		{
			cout<<"1. Add product to Business Warehouse"<<endl;
			cout<<"2. Check a product's inventory."<<endl;
			cout<<"3. Ship product to store"<<endl;
			cout<<"4. Go to store."<<endl;
			cout<<"5. Create new store."<<endl;
			cout<<"6. Delete store."<<endl;
			cout<<"7. Print stores."<<endl;
			cout<<"8. Leave Business."<<endl;

			int choice;
			cin>>choice;
			switch(choice)
			{
				case 1:
				{
					//Add Product
					cin.clear();
					cin.ignore();

					int newPrice;
					int newQuantity;
					string newName;
					
					cout<<"New Product"<<endl;
					cout<<"Name:"<<endl;
					getline(cin, newName);
					cin.clear();
					cout<<"Price:"<<endl;
					cin>>newPrice;
					cin.clear();
					cout<<"quantity:"<<endl;
					cin>>newQuantity;
					cin.clear();

					addProduct(newName, newPrice, newQuantity);
					break;

				}
				case 2:
				{
					//Check inventory
					cin.clear();
					cin.ignore();

					string checkName;
					cout<<"Input the name of the product."<<endl;
					cin>>checkName;

					bHouse.productInfo(checkName);
					break;

				}
				case 3:
				{
					//ship product
					cin.clear();
					cin.ignore();

					string prodName;
					string storeName;
					int numShip;

					cout<<"Enter the name of the product you would like to ship."<<endl;
					getline(cin,prodName);
					cin.clear();
					cout<<"Enter the name of the store to ship to"<<endl;
					getline(cin,storeName);
					cin.clear();
					cout<<"Enter the number you would like to ship"<<endl;
					cin>>numShip;
					cin.clear();

					shipProduct(prodName, numShip, storeName);
					break;

				}
				case 4:
				{
					//go to store
					cin.clear();
					cin.ignore();

					cout<<"Enter the name of the store."<<endl;

					string sName;
					getline(cin, sName);
					cin.clear();

					storeNode* tempStore= stores.findStore(sName);

					if(tempStore==NULL)
					{
						cout<<"There is not a store under that name."<<endl;
						break;
					}

					tempStore->storeMenu();
					break;

				}
				case 5:
				{
					//create store

					cin.clear();
					cin.ignore();

					cout<<"Please input the name of the new store."<<endl;
					string newStore;
					getline(cin, newStore);
					cin.clear();

					stores.insertStore(newStore);
					break;

				}
				case 6:
				{
					//delete store
					cin.clear();
					cin.ignore();

					cout<<"Enter the name of the store to delete"<<endl;
					string toBeDel;

					getline(cin, toBeDel);

					stores.deleteStore(toBeDel);
					break;

				}
				case 7:
				{
					//print stores
					stores.printStores();
					break;

				}
				case 8:
				{
					//leave business
					cout<<"Returning to main menu..."<<endl;
					return;
				}
				default:
				{
					cout<<"Please choose a number between 1 and 5."<<endl;
					break;
				}
			}

		}
	}

		string getBusName()
		{
			return name;
		}




};



/*===========
	Driver
  ===========*/

class Driver
{
public:
	vector<Business> businessVec;

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
					cin.clear();
					cin.ignore();

					cout<<"Enter the name of the business you would like to enter."<<endl;
					string busName;
					getline(cin, busName);
					cin.clear();

					Business* temp=NULL;
					for(int i=0; i< businessVec.size(); i++)
					{
						if(businessVec[i].getBusName()==busName)
						{
							temp=&businessVec[i];
							break;
						}

					}

					if(temp==NULL)
					{
						cout<<"Business not found."<<endl;
						break;
					}

					temp->businessMenu();

					break;

				}
				case 2:
				{
					//Create Business
					cin.clear();
					cin.ignore();

					string newName;

					cout<<"Please enter the name of tbe business you would like to create."<<endl;
					getline(cin,newName);
					cin.clear();

					Business newBus(newName);

					businessVec.push_back(newBus);

					break;

				}
				case 3:
				{
					//Delete Business
					cin.clear();
					cin.ignore();
					string busToBeDel;

					cout<<"Input the name of the business you want to delete."<<endl;
					getline(cin, busToBeDel);

					for(int i=0; i< businessVec.size(); i++)
					{
						if(businessVec[i].getBusName()==busToBeDel)
						{
							businessVec.erase(businessVec.begin()+i);
							busToBeDel="";
							break;
						}

					}

					if(busToBeDel!="")
					{
						cout<<"Business not found."<<endl;
						break;
					}

					break;

				}
				case 4:
				{
					//Quit;
					cout<<"Goodbye."<<endl;
					exit(1);
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
	Driver d;
	d.runProgram();
};