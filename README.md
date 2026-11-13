CHRONOPOST
The Interdimensional Postal Service
Phase 1: Core Foundation and Basic System Implementation
Objective:
To develop the initial structure of ChronoPost, an interdimensional postal management application using C++. This phase focuses on implementing customer registration, dimension management and parcel registration while demonstrating the fundamental concepts of object-oriented programming.
Project Description
ChronoPost is a fictional interdimensional postal service designed to facilitate parcel delivery across different timelines and dimensions. The application allows users to register customers, define new dimensions, create parcels and view registered information.
Each customer is assigned a unique identification number, while every parcel receives a separate tracking identification number. The system maintains information about the sender, recipient, destination dimension, parcel weight and delivery status.
Functionalities Implemented
Customer Registration: Registers customers with unique IDs and their respective home dimensions.
Dimension Management: Maintains predefined dimensions and allows administrators to register new dimensions.
Parcel Registration: Creates parcels by accepting sender details, recipient information, destination and weight.
Customer Records: Displays all registered customers and their information.
Parcel Records: Displays registered parcels along with their identification numbers and delivery status.
Dimension Records: Displays available dimensions, timeline years and distance factors.
Interactive Menu: Provides a menu-driven interface for accessing different application functionalities.
OOP Concepts Demonstrated
1. Classes and Objects
Three major classes are implemented: Customer, Parcel and ChronoPostSystem. Objects of these classes represent individual customers, parcels and the complete postal management system.
2. Structures
A Dimension structure is used to group related information such as dimension name, timeline year and distance factor.
3. Constructors
Default constructors initialize objects with default values, parameterized constructors initialize objects with user-provided information, and copy constructors create objects using existing objects.
4. Destructors
Destructors are implemented to demonstrate automatic object destruction when objects go out of scope.
5. Encapsulation
Data members of Customer and Parcel classes are declared private and accessed through public member functions.
6. Functions and References
Separate member functions handle registration, validation and display operations. Constant references are used while traversing collections to avoid unnecessary object copying.
7. Arrays and STL Containers
Arrays and collections are used to organize and access application data. The vector container maintains dynamically growing collections of customers, parcels and dimensions.
8. Manipulators
The setw() and left manipulators are used to format tabular output and improve readability.
Technologies Used
Programming Language: C++
Compiler: GCC / MinGW
IDE: Visual Studio Code
Standard: C++17
Libraries: iostream, vector, string and iomanip
Conclusion
The first phase successfully establishes the foundation of ChronoPost. The application supports customer registration, dimension management and parcel creation through a structured, menu-driven interface.
The implementation establishes the basic class architecture and data management mechanisms required for integrating advanced object-oriented programming concepts in subsequent phases.

