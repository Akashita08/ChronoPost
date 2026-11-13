#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include<iomanip>
#include <stdexcept>
#include<limits>
using namespace std;
struct Dimension {
    string name;
    int timelineYear;
    double distanceFactor;
};
class ChronoPostException :public runtime_error {
  public:
    ChronoPostException(const string& message) : runtime_error(message) {}
};
class InvalidWeightException : public ChronoPostException {
  public:
    InvalidWeightException() : ChronoPostException("Invalid weight: Weight must be positive.") {}
};
class InvalidDimensionException : public ChronoPostException {
  public:
    InvalidDimensionException() : ChronoPostException("Invalid dimension: Dimension not found.") {}
};
class TemporalAnomalyException : public ChronoPostException {
  public:
    TemporalAnomalyException() : ChronoPostException("Temporal anomaly detected: Parcel cannot be sent to the past.") {}
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
    string getHomeDimension() const {
            return homeDimension;
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
     double distanceFactor;
     string status;
    public:
        Parcel(){
            parcelID=0;
            senderID=0;
            recipientName="Unknown";
            destinantion="Unknown";
            weight=0.0;
            distanceFactor=1.0;
            status="REGISTERED";
        }
        Parcel(int pid,int sid,string rname,string dest,double w ,double df=1.0){
            parcelID=pid;
            senderID=sid;
            recipientName=rname;
            destinantion=dest;
            weight=w;
            distanceFactor=df;
            status="REGISTERED";
        }
     
       virtual ~Parcel(){
        }
        virtual double calculateCharge() const{
            return weight*10.0 *distanceFactor;
        }

        int getId() const {
                return parcelID;
            }
        string getStatus() const {
                return status;
            }
        virtual  void display() const {
             cout<<left<<setw(12)<<parcelID<<setw(12)<<senderID<<setw(22)<<recipientName<<setw(22)<<destinantion<<setw(12)<<weight<<status<<fixed<<setprecision(2)<<calculateCharge()<<endl;
         }
         Parcel& operator++(){
            if(status=="REGISTERED") status = "DISPATCHED";
            else if(status=="DISPATCHED") status = "IN TRANSIT";
            else if(status=="IN TRANSIT") status = "DELIVERED";
            return *this;
         }
         friend void inspectParcel(const Parcel &p);
         friend class ChronoPostSystem;
         friend class ChronoPostAdmin;
};
class NormalParcel : public Parcel {
    public:
     NormalParcel(int id,int sid,string rname,string dest,double w , double df):Parcel(id,sid,rname,dest,w,df){
        
     }
     double calculateCharge() const override {
        return weight * 10.0 * distanceFactor;
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
        return weight * 5.0 * distanceFactor;
     }

};
class TimeBound : virtual public Parcel {
    public: 
     TimeBound(){}
     double urgencyCharge() const {
        return weight * 8.0 * distanceFactor;
     }
};
class FragileParcel : public Fragile {
   public:
    FragileParcel(int id,int sid,string rname,string dest,double w,double df):Parcel(id,sid,rname,dest,w,df){
        
     }
     double calculateCharge() const override {
        return weight * 10.0 * distanceFactor + protectionCharge();
    }
    void display() const override{
        cout<<"Fragile Parcel: ";
        Parcel::display();
    }
};
class TimeBoundParcel : public TimeBound {
    public:
     TimeBoundParcel(int id,int sid,string rname,string dest,double w,double df):Parcel(id,sid,rname,dest,w,df){
        
     }
     double calculateCharge() const override {
        return weight * 10.0 * distanceFactor + urgencyCharge();
    }
    void display() const override{
        cout<<"Time Bound Parcel: ";
        Parcel::display();
    }
};

class InterdimensionalParcel : public Fragile,public TimeBound {
    public:
     InterdimensionalParcel(int id,int sid,string rname,string dest,double w,double df):Parcel(id,sid,rname,dest,w,df){
        
     }
     double calculateCharge() const override {
        return weight * 10.0 * distanceFactor + protectionCharge() + urgencyCharge();
    }
    void display() const override{
        cout<<"Interdimensional Parcel: ";
        Parcel::display();
    }
};
class SpecialParcel : public Fragile,public TimeBound{
    public: 
     SpecialParcel(int id, int sid, string rname, string dest, double w, double df = 1.0)
    : Parcel(id, sid, rname, dest, w, df) {}
     void displaySpecial(){
        cout<<"Special Parcel: ";
        cout<<"Parcel ID"<< parcelID<<"Sender ID"<<senderID<<"Recipient Name"<<recipientName<<"Destination"<<destinantion<<"Weight"<<weight<<"Status"<<status<<endl;

     }
     
};
class ShippingBill {
    public:
     double amount;
     ShippingBill(double amt=0){
        amount=amt;
     }
     ShippingBill operator+(const ShippingBill &other) const {
        return ShippingBill(amount + other.amount);
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
        cout<<"Distance Factor: "<<p.distanceFactor<<endl;
     }
};
void inspectParcel(const Parcel &p){
    cout<<"Parcel ID: "<<p.parcelID<<endl;
    cout<<"Sender ID: "<<p.senderID<<endl;
    cout<<"Recipient Name: "<<p.recipientName<<endl;
    cout<<"Destination: "<<p.destinantion<<endl;
    cout<<"Weight: "<<p.weight<<endl;
    cout<<"Status: "<<p.status<<endl;
    cout<<"Distance Factor: "<<p.distanceFactor<<endl;
};
template<typename T>
void displayRecordCount(const vector<T>&records,const string & label){
    cout<<label<<":"<<records.size()<<endl;
}
class ChronoPostSystem {
    private:
        vector<Customer> customers;
        vector<Parcel*> parcels;
        vector<Dimension> dimensions;

