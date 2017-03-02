#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct route {
    void *Destination;          //Pointer to destination state
    unsigned int Cost;           //Cost of the route
};

struct state {
    string Name;                //Name of the state
    list<route *> Routes;       //List of routes
    unsigned int Heuristic;     //Estimated time to goal
};

class BreadthFirstSearch {
private:
    struct node {
        state *State;               //Pointer to current state
        unsigned int PathCost;      //Path cost till current state
        node *Parent;               //Pointer to parent node
    };

    string print(node *Trace) {
        string Output = "";
        while(Trace != nullptr) {
            string t = Trace->State->Name + " " + to_string(Trace->PathCost) + "\n";
            Output = t + Output;
            Trace = Trace->Parent;
        }
        return Output;
    }

public:
    string run(state *Start, state *Goal) {
        queue<node *> Frontier;                      //Frontier node list
        unordered_set<string> Explored;              //Stores set of all nodes opened and closed

        //Create and add start node in frontier
        node *CurrentNode = new node;
        CurrentNode->State = Start;
        CurrentNode->PathCost = 0;
        CurrentNode->Parent = nullptr;
        Frontier.push(CurrentNode);

        //Register node as explored
        Explored.insert(CurrentNode->State->Name);

        while (!Frontier.empty()) {
            //Choose shallowest node from frontier
            CurrentNode = (node *)Frontier.front();
            //Remove the node from frontier
            Frontier.pop();

            //Goal test
            if(CurrentNode->State == Goal) {
                return print(CurrentNode);
            }

            //Iterate over all possible routes from current node
            for(list<route *>::iterator i = CurrentNode->State->Routes.begin(); i!=CurrentNode->State->Routes.end(); i++) {
                //Check if the node for the route has been explored before
                unordered_set<string>::iterator Location = Explored.find(((state *)(*i)->Destination)->Name);

                //If node doesnt exist in Explored i.e its not opened or closed,
                //New route found
                if(Location == Explored.end()) {
                    //Create new node for the route
                    node *Child = new node;
                    Child->State = (state *)(*i)->Destination;
                    Child->PathCost = CurrentNode->PathCost+1;
                    Child->Parent = CurrentNode;

                    //Add the route to the frontier
                    Frontier.push(Child);

                    //Register node as explored
                    Explored.insert(Child->State->Name);
                }
            }
        }

        //If Frontier is empty and BFS ended then route doesnt exist.
        cout<<"Couldn't find a route!"<<endl;
        return print(nullptr);
    }
};

class DepthFirstSearch {
private:
    struct node {
        state *State;              //Pointer to current state
        unsigned int PathCost;     //Path cost till current state
        node *Parent;              //Pointer to parent node
    };

    string print(node *Trace) {
        string Output = "";
        while (Trace != nullptr) {
            string t = Trace->State->Name + " " + to_string(Trace->PathCost) + "\n";
            Output = t + Output;
            Trace = Trace->Parent;
        }
        return Output;
    }

public:
    string run(state *Start, state *Goal) {
        stack<node *> Frontier;                      //Frontier node list
        unordered_set<string> Explored;              //Stores set of all nodes opened and closed

        //Create and add start node in frontier
        node *CurrentNode = new node;
        CurrentNode->State = Start;
        CurrentNode->PathCost = 0;
        CurrentNode->Parent = nullptr;
        Frontier.push(CurrentNode);

        //Register node as explored
        Explored.insert(CurrentNode->State->Name);

        while (!Frontier.empty()) {
            //Choose shallowest node from frontier
            CurrentNode = (node *)Frontier.top();
            //Remove the node from frontier
            Frontier.pop();

            //Goal test
            if(CurrentNode->State == Goal) {
                return print(CurrentNode);
            }

            //Iterate over all possible routes from current node
            for(list<route *>::reverse_iterator i = CurrentNode->State->Routes.rbegin(); i!=CurrentNode->State->Routes.rend(); i++) {
                //Check if the node for the route has been explored before
                unordered_set<string>::iterator Location = Explored.find(((state *)(*i)->Destination)->Name);

                //If node doesnt exist in Explored i.e its not opened or closed,
                //New route found
                if(Location == Explored.end()) {
                    //Create new node for the route
                    node *Child = new node;
                    Child->State = (state *)(*i)->Destination;
                    Child->PathCost = CurrentNode->PathCost+1;
                    Child->Parent = CurrentNode;

                    //Add the route to the frontier
                    Frontier.push(Child);

                    //Register node as explored
                    Explored.insert(Child->State->Name);
                }
            }
        }

        //If Frontier is empty and DFS ended then route doesnt exist.
        cout<<"Couldn't find a route!"<<endl;
        return print(nullptr);
    }
};

