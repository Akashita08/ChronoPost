#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;
struct Dimension {
    string name;
    int timelineYear;
    double distanceFactor;
};
class Customer{
    private:
      int customerID;
      string name;
      string homeDimension;
    public:
      Customer(){
        customerID = 0;
        name="Unknown";
        homeDimension="Earth";
      }
      Customer(int id,string n,string dim){
        customerID=id;
        name=n;
        homeDimension=dim;
      }
      Customer(const Customer &c){
        customerID=c.customerID;
        name=c.name;
        homeDimension=c.homeDimension;
      }
      ~Customer(){
      }
      int getID() const {
        return customerID;
      }
     string getName() const {
            return name;
        }
     void display() const {
        cout<<left<<setw(12)<<customerID<<setw(22)<<name<<homeDimension<<endl;
     }

};
class Parcel {
    private:
     int parcelID;
     int senderID;
     string recipientName;
     string destinantion;
     double weight;
     string status;
    public:
        Parcel(){
            parcelID=0;
            senderID=0;
            recipientName="Unknown";
            destinantion="Unknown";
            weight=0.0;
            status="Registered";
        }
        Parcel(int pid,int sid,string rname,string dest,double w,string s){
            parcelID=pid;
            senderID=sid;
            recipientName=rname;
            destinantion=dest;
            weight=w;
            status=s;
        }
     
        ~Parcel(){
        }
        int getId() const {
                return parcelID;
            }
        
         void display() const {
             cout<<left<<setw(12)<<parcelID<<setw(12)<<senderID<<setw(22)<<recipientName<<setw(22)<<destinantion<<setw(12)<<weight<<status<<endl;
         }
};
class ChronoPostSystem {
    private:
        vector<Customer> customers;
        vector<Parcel> parcels;
        vector<Dimension> dimensions;

        int nextCustomerID;
        int nextParcelID;
    public:
       ChronoPostSystem() {
            nextCustomerID = 1001;
            nextParcelID = 5001;
            dimensions.push_back({"Earth-Prime",2026,1.0});
            dimensions.push_back({"Future-Earth",2050,1.5});
            dimensions.push_back({"Neo-Terra",3026,2.5});
            dimensions.push_back({"Parallel-7",2026,3.0});

        }
       void registerCustomer(){
        string name,home;
        cout<<"\nEnter customer name: ";
        getline(cin>>ws,name);
        cout<<"\nAvailable Dimensions:\n";
        for(int i =0;i<dimensions.size();i++){
            cout<<i+1<<"."<<dimensions[i].name<<endl;

        }
        cout<<"Enter home dimesnion";
        getline(cin>>ws,home);
        bool found = false;
        for(const auto &d :dimensions){
            if(d.name==home){
                found=true;
                break;
            }
        }
        if(!found){
            cout<<"\nInvalid dimension\n";
            return ;
        }
        customers.emplace_back(nextCustomerID++,name,home);
        cout<<"\nCustomer registered successfully with ID: "<<nextCustomerID-1<<endl;
       }
       void registerDimension(){
        Dimension d ;
        cout<<"\nEnter dimension name: ";
        getline(cin>>ws,d.name);
        for(const auto &existing:dimensions){
            if(existing.name==d.name){
                cout<<"\nDimension already exists\n";
                return;
            }
        }
        cout<<"\nEnter timeline year: ";
        cin>>d.timelineYear;
        cout<<"\nEnter distance factor: ";
        cin>>d.distanceFactor;
        if(d.distanceFactor<=0){
            cout<<"\nDistance factor must be positive\n";
            return;
        }
        dimensions.push_back(d);
        cout<<"\nDimension registered successfully\n";

       }
       void createParcel(){
        if(customers.empty()){
            cout<<"\nNo customers registered. Please register a customer first.\n";
            return;
        }
        int senderID;
        string recipient;
        string destination;
        double weight;
        cout<<"\nnRegistered Customers:\n";
        displayCustomers();
        cout<<"\nEnter sender ID: ";
        cin>>senderID;
        bool customerFound=false;
        for(const auto &c:customers){
            if(c.getID()==senderID){
                customerFound=true;
                break;
            }
        }
        if(!customerFound){
            cout<<"\nSender ID not found\n";
            return;
        }
        cout<<"Enter recipient name";
        getline(cin>>ws,recipient);
        cout<<"Available Dimensions:\n";
        for(const auto&d : dimensions){
            cout<<d.name<<"Year: "<<d.timelineYear<<endl;

        }
        cout<<"Enter destination dimension: ";
        getline(cin>>ws,destination);
        bool destinationFound=false;
        for(const auto &d:dimensions){
            if(d.name==destination){
                destinationFound=true;
                break;
            }
        }
        if(!destinationFound){
            cout<<"\nDestination dimension not found\n";
            return;
        }
        cout<<"Enter weight of the parcel: ";
        cin>>weight;
        if(weight<=0){
            cout<<"\nWeight must be positive\n";
            return;
        }
        parcels.emplace_back(nextParcelID++,senderID,recipient,destination,weight);
        cout<<"\nParcel created successfully with ID: "<<nextParcelID-1<<endl;
        }
        void displayCustomers() const {
            if(customers.empty()){
                cout<<"\nNo customers registered\n";
                return;
            }
            cout<<"\n"<<left<<setw(12)<<"Customer ID"<<setw(22)<<"Name"<<"Home Dimension"<<endl;
            for(const auto &c:customers){
                c.display();
            }


       }
       void displayParcels() const {
            if(parcels.empty()){
                cout<<"\nNo parcels created\n";
                return;
            }
            cout<<"\n"<<left<<setw(12)<<"Parcel ID"<<setw(12)<<"Sender ID"<<setw(22)<<"Recipient Name"<<setw(22)<<"Destination"<<setw(12)<<"Weight"<<"Status"<<endl;
            for(const auto &p:parcels){
                p.display();
            }
       }
       void displayDimensions() const {
            cout<<"\nRegistered Dimensions:\n";
            cout<<"\n"<<left<<setw(22)<<"Dimension Name"<<"Timeline Year"<<"Distance Factor"<<endl;
            for(const auto &d:dimensions){
                cout<<left<<setw(22)<<d.name<<d.timelineYear<<setw(12)<<d.distanceFactor<<endl;
            }
       }
       void menu (){
        int choice;
        do{
              cout << "\n";
            cout << "========================================\n";
            cout << "           C H R O N O P O S T          \n";
            cout << "     THE INTERDIMENSIONAL POSTAL SERVICE\n";
            cout << "========================================\n";

            cout << "1. Register Customer\n";
            cout << "2. Register New Dimension\n";
            cout << "3. Create New Parcel\n";
            cout << "4. View Customers\n";
            cout << "5. View Parcels\n";
            cout << "6. View Dimensions\n";
            cout << "0. Exit ChronoPost\n";

            cout << "\nEnter your choice: ";
            cin >> choice;
           
            switch (choice) {
                case 1:
                    registerCustomer();
                    break;
                case 2:
                    registerDimension();
                    break;
                case 3:
                    createParcel();
                    break;
                case 4:
                    displayCustomers();
                    break;
                case 5:
                    displayParcels();
                    break;
                case 6:
                    displayDimensions();
                    break;
                case 0:
                    cout << "\nExiting ChronoPost. Goodbye!\n";
                    break;
                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }
        }
        while (choice != 0);

       }


};
int main() {
    ChronoPostSystem system;
    system.menu();
    return 0;
}