        int nextCustomerID;
        int nextParcelID;

        const Dimension* findDimension(const string &name) const{
            for(const auto &d:dimensions){
                if(d.name==name){
                    return &d;
                }
            }
            return nullptr;
        }
        const Customer* findCustomer(int id) const{
            for(const auto &c:customers){
                if(c.getID()==id){
                    return &c;
                }
            }
            return nullptr;
        }
        void recordTracking(int parcelId, const string &event){
            ofstream file("tracking.txt",ios::app);
            if(file.is_open()){
                file<<"Parcel ID: "<<parcelId<<", Event: "<<event<<endl;
                file.close();
            }
            else{
                cout<<"\nUnable to open tracking file\n";
            }
        }

    public:
       ChronoPostSystem() {
            nextCustomerID = 1001;
            nextParcelID = 5001;
            dimensions.push_back({"Earth-Prime",2026,1.0});
            dimensions.push_back({"Future-Earth",2050,1.5});
            dimensions.push_back({"Neo-Terra",3026,2.5});
            dimensions.push_back({"Parallel-7",2026,3.0});
            loadData();

        }
        ~ChronoPostSystem() {
            for(auto p : parcels){
                delete p;
            }
        }

       void registerCustomer(){
        try {
            string name,home;
            cout<<"\nEnter customer name: ";
            getline(cin>>ws,name);
            if(name.empty()){
                throw runtime_error("Customer name cannot be empty.");
            }
            cout<<"\nAvailable Dimensions:\n";
            displayDimensions();
            cout<<"\nEnter home dimension: ";
            getline(cin>>ws,home);
            if(findDimension(home)==nullptr){
                throw InvalidDimensionException();
            }
            customers.emplace_back(nextCustomerID++,name,home);
            cout<<"\nCustomer registered successfully with ID: "<<nextCustomerID-1<<endl;
        }
       catch(const exception &e){
        cout<<"\n Registration failed: "<<e.what()<<endl;
       }
       }
       void registerDimension(){
        try {
            Dimension d;
            cout<<"\nEnter dimension name: ";
            getline(cin>>ws,d.name);
            if(d.name.empty()){
                throw runtime_error("Dimension name cannot be empty.");
            }
            if(findDimension(d.name)!=nullptr){
                throw runtime_error("Dimension already exists.");
            }
            cout<<"\nEnter timeline year: ";
            if(!(cin>>d.timelineYear)){
                throw runtime_error("Invalid input for timeline year.");
            }
            cout<<"\nEnter distance factor: ";
            if(!(cin>>d.distanceFactor)){
                throw runtime_error("Invalid input for distance factor.");
            }
            if(d.distanceFactor<=0){
                throw runtime_error("Distance factor must be positive.");
            }
            dimensions.push_back(d);
            cout<<"\nDimension registered successfully.\n";
        }
        catch(const exception &e){
            cout<<"\n Dimension registration failed: "<<e.what()<<endl;
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
        }
       

       }