class UniformCostSearch {
private:
    struct node {
        state *State;               //Pointer to current state
        unsigned int PathCost;      //Path cost till current state
        node *Parent;               //Pointer to parent node
        bool Closed;                //Indicates whether the node is closed
    };

    string print(node *Trace) {
        string Output = "";
        while(Trace != nullptr) {
            string t = Trace->State->Name + " " + to_string(Trace->PathCost) + "\n";
            Output = t + Output;
            Trace = Trace->Parent;
        }
        return Output;
    }

public:
    string run(state *Start, state *Goal) {
        list<node *> Frontier;                      //Frontier node list
        unordered_map<string, node *> Explored;     //Stores set of all nodes opened and closed

        //Create and add start node in frontier
        node *CurrentNode = new node;
        CurrentNode->State = Start;
        CurrentNode->PathCost = 0;
        CurrentNode->Parent = nullptr;
        CurrentNode->Closed = false;
        Frontier.push_back(CurrentNode);

        //Register node as explored
        Explored[CurrentNode->State->Name] = CurrentNode;

        while (!Frontier.empty()) {
            //Choose shallowest node from frontier
            CurrentNode = (node *)Frontier.front();
            //Remove the node from frontier
            Frontier.pop_front();

            //Goal test
            if(CurrentNode->State == Goal) {
                return print(CurrentNode);
            }

            //Iterate over all possible routes from current node
            for(list<route *>::iterator i = CurrentNode->State->Routes.begin(); i!=CurrentNode->State->Routes.end(); i++) {
                //Check if the node for the route has been explored before
                unordered_map<string, node *>::iterator Location = Explored.find(((state *)(*i)->Destination)->Name);

                //If node doesnt exist in Explored i.e its not opened or closed,
                //New route found
                if(Location == Explored.end()) {
                    //Create new node for the route
                    node *Child = new node;
                    Child->State = (state *)(*i)->Destination;
                    Child->PathCost = CurrentNode->PathCost + (*i)->Cost;
                    Child->Parent = CurrentNode;
                    Child->Closed = false;

                    //Add the route to the frontier
                    Frontier.push_back(Child);

                    //Register node as explored
                    Explored[Child->State->Name] = Child;
                }
                //If node exists in Explored and is open i.e it is present in the Frontier
                else if(!(*Location).second->Closed) {
                    unsigned int ChildPathCost = CurrentNode->PathCost + (*i)->Cost;
                    //if PathCost(child) < PathCost(node)
                    //Better path found
                    if(ChildPathCost < (*Location).second->PathCost) {
                        //Update node
                        (*Location).second->Parent = CurrentNode;
                        (*Location).second->PathCost = ChildPathCost;
                    }
                }
                //If node exists in Explored and is closed
                else if((*Location).second->Closed) {
                    unsigned int ChildPathCost = CurrentNode->PathCost + (*i)->Cost;
                    //if PathCost(child) < PathCost(node)
                    //Better path found
                    if(ChildPathCost < (*Location).second->PathCost) {
                        //Update node
                        (*Location).second->Parent = CurrentNode;
                        (*Location).second->PathCost = ChildPathCost;
                        (*Location).second->Closed = false;
                        //Add node back to Frontier
                        Frontier.push_back((*Location).second);
                    }
                }
            }

            //Close the Current Node
            CurrentNode->Closed = true;
            Frontier.sort([](const node *i, const node *j) { return (i->PathCost < j->PathCost); });
        }

        //If Frontier is empty and BFS ended then route doesnt exist.
        cout<<"Couldn't find a route!"<<endl;
        return print(nullptr);
    }
};

