#include<iostream>
#include<cstring>
#include<vector>
#include<iomanip>
#include<algorithm>

class Process
{
    public:
        char processID;
        float brustTime;
        float arrivalTime;
        Process(char PID = '\0', float BT = 0, float AT = 0) {processID = PID; brustTime = BT; arrivalTime = AT;}
};

bool comparison(const Process &, const Process &);

class Scheduler
{
    friend bool comparison(const Process &, const Process &);
    protected:
        std::vector<Process> arr;
        void sort()
        {
            std::sort(arr.begin(), arr.end(), comparison);
        }
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
        else if(!strcmp(command, "get_array"))
            Sc->get_array();
        else if(!strcmp(command, "show"))
            Sc->show();
        else if(!strcmp(command, "calculate"))
            Sc->calculate();
    }
    return 0;
}

void RoundRobin::get_array()
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
    sort();
}

void RoundRobin::calculate()
{

}

void RoundRobin::show()
{
    std::cout<<"PID  "<<"BT  "<<"AT  \n";
    for(int i=0; i<arr.size(); i++)
    {
        std::cout<<arr[i].processID<<"  "
                 <<arr[i].brustTime<<"  "
                 <<arr[i].arrivalTime<<"\n";
    }
}

bool comparison(const Process &i, const Process &j)
{
    return (i.arrivalTime < j.arrivalTime)? true:false;
}