Phase 2: Advanced Object-Oriented Programming
Objective
To extend the ChronoPost application by implementing advanced object-oriented programming concepts, including inheritance, multiple inheritance, virtual inheritance, operator overloading, friend functions, friend classes, type conversion and runtime polymorphism.
Implementation Details
1. Inheritance
A base class named Parcel is created, containing common parcel attributes and operations. Derived classes NormalParcel, FragileParcel, TimeSensitiveParcel and InterdimensionalParcel extend its functionality.
2. Multiple Inheritance
The classes Fragile and TimeBound represent different characteristics of special parcels. InterdimensionalParcel inherits from both classes to demonstrate multiple inheritance.
3. Virtual Inheritance
Fragile and TimeBound virtually inherit from Parcel. The SpecialParcel class inherits from both, demonstrating how virtual inheritance prevents duplicate instances of a common base class in a diamond inheritance hierarchy.
4. Friend Function
The function inspectParcel() is declared as a friend of Parcel. It accesses private parcel information for inspection purposes.
5. Friend Class
ChronoPostAdmin is declared as a friend class of Parcel. It can access private parcel attributes to perform administrative inspection.
6. Unary Operator Overloading
The prefix increment operator is overloaded using a member function. The expression ++parcel advances the parcel through its delivery statuses:
REGISTERED → DISPATCHED → IN TRANSIT → DELIVERED.
7. Binary Operator Overloading
The addition operator is overloaded in the ShippingBill class. It combines two shipping bill amounts and returns a new ShippingBill object containing the total.
8. Type Conversion
The Weight class demonstrates user-defined-to-basic conversion through a conversion operator that converts a Weight object into a double value.
9. Virtual Functions and Runtime Polymorphism
The calculateCharge() and display() functions are declared virtual in the Parcel base class and overridden in derived classes. Base-class pointers are used to invoke the appropriate derived-class implementations at runtime.
10. Empty Class
An EmptyClass is created without any data members or member functions. Its size is examined using sizeof() to demonstrate that an empty class occupies non-zero storage.
Functionalities Added
Multiple parcel categories.
Category-specific shipping charge calculations.
Parcel status advancement.
Administrative parcel inspection.
Friend function-based parcel inspection.
Combined shipping bill calculation.
Virtual inheritance demonstration.
Basic-to-user-defined and user-defined-to-basic conversion foundations.
Conclusion
The second phase enhances ChronoPost through advanced object-oriented programming techniques. Inheritance and polymorphism allow different parcel categories to exhibit specialized behaviour, while friend functions, operator overloading and virtual inheritance demonstrate additional C++ capabilities.
The application now has a more extensible architecture and is ready for further development involving exception handling, delivery calculations and data persistence.
Phase 3: Exception Handling and Intelligent Delivery Management
Objective
To enhance the ChronoPost application by implementing exception handling, custom exceptions, input validation, dimensional delivery charge calculations and temporal anomaly detection.
Implementation Details
1. Exception Handling
Try-catch blocks are implemented to handle invalid inputs and prevent unexpected program termination. Throw statements are used whenever an invalid operation is detected.
2. Custom Exception Classes
The application introduces custom exception classes:
ChronoPostException: Base exception class for application-related errors.
InvalidWeightException: Handles zero or negative parcel weights.
InvalidDimensionException: Handles invalid dimension selections.
TemporalAnomalyException: Handles delivery attempts to an earlier timeline.
3. Dimensional Delivery Charge Calculation
Each dimension has an associated distance factor. The delivery charge is calculated according to parcel weight, base shipping rate and destination distance factor.
Different parcel categories have additional charges for fragile handling and time-sensitive delivery.
4. Temporal Anomaly Detection
The system compares the timeline year of the sender's home dimension with the destination dimension. If the destination timeline is earlier than the sender's timeline, a TemporalAnomalyException is thrown.
5. Input Validation
Validation mechanisms are implemented for customer IDs, parcel weights, destination dimensions, parcel categories and numeric inputs.
6. Type Conversion
The Weight class demonstrates conversion from a basic data type to a user-defined type through its constructor and conversion from a user-defined type to a basic data type through a conversion operator.
Functionalities Added
Dimension-based shipping charge calculation.
Temporal anomaly detection.
Custom exception handling.
Invalid parcel weight detection.
Invalid destination detection.
Customer ID validation.
Parcel category validation.
Improved input error handling.
Conclusion
The third phase improves the reliability and intelligence of ChronoPost. Exception handling ensures that invalid operations are managed safely, while dimensional charge calculations and temporal anomaly detection introduce application-specific functionality.
The application is now prepared for the final phase, which will focus on persistent data storage, file operations, templates and STL-based data management.
Phase 4 — File Handling, Templates and STL
The final phase focuses on data persistence and efficient collection management.
Features Implemented
Implemented file handling using ifstream and ofstream.
Added permanent storage for customer, dimension and parcel records.
Implemented data loading when the application starts.
Implemented automatic data saving when the application exits.
Added parcel tracking history using file append mode.
Used std::quoted to preserve names containing spaces.
Implemented a function template to display collection counts.
Used STL algorithms such as find_if() and for_each().
Used iterators to traverse collections during file operations.
Restored the correct derived parcel types when loading saved records.
Files Generated
customers.txt
dimensions.txt
parcels.txt
tracking.txt
Final Outcome
ChronoPost now supports persistent data storage, parcel tracking, object-oriented parcel management, exception handling and STL-based collection operations.

