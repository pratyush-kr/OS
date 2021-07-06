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
        std::vector<Process> sort()
        {
            std::vector<Process> Queue;
            std::vector<Process> vec = arr;
            std::sort(vec.begin(), vec.end(), comparison);
            for(int i=0; i<vec.size(); i++)
                Queue.push_back(vec[i]);
            return Queue;
        }
    public:
        void get_array();
        void show();
        virtual void calculate() = 0;
};

class RoundRobin : public Scheduler
{
    private:
        std::vector<Process> GantChart;
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
    int time = -1;
    int rem_bt[arr.size()];
    std::vector<Process> ready_queue = sort();
    for(int i=0; i<arr.size(); i++)
        rem_bt = arr[i].brustTime;
    bool done = false;
    Process *front = NULL;
    while(!done)
    {
        done = true;
        time++;
        while(ready_queue[0].arrivalTime > time)
        {
            //find what Process arrived then delete it from ready queue 
            if(ready_queue[0].arrivalTime <= time)
                Arrivals.push(ready_queue[0]),
                ready_queue.erase(ready_queue.begin());
        }
        if(front) Arrivals.push(*front);
        front = NULL;
        if(Arrivals.front()) //Arrivals.front() != NULL
        {
            if(Arrivals.front().brustTime > TimeQuantum)
            {
                front = &Arrivals.front();
                GantChart.push_back(*front);
                front->brustTime -= TimeQuantum;
                //in case Process faces cpu for 1st time
                if(front->got_cpu_at == -1) front()->got_cpu_at = time;
                time += TimeQuantum;
                Arrivals.pop();
            }
            else
            {
                time += Arrivals.front().brustTime;
                Arrivals.front().brustTime = 0;
            }
        }
        time--;
    }
}