#include "Booking_Process.h"

int main()
{
    string input,P_name;
    int N_route,P_age,P_count;
    char S_station,P_destination;
    int check=0,check_queue=1;
    cout<<endl<<"####__#### Hyperloop Passenger Booking ####__####"<<endl;
    map<string,int> command = {{"INIT",1},{"ADD_PASSENGER",2},{"START_POD",3},{"PRINT_Q",4},{"EXIT",5}};

    hyperloop pickup;
    while(1)
    {
        cout<<endl<<"__________________________________________________________________________________________"<<endl;
        cout<<"The Available Command Words are..,"<<endl<<endl;
        cout<<"INIT"<<endl<<"ADD_PASSENGER"<<endl<<"START_POD"<<endl<<"PRINT_Q"<<endl<<"EXIT"<<endl<<endl;
        cout<<"Enter your command : ";
        cin>>input;
        switch(command[input])
        {
            case 1:
                    cout<<"Initialing The System"<<endl;
                    cout<<"Enter the Number of interconnecting routes and the Source station : ";
                    cin>>N_route>>S_station;
                    check = pickup.Init(N_route,S_station);
                    break;
            case 2:
                    if(check==1)
                        pickup.Add_passenger();
                    break;
            case 3:
                    if(check==1)
                        check_queue = pickup.Start_pod();
                    if(check_queue==0)
                        cout<<endl<<"Not able to Start the POD, No Passengers are Available."<<endl;
                    break;
            case 4:
                    if(check==1)
                        pickup.Print_queue();
                    break;
            case 5:
                    cout<<"Terminating the System . . .";
                    exit (0);
            default:
                    cout<<"Invalid Command, Choose the Available Commands Only."<<endl;
                    break;
        }
        if(check==0)
            cout<<"You can't give other command without Initializing the 'INIT' command."<<endl;   
    }
    return 0;
}