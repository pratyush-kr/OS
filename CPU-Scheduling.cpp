// TO RUN: g++ -o CPU-Scheduling CPU-Scheduling.cpp && ./CPU-Scheduling

/*
    Test Case:
        RoundRobin 2 get_array A 3 0 B 4 7 C 9 0 D 0 2 E 7 6 exit calculate show
        FCFS get_array A 3 0 B 4 7 C 9 0 D 0 2 E 7 6 exit calculate show
*/

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
        float waiting_time;
        float turn_around_time;
        float response_time;
        unsigned int priority;
        Process(char PID = '\0', float BT = 0, float AT = 0, unsigned int P = 0)
        {
            processID = PID;
            brustTime = BT;
            arrivalTime = AT;
            got_cpu_at = completion_time = waiting_time  = turn_around_time = response_time = -1;
            priority = P;
        }
};


//These Function is used to sort the vector arr
bool compareAT(const Process &i, const Process &j)
{
    return (i.arrivalTime < j.arrivalTime)? true:false;
}

bool comparePID(const Process &i, const Process &j)
{
    return (i.processID < j.processID)? true:false;
}

bool compareP(const Process &i, const Process &j)
{
    return (i.priority < j.priority)? true:false;
}


//The Main Class Containing the array of Processes and
//and some general functions
class Scheduler
{
    protected:
        std::vector<Process> arr;
    public:
        void show();
        void get_array();
        virtual void calculate() = 0;
        virtual void printGanttChart() = 0;
};

//Specialized Class for RoundRobin
//Dedicated calculate Function and GanttCharts' Are avilable
class RoundRobin : public Scheduler
{
    private:
        std::vector<Process> GanttChart;
        std::queue<Process*> Arrivals;
        int TimeQuantum;
    public:
        RoundRobin(int TQ = 2){TimeQuantum = TQ;}
        void calculate();
        void printGanttChart()
        {
            for(int i=0; i<GanttChart.size(); i++)
                std::cout<<"| "<<GanttChart[i].processID<<" ";
            std::cout<<"|\n";
            for(int i=0; i<GanttChart.size(); i++)
                std::cout<<GanttChart[i].got_cpu_at<<std::setw(4)<<std::right;
            std::cout<<GanttChart[GanttChart.size() - 1].completion_time<<"\n";
        }
};


//Specialized Class for FCFS
//Dedicated calculate Function and GanttCharts' Are avilable
class FCFS : public Scheduler
{
    private:
        std::vector<Process> GanttChart;
    public:
        void calculate();
        void printGanttChart()
        {
            for(int i=0; i<GanttChart.size(); i++)
                std::cout<<"| "<<GanttChart[i].processID<<" ";
            std::cout<<"|\n";
            for(int i=0; i<GanttChart.size(); i++)
                std::cout<<GanttChart[i].got_cpu_at<<std::setw(4)<<std::right;
            std::cout<<GanttChart[GanttChart.size() - 1].completion_time<<"\n";
        }
};

class Priority : public Scheduler
{
    private:
        std::vector<Process> GanttChart;
    public:
        void calculate();
        void printGanttChart()
        {
            for(int i=0; i<GanttChart.size(); i++)
                std::cout<<GanttChart[i].processID<<" ";
            std::cout<<"\n";
        }
};

int main()
{
    char command[20];
    Scheduler *Sc = NULL;
    int TQ;
    while(1)
    {
        std::cout<<"command: ";
        std::cin>>command;
        if(!strcmp(command, "exit"))
            break;
        else if(!strcmp(command, "RoundRobin"))
        {
            if(Sc) delete Sc; //if Sc contains any Object Delete it 1st
            Sc = NULL;
            std::cout<<"Time Quantum (ms): ";
            std::cin>>TQ;
            Sc = new RoundRobin(TQ);
        }
        else if(!strcmp(command, "FCFS"))
        {
            if(Sc) delete Sc; //if Sc contains any Object Delete it 1st
            Sc = NULL;
            Sc = new FCFS();
        }
        else if(!strcmp(command, "Priority"))
        {
            if(Sc) delete Sc; //if Sc contains any Object Delete it 1st
            Sc = NULL;
            Sc = new Priority();
        }
        //Do these Only if Sc has an Object
        else if(!strcmp(command, "get_array"))
            if(Sc) Sc->get_array();
            else std::cout<<"No Algo Selected\n";
        else if(!strcmp(command, "show"))
           if(Sc) Sc->show();
           else std::cout<<"No Algo Selected\n";
        else if(!strcmp(command, "calculate"))
            if(Sc) Sc->calculate();
            else std::cout<<"No Algo Selected\n";
        else if(!strcmp(command, "GanttChart"))
            if(Sc) Sc->printGanttChart();
            else std::cout<<"No Algo Selected\n";
        else if(!strcmp(command, "delete"))
            if(Sc) delete Sc;
    }
    return 0;
}

//Takes Array Input
void Scheduler::get_array()
{
    bool req = false;
    char PID;
    int BT, AT, P = 0;
    std::string str;
    std::cout<<"Priority Required? ";
    std::cin>>req;
    std::cout<<"Type exit to quit entering\n";
    std::cout<<"PID BT AT";
    if(req) std::cout<<" Priority";
    std::cout<<'\n';
    while(1)
    {
        std::cin>>str;
        if(str == "exit")
            break;
        PID = str[0];
        std::cin>>BT>>AT;
        if(req) std::cin>>P;
        arr.push_back(*(new Process(PID, BT, AT, P)));
    }
}