       void createParcel(){
         try {
            if(customers.empty()){
                throw runtime_error("No customers registered. Please register a customer first.");
            }
            int senderID,type;
            string recipient,destination;
            double weight;
            displayCustomers();
            cout<<"\nEnter sender ID: ";
            if(!(cin>>senderID)){
                throw runtime_error("Invalid input for sender ID.");
            }
            const Customer* sender = findCustomer(senderID);
            if(sender==nullptr){
                throw runtime_error("Sender ID not found.");
            }
            cout<<"\nEnter recipient name: ";
            getline(cin>>ws,recipient);
            if(recipient.empty()){
                throw runtime_error("Recipient name cannot be empty.");
            }
            displayDimensions();
            cout<<"\nEnter destination dimension: ";
            getline(cin>>ws,destination);
            const Dimension* destDim = findDimension(destination);
            if(destDim==nullptr){   
                throw InvalidDimensionException();
            }
            const Dimension* senderDim = findDimension(sender->getHomeDimension());
            if(senderDim==nullptr){
                throw InvalidDimensionException();
            }
            if(destDim->timelineYear < senderDim->timelineYear){
                throw TemporalAnomalyException();
            }
            cout<<"\nEnter weight (kg): ";
            if(!(cin>>weight)){
                throw runtime_error("Invalid input for weight.");
            }
            if(weight<=0){
                throw InvalidWeightException();
            }
             cout<<"\nSelect parcel type:\n";
             cout<<"1. Normal Parcel\n";
             cout<<"2. Fragile Parcel\n";
             cout<<"3. Time Bound Parcel\n";
             cout<<"4. Interdimensional Parcel\n";   

             cout<<"Enter your choice: ";
             if(!(cin>>type)){
                throw runtime_error("Invalid input for parcel type.");
             }
             int id = nextParcelID++;
             double factor= destDim->distanceFactor;
        switch(type){
            case 1:
                parcels.push_back(new NormalParcel(id,senderID,recipient,destination,weight,factor));
                break;
            case 2:
                parcels.push_back(new FragileParcel(id,senderID,recipient,destination,weight,factor));
                break;
            case 3:
                parcels.push_back(new TimeBoundParcel(id,senderID,recipient,destination,weight,factor));
                break;
            case 4:
                parcels.push_back(new InterdimensionalParcel(id,senderID,recipient,destination,weight,factor));
                break;
            default:
              nextParcelID--; 
                throw ChronoPostException("Invalid parcel type selected.");
        }
        cout<<"\nParcel created successfully with ID: "<<id<<endl;
        cout<<"\nShipping Charge: "<<parcels.back()->calculateCharge()<<endl;
         }
         catch(const exception &e){
            cout<<"\n Parcel creation failed: "<<e.what()<<endl;
            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
         }
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
            displayRecordCount(customers, "Total customers");


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
            displayRecordCount(parcels, "Total parcels");
       }
       void displayDimensions() const {
            cout<<"\nRegistered Dimensions:\n";
            cout<<"\n"<<left<<setw(22)<<"Dimension Name"<<"Timeline Year"<<"Distance Factor"<<endl;
            for(const auto &d:dimensions){
                cout<<left<<setw(22)<<d.name<<d.timelineYear<<setw(12)<<d.distanceFactor<<endl;
            }
            displayRecordCount(dimensions, "Total dimensions");
       }
       void advanceParcel(){
        int id;
        cout<<"\nEnter parcel ID to advance: ";
        if(!(cin >> id)) {
    cout << "\nInvalid parcel ID.\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
}
        for(auto &p:parcels){
            if(p->getId()==id){
                ++(*p);
                cout<<"\nParcel status advanced to: "<<p->getStatus()<<endl;
                recordTracking(id, p->getStatus());
                return;
            }
        }
        cout<<"\nParcel not found\n";
       }
       void inspect(){
        int id;
        cout<<"\nEnter parcel ID to inspect: ";
       if(!(cin>>id)){
            cout<<"\nInvalid input for parcel ID.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            return;
        }
        for(const auto &p:parcels){
            if(p->getId()==id){
               inspectParcel(*p);
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
       void loadData(){
        ifstream CustomerFile("customers.txt");
        if(CustomerFile.is_open()){
            customers.clear();
            int id;
            string name,home;
            while(CustomerFile>>id>>quoted(name)>>quoted(home)){
                customers.emplace_back(id,name,home);
                if(id>=nextCustomerID){
                    nextCustomerID=id+1;
                }
            }
            CustomerFile.close();
       }
       ifstream dimensionFile("dimensions.txt");
       if(dimensionFile.is_open()){
        dimensions.clear();
       Dimension d;
        while(dimensionFile>>quoted(d.name)>>d.timelineYear>>d.distanceFactor){
            dimensions.push_back(d);
        }
        dimensionFile.close();
        if(dimensions.empty()){
            dimensions.push_back({"Earth-Prime",2026,1.0});
            dimensions.push_back({"Future-Earth",2050,1.5});
            dimensions.push_back({"Neo-Terra",3026,2.5});
            dimensions.push_back({"Parallel-7",2026,3.0});
        }
       }
       ifstream parcelFile("parcels.txt");
       if(parcelFile.is_open()){
        int id,sid;
        string type,recipient,destination,status;
        double weight,df;
        while(parcelFile>>id>>sid>>quoted(recipient)>>quoted(destination)>>weight>>df>>quoted(status)>>quoted(type)){
            Parcel *p=nullptr;
            if(type=="Normal"){
                p=new NormalParcel(id,sid,recipient,destination,weight,df);
            }
            else if(type=="Fragile"){
                p=new FragileParcel(id,sid,recipient,destination,weight,df);
            }
            else if(type=="TimeBound"){
                p=new TimeBoundParcel(id,sid,recipient,destination,weight,df);
            }
            else if(type=="Interdimensional"){
                p=new InterdimensionalParcel(id,sid,recipient,destination,weight,df);
            }
            if(p!=nullptr){
                p->status=status;
                parcels.push_back(p);
                if(id>=nextParcelID){
                    nextParcelID=id+1;
                }
            }
        }
        parcelFile.close();
    }
}

       void saveData() const {
        ofstream CustomerFile("customers.txt");
        if(CustomerFile.is_open()){
            for(auto it = customers.begin(); it != customers.end(); ++it){
                CustomerFile<<it->getID()<<" "<<quoted(it->getName())<<" "<<quoted(it->getHomeDimension())<<endl;
            }
            CustomerFile.close();
        }
        else cout<<"\nUnable to open customers.txt for writing\n";
        ofstream dimensionFile("dimensions.txt");
        if(dimensionFile.is_open()){
            for(auto it = dimensions.begin(); it != dimensions.end(); ++it){
                dimensionFile<<quoted(it->name)<<" "<<it->timelineYear<<" "<<it->distanceFactor<<endl;
            }
            dimensionFile.close();
        }
        else cout<<"\nUnable to open dimensions.txt for writing\n";
        ofstream parcelFile("parcels.txt");
        if(parcelFile.is_open()){
            for(auto it = parcels.begin(); it != parcels.end(); ++it){
                parcelFile<<(*it)->getId()<<" "<<(*it)->senderID<<" "<<quoted((*it)->recipientName)<<" "<<quoted((*it)->destinantion)<<" "<<(*it)->weight<<" "<<(*it)->distanceFactor<<" "<<quoted((*it)->status)<<" ";
              if(dynamic_cast<InterdimensionalParcel*>(*it))
                 parcelFile << quoted("Interdimensional") << endl;
              else if(dynamic_cast<FragileParcel*>(*it))
                  parcelFile << quoted("Fragile") << endl;
             else if(dynamic_cast<TimeBoundParcel*>(*it))
                   parcelFile << quoted("TimeBound") << endl;
            else if(dynamic_cast<NormalParcel*>(*it))
                  parcelFile << quoted("Normal") << endl;
            }
            parcelFile.close();
        }
        else cout<<"\nUnable to open parcels.txt for writing\n";
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
           if(!(cin >> choice)) {
    cout << "\nPlease enter a valid numeric choice.\n";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    continue;
}

           
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
                    saveData();
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
