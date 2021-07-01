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
        std::vector<Process*> GantChart;
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
    sort();
    std::vector<Process> processes = arr;
    int time = -1;
    Process *temp = NULL;
    while(!done)
    {
        done = true;
        time++;
        //search for the arrived processess
        for(int i=0; i<processes.size() && processes[i].arrivalTime <= time; i++)
        {
            if(processes[i].arrivalTime <= time)
                Arrivals.push(processes[i]),
                processes.erase(processes.begin());
        }
        if(temp != NULL) Arrivals.push(*temp);
        temp = NULL;
        //push the front of arrivals to cpu i.e GantChart
        GantChart.push_back(&(Arrivals.front()));
        int size = GantChart.size();
        //add got_cpu_at 
        if(GantChart[size-1]->got_cpu_at == -1)
            GantChart[size-1]->got_cpu_at = time;
        //increase by TQ
        if(GantChart[size-1]->brustTime > TimeQuantum)
            time += TimeQuantum;
        else
            time += GantChart[size-1]->brustTime;
        GantChart[size-1]->brustTime -= TimeQuantum;
        if(GantChart[size-1]->brustTime <= 0)
        {
            GantChart[size-1]->brustTime = 0;
            GantChart[size-1]->completion_time = time;
        }
        else
            temp = &(Arrivals.front());
        time --;
        Arrivals.pop();
        for(int i=0; i<processes.size(); i++)
            if(processes[i].brustTime > 0)
            {
                done = false;
                break;
            }
    }
    for(int i=0; i<arr.size(); i++)
    {
        arr[i].got_cpu_at = processes[i].got_cpu_at;
        arr[i].completion_time = processes[i].completion_time;
    }
}