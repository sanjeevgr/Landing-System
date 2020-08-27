//FLIGHT LANDING MANAGEMENT SYSTEM
//BY: SANJEEV GANGA RAJU
#include <iostream>
#include <cstdlib>
using namespace std;

class LandingTimes
{
private:
	class flight
	{
	public:
		flight* left;
		flight* right;
		flight* parent;
		int time;
		string flightNumber;
	};


public:
	flight* upNext;
	LandingTimes()
	{
		upNext = NULL;
	}
	bool isEmpty() const { return upNext == NULL; }
	void FLIGHT_DISPLAY(flight*);
	void FLIGHT_INSERT(int, string, int);
	flight* SUCCESSOR(flight*);
	flight* PREDECESSOR(flight*);
	void DELETE_FLIGHT(flight*);
	flight* SEARCH(flight*, string);

};

void LandingTimes::FLIGHT_INSERT(int d, string n, int k)
{
	flight* z = new flight();
	z->time = d;
	z->flightNumber = n;
	z->left = NULL;
	z->right = NULL;

	flight* y = NULL;
	flight* x = upNext;

	while (x != NULL)
	{
		y = x;
		if (z->time < x->time)
			x = x->left;
		else
			x = x->right;
	}

	z->parent = y;
	if (y == NULL)
		upNext = z;
	else if (z->time < y->time)
		y->left = z;
	else
		y->right = z;

    if(z!=upNext){
        flight* pre = PREDECESSOR(z);
        flight* suc = SUCCESSOR(z);
        int left = 0;
        int right = 0;
        if(z->left!=NULL){
            left = z->left->time;
        }
        if(z->right!=NULL){
            right = z->right->time;
        }
        if(((z->time-pre->time)<k)&&((suc->time-z->time)<k)){
            cout << "Access Granted: Flight Added!" << endl;
        }
        else{
            DELETE_FLIGHT(z);
            cout << "Access Denied: Time Slot Not Available!" << endl;
        }
    }
    else{
        cout << "Access Granted: Flight Added!" << endl;
    }
}

void LandingTimes::FLIGHT_DISPLAY(flight* x){
	if (x != NULL)
	{
		if (x->left) FLIGHT_DISPLAY(x->left);
		cout << "Flight Number: " << x->flightNumber << endl;
		cout << "Time Till Land: " << x->time << " Mins" << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		if (x->right) FLIGHT_DISPLAY(x->right);
	}


}

LandingTimes::flight* LandingTimes::SUCCESSOR(flight* x){
    if(x->right!=NULL){
        x = x->right;
        while (x->left != NULL){
        x = x->left;
        }
        return x;
    }
    else{
        flight* y = x->parent;
        while((y!=NULL)&&(x==y->right)){
            x=y;
            y=y->parent;
        }
        return y;
    }
}

LandingTimes::flight* LandingTimes::PREDECESSOR(flight* x){
    if(x->left!=NULL){
        x = x->left;
        while (x->right != NULL){
        x = x->right;
        }
        return x;
    }
    else{
        flight* y = x->parent;
        while((y!=NULL)&&(x==y->left)){
            x=y;
            y=y->parent;
        }
        return y;
    }
}

void LandingTimes::DELETE_FLIGHT(flight* x){
    flight* y = NULL;
    flight* z = NULL;
    if((x->left==NULL)||(x->right==NULL)){
        y=x;
    }
    else{
        y = SUCCESSOR(x);
    }

    if(y->left!=NULL){
        z = y->left;
    }
    else{
        z = y->right;
    }

    if(z!=NULL){
        z->parent = y->parent;
    }

    if(y->parent==NULL){
            upNext = z;
    }
    else{
        if(y==(y->parent->left)){
            y->parent->left = z;
        }
        else{
            y->parent->right = z;
        }
    }
    if(y!=x){
        x->time = y->time;
    }
}

LandingTimes::flight* LandingTimes::SEARCH(flight* x, string target){
    if(x == NULL || x->flightNumber == target){
        return x;
    }
    else if(x->flightNumber < target){
        return SEARCH(x->right, target);
    }
    else{
        return SEARCH(x->left, target);
    }
}

int main()
{
	LandingTimes flights;
	int choice, time, k;
	string number, input;
	cout << "Enter a desired 'time gap' value : " << endl;
    cin >> k;
	while (true)
	{
		cout << endl << endl;
		cout << "     FLIGHT LANDING SYSTEM " << endl;
		cout << " ----------------------------- " << endl;
		cout << " 1. Request a Land " << endl;
		cout << " 2. Cancel Landing Request " << endl;
		cout << " 3. Display Landing Queue " << endl;
		cout << " 4. Exit " << endl;
		cout << " Enter your choice : ";
		cin >> choice;
		switch (choice)
		{
		case 1: cout << " Enter time until land: ";
			cin >> time;
			cout << " Enter Flight Number: ";
			cin >> number;
			flights.FLIGHT_INSERT(time, number, k);
			break;
        case 2: cout << endl;
            cout << "Enter the flight number you want to delete : " << endl;
            cin >> input;
			flights.DELETE_FLIGHT(flights.SEARCH(flights.upNext, input));
			cout << "DELETED FLIGHT " << input << endl;
			break;
		case 3: cout << endl;
			cout << "    UPCOMING ARRIVALS " << endl;
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			flights.FLIGHT_DISPLAY(flights.upNext);
			break;
		case 4: system("pause");
			return 0;
			break;
		default:
			cout << "Invalid choice";
		}
	}
}
