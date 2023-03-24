#include <iostream>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <windows.h>
using namespace std;

//this is used to display success and error messages in different colours
HANDLE color_of_texts =GetStdHandle(STD_OUTPUT_HANDLE);

fstream file1,file2;
//an array that I use to store id from file to check user input/new id is used by another student
string *arr = new string[50];

//int size = 0;//the size of students that registered in a student file
string Name,L_Name,ID,Department,Age;
//These are the functions that I use for different purpose
void home_page();
void display_student_information();
void register_student();
void update_student_information();
void search_student();
void display_instructor_info();
void display_course_info();
string is_id_exist();


struct Student{
    string Name;
    string L_Name;
    string ID;
    string Department;
    int gpa;
    int Age = 0;
};
Student *s1 = new Student[100];
struct Instructor{
    string Name;
    string F_Name;
    string ID;
     int Age = 0;
};

/**this register_student() function works like this
 * 1.it store all Id's of registered students in an array called arr[] this is to make easier to check if id is already exist
 * 2.and again it open student.txt in append mode to write/register students into the file
 * 3.when user prompt to Enter Id it uses the array arr[] which previously stores all the id's that exist
 * 4.and then using for() loop and if() statement it checks one user input Id to all the id's already in use
 * 5.if id is not taken by another student it continues and ask students department
 * 6.then by giving equal space it writes all the information of students in to a file and the user is registered.
*/
void register_student() {
    bool is_exist = false;
    int tries = 0;
    string line;
    //string *arr = new string[50];

    file1.open("student.txt", ios::in); // Open the file for reading data from the beginning
//we open file1 in read mode to collect all the student id from a file
    int size = 0;
    if (file1.is_open()) {
        //string Name, L_Name, ID, Department;
        int Age;
        while (getline(file1, line)) {
            stringstream ss(line);
            ss >> Name >> L_Name >> ID >> Department >> Age;
            arr[size] = ID;
            size++;
        }
        file1.close();

    }


file1.open("student.txt",ios::app);
    if (file1.is_open()) {
        int number_Of_Users;
        cout << "How many students you want to register: ";
        cin >> number_Of_Users;
       // file2 << left << setw(20) << "First Name" << setw(20) << "Last Name" << setw(15) << "ID" << setw(25) << "Department" << setw(10) << "Age" << endl;
        for (int i = 0; i < number_Of_Users; i++) {
            cout << "Enter Student First Name: ";
            cin >> s1[i].Name;
            cout << "Enter Student Last Name: ";
            cin >> s1[i].L_Name;
            int j = 0;
// allowed to try 3x to ender id that doesn't exist


            while( tries != 3){
                if(tries == 0){
                    cout << "Enter Student ID: ";
                    cin >> s1[i].ID;
                }else{
                    cout << "ID Already Exist Please Enter New Student ID: ";
                    cin >> s1[i].ID;
                }

                for(int j = 0; j<size; j++ ){
                    if(arr[j] == s1[i].ID){
                        is_exist = true;
                        tries++;
                        break;
                    }else{
                        is_exist = false;
                    }
                }
                if(!is_exist){
                    break;
                }
                }
           if(is_exist){
               SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_INTENSITY);
               cout<<"\n\n\t\t-------WARNING:Too Many Tries please Try Again Latter!-------\n\n";
               SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

               break;}

            cout << "Enter Student department: ";
            cin >> s1[i].Department;
            cout << "Enter Student Age: ";
            cin >> s1[i].Age;

            file1 <<left << setw(20) << s1[i].Name << setw(20) << s1[i].L_Name << setw(15) << s1[i].ID << setw(25) << s1[i].Department << setw(10) << s1[i].Age << endl;

            if (i == 0){
                SetConsoleTextAttribute(color_of_texts, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout << "\n Successful " << i + 1 << " Student registered.\n\n";
                SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else{
                SetConsoleTextAttribute(color_of_texts, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "\n Successful " << i + 1 << " Student's registered.\n\n";
                SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

            }

        }
        file1.close();
        home_page();
    }

}




void display_student_information() {
    ifstream file2("student.txt", ios::in);
    if (file2.is_open()) {
        string line;
        // Display table header
        cout << "--------------------------------------------------------------------------------\n";
        cout << "N.O\t| First Name\t| Last Name\t| ID\t\t| Department\t| Age\t|\n";
        cout << "--------------------------------------------------------------------------------\n";
        int No=0;
        while (getline(file2, line)) {

                stringstream ss(line);
                string fname, lname, id, dept, age;
                // Extract data from each line
                ss >> fname >> lname >> id >> dept >> age;
                // Display data in tabular format
                cout <<No+1<< ".\t| " << left << setw(10) << fname << "\t| " << left << setw(12) << lname << "\t| " << left
                     << setw(12) << id << "\t| " << left << setw(12) << dept << "\t| " << left << setw(5) << age
                     << "\t| \n";
                cout << "--------------------------------------------------------------------------------\n";

            No++;
        }
    }


    file2.close();
    home_page();
}



void display_instructor_info(){
    /*
    file1.open("instructor.txt",ios::app);
    file1 <<left << setw(20) << "Abebe" << setw(20) << "Lemma" << setw(15) << "1001" << setw(25) << "CS"<< setw(10) << "45" << endl;
    file1 <<left << setw(20) << "Alemu" << setw(20) << "Feleke" << setw(15) << "1002" << setw(25) << "ACC"<< setw(10) << "55" << endl;
    file1 <<left << setw(20) << "Lemlem" << setw(20) << "G/Micael" << setw(15) << "1003" << setw(25) << "ACC"<< setw(10) << "49" << endl;
    file1 <<left << setw(20) << "Fikadu" << setw(20) << "Mekonnen" << setw(15) << "1004" << setw(25) << "CS"<< setw(10) << "47" << endl;
    file1 <<left << setw(20) << "Girum" << setw(20) << "Belete" << setw(15) << "1005" << setw(25) << "ACC"<< setw(10) << "58" << endl;
    file1 <<left << setw(20) << "Girma" << setw(20) << "Wondesen" << setw(15) << "1006" << setw(25) << "CS"<< setw(10) << "68" << endl;
        file1.close();*/
    file1.open("instructor.txt",ios::in);
    if(file1.is_open()){
        string line;
        // Display table header
        cout<<"\n\t\t\t*****Instructor Information*****\n\n";
        cout << "--------------------------------------------------------------------------------\n";
        cout << "N.O\t| First Name\t| Last Name\t| ID\t\t| Department\t| Age\t|\n";
        cout << "--------------------------------------------------------------------------------\n";
        int No=0;
        while (getline(file1, line)) {
//use if i != 0 because I don't need the first line from file it help me to jump the first line

            stringstream ss(line);
            string fname, lname, id, dept, age;
            // Extract data from each line
            ss >> fname >> lname >> id >> dept >> age;
            // Display data in tabular format
            cout <<No+1<< ".\t| " << left << setw(10) << fname << "\t| " << left << setw(12) << lname << "\t| " << left
                 << setw(12) << id << "\t| " << left << setw(12) << dept << "\t| " << left << setw(5) << age
                 << "\t| \n";
            cout << "--------------------------------------------------------------------------------\n";

            No++;
        }
    }
    file1.close();
    home_page();
}


void display_course_info(){
    /*
    file1.open("course.txt",ios::app);
    file1 <<left << setw(40) << "Introduction_To_C++" << setw(15) << "C-2001" << setw(25) << "4"<< endl;
    file1 <<left << setw(40) << "Linear_Algebra"  << setw(15) << "C-2002" << setw(25) << "4" << endl;
    file1 <<left << setw(40) << "Social_Anthropology" << setw(15) << "C-2003" << setw(25) << "3" << endl;
    file1 <<left << setw(40) << "Advanced_Database" << setw(15) << "C-2004" << setw(25) << "4" << endl;
    file1 <<left << setw(40) << "Object_Oriented_Programming"<< setw(15) << "C-2005" << setw(25) << "3"<< endl;
    file1 <<left << setw(40) << "Economics"  << setw(15) << "C-2006" << setw(25) << "3" << endl;
    file1 <<left << setw(40) << "Operating_System"  << setw(15) << "C-2006" << setw(25) << "3" << endl;
    file1 <<left << setw(40) << "Information_Retrieval" << setw(15) << "C-2006" << setw(25) << "3" << endl;
    file1.close();*/
    file1.open("course.txt",ios::in);

    if(file1.is_open()){
        string line;
        // Display table header
        cout<<"\n\t\t\t*****Course Information*****\n\n";
        cout << "-------------------------------------------------------------------------------------\n";
        cout <<"N.O"<< ".\t| " << left << setw(30) << "Course Title" << "\t| " << left << setw(20) << "Course ID" << "\t| " << left
             << setw(10) << "Credit.Hr" << "| \n";
        //cout << "N.O\t| Course Title\t\t\t| Course ID\t\t\t| Credit.Hr |\t\t\t|\n";
        cout << "-------------------------------------------------------------------------------------\n";
        int No=0;
        while (getline(file1, line)) {

            stringstream ss(line);
            string courseTitle, courseID, credit_hr;
            // Extract data from each line
            ss >> courseTitle >> courseID >> credit_hr;
            // Display data in tabular format
            cout <<No+1<< ".\t| " << left << setw(30) << courseTitle << "\t| " << left << setw(20) << courseID << "\t| " << left
                 << setw(10) << credit_hr << "| \n";
            cout << "-------------------------------------------------------------------------------------\n";

            No++;
        }
    }
    file1.close();
    home_page();
}






/**I use This is_id_exist() function to check if the id is already used by other student's
 * this is how it works
 * 1.when the update function starts to update the id of students it call this function
 * 2.after this function called it collect all the id's from student.txt file and stores it on an array
 * 3.and by using for loop it checks one user input id with the array that stores all the id's that used by other students
 * 4.after checking if user input is is not used by other students it return the new id else it return a string "0"
 * 5.when update function gets the new returned id it continue the updating or if it gets the return "0" it stop the updating progress
 * */
string is_id_exist(){
    fstream f1;
    f1.open("student.txt", ios::in);//read mode
    string lines_from_file;
    bool is_id_exist ;
    int size = 0;
    int try1 = 0;
    string First_Name,Last_Name,ID,Department,Age;
    //this while loop help me to collect all the id used by other student for checking if new id is existed
    while(getline(f1,lines_from_file)){
        stringstream ss(lines_from_file);
        ss>>First_Name>>Last_Name>>ID>>Department>>Age;

        //I use this array because I need to check the id when Student are updating id to remove repitition
        arr[size] = ID;
        size++;
    }
    f1.close();
    string id;
    /*
    for(int i = 0; i<size; i++){
        cout<<arr[i]<<endl;
    }*/
    while (try1 !=3){
        if(try1 == 0){
            cout<<"Enter Student ID: ";
            cin>>id;
        }
        else{
            cout<<"ID Already Exist Enter Student ID: ";
            cin>>id;
        }

        for(int i =0; i<size; i++){
            if(id == arr[i]){
                is_id_exist =true;
                try1++;
                break;
            }else{
                is_id_exist = false;
            }
        }
        if(!is_id_exist)
            break;
    }
    if(!is_id_exist ){
       // cout<<"\n\nis is Not used";
        return id;
    }
    else{
        string x ="0";
        cout<<"\nYou Have Tried 3 times please Try again latter";
        return x;
    }

}



void update_student_information(){
    //when updating ID I need to check id is not going to repeat
    //I have is_id_exist function if the user input id exists it return a string "0"
    string return_value ="0";

    // cout<<is_id_exist()<<endl<<return_value<<endl;
    int choose,size;
    bool is_the_id_exist = false;
    bool is_updated = false;
    string user_input_id,lines_from_file;
    //string return_value ="0";
    file1.open("student.txt", ios::in);//read
    file2.open("temp.txt",ios::app);//write

    if(file1.is_open() && file2.is_open()){
        cout<<"Enter student ID To Perform Update: ";
        cin>>user_input_id;
        cout<<"Searching";
        for (int i = 0; i < 3; i++) {
            cout << ".";
            //cout.flush();
            sleep(1);
        }
        cout << "\n";

        string temp_firstN, tempLastN,tempId,tempDep,tempAge;
        string First_Name,Last_Name,ID,Department,Age;
        while(getline(file1,lines_from_file)){
            stringstream ss(lines_from_file);
            //stringstream ss1(lines_from_file);
            ss>>First_Name>>Last_Name>>ID>>Department>>Age;
            temp_firstN=First_Name;
            tempLastN = Last_Name;
            tempId=ID;
            tempDep=Department;
            tempAge= Age;

            if(user_input_id != ID){

                file2 <<left << setw(20) << First_Name << setw(20) << Last_Name << setw(15) << ID << setw(25) << Department << setw(10) << Age << endl;
            } else{
                is_the_id_exist = true;
                cout<<"Success:Id Found.";
                cout<<"\n\n\t\t####### Welcome To Update Page ########\n";
                cout<<"\n\t\t********Which Part you want to update*******"<<endl;
                cout<<"---------------------------------------------------------------"<<endl;
                cout<<"press 1 For Full Update"<<endl;
                cout<<"press 2 For First Name Update"<<endl;
                cout<<"press 3 For Last Name Update"<<endl;
                cout<<"press 4 For ID Update"<<endl;
                cout<<"press 5 For Department Update"<<endl;
                cout<<"press 6 For Age Update"<<endl;
                cout<<"---------------------------------------------------------------"<<endl;
                cout<<"Select the one to Perform an update: ";
                cin>>choose;
                switch (choose) {

                    case 1:
                        cout<<"\n\n*********Please Enter Your Information Correctly To Update*********\n"<<endl;
                        cout<<"Enter Student First Name: ";
                        cin>>First_Name;
                        cout<<"Enter Student Last Name: ";
                        cin>>Last_Name;

                        ID = is_id_exist();
                       // cout<<ID<<endl<<return_value<<endl;
                        if(ID != return_value){
                            is_updated = true;
                            cout<<"Enter Student Department: ";
                            cin>>Department;
                            cout<<"Enter Student Age: ";
                            cin>>Age;
                            file2 <<left << setw(20) << First_Name << setw(20) << Last_Name << setw(15) << ID << setw(25) << Department << setw(10) << Age << endl;
                            break;
                        }else{
                            is_updated = false;
                            file2 <<left << setw(20) << temp_firstN <<setw(20) << tempLastN << setw(15) << tempId << setw(25) << tempDep << setw(10) << tempAge << endl;
                        }
                        break;
                    case 2:
                        cout<<"Enter Student First Name: ";
                        cin>>First_Name;
                        is_updated = true;
                        file2 <<left << setw(20) << First_Name << setw(20) << Last_Name << setw(15) << ID << setw(25) << Department << setw(10) << Age << endl;
                        break;

                    case 3:
                        is_updated = true;
                        cout<<"Enter Student Last Name: ";
                        cin>>Last_Name;
                        file2 <<left << setw(20) << First_Name << setw(20) << Last_Name << setw(15) << ID << setw(25) << Department << setw(10) << Age << endl;
                        break;
                    case 4:
                        ID = is_id_exist();
                        if(ID != return_value){
                            is_updated = true;
                            file2 <<left << setw(20) << First_Name << setw(20) << Last_Name << setw(15) << ID << setw(25) << Department << setw(10) << Age << endl;}
                        else{
                            is_updated = false;
                            file2 <<left << setw(20) << temp_firstN <<setw(20) << tempLastN << setw(15) << tempId << setw(25) << tempDep << setw(10) << tempAge << endl;
                        }
                        break;
                    case 5:
                        is_updated = true;
                        cout<<"Enter Student Department: ";
                        cin>>Department;
                        file2 <<left << setw(20) << First_Name << setw(20) << Last_Name << setw(15) << ID << setw(25) << Department << setw(10) << Age << endl;
                        break;
                    case 6:
                        is_updated = true;
                        cout<<"Enter Student Age: ";
                        cin>>Age;
                        file2 <<left << setw(20) << First_Name << setw(20) << Last_Name << setw(15) << ID << setw(25) << Department << setw(10) << Age << endl;
                        break;
                }
                if(is_updated){
                    SetConsoleTextAttribute(color_of_texts, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                    cout<<"\nUpdating";
                    for (int i = 0; i < 3; i++) {
                        cout << ".";
                        //cout.flush();
                        sleep(1);
                    }
                    cout << "\n\n\t\tUpdate:Successful.\n";

                    SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                }else{
                    SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_INTENSITY);
                    cout << "\n\n\t\tUpdate:UnSuccessful Because Existed ID Used.";
                    SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

                }


            }
        }
        /** I use this code after user enter An ID and if that ID is not existed in student information
         *if the user input id contain a student information it perform an update otherwise it delete the temp.txt file
         * and close the opened files and close the update function and prompts the user to try again or to go back to the home page
        */
        if(!is_the_id_exist){
            file1.close();
            file2.close();
            remove("student.txt");
            rename("temp.txt","student.txt");

            SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout<<"\n\n\t\tError: Unable To Perform Update B/C ID Does Not Exist";
            SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            int ch;
            cout<<"\n\n----------------------------------------\n";
            cout<<"\nPress 0 For Try Again.\n";
            cout<<"Press 1 To GO Back\n";
            cout<<"\n----------------------------------------\n";
            cout<<"Choose One To Continue: ";
            cin>>ch;
            switch(ch){
                case 0:
                    update_student_information();
                    break;
                case 1:
                    home_page();
                    break;

            }
        }else{
            file1.close();
            file2.close();
            remove("student.txt");
            rename("temp.txt","student.txt");
            home_page();

        }

    }

}
void delete_student_information(){
    file1.open("student.txt",ios::in);
    file2.open("temp.txt",ios::app);
    bool is_the_id_exist = false;
    bool is_deleted = false;
    string First_Name,Last_Name,ID,Department,Age;


    if(file1.is_open() && file2.is_open()){
        string lines_from_file,user_input_id;
        cout<<"Enter The ID Of The Student You Want To Delete: ";
        cin>>user_input_id;
        while(getline(file1,lines_from_file)){
            stringstream ss(lines_from_file);
            ss>>First_Name>>Last_Name>>ID>>Department>>Age;
            if(ID != user_input_id){
                file2 <<left << setw(20) << First_Name << setw(20) << Last_Name << setw(15) << ID << setw(25) << Department << setw(10) << Age << endl;

            }else{
                is_the_id_exist = true;
                char choose;

                cout<<"Success:The Student Is Found. \nThe Student Information Is: ";
                cout<<"\n\t\t#########################";
                cout<<"\n\t\t# First Name: "<<First_Name<<"\t#"<<endl;
                cout<<"\t\t# Last Name: "<<Last_Name<<"\t#"<<endl;
                cout<<"\t\t# ID: "<<ID<<"\t        #"<<endl;
                cout<<"\t\t# Department: "<<Department<<"        #"<<endl;
                cout<<"\t\t# Age: "<<Age<<" \t        #"<<endl;
                cout<<"\t\t#########################\n";
                cout<<"\nare you sure you want to Delete? Y/N: ";
                cin>>choose;
                if(choose == 'y' || choose == 'Y'){

                    is_deleted = true;
                }else if(choose == 'n' || choose == 'N'){

                    is_deleted = false;
                    file2 <<left << setw(20) << First_Name << setw(20) << Last_Name << setw(15) << ID << setw(25) << Department << setw(10) << Age << endl;

                }

            }

        }
        //cout<<endl<<boolalpha<<is_the_id_exist<<endl<<boolalpha<<is_deleted<<endl;
        if(!is_the_id_exist){
            file1.close();
            file2.close();
            remove("student.txt");
            rename("temp.txt","student.txt");
            SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout<<"\nError:There Is No Student Represented By That ID.\n";
            SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

            home_page();
        }else{
            file1.close();
            file2.close();
            remove("student.txt");
            rename("temp.txt","student.txt");
        }

         if( is_deleted){
                 SetConsoleTextAttribute(color_of_texts, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            cout<<"\nSuccess:The Student Information Successfully Deleted.\n";
            SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);


            home_page();
        }else if( !is_deleted){
            SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout<<"\nDeleting Student information Terminated.\n";
            SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

            home_page();
        }
        }

}

//we can make our search engine to search by student students by First_Name,Last_Name,ID,Department And by Age
//for now not to make the code longer we only apply search by ID
void search_student() {
    file1.open("student.txt", ios::in);
    if (file1.is_open()) {
        string user_input_id;
        bool is_student_found = false;
        cout << "Enter the ID of student you want to search: ";
        cin >> user_input_id;
        string line;
        int size = 0;
        string name, fname, id, department, age;
        while (getline(file1, line)) {
            stringstream ss(line);
            ss >> name >> fname >> id >> department >> age;
            if (user_input_id == id) {
                is_student_found = true;
                SetConsoleTextAttribute(color_of_texts, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "\nSuccess Student Found:\n\n";
                SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                SetConsoleTextAttribute(color_of_texts, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                cout << "#################################\n";
                cout<<  "#  Search results:-\t\t#\n";
                cout<<  "#                  \t\t#\n";
                cout << "#  First Name: " << name << "\t\t#" << endl;
                cout << "#  Last Name: " << fname << "\t\t#" << endl;
                cout << "#  Student ID: " << id << "\t\t#" << endl;
                cout << "#  Department: " << department << "\t\t#" << endl;
                cout << "#  Student Age: " << age << "\t\t#" << endl;
                cout << "#################################\n";
                SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;
            }
        }
        if (!is_student_found) {
            file1.close();
            SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << "\nFaild:There is no student information by that ID"<<endl;
            SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            int ch;
            cout << "\n----------------------------------------\n";
            cout << "\nPress 0 For Try Again.\n";
            cout << "Press 1 To GO Back\n";
            cout << "\n----------------------------------------\n";
            cout << "Choose One To Continue: ";
            cin >> ch;
            switch (ch) {
                case 0:
                    search_student();
                    break;
                case 1:
                    home_page();
                    break;
            }

        } else {
            file1.close();
            int ch;
            cout << "\n\n----------------------------------------\n";
            cout << "\nPress 0 To Search Again.\n";
            cout << "Press 1 To GO Back\n";
            cout << "\n----------------------------------------\n";
            cout << "Choose One To Continue: ";
            cin >> ch;
            switch (ch) {
                case 0:
                    search_student();
                    break;
                case 1:
                    home_page();
                    break;

            }
        }
    }
}
void developed_by(){

    SetConsoleTextAttribute(color_of_texts, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout<<"\n\n\t\t\t\t\t\t      **************DEVELOPERS*************** \n\n";

    cout << "\t\t\t\t\t\t --------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t NAME" << "\t\t\t|\t ID" << endl;
    cout << "\t\t\t\t\t\t --------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t Biruktawit Amde" << "\t|\t RDCS-135-21A" << endl;
    cout << "\t\t\t\t\t\t --------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t Enaya Kebadu" << "\t\t|\t RDCS-139-21A" << endl;
    cout << "\t\t\t\t\t\t --------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t Etsehiwot Dereje " << "\t|\t RDCS-140-21A" << endl;
    cout << "\t\t\t\t\t\t --------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t Euel Suraphal" << "\t\t|\t RDCS-142-21A" << endl;
    cout << "\t\t\t\t\t\t --------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t Mikias Moges" << "\t\t|\t RDCS-161-21A" << endl;
    cout << "\t\t\t\t\t\t --------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t Sara Feleke" << "\t\t|\t RDCS-180-21A" << endl;
    cout << "\t\t\t\t\t\t --------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t Tomas Tesema" << "\t\t|\t RDCS-190-21A" << endl;
    cout << "\t\t\t\t\t\t --------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t Yadenno Galassa" << "\t|\t RDCS-191-21A" << endl;
    cout << "\t\t\t\t\t\t --------------------------------------------" << endl;
    SetConsoleTextAttribute(color_of_texts, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    int ch;
    cout << "\n\n----------------------------------------\n";
            cout << "\nPress 1 To GO Back.\n";
            cout << "Press 2 To Exit.\n";
            cout << "\n----------------------------------------\n";
            cout << "Choose One To Continue: ";
            cin >> ch;
            switch (ch) {
                case 1:
                    system("cls");
                    home_page();
                    break;
                case 2:
                    exit(0);
                    break;}

}

void home_page(){

    cout<<"\n******************************************************"<<endl;
    cout << "Press 1 to Display Student information" << endl;
    cout << "Press 2 to Display Teacher information" << endl;
    cout << "Press 3 to Display Course information" << endl;
    cout << "Press 4 to Register Student " << endl;
    cout << "Press 5 to Update Student information"<<endl;
    cout << "Press 6 to Delete Student information"<<endl;
    cout<<  "Press 7 to Search Student "<<endl;
    cout << "Press 8 to Developers" << endl;
    cout << "Press 9 to Exit" << endl;
    cout<<"******************************************************"<<endl;

    int choice;
    cout<<"choose what you want to do: ";
    cin>>choice;
    switch (choice){
        case 1:
            display_student_information();
            break;
        case 2:

            display_instructor_info();
            break;
        case 3:
           display_course_info();
            break;
        case 4:
            register_student();
            break;
        case 5:
            update_student_information();
            break;
        case 6:

            delete_student_information();
            break;
        case 7:
            system("cls");
            search_student();
            break;
        case 8:
            system("cls");
            developed_by();
            break;

        case 9:
            exit(0);

            break;
        default:
            cout << endl << "\t PLEASE PRESS ONLY 1/2/3/4/5/6/7/8/9/10: " << endl;
            home_page();
    }

}

int main() {
    home_page();
    return 0;
}
