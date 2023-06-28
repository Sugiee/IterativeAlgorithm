// Satheyaseelan Sugieethan
// ID: 20318670
//--------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
#include <iostream> // Required for cout
#include <conio.h> // Required for !kbhit
//--------------------------------------------------------------------------------------------------------------------------------------
// Templated Class 'iterativeAlgorithmObject' for calculations and function call to 2nd functor for monitoring
//--------------------------------------------------------------------------------------------------------------------------------------
template <typename T, typename ObjectType, int sizeOfArray>
class iterativeAlgorithmObject {
    public:
        iterativeAlgorithmObject(T const *_inputDataArray, T const _maximumError) : maximumError(_maximumError) {   //constructor
                                                                        for (int i = 0; i < sizeOfArray; ++i) {
                                                                            inputDataArray[i] = _inputDataArray[i];}
                                                                        }
        ~iterativeAlgorithmObject() {};                                                                             // Destructor
        iterativeAlgorithmObject(const iterativeAlgorithmObject& obj) {inputDataArray = obj.inputDataArray;         // Copy Constructor
                                                                         maximumError = obj.maximumError;}
        iterativeAlgorithmObject& operator=(const iterativeAlgorithmObject& obj) {if(this==&obj) return(*this);     // Assignment
                                                                                  inputDataArray = obj.inputDataArray;
                                                                                  maximumError = obj.maximumError;
                                                                                  return(*this);}

        T operator()() const {     //Functor
            T error(1e50);
            T result(0);
            int iterationNumber(0);     // If client needs, this variable can also be templated but not needed right now
            ObjectType REPORT_OBJECT;   //Make object
                                           
            while(error>maximumError && !kbhit()){  // kbhit allows loop to be terminated when any key pressed
                // Do the calculations and evaluate the latest values of result and error
                ++ iterationNumber;

                // Please select either test case 1 or test case 2 by commenting/uncommenting equation !!
                // Test case 1:
                error = inputDataArray[iterationNumber] - inputDataArray[iterationNumber + 1];
                // Test case 2: (to test termination of code if stuck in loop)
                //error = error/1;

                result = error;
                // Report on progress here
                REPORT_OBJECT(result, maximumError, iterationNumber); // Call functor to print in 'report' struct
            }
            return (error);
         }
                // Setters and Getters if there is need to view/change private variable value
        T get_maximumError() {return maximumError;}                                     // get
        void set_maximumError(T _maximumError) {maximumError = _maximumError;}          // set
                // Didn't set/get the inputDataArray as in real world cases the data would be passed in through a separate text file
                // but could be added if specific client requests that ability 
    private:
        double inputDataArray[sizeOfArray], maximumError;
};
//--------------------------------------------------------------------------------------------------------------------------------------
// Struct to report the values when functor called
//--------------------------------------------------------------------------------------------------------------------------------------
struct report { //used struct as no private variables needed as only printing values that are passed to it.
    report(){}                  // constructor
    ~report() {};               // destructor
    report (const report& Arc); // copy constructor
    report & operator=(const report& obj) {if(this==&obj) return(*this); return(*this);} // Assignment

    void operator()(const double result, const double maximumError, const int iterations) const {
        std::cout << "Result:" << result << "\t\t" << "Maximum Error:" << maximumError<< "\t\t"
                  << "Iterations:" << iterations << "\n";
            }; // Functor to print values
};
//--------------------------------------------------------------------------------------------------------
// Main program to demonstrate the use of 'report' object and ability to terminate code
//--------------------------------------------------------------------------------------------------------
int main () {
    double INPUT_DATA_ARRAY [15] = {100000000, 50000000, 600000, 80000, 9000, 5000,
                                    4000, 3750, 3700, 3595, 3500, 290, 34, 29, 14};
    double maximumError = 10;
                                // Call parameterised  constructor and fill template types
    iterativeAlgorithmObject <double, report,15> obj(INPUT_DATA_ARRAY, maximumError);
    obj();  // Call functor of class 'iterativeAlgorithmObject'
}
//--------------------------------------------------------------------------------------------------------
// Test1 - To test passing data of array and the code stopping when error becomes smaller then MaxError
// Code stops when Result becomes smaller then maxError
// maximumError = 10
// INPUT_DATA_ARRAY [15] = {100000000, 50000000, 600000, 80000, 9000, 5000,
//                          4000, 3750, 3700, 3595, 3500, 290, 34, 29, 14};
//
// Successful output of function when:
//--------------------------------------------------------------------------------------------------------
// Result:4.94e+007                Maximum Error:10                Iterations:1
// Result:520000           Maximum Error:10                Iterations:2
// Result:71000            Maximum Error:10                Iterations:3
// Result:4000             Maximum Error:10                Iterations:4
// Result:1000             Maximum Error:10                Iterations:5
// Result:250              Maximum Error:10                Iterations:6
// Result:50               Maximum Error:10                Iterations:7
// Result:105              Maximum Error:10                Iterations:8
// Result:95               Maximum Error:10                Iterations:9
// Result:3210             Maximum Error:10                Iterations:10
// Result:256              Maximum Error:10                Iterations:11
// Result:5                Maximum Error:10                Iterations:12
//--------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------
// Test 2 - To test termination of code when any keystroke entered if stuck in loop
// maximumError = 10
// INPUT_DATA_ARRAY [] = not needed for this test
//
// Successful output of function when:
//--------------------------------------------------------------------------------------------------------
// Result:1e+050           Maximum Error:10                Iterations:1
// Result:1e+050           Maximum Error:10                Iterations:2
// Result:1e+050           Maximum Error:10                Iterations:3
// Result:1e+050           Maximum Error:10                Iterations:4
// Result:1e+050           Maximum Error:10                Iterations:5
// Result:1e+050           Maximum Error:10                Iterations:6
// Result:1e+050           Maximum Error:10                Iterations:7
// Result:1e+050           Maximum Error:10                Iterations:8
// Result:1e+050           Maximum Error:10                Iterations:9
// Result:1e+050           Maximum Error:10                Iterations:10
// Result:1e+050           Maximum Error:10                Iterations:11
// Result:1e+050           Maximum Error:10                Iterations:12
// Result:1e+050           Maximum Error:10                Iterations:13
// Result:1e+050           Maximum Error:10                Iterations:14
// Result:1e+050           Maximum Error:10                Iterations:15
// Result:1e+050           Maximum Error:10                Iterations:16
// Result:1e+050           Maximum Error:10                Iterations:17
// Result:1e+050           Maximum Error:10                Iterations:18
// Result:1e+050           Maximum Error:10                Iterations:19
// Result:1e+050           Maximum Error:10                Iterations:20
// ect. till keystroke pressed
//--------------------------------------------------------------------------------------------------------