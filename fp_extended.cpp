// A program to allot colleges with branches to the students by their ranks

#include "global.h"

using namespace std;
// defining variables required for the project
const int total_colleges = 10;
const int total_branch = 5;
string college_branch[total_colleges][total_branch] = {{"CSE - IIT BOMBAY", "DSAI - IIT BOMBAY", "MnC - IIT BOMBAY", "ECE - IIT BOMBAY", "EEE - IIT BOMBAY"}, 
                                                       {"CSE - IIT DELHI", "DSAI - IIT DELHI","MnC - IIT DELHI","ECE - IIT DELHI","EEE - IIT DELHI"}, 
                                                       {"CSE - IIT MADRAS", "DSAI - IIT MADRAS","MnC - IIT MADRAS","ECE - IIT MADRAS","EEE - IIT MADRAS"}, 
                                                       {"CSE - IIT KANPUR", "DSAI - IIT KANPUR","MnC - IIT KANPUR","ECE - IIT KANPUR","EEE - IIT KANPUR"}, 
                                                       {"CSE - IIT KHARAGPUR", "DSAI - IIT KHARAGPUR","MnC - IIT KHARAGPUR","ECE - IIT KHARAGPUR","EEE - IIT KHARAGPUR"},
                                                       {"CSE - IIT ROORKEE", "DSAI - IIT ROORKEE","MnC - IIT ROORKEE","ECE - IIT ROORKEE","EEE - IIT ROORKEE"}, 
                                                       {"CSE - IIT GUWAHATI", "DSAI - IIT GUWAHATI","MnC - IIT GUWAHATI","ECE - IIT GUWAHATI","EEE - IIT GUWAHATI"}, 
                                                       {"CSE - IIT HYDERABAD", "DSAI - IIT HYDERABAD","MnC - IIT HYDERABAD","ECE - IIT HYDERABAD","EEE - IIT HYDERABAD"}, 
                                                       {"CSE - IIT INDORE", "DSAI - IIT INDORE","MnC - IIT INDORE","ECE - IIT INDORE","EEE - IIT INDORE"}, 
                                                       {"CSE - IIT VARANASI", "DSAI - IIT VARANASI","MnC - IIT VARANASI","ECE - IIT VARANASI","EEE - IIT VARANASI",}}; 
const int total_students = 100;
map<int, int> rank_roll;
const int max_preference = 10;
int rank_preference[total_students][max_preference];
int seats_filled[total_colleges][total_branch];
map<int, int> roll_allotment;
int seat_max = 2;
bool roll_allotted[total_students];

//Function to initialize the the ranks and the preferences of the student
void initialize()
{
    //Initializing ranks to roll no.
    for(int i=0;i<total_students;i++)
    {
        if(i<25)
        {
            rank_roll[i] = 50-i;
        }
        else if(i>=25 && i<50)
        {
            rank_roll[i] = 100-i;
        }
        else if(i>=50 && i<=75)
        {
            rank_roll[i] = 75-i;
        }
        else{
            rank_roll[i] = i;
        }
    }

    // Initialising random preferences to students
    for(int i=0;i<total_students;i++)
    {
        for(int j=0;j<max_preference;j++)
        {
            rank_preference[i][j] = rand()%50;
        }
    }

    // Setting the number of seats filled to zero.
    for(int i=0;i<total_colleges;i++)
    {
        for(int j=0;j<total_branch;j++)
        {
            seats_filled[i][j] = 0;
        }
    }

    for(int i=0;i<total_students;i++)
    {
        roll_allotted[i] = false;
    }

}

// Storing the data initialised in a file
void store_data()
{
    fstream file("data_extended.txt");
    file<<"Rank"<<"    |    "<<"Roll"<<"        |        "<<"Preference Order"<<endl;
    for(int i=0;i<total_students;i++)
    {
        file<<i<<"\t"<<"    |    "<<"\t"<<rank_roll[i]<<"\t"<<"     |     ";
        for(int j=0;j<max_preference;j++)
        {
            // if(j!=9)
            // {
            //     file<<preference[i][j]<<","<<"\t";
            // }
            // else{
            //     file<<preference[i][j];
            // }
            // file<<endl;
            file<<rank_preference[i][j]<<","<<"\t";
        }
        file<<endl;
    }
}

// Allotting college and branches to the students
void allotment()
{
    for(int i=0;i<total_students;i++)
    {
        int roll = rank_roll[i];
        for(int j=0;j<max_preference;j++)
        {
            if(seats_filled[rank_preference[i][j]/5][rank_preference[i][j]%5]<seat_max)
            {
                roll_allotment[roll] = rank_preference[i][j];
                roll_allotted[roll] = true;
                seats_filled[rank_preference[i][j]/5][rank_preference[i][j]%5]++;
                break;
            }
        }
    }
}

