#include<iostream>
#include<cstring>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<queue>

class Process
{
    public:
        char processID;
        float brustTime;
        float arrivalTime;
        float got_cpu_at;
        float completion_time;
        Process(char PID = '\0', float BT = 0, float AT = 0) 
        {
            processID = PID;
            brustTime = BT;
            arrivalTime = AT;
            got_cpu_at = completion_time = -1;
        }
};


//This Function is used to sort the vector arr
bool comparison(const Process &i, const Process &j)
{
    return (i.arrivalTime < j.arrivalTime)? true:false;
}

class Scheduler
{
    protected:
        std::vector<Process> arr;
        void sort()
        {
            std::sort(arr.begin(), arr.end(), comparison);
        }
    public:
        void get_array();
        void show();
        virtual void calculate() = 0;
};

class RoundRobin : public Scheduler
{
    private:
        std::vector<std::reference_wrapper<Process>> GantChart;
        std::queue<Process> Arrivals;
        int TimeQuantum;
    public:
        void calculate();
        RoundRobin(int TQ = 2){TimeQuantum = TQ;}
};

int main()
{
    char command[20];
    Scheduler *Sc;
    int TQ;
    while(1)
    {
        std::cout<<"command: ";
        std::cin>>command;
        if(!strcmp(command, "exit"))
            break;
        else if(!strcmp(command, "RoundRobin"))
        {
            std::cout<<"Time Quantum (ms): ";
            std::cin>>TQ;
            Sc = new RoundRobin(TQ);
        }
        else if(!strcmp(command, "get_array"))
            Sc->get_array();
        else if(!strcmp(command, "show"))
            Sc->show();
        else if(!strcmp(command, "calculate"))
            Sc->calculate();
    }
    return 0;
}

void Scheduler::get_array()
{
    char PID;
    int BT, AT;
    std::string str;
    std::cout<<"Type exit to quit entring\n";
    std::cout<<"PID BT AT\n";
    while(1)
    {
        std::cin>>str;
        if(str == "exit")
            break;
        PID = str[0];
        std::cin>>BT>>AT;
        arr.push_back(*(new Process(PID, BT, AT)));
    }
}

void Scheduler::show()
{
    std::cout<<"PID  BT  AT  CT\n";
    for(int i=0; i<arr.size(); i++)
    {
        std::cout<<arr[i].processID<<"  "
                 <<arr[i].brustTime<<"  "
                 <<arr[i].arrivalTime<<"  "
                 <<arr[i].completion_time<<"\n";
    }
}

void RoundRobin::calculate()
{
    bool done = false;
    int time = -1;
    sort();
    std::queue<Process> Queue;
    for(int i=0; i<arr.size(); i++)
        Queue.push(arr[i]);
    while(!done)
    {
        time++;
        //iterate over the abc and find what processess have arriverd
        for(int i=0; i<Arr.size(); i++)
        {
            if(Queue.front().arrivalTime <= time)
            {
                Arrivals.push(Queue.front());
                Queue.pop();
            }
        }
    }
}