#include <cstdlib> 
#include <cmath>
#include<random>
#include<iostream>
#include<ctime>
#include<tuple>



using namespace std;


int main()
{
    tuple <int,float,float> result;
    float x; // for exponential 
    float arrivaltotalTime; 
    float totalServiceTime;
    float arrivalaverage;
     

    for ( int i = 1; i <=1000;i++)
    {
        x = (-1.0) * log(((double)rand()/(double)RAND_MAX)); // exponetial distribution  service time 
        arrivaltotalTime+= (-1.0/2.0) * log(((double)rand()/(double)RAND_MAX)); // poisson Dist. interarrival times
        totalServiceTime+=x;
        result = make_tuple( i,arrivaltotalTime,x);
        cout << "< #" << get<0>(result) <<","<< get<1>(result) <<","<<get<2>(result) <<" >" << endl;
    }

    cout<< endl<< endl;
       cout<< "Total Arrival time: " << arrivaltotalTime << endl ;
       cout<< "average service time " << (totalServiceTime / 1000.0)<< " second(s)" << endl;  
       cout << "Actual Average of arrivals:" << 1000.0/arrivaltotalTime << " arrivals per second" <<  endl;   
    return 0;
 }