class AStarSearch {
private:
    struct node {
        state *State;                   //Pointer to current state
        unsigned int PathCost;          //Path cost till current state
        unsigned int EstimatedPathCost; //Estimated Cost = PathCost + Heuristic
        node *Parent;                   //Pointer to parent node
        bool Closed;                    //Indicates whether the node is closed
    };

    string print(node *Trace) {
        string Output = "";
        while(Trace != nullptr) {
            string t = Trace->State->Name + " " + to_string(Trace->PathCost) + "\n";
            Output = t + Output;
            Trace = Trace->Parent;
        }
        return Output;
    }

public:
    string run(state *Start, state *Goal) {
        list<node *> Frontier;                      //Frontier node list
        unordered_map<string, node *> Explored;     //Stores set of all nodes opened and closed

        //Create and add start node in frontier
        node *CurrentNode = new node;
        CurrentNode->State = Start;
        CurrentNode->PathCost = 0;
        CurrentNode->EstimatedPathCost = Start->Heuristic;
        CurrentNode->Parent = nullptr;
        CurrentNode->Closed = false;
        Frontier.push_back(CurrentNode);

        //Register node as explored
        Explored[CurrentNode->State->Name] = CurrentNode;

        while (!Frontier.empty()) {
            //Choose shallowest node from frontier
            CurrentNode = (node *)Frontier.front();
            //Remove the node from frontier
            Frontier.pop_front();

            //Goal test
            if(CurrentNode->State == Goal) {
                return print(CurrentNode);
            }

            //Iterate over all possible routes from current node
            for(list<route *>::iterator i = CurrentNode->State->Routes.begin(); i!=CurrentNode->State->Routes.end(); i++) {
                //Check if the node for the route has been explored before
                unordered_map<string, node *>::iterator Location = Explored.find(((state *)(*i)->Destination)->Name);

                //If node doesnt exist in Explored i.e its not opened or closed,
                //New route found
                if(Location == Explored.end()) {
                    //Create new node for the route
                    node *Child = new node;
                    Child->State = (state *)(*i)->Destination;
                    Child->PathCost = CurrentNode->PathCost + (*i)->Cost;
                    Child->EstimatedPathCost = Child->PathCost + Child->State->Heuristic;
                    Child->Parent = CurrentNode;
                    Child->Closed = false;

                    //Add the route to the frontier
                    Frontier.push_back(Child);

                    //Register node as explored
                    Explored[Child->State->Name] = Child;
                }
                //If node exists in Explored and is open i.e it is present in the Frontier
                else if(!(*Location).second->Closed) {
                    unsigned int ChildPathCost = CurrentNode->PathCost + (*i)->Cost;
                    //if PathCost(child) < PathCost(node)
                    //Better path found
                    if(ChildPathCost < (*Location).second->PathCost) {
                        //Update node
                        (*Location).second->Parent = CurrentNode;
                        (*Location).second->PathCost = ChildPathCost;
                        (*Location).second->EstimatedPathCost = ChildPathCost + (*Location).second->State->Heuristic;
                    }
                }
                //If node exists in Explored and is closed
                else if((*Location).second->Closed) {
                    unsigned int ChildPathCost = CurrentNode->PathCost + (*i)->Cost;
                    //if PathCost(child) < PathCost(node)
                    //Better path found
                    if(ChildPathCost < (*Location).second->PathCost) {
                        //Update node
                        (*Location).second->Parent = CurrentNode;
                        (*Location).second->PathCost = ChildPathCost;
                        (*Location).second->EstimatedPathCost = ChildPathCost + (*Location).second->State->Heuristic;
                        (*Location).second->Closed = false;
                        //Add node back to Frontier
                        Frontier.push_back((*Location).second);
                    }
                }
            }

            //Close the Current Node
            CurrentNode->Closed = true;
            Frontier.sort([](const node *i, const node *j) { return (i->EstimatedPathCost < j->EstimatedPathCost); });
        }

        //If Frontier is empty and BFS ended then route doesnt exist.
        cout<<"Couldn't find a route!"<<endl;
        return print(nullptr);
    }
};

