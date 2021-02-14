//Vivek Bhandari
//ICS4U Summative
//November 12th, 2020
#include <iostream>
using namespace std;
#include <ctime>
#include <stdlib.h>
#include <ctime>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

struct HOTEL //declared a strcture to store multiple variables of different types used in the program
{
    int option, rooms;
    int random;
    string date, name, pin;
};
void totals (double *tot, char *type, int *people); //void function to calculate the total cost of the room per night
void totals (double *tot); //void function to add tax to the final cost of the room per night (function overload)
void pay(double *amount); //void function to receive payment from customer
int main()
{
    int vactot=0; //int variable to store number of rooms that are either booked or checked into (unavailable rooms)
    char type;
    int people;
    vector<int>random; //array to store booking pin
    vector<char>types; //array to store room type
    vector<int>peoples; //array to store number of people per room
    vector<string>date; //array to store checkin date
    vector<double>total; //array to store cost of room per night
    HOTEL hotel;
    srand (time(NULL));
    hotel.random=rand() % 999 + 100; //generates a random number when giving customers their booking pin
    start:
    double tot=0;
    ofstream obj13;
    obj13.open("vacant.txt",ios::app); //creates a file to store number of rooms that are either booked or checked into (unavailable rooms)
    obj13.close();
    cout<<"--------------------------------------"<<endl; //diaplays options to user
    cout<<"\t     Vivek's Hotel"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<"1. Book A Room"<<endl;
    cout<<"2. Check In"<<endl;
    cout<<"3. Check Out"<<endl;
    cout<<"4. Cancel Booking"<<endl;
    cout<<"5. End Session"<<endl;
    cout<<"--------------------------------------"<<endl;
    cout<<"Please select one of the options above"<<endl;
    cin>>hotel.option; //stores what option the user selected
    cin.ignore(); //flushes the stream
    if (hotel.option==1) //if statement that executes if if the user wants to book a room (entered 1)
    {
        cout<<"Enter Your Name"<<endl;
        getline(cin,hotel.name); //stores users name
        cout<<"How many rooms would you like to book"<<endl;
        cin>>hotel.rooms; //stores number of rooms the user wants to book
        string line3;
        ifstream obj14;
        obj14.open("vacant.txt",ios::in); //opens vacant.txt file to read from
        while (getline(obj14,line3)) //reads all lines from the file
        {
            vector<string> result3; //array to store the results at each line
            std::istringstream iss(line3);
            for(std::string line3; iss >> line3;)
                result3.push_back(line3);
                vactot=stoi(result3[0]); //sets vactot to the number of rooms that are either booked or checked into (unavailable rooms) which is the value in the [0] index in result3 array
        }
        vactot=vactot+hotel.rooms; //adds the number of rooms the user booked to vactot
        if (vactot>10)// if statement that executes the user trys to book more rooms than there are available (there are 10 aviliable rooms at the start)
        {
            vactot=vactot-hotel.rooms; ////subtracts the number of rooms the user booked to vactot as there arent that many rooms available
            cout<<"Sorry, we only have "<<10-vactot<<" rooms available."<<endl; //displays sorry message
            system("pause"); //pauses program (press any key to continue)
            system("cls"); //clears screen

            goto start; //jump statemnt that sends the user back to the start of the program
        }


        ofstream obj1;
        obj1.open("Bookings.txt",ios::app); //opens the Bookings.txt to write in
        for (int i=0; i<hotel.rooms; i++) //for loop that repeats based on the number of rooms the user wants to book
        {
            tot=0;
            roomtype:
            cout<<"Would you like to book a regular room(R) for $70 or a suite(S) for $100"<<endl;
            cin>>type;//stores what type of room the user wants in the variable type
            if (type=='R' || type=='r' || type=='S' || type=='s')
            {

            }
            else //else statment that executes if the user enters an invalid option (!= was not working on my mac)
            {
                cout<<"Sorry, please enter a valid option"<<endl; //displays sorry message
                goto roomtype; //jump statemnt that sends user to the part of the program where they can enetr a room type
            }
            people:
            cout<<"How many people will stay in this room, each person is an additional $15 (maximum of 4 people per room)"<<endl;
            cin>>people; //stores the number of people that will stay in the room
            if (people>=5 || people<1) //if statemnt that executes if the user wants less than one or more than 4 people in one room
            {
                cout<<"Sorry, please enter a valid option"<<endl; //displays sorry message
                goto people; //jump statemnt that sends user to the part of the program where they can enetr the number of people in the room
            }
            totals(&tot, &type, &people); //passes (by refrence) tot, roomtype, and number of people to tatals function that calculates the cost of the room per night
            totals(&tot); //passes (by refrence) tot tatals function that adds tax to the cost of the room per night
            types.push_back(type); //pushes back room type into the types array
            peoples.push_back(people); //pushes back the number of people in the room into the peoples array
            total.push_back(tot); //pushes back total after tax into the total array
            cout<<"What date will you be checking into this room (MM/DD/YYYY)"<<endl;
            cin>>hotel.date; //stores the date that the user will be checing into their room
            date.push_back(hotel.date); //pushes back the date that the user will be checing into their room into the total date
            hotel.random++; //incriments pin number so that no room is assignmed the same pin number
            cout<<"Thank you for booking a room at Vivek's Hotel! Please enter this pin ("<<hotel.random<<") when you are checking in"<<endl; //displays thank you message
            random.push_back(hotel.random); //pushes back the booking pin into the random array
            obj1<<random[i]<<" "; //writes booking pin to the Bookings.txt file
            obj1<<types[i]<<" "; //writes room type to the Bookings.txt file
            obj1<<peoples[i]<<" "; //writes number of people in the room to the Bookings.txt file
            obj1<<date[i]<<" "; //writes check in date to the Bookings.txt file
            obj1<<total[i]<<" "; //writes total after tax to the Bookings.txt file
            obj1<<hotel.name<<endl; //writes name to the Bookings.txt file
        }
        ofstream obj15;
        obj15.open("vacant.txt",ios::out);//opens vacant.txt file to write in
        obj15<<vactot<<endl; //writes the number of unaviliable rooms to the file
        obj15.close();
        obj1.close();
        system("pause");
        system("cls");
        goto start; //sends user back to the start of the program
    }
    else if (hotel.option==2) //else if statement that executes if the user wants to checkin (option 2)
    {
        string line;
        string close="***";
        int counter=0;
        ifstream obj2;
        obj2.open("Bookings.txt",ios::in); //opend Bookings.txt file to read from
        cout<<"Please enter a booking pin"<<endl; //asks user to enter their booking pin
        cin>>hotel.pin; //stores the booking pin the user entered
        vector<vector<string> >results; //stores result after each space
        while (getline(obj2,line))
        {
            vector<string> result; //stores result of each line
            std::istringstream iss(line);
            for(std::string line; iss >> line;)
                result.push_back(line);
                results.push_back(result);
            if (result[0] == hotel.pin) //if statement that executes if the booking pin entered in found in the bookings file (which is stored in result[0])
            {
                counter++; //adds one the int counter
                system("cls");
                cout<<"Thank you for checking in "<<result[5]<<endl; //displays the information of the room that the user checked into
                cout<<"--------------------------------------"<<endl;
                cout <<"Room type: "<<result[1] << '\n';
                cout <<"Number of People in the Room: "<<result[2] << '\n';
                cout <<"Check in Date: "<<result[3] << '\n';
                cout<<fixed;
                cout.precision(2);
                cout <<"Total Amount Due Per Night: $"<<result[4] << '\n';
                cout<<"--------------------------------------"<<endl;
                system("pause");
                system("cls");

                ofstream obj3;
                obj3.open("checkin.txt",ios::app); //opens a file named checkin.txt to write in
                obj3<<result[0]<<" "<<result[4]<<" "<<"CHECKED IN"<<" "<<endl; //writes the pin number, amount due per night, and CHECKED IN to the file
                obj3.close();
                for (int i=0; i<results.size(); i++){
                if (results[i][0] == hotel.pin){
                results[i][0] = close; //sets the information of the room checked into as "***"
                results[i][1] = close;
                results[i][2] = close;
                results[i][3] = close;
                results[i][4] = close;
                results[i][5] = close;
                }
            }
            }
        }
        int co=0;
        ifstream obj6;
        obj6.open("Bookings.txt",ios::in); //opens Bookings.txtfile to read from
        while (getline(obj6,line))
        {
            co++; //stores number of lines in the Bookings.txt file
        }

            ofstream obj7;
            obj7.open("Bookings.txt",ios::out); //opens Bookings.txtfile to write in
            for (int i=0; i<co; i++){
            for(int j=0; j<6; j++){
                obj7 << results[i][j] << " "; //rewrites the file with the new information
                }
                    obj7<<"\n";
                }
        obj6.close();
        if (counter==0) //if statement that executes if counter is still zero (meaning that the booking pin that the user entered was not found in the Bookings.txt file)
        {
            cout<<"Sorry, this pin number was not found."<<endl; //displays sorry message
        }
        system("pause");
        system("cls");
        goto start; //sends the user to the start of the program

    }
    else if (hotel.option==3) //else if statement that executes if the user wants to check out (option 3)
    {
        string line2;
        int counter2=0;
        ifstream obj4;
        obj4.open("checkin.txt",ios::in); //opens checkin.txt file to read from
        cout<<"Please enter a booking pin"<<endl;
        cin>>hotel.pin;

        vector<vector<string> >results2;
        while (getline(obj4,line2))
        {
            vector<string> result2;
            std::istringstream iss(line2);
            for(std::string line2; iss >> line2;)
                result2.push_back(line2);
                results2.push_back(result2);
            for (int i=0; i<results2.size(); i++){
            if (results2[i][0] == hotel.pin)
            {
                counter2++;
                stringstream geek(results2[i][1]); //converts the amount the room cost per night from a string to a double (becuse everything stored in a file is a string)
                double amount=0;
                geek>>amount; //sets the double amount to the total cost of the toom after tax
                pay(&amount); //passes amount (by refrence) to the pay function
                cout<<"Thank you for choosing Vivek's Hotel, come again soon!"<<endl; //displays thank you message
                results2[i][0] = "---"; //sets the booking pin to ---
                results2[i][1] = "---"; //sets the cost of the room per night to ---
                results2[i][2] = "CHECKED"; //changes checked in to checked out
                results2[i][3] = "OUT";
                string line4;
                ifstream obj16;
                obj16.open("vacant.txt",ios::in); //opens vacant.txt file to read from
                while (getline(obj16,line4))
                {
                    vector<string> result4;
                    std::istringstream iss(line4);
                    for(std::string line4; iss >> line4;)
                        result4.push_back(line4);
                        vactot=stoi(result4[0]);
                        vactot=vactot-1; //subtracts 1 from vactot (meaning that there is one more room aviliavle to book)
                        ofstream obj17;
                    obj17.open("vacant.txt",ios::out); //opens vacant.txt file to write in
                    obj17<<vactot<<endl; //writs the new value of vactot to the file
                    obj17.close();
                }
            }
            }
        }

        int cou=0;
        ifstream obj8;
        obj8.open("checkin.txt",ios::in);
        while (getline(obj8,line2))
        {
            cou++; //stores number of lines in the checkin.txt file
        }
            ofstream obj9;
            obj9.open("checkin.txt",ios::out);
            for (int x=0; x<cou; x++){
            for(int y=0; y<4; y++){
                obj9 << results2[x][y] << " "; //rewrites the file with the updated results
                }
                    obj9<<"\n";
                }
        obj8.close();
        if (counter2==0)//if statement that executes if counter2 is still equal to 0 (meaning that the booking pin that the user entered was not found in the checkin.txt file)
        {
            cout<<"Sorry, this pin number was not found."<<endl;
        }
        system("pause");
        system("cls");
        goto start; //sends the use back to the start of the program
    }
    else if (hotel.option==4) //else if statement that executes if the user wants to cancel their booking(option 4)
    {
        string line;
        string close="***";
        int counter3=0;
        ifstream obj10;
        obj10.open("Bookings.txt",ios::in); //opens Bookings.txt file to read from
        cout<<"Please enter a booking pin"<<endl; //asks the user to enter the booking pin of the room they would like to cancel the booking of
        cin>>hotel.pin;
        vector<vector<string> >results;
        while (getline(obj10,line))
        {
            vector<string> result;
            std::istringstream iss(line);
            for(std::string line; iss >> line;)
                result.push_back(line);
                results.push_back(result);
            if (result[0] == hotel.pin) //if statement the executes of the user pin entred was found in the Bookings.txt file
            {
                counter3++; //adds 1 to counter3
            for (int i=0; i<results.size(); i++){
                if (results[i][0] == hotel.pin){
                results[i][0] = close; //sets the information of the room cancelled as "***"
                results[i][1] = close;
                results[i][2] = close;
                results[i][3] = close;
                results[i][4] = close;
                results[i][5] = close;
                }
            }
            string line5;
                ifstream obj18;
                obj18.open("vacant.txt",ios::in); //opens vacant.txt file to read from
                while (getline(obj18,line5))
                {
                    vector<string> result5;
                    std::istringstream iss(line5);
                    for(std::string line5; iss >> line5;)
                        result5.push_back(line5);
                        vactot=stoi(result5[0]);
                        vactot=vactot-1; //subtracts 1 from vactot (meaning that there is one more room aviliavle to book)
                        ofstream obj19;
                    obj19.open("vacant.txt",ios::out); //opens the vacant.txt file to write in
                    obj19<<vactot<<endl; //writs the new value of vactot to the file
                    obj19.close();
                }
            }
        }
        int co=0;
        ifstream obj11;
        obj11.open("Bookings.txt",ios::in);
        while (getline(obj11,line))
        {
            co++; //stores the number of line in the Bookings.txt file
        }

            ofstream obj12;
            obj12.open("Bookings.txt",ios::out); //opens the Bookings.txt file to write in
            for (int i=0; i<co; i++){
            for(int j=0; j<6; j++){
                obj12 << results[i][j] << " "; //rewrites the file with the updated results
                }
                    obj12<<"\n";
                }
        obj11.close();
        if (counter3==0) //if statement that executes if counter3 is still equal to 0 (meaning that the booking pin that the user entered was not found in the checkin.txt file)
        {
            cout<<"Sorry, this pin number was not found."<<endl; //displays sorry message
        }
        else //if statement that executes if counter3 is not equal to 0 (meaning that the booking pin that the user entered was  found in the checkin.txt file)
        {
            cout<<"Your Booking Has Been Cancelled"<<endl; //displays that the booiking has been cancelled
        }
        system("pause");
        system("cls");
        goto start; //sends the use back to the start of the program

    }
    else if (hotel.option==5) //if statement that executes if the user wants to exid the program (option 5)
    {
        cout<<"Thank you for choosing Vivek's Hotel, come again soon!"<<endl; //displays thank you message
        return 0; //ends program
    }
    else //if statement that executes if the user entered a number that was not 1,2,3,4 or 5
    {
        cout<<"Sorry, please enter a valid option"<<endl; //prompts the user to enter a valid option
        goto start; //sends user to the start of the program
    }
}
void totals (double *tot, char *type, int *people)
{

    if (*type=='R' || *type=='r') //if statement that executes if the user wanted a regular room
        {
            *tot=*tot+70; //adds 70 to tot (because the cost of a regular room per night is $70)
        }
    else if (*type=='S' || *type=='s') //if statement that executes if the user wanted a suite
        {
            *tot=*tot+100; //adds 70 to tot (because the cost of a suite per night is $100)
        }
    *tot=*tot+(15*(*people)); //adds 15 times number of peoples to tot because there is an additional charge of $15 per person
}
void totals (double *tot)
{
    *tot=*tot*1.13; //multiples tot by 1.13 (this adds tax to the total cost of the room per night)
}
void pay(double *amount)
{
    night:
    int nights;
    double t, owed;
    cout<<"How many nights did you stay in this room?"<<endl;
    cin>>nights; //stores the number of nights the user sated in their room
    if (nights==0 || nights<1) //if statement that executes if the user enters a number less than 1
    {
        cout<<"Sorry, please enter a valid numder."<<endl; //prompts user to enter a valid number
        goto night; //jump statement that allows user to enter the number of nights the stayed again
    }
    t=0; //sets t to 0
    owed=*amount*nights; //sets owed to cost per night times number of nights (total cost)
    cout<<fixed;
    cout.precision(2); //amount are displayed with 2 decimal points
    cout<<"Amount due: $"<<(*amount)*nights<<endl; //displays total amount due
    do
    {
    owed=owed-t;
    cout<<"Please enter the amount you are paying: \n$";
    cin>>t; //get input for the amount tendered
    if (t<owed)//if statement that will execute if the amount tendered is less than the amount owed
    {
        cout<<"You need to pay $"<<owed-t<<" more"<<endl; //displayed the amount the customer still owes
    }
    }while(t<owed); //do while loop that repeats untill the user tenders an amount more than the amount due

    double changedue=(owed-t)*-1; //sets chage due to owed minus the amount tendered *-1 (to covert the change to a positive number)
        cout<<fixed;
        cout.precision(2); //money is printed with 2 decimals
        cout<<"Change due: $"<<changedue<<endl;//displays the change due to the user
}



