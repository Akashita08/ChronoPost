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
    protected:
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
        Parcel(int pid,int sid,string rname,string dest,double w){
            parcelID=pid;
            senderID=sid;
            recipientName=rname;
            destinantion=dest;
            weight=w;
            status="Registered";
        }
     
       virtual ~Parcel(){
        }
        virtual double calculateCharge() const{
            return weight*10.0;
        }

        int getId() const {
                return parcelID;
            }
        string getStatus() const {
                return status;
            }
        virtual  void display() const {
             cout<<left<<setw(12)<<parcelID<<setw(12)<<senderID<<setw(22)<<recipientName<<setw(22)<<destinantion<<setw(12)<<weight<<status<<endl;
         }
         Parcel& operator++(){
            if(status=="REGISTERED") status = "DISPATCHED";
            return *this;
         }
         friend void inspectPracel(const Parcel &p);
         friend class ChronoPostSystem;
         friend class ChronoPostAdmin;
};
class NormalParcel : public Parcel {
    public:
     NormalParcel(int id,int sid,string rname,string dest,double w):Parcel(id,sid,rname,dest,w){
        
     }
     double calculateCharge() const override {
        return weight * 10.0;
    }
    void display() const override{
        cout<<"Normal Parcel: ";
        Parcel::display();
    }
};
class Fragile: virtual public Parcel {
    public:
     Fragile() {}
     double protectionCharge() const {
        return weight * 5.0;
     }

};
class TimeBound : virtual public Parcel {
    public: 
     TimeBound(){}
     double urgencyCharge() const {
        return weight * 8.0;
     }
};
class FragileParcel : public Fragile {
   public:
    FragileParcel(int id,int sid,string rname,string dest,double w):Parcel(id,sid,rname,dest,w){
        
     }
     double calculateCharge() const override {
        return weight * 10.0 + protectionCharge();
    }
    void display() const override{
        cout<<"Fragile Parcel: ";
        Parcel::display();
    }
};
class TimeBoundParcel : public TimeBound {
    public:
     TimeBoundParcel(int id,int sid,string rname,string dest,double w):Parcel(id,sid,rname,dest,w){
        
     }
     double calculateCharge() const override {
        return weight * 10.0 + urgencyCharge();
    }
    void display() const override{
        cout<<"Time Bound Parcel: ";
        Parcel::display();
    }
};

class InterdimensionalParcel : public Fragile,public TimeBound {
    public:
     InterdimensionalParcel(int id,int sid,string rname,string dest,double w):Parcel(id,sid,rname,dest,w){
        
     }
     double calculateCharge() const override {
        return weight * 10.0 + protectionCharge() + urgencyCharge();
    }
    void display() const override{
        cout<<"Interdimensional Parcel: ";
        Parcel::display();
    }
};
class SpecialParcel : public Fragile,public TimeBound{
    public: 
     SpecialParcel(int id,int sid,string rname,string dest,double w){
        parcelID=id;
        senderID=sid;
        recipientName=rname;
        destinantion=dest;
        weight=w;
        status="Registered";
        
     }
     void displaySpecial(){
        cout<<"Special Parcel: ";
        cout<<"Parcel ID"<< parcelID<<"Sender ID"<<senderID<<"Recipient Name"<<recipientName<<"Destination"<<destinantion<<"Weight"<<weight<<"Status"<<status<<endl;

     }
     
};
class EmptyClass {};
class ShippingBill {
    public:
     double amount;
     ShippingBill(double amt=0){
        amount=amt;
     }
    operator double() const {
        return amount;
    }


};
class Weight{
    public:
     double kg;
     Weight(double w=0){
        kg=w;
     }
     operator double() const {
        return kg;
}
};
class ChronoPostAdmin{
    public:
     void showPrivateDetails(const Parcel &p){
        cout<<"Parcel ID: "<<p.parcelID<<endl;
        cout<<"Sender ID: "<<p.senderID<<endl;
        cout<<"Recipient Name: "<<p.recipientName<<endl;
        cout<<"Destination: "<<p.destinantion<<endl;
        cout<<"Weight: "<<p.weight<<endl;
        cout<<"Status: "<<p.status<<endl;
     }
};
void inspectPracel(const Parcel &p){
    cout<<"Parcel ID: "<<p.parcelID<<endl;
    cout<<"Sender ID: "<<p.senderID<<endl;
    cout<<"Recipient Name: "<<p.recipientName<<endl;
    cout<<"Destination: "<<p.destinantion<<endl;
    cout<<"Weight: "<<p.weight<<endl;
    cout<<"Status: "<<p.status<<endl;
};
class ChronoPostSystem {
    private:
        vector<Customer> customers;
        vector<Parcel*> parcels;
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
        ~ChronoPostSystem() {
            for(auto p : parcels){
                delete p;
            }
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
        int senderID,type;
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
        cout<<"\nSelect parcel type:\n";
        cout<<"1. Normal Parcel\n";
        cout<<"2. Fragile Parcel\n";
        cout<<"3. Time Bound Parcel\n";
        cout<<"4. Interdimensional Parcel\n";   

        cout<<"Enter your choice: ";
        cin>>type;
        int id = nextParcelID++;
        switch(type){
            case 1:
                parcels.push_back(new NormalParcel(id,senderID,recipient,destination,weight));
                break;
            case 2:
                parcels.push_back(new FragileParcel(id,senderID,recipient,destination,weight));
                break;
            case 3:
                parcels.push_back(new TimeBoundParcel(id,senderID,recipient,destination,weight));
                break;
            case 4:
                parcels.push_back(new InterdimensionalParcel(id,senderID,recipient,destination,weight));
                break;
            default:
                cout<<"\nInvalid parcel type\n";
                return;
        }

        
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
                p->display();
            }
       }
       void advanceParcel(){
        int id;
        cout<<"\nEnter parcel ID to advance: ";
        cin>>id;
        for(auto &p:parcels){
            if(p->getId()==id){
                ++(*p);
                cout<<"\nParcel status advanced to: "<<p->getStatus()<<endl;
                return;
            }
        }
        cout<<"\nParcel not found\n";
       }
       void inspect(){
        int id;
        cout<<"\nEnter parcel ID to inspect: ";
        cin>>id;
        for(const auto &p:parcels){
            if(p->getId()==id){
                inspectPracel(*p);
                ChronoPostAdmin admin;
                admin.showPrivateDetails(*p);
                return;
            }
        }
        cout<<"\nParcel not found\n";
       }
       void showBill(){
        double a,b;
        cout<<"\nEnter first amount: ";
        cin>>a;
        cout<<"\nEnter second amount: ";
        cin>>b;
        ShippingBill bill1(a),bill2(b);
        ShippingBill total = bill1 + bill2;
        cout<<"\nTotal bill: "<<static_cast<double>(total)<<endl;
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
            cout << "7. Advance Parcel Status\n";
            cout << "8. Inspect Parcel\n";
            cout << "9. Show Shipping Bill\n";
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
                case 7:
                    advanceParcel();
                    break;
                case 8:
                    inspect();
                    break;
                case 9:
                    showBill();
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