int main() {
    string Algo, Start, Goal;
    int LTLNum, STLNum;
    unordered_map<string, state *> StateList;      //Stores pointers to each state

    ifstream InputFile ("input.txt");
    if(InputFile.is_open()) {
        getline(InputFile,Algo);    //Get Algorithm Name
        getline(InputFile,Start);   //Get Start State Name
        getline(InputFile,Goal);    //Get Goal State Name

        string TempString;          //Stores Temp Input Lines

        //Get and Store Live Traffic Data
        getline(InputFile,TempString);
        LTLNum = stoi(TempString);
        for(int i=0; i<LTLNum; i++) {
            getline(InputFile,TempString);

            //Split and store TempString over " "
            string TempArray[3];
            stringstream SS(TempString);
            for(int j=0; j<3; j++)
                SS>>TempArray[j];

            state *TempStateA, *TempStateB;         //Variables for Temp States

            //Check if State A Exists in StateList
            if(StateList.find(TempArray[0]) != StateList.end()) {
                TempStateA = StateList[TempArray[0]];
            }
            else {
                //Else create new State A and Insert in StateList
                TempStateA = new state;
                StateList[TempArray[0]] = TempStateA;
                TempStateA->Name = TempArray[0];
            }
            //Check if State B Exists in StateList
            if(StateList.find(TempArray[1]) != StateList.end()) {
                TempStateB = StateList[TempArray[1]];
            }
            else {
                //Else create new State B and Insert in StateList
                TempStateB = new state;
                StateList[TempArray[1]] = TempStateB;
                TempStateB->Name = TempArray[1];
            }

            //Create new route
            route *TempRoute = new route;
            TempRoute->Destination = TempStateB;
            TempRoute->Cost = (unsigned int)stoi(TempArray[2]);

            //Add route to State A's routes
            TempStateA->Routes.push_back(TempRoute);
        }

        //Get and Store Sunday Traffic Data
        getline(InputFile,TempString);
        STLNum = stoi(TempString);
        for(int i=0; i<STLNum; i++) {
            getline(InputFile,TempString);

            //Split and store TempString over " "
            string TempArray[2];
            stringstream SS(TempString);
            for(int j=0; j<2; j++)
                SS>>TempArray[j];

            //Store heuristic in State
            StateList[TempArray[0]]->Heuristic = (unsigned int)stoi(TempArray[1]);
        }

        InputFile.close();
    }
    else {
        cout<<"Input file failed to load"<<endl;
    }


    cout<<"Selecting Algorithm....."<<endl;

    //Output variable containing the trace from Goal to Start
    string Output = "";

    //Run specified algorithm
    if(Algo.compare("BFS") == 0) {
        cout<<"Running Breadth First Search"<<endl;
        BreadthFirstSearch BFS;
        Output = BFS.run(StateList[Start], StateList[Goal]);
    }
    else if(Algo.compare("DFS") == 0) {
        cout<<"Running Depth First Search"<<endl;
        DepthFirstSearch DFS;
        Output = DFS.run(StateList[Start], StateList[Goal]);
    }
    else if(Algo.compare("UCS") == 0) {
        cout<<"Running Uniform Cost Search"<<endl;
        UniformCostSearch UCS;
        Output = UCS.run(StateList[Start], StateList[Goal]);
    }
    else if(Algo.compare("A*") == 0) {
        cout<<"Running A* Search"<<endl;
        AStarSearch ASS;
        Output = ASS.run(StateList[Start], StateList[Goal]);
    }

    cout<<Output;

    ofstream OutputFile ("output.txt");
    if(OutputFile.is_open()) {
        OutputFile<<Output;
        cout<<"Output Success"<<endl;
    }
    else {
        cout<<"Output file failed to load"<<endl;
    }

    return 0;
}
