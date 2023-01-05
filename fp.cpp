#include<bits/stdc++.h>

using namespace std;

const int total_colleges = 10;
string college[10] = {"IIT BOMBAY", "IIT DELHI", "IIT MADRAS", "IIT KANPUR", "IIT KHARAGPUR", "IIT ROORKEE", "IIT GUWAHATI", "IIT HYDERABAD", "IIT INDORE", "IIT VARANASI"}; 
const int total_students = 100;
map<int, int> rank_roll;
int rank_preference[total_students][total_colleges];
int seats_filled[total_colleges];
map<int, int> roll_allotment;
int seat_max = 10;
bool roll_allotted[total_students];

void initialize()
{
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

    for(int i=0;i<total_students;i++)
    {
        for(int j=0;j<10;j++)
        {
            rank_preference[i][j] = j;
        }
    }

    for(int i=0;i<total_colleges;i++)
    {
        seats_filled[i] = 0;
    }

    for(int i=0;i<total_students;i++)
    {
        roll_allotted[i] = false;
    }

}

void store_data()
{
    fstream file("data.txt");
    file<<"Rank"<<"    |    "<<"Roll"<<"        |        "<<"Preference Order"<<endl;
    for(int i=0;i<total_students;i++)
    {
        file<<i<<"\t"<<"    |    "<<"\t"<<rank_roll[i]<<"\t"<<"     |     ";
        for(int j=0;j<total_colleges;j++)
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

void allotment()
{
    for(int i=0;i<total_students;i++)
    {
        int roll = rank_roll[i];
        for(int j=0;j<total_colleges;j++)
        {
            if(seats_filled[rank_preference[i][j]]<seat_max)
            {
                roll_allotment[roll] = rank_preference[i][j];
                roll_allotted[roll] = true;
                seats_filled[rank_preference[i][j]]++;
                break;
            }
        }
    }
}

void export_data()
{
    fstream file2("output.txt");
    file2<<"Rank"<<"\t"<<"  |    "<<"Roll"<<"\t\t"<<"  | "<<"\t"<<"College Allotted"<<endl;
    for(int i=0;i<total_students;i++)
    {
        file2<<i<<"\t\t"<<"  |  "<<"\t"<<rank_roll[i]<<"\t\t"<<"  |  "<<"\t\t"<<roll_allotment[rank_roll[i]]<<"\t\t"<<endl;
    }
}

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
            cout<<i<<"."<<college[i]<<endl;
        }
        cout<<"Write the numbers adjacent to the college names in the order of your preference"<<endl;
        for(int i=0;i<total_colleges;i++)
        {
            cin>>rank_preference[student_rank][i];
        }
    }
    return student_roll;
}

void show_allotment(int student_roll)
{
    if(roll_allotted[student_roll] == true)
    {
        cout<<"Your alloted college is "<<college[roll_allotment[student_roll]]<<endl;
        cout<<"Best of luck for your new journey"<<endl;
    }
    else{
        cout<<"Sorry you have not been allotted a college in this round! Better luck next time."<<endl;
    }
}

int main(){

    clock_t star, end;
    star = clock();
    initialize();
    // for(int i=0;i<total_students;i++)
    // {
        // cout<<i<<" | "<<rank_roll[i]<<endl;
    // }

    // for(int i=0;i<total_students;i++)
    // {
    //     cout<<i<<" | ";
    //     for(int j=0;j<total_colleges;j++)
    //     {
    //         if(j!=9)
    //         {
    //             cout<<rank_preference[i][j]<<",";
    //         }
    //         else{
    //             cout<<rank_preference[i][j];
    //         }
    //     }
    //     cout<<endl;
    // }

    store_data();


    // allotment();
    // cout<<"Rank"<<"\t"<<"  |  "<<"Roll"<<"\t"<<"  |  "<<"\t"<<"College Allotted"<<endl;
    // for(int i=0;i<total_students;i++)
    // {
    //     cout<<i<<"\t"<<"  |  "<<"\t"<<rank_roll[i]<<"\t"<<"  |  "<<"\t"<<roll_allotment[rank_roll[i]]<<"\t"<<endl;
    // }
    // export_data();
    int student_roll = student_edit();
    if(student_roll>=0)
    {
        allotment();
        store_data();
        export_data();
        show_allotment(student_roll);
    }

    end = clock();
    double time_taken = double(end - star) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed 
         << time_taken << setprecision(5);
    cout << " sec " << endl;
}