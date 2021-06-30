#include<iostream>
#include<cstring>
#include<vector>
#include<iomanip>

class Process
{
    public:
        char processID;
        float brustTime;
        float arrivalTime;
        Process(char PID = '\0', float BT = 0, float AT = 0) {processID = PID; brustTime = BT; arrivalTime = AT;}
};

class Scheduler
{
    protected:
        std::vector<Process> arr;
    public:
        virtual void get_array() = 0;
        virtual void calculate() = 0;
        virtual void show() = 0;
};

class RoundRobin : public Scheduler
{
    private:
        std::vector<Process> GantChart;
        std::vector<Process> Arrivals;
    public:
        void get_array();
        void calculate();
        void show();
};

int main()
{
    char command[20];
    Scheduler *Sc;
    while(1)
    {
        std::cout<<"command: ";
        std::cin>>command;
        if(!strcmp(command, "exit"))
            break;
        else if(!strcmp(command, "RoundRobin"))
            Sc = new RoundRobin();
    }
    return 0;
}

void RoundRobin::get_array()
{
    char PID;
    int BT, AT;
    std::string str;
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

void RoundRobin::calculate()
{}