#include <cstdlib> 
#include <cmath>
#include<random>
#include<iostream>
#include<ctime>
#include<tuple>



using namespace std;


int main()
{
    srand(time(NULL));
    double x1; // for exponential 
    double x2;
    double failures1;
    double failures2;;
    double totalTimeBetweenFailures;
    double mtbf1;
    double mtbf2;
    double server1TimeCounter = 0.0  ;
    double server2TimeCounter = 0.0 ;
    double TotalServerShutdown = 0.0;
    double temp;
    int count = 1 ;
    double serverOnevalues[400];
    double servertwovalues[400];
    double totalShutdownAverage = 0;
    double simulations;

    cout<< "Please enter the number of times you would like to run the simulation: " ;
    cin >> simulations;


    for ( int i = 1 ; i <= simulations; i++)
    {
    
        failures1 = 0;
        failures2 = 0;
        totalTimeBetweenFailures= 0.0;
        mtbf1 = 0;
        mtbf2 = 0;
        server1TimeCounter = 0.0  ;
        server2TimeCounter= 0.0 ;
        temp = 0.0;
        count = 1 ;
        TotalServerShutdown = 0.0;
        cout << " Simulation # "<< i << endl << endl;

    while (server1TimeCounter < (20.0*365.0*24.0) || server2TimeCounter < (20.0*365.0*24.0)  )

    {
        

        x1 = (-500.0) * log(((double)rand()/(double)RAND_MAX)); // exponetial distribution  service time 


        x2 = (-500.0) * log(((double)rand()/(double)RAND_MAX)); // exponetial distribution  service time 


        serverOnevalues[count] =server1TimeCounter;
        servertwovalues[count]=server2TimeCounter;

        if ( server1TimeCounter < (20.0*365.0*24.0))
            {
                failures1++;
                server1TimeCounter+= x1;  
                serverOnevalues[count] = server1TimeCounter;
                mtbf1+=x1;
                server1TimeCounter+=10.0;
            }

        if (server2TimeCounter < (20.0*365.0*24.0))
        {
            failures2++;
            server2TimeCounter+= x2;
            servertwovalues[count] = server2TimeCounter;
            mtbf2+=x2;
            server2TimeCounter+=10.0;
        }

        count++;
    }

    
    for ( int i = 1; i < failures1 ; i++)
    {
        for (int j= 1 ;  j < failures2; j++)
        {
            if ((serverOnevalues[i] >= servertwovalues[j]) )
            {   
                if ((serverOnevalues[i] - servertwovalues[j]) < 10)
                {
                    temp = serverOnevalues[i];
                    if ( TotalServerShutdown  == 0 )
                    {
                        TotalServerShutdown = temp;
                    }
                    if ( temp < TotalServerShutdown)
                    {
                    TotalServerShutdown = temp; 
                    }   
                }
            }   

            else
            {
                if((servertwovalues[j] - serverOnevalues[i]) < 10)
                {
                    temp = servertwovalues[j];
                    if ( TotalServerShutdown  == 0 )
                    {
                        TotalServerShutdown = temp;
                    }
                    if ( temp < TotalServerShutdown)
                    {
                        TotalServerShutdown = temp; 
                    }
                }
            }
        }
    }

    for ( int i = 1; i <= failures1 ; i++)
    {
    cout<< "time when server 1 failed: " << serverOnevalues[i] << " hours" <<", time when server 1 was restored " << serverOnevalues[i]+10 <<" hours" << endl ;
    }

     for ( int i = 1; i <= failures2 ; i++)
    {
    cout<< "time when server 2 failed: " << servertwovalues[i] << " hours" << ", time when server 2 was restored " << servertwovalues[i]+10 << " hours" << endl ;
    }



    cout << " Results for simulation # " << i << endl;
    cout<< endl<< "Total amount of failures for server 1: " << failures1 << endl <<   "total amount of failures for server 2: " << failures2 << endl;
    cout<< "Time where we have a total system shutdown: " << TotalServerShutdown << " hours" << endl;
    cout << "MTBF for server 1 is: " <<mtbf1/failures1 << " hours" <<endl ;
    cout << "MTBF for server 2 is: " <<mtbf2/failures2 << " hours" << endl << endl << endl ;
    totalShutdownAverage+=TotalServerShutdown;
}
 
    cout << endl << "Actual Total Shutdown Average from "<< simulations << " simulations :" << totalShutdownAverage/simulations << " Hours" << endl << endl;
    return 0;
}

