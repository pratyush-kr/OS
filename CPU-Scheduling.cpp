#include<iostream>
#include<cstring>
#include<vector>

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
};

class RoundRobin : public Scheduler
{
    private:
        std::vector<Process> GantChart;
        std::vector<Process> Arrivals;
    public:
        void get_array();
        void calculate();
};

int main()
{
    char command[20];
    while(1)
    {
        std::cout<<"command: ";
        std::cin>>command;
        if(!strcmp(command, "exit"))
            break;
    }
    return 0;
}