void Scheduler::show()
{
    std::cout<<"PID"<<std::setw(4)<<std::right
             <<"BT"<<std::setw(5)<<std::right
             <<"AT"<<std::setw(13)<<std::right
             <<"Priority"<<std::setw(5)<<std::right
             <<"CT"<<std::setw(5)<<std::right
             <<"WT"<<std::setw(5)<<std::right
             <<"TAT"<<std::setw(5)<<std::right
             <<"RT\n";
    for(int i=0; i<arr.size(); i++)
    {
        std::cout<<arr[i].processID<<std::setw(5)<<std::right
                <<arr[i].brustTime<<std::setw(5)<<std::right
                <<arr[i].arrivalTime<<std::setw(11)<<std::right
                <<arr[i].priority<<std::setw(7)<<std::right
                <<arr[i].completion_time<<std::setw(5)<<std::right
                <<arr[i].waiting_time<<std::setw(5)<<std::right
                <<arr[i].turn_around_time<<std::setw(5)<<std::right
                <<arr[i].response_time<<"\n";
    }
}

void RoundRobin::calculate()
{
    if(arr.size() == 0)
    {
        std::cout<<"No Array to operate\n";
        return;
    }
    int time = -1;
    bool done = false;
    Process *front = NULL, *ptr = NULL;
    std::sort(arr.begin(), arr.end(), compareAT);
    std::vector<Process> bt = arr;
    std::queue<Process*> ReadyQueue;
    for(int i=0; i<arr.size(); i++)
        ReadyQueue.push(&arr[i]);
    while(!done)
    {
        done = true;
        time++;
        while(ReadyQueue.size() > 0 && ReadyQueue.front()->arrivalTime <= time)
        { 
            Arrivals.push(ReadyQueue.front());
            ReadyQueue.pop();
        }
        if(front) Arrivals.push(front);
        front = NULL;
        if(!Arrivals.empty())
        {
            if(Arrivals.front()->brustTime > TimeQuantum)
            {
                front = Arrivals.front();
                //in case Process faces cpu for 1st time
                if(front->got_cpu_at == -1) front->got_cpu_at = time;
                front->brustTime -= TimeQuantum;
                ptr = new Process(front->processID);
                ptr->got_cpu_at = time;
                time += TimeQuantum;
                GanttChart.push_back(*ptr);
                Arrivals.pop();
            }
            else
            {
                front = Arrivals.front();
                if(front->got_cpu_at == -1) front->got_cpu_at = time;
                ptr = new Process(front->processID);
                ptr->got_cpu_at = time;
                time += front->brustTime;
                front->brustTime = 0;
                front->completion_time = time;
                ptr->completion_time = time;
                GanttChart.push_back(*ptr);
                Arrivals.pop();
                front = NULL;
            }
            time--;
        }
        for(int i=0; i<arr.size(); i++)
            if(arr[i].brustTime > 0)
            {
                done = false;
                break;
            }
    }
    for(int i=0; i<arr.size(); i++)
        arr[i].brustTime = bt[i].brustTime;
    std::sort(arr.begin(), arr.end(), comparePID);
    for(int i=0; i<arr.size(); i++)
    {
        arr[i].waiting_time = arr[i].completion_time - arr[i].brustTime - arr[i].arrivalTime;
        arr[i].turn_around_time = arr[i].waiting_time + arr[i].brustTime;
        arr[i].response_time = arr[i].got_cpu_at - arr[i].arrivalTime;
    }
}

void FCFS::calculate()
{
    if(arr.size() == 0)
    {
        std::cout<<"No Array to operate\n";
        return;
    }
    int time = 0;
    std::sort(arr.begin(), arr.end(), compareAT);
    time += arr[0].arrivalTime;
    std::queue<Process*> Queue;
    for(int i=0; i<arr.size(); i++)
        Queue.push(&arr[i]);
    while(!Queue.empty())
    {
        if(Queue.front()->arrivalTime <= time)
        {
            Queue.front()->got_cpu_at = time;
            time += Queue.front()->brustTime;
            Queue.front()->completion_time = time;
            GanttChart.push_back(*Queue.front());
            time--;
            Queue.pop();
        }
        time++;
    }
    for(int i=0; i<arr.size(); i++)
    {
        arr[i].waiting_time = arr[i].completion_time - arr[i].brustTime - arr[i].arrivalTime;
        arr[i].turn_around_time = arr[i].waiting_time + arr[i].brustTime;
        arr[i].response_time = arr[i].got_cpu_at - arr[i].arrivalTime;
    }
    std::sort(arr.begin(), arr.end(), comparePID);
}

void Priority::calculate()
{
    int time = -1;
    if(arr.size() == 0)
    {
        std::cout<<"No Array to operate\n";
        return;
    }
    std::sort(arr.begin(), arr.end(), compareAT);
    std::queue<Process> ReadyQueue;
    for(int i=0; i<arr.size(); i++)
        ReadyQueue.push(arr[i]);
    while(1)
    {
        time++;
    }
}