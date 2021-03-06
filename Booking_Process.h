#include<iostream>
#include<queue>
#include<vector>
#include<string>
#include <climits>
#include<map>

using namespace std;

class hyperloop;
const int Vertex = 26;
int short_path[Vertex+1] = {-1};

vector <hyperloop> Passenger;
queue <hyperloop> Passenger_queue;
vector<pair<int,int>> graph[Vertex+1];

class hyperloop
{
    int Interconnecting_routes, Distance, Passenger_age;
    char Source_station, Starting_station, Ending_station, Passenger_destination;
    string Passenger_name;
    int So_station,St_station,En_station;

    public:
        hyperloop(){}
        hyperloop(string P_name, int P_age, char P_destination)
        {
            Passenger_name = P_name;
            Passenger_age = P_age;
            Passenger_destination = P_destination;
        }

        bool Init(int N_route,char S_station)
        {
            Interconnecting_routes = N_route;
            Source_station = S_station;
            cout<<"Enter the Starting Station , Ending Station and Distance between them : "<<endl;

            for(int i=0;i<Interconnecting_routes;++i)
            {
                cin>>Starting_station>>Ending_station>>Distance;

                St_station = (int) (Starting_station-64);
                En_station = (int) (Ending_station-64);

                graph[St_station].push_back(make_pair(En_station,Distance));
                graph[En_station].push_back(make_pair(St_station,Distance));
            }
            return 1;
        }

        void Add_passenger()
        {
            cout<<endl;
            for(int i=0; i<Passenger.size(); i++)
            {
                Passenger_queue.pop();
            }
            
            int P_count,P_age;
            char P_destination;
            string P_name;

            cout<<"Enter the Passengers Count : ";
            cin>>P_count;

            for(int i=0;i<P_count;++i)
            {
                cout<<endl;
                cout<<"Enter the Passenger Name : ";
                cin>>P_name;
                cout<<"Enter the Passenger Age : ";
                cin>>P_age;
                cout<<"Enter the Passenger Destination : ";
                cin>>P_destination;

                Passenger.push_back(hyperloop(P_name,P_age,P_destination));
            }
            Queue_sort();
        }

        void Queue_sort()
        {
            hyperloop temp;
            int min_index;

            for (int i = 0; i < Passenger.size(); i++)
            {
                min_index=i;
                for (int j = i + 1; j < Passenger.size(); j++)
                {
                    if (Passenger[j].Passenger_age > Passenger[min_index].Passenger_age)
                    {
                        min_index = j;
                    }
                }
                temp = Passenger[min_index];
                Passenger[min_index] = Passenger[i];
                Passenger[i] = temp;
            }

            for (int i = 0; i < Passenger.size(); i++)
            {
                Passenger_queue.push({Passenger[i].Passenger_name,Passenger[i].Passenger_age,Passenger[i].Passenger_destination});
            }
        }

        void printPath(int short_path[], int j)
        {
            if (short_path[j] == -1)
                return;
            printPath(short_path, short_path[j]);
            char p = j+64;
            cout<<p<<" ";
        }

        int Start_pod()
        {
            int Passenger_count;
            cout<<"Enter the Passengers count to Start the Pod : ";
            cin>>Passenger_count;

            if(!Passenger_queue.empty())
            {
                for(int i=0; i < Passenger_count; ++i)
                {
                    string name = Passenger_queue.front().Passenger_name;
                    int age = Passenger_queue.front().Passenger_age; 
                    char destination = Passenger_queue.front().Passenger_destination;
                    priority_queue< pair<int,int> , vector<pair<int,int>> , greater<pair<int,int>>> pq;
                    vector<int> short_distance (Vertex+1,INT_MAX);

                    So_station = (int) (Source_station-64);

                    short_distance[So_station]=0;
                    pq.push(make_pair(0,So_station));

                    while(!pq.empty())
                    {
                        int pq_distance = pq.top().first;
                        int pq_vertex = pq.top().second;
                        pq.pop();
                        vector<pair<int,int>> :: iterator it;

                        for(it=graph[pq_vertex].begin(); it!=graph[pq_vertex].end(); it++)
                        {
                            int graph_vertex = it->first;
                            int graph_distance = it->second;

                            if(short_distance[graph_vertex] > short_distance[pq_vertex] + graph_distance)
                            {
                                short_path[graph_vertex] = pq_vertex;

                                short_distance[graph_vertex] = short_distance[pq_vertex] + graph_distance;
                                pq.push(make_pair(short_distance[graph_vertex] , graph_vertex));
                            }
                        }
                    }

                    int Pa_destination = (int) destination-64;
                    cout<<"The Shorest distance from Source Station : "<<Source_station<<" and Passenger Destination : "<<destination<<" is = ";

                    for(int i=1;i<=Vertex; i++)
                    {
                        if(i==Pa_destination)
                        {
                            cout<<short_distance[i]<<endl;
                            cout<<name<<" ";
                            printPath(short_path, i);
                        }
                    }
                    cout<<endl;
                    Passenger_queue.pop();
                }
            }
            else
            {
                return 0;
            }
            return 1;
        }

        void Print_queue()
        {        
            cout<<Passenger_queue.size()<<endl;
            Print(Passenger_queue);
        }

        void Print(queue <hyperloop> tempQ)
        {
            while(!tempQ.empty())
            {
                string name = tempQ.front().Passenger_name;
                int age = tempQ.front().Passenger_age;
                cout<<name<<" "<<age<<endl;
                tempQ.pop();
            }
        }
};