// Exporting the allotments in a file to save the results
void export_data()
{
    fstream file2("output_extended.txt");
    file2<<"Rank"<<"\t"<<"  |    "<<"Roll"<<"\t\t"<<"  | "<<"\t"<<"College Allotted"<<endl;
    for(int i=0;i<total_students;i++)
    {
        file2<<i<<"\t\t"<<"  |  "<<"\t"<<rank_roll[i]<<"\t\t"<<"  |  "<<"\t\t"<<roll_allotment[rank_roll[i]]<<"\t\t"<<endl;
    }
    file2<<endl;
    file2<<"Seats filled:"<<endl;
    file2<<endl;
    for(int i=0;i<total_colleges;i++)
    {
        for(int j=0;j<total_branch;j++)
        {
            file2<<((5*i)+j)<<".\t"<<"\t"<<college_branch[i][j]<<"\t"<<"\t:\t"<<seats_filled[i][j]<<endl;
        }
    }
}

// Option for the students to edit their preferences
int student_edit()
{
    int student_roll;
    int student_rank;
    cout<<"Enter your roll number"<<endl;
    cin>>student_roll;
    for(int i=0;i<total_students;i++)
    {
        if(rank_roll[i] == student_roll)
        {
            student_rank = i;
            cout<<"Roll Number found"<<endl;
            cout<<"Your rank is "<<student_rank<<endl;
            break;
        }
        else if(i==total_students-1){
            cout<<"Roll number not found!"<<endl;
            return -1;
        }
    }
    char change_pref;
    cout<<"Do you want to change your preference order(y/n)"<<endl;
    cin>>change_pref;
    if(change_pref=='y')
    {
        cout<<"Choose the order from the following colleges"<<endl;
        for(int i=0;i<total_colleges;i++)
        {
            for(int j=0;j<total_branch;j++)
            {
                cout<<((5*i)+j)<<"."<<"\t"<<college_branch[i][j]<<endl;
            }
        }
        cout<<"Write the numbers adjacent to the college names in the order of your preference"<<endl;
        cout<<"You can enter a maximum of 10 preferences"<<endl;
        for(int i=0;i<max_preference;i++)
        {
            cin>>rank_preference[student_rank][i];
        }
    }
    return student_roll;
}

// Showing the allotment of a student by taking roll number 
void show_allotment(int student_roll)
{
    if(roll_allotted[student_roll] == true)
    {
        cout<<"Your alloted college is "<<college_branch[roll_allotment[student_roll]/5][roll_allotment[student_roll]%5]<<endl;
        cout<<"Best of luck for your new journey"<<endl;
    }
    else{
        cout<<"Sorry you have not been allotted a college in this round! Better luck next time."<<endl;
    }
}

// Driver Function
int main(){

    // Function to calculate time
    clock_t star, end;
    star = clock();
    // Calling the functions
    initialize();
    allotment();
    store_data();
    export_data();

    // Menu Driven program
    cout<<"To view your allotment enter 1."<<endl;
    cout<<"To edit your preferences enter 2."<<endl;
    int choice;
    cin>>choice;
    int student_roll;
    if(choice ==1)
    {
        cout<<"Enter your roll number"<<endl;
        cin>>student_roll;
        show_allotment(student_roll);
    }
    else if(choice==2){
        student_roll = student_edit();
        if(student_roll>0)
        {
            allotment();
            store_data();
            export_data();
            show_allotment(student_roll);
        }
    }
    else{
        cout<<"Sorry! You entered the wrong number"<<endl;
    }
    // initialize();
    // // for(int i=0;i<total_students;i++)
    // // {
    //     // cout<<i<<" | "<<rank_roll[i]<<endl;
    // // }

    // // for(int i=0;i<total_students;i++)
    // // {
    // //     cout<<i<<" | ";
    // //     for(int j=0;j<total_colleges;j++)
    // //     {
    // //         if(j!=9)
    // //         {
    // //             cout<<rank_preference[i][j]<<",";
    // //         }
    // //         else{
    // //             cout<<rank_preference[i][j];
    // //         }
    // //     }
    // //     cout<<endl;
    // // }

    // store_data();
    // export_data();

    // // allotment();
    // // cout<<"Rank"<<"\t"<<"  |  "<<"Roll"<<"\t"<<"  |  "<<"\t"<<"College Allotted"<<endl;
    // // for(int i=0;i<total_students;i++)
    // // {
    // //     cout<<i<<"\t"<<"  |  "<<"\t"<<rank_roll[i]<<"\t"<<"  |  "<<"\t"<<roll_allotment[rank_roll[i]]<<"\t"<<endl;
    // // }
    // // export_data();
    // int student_roll = student_edit();
    // if(student_roll>=0)
    // {
    //     allotment();
    //     store_data();
    //     export_data();
    //     show_allotment(student_roll);
    // }

    end = clock();
    double time_taken = double(end - star) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5);
    cout << " sec " << endl;
}