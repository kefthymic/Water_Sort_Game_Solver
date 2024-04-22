#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>

#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>

#include "Jar.h"
#include "Game.h"

using namespace std;



Game *BFS(Game *start){
    long int memory;
    long int examined;
    queue<Game*>* forSearch;
    unordered_set<string> closed;


    forSearch= new queue<Game*>;

    forSearch->push(start);

    memory=1;
    examined=0;

    while(forSearch->size()>0){
        if(forSearch->size() + closed.size()> memory){
            memory= forSearch->size() + closed.size();
        }

        Game* s= forSearch->front();
        forSearch->pop();

        if(closed.count(s->getKey())==0){
            examined++;
            if(s->gameOver()){
                cout<<"Solved"<<endl;
                cout<<"Memory: "<<memory<<", examined: "<<examined<<endl;
                return s;
            }

            closed.insert(s->getKey());

            vector<Game*> children=s->expand();
            for(unsigned int i=0; i<children.size();i++){
                if(closed.count(children[i]->getKey())==0 ){
                    forSearch->push(children[i]);
                }
            }
        }
    }
    return nullptr;
}


int main()
{
    srand(time(NULL));
    int howManyColors;

    do{
        howManyColors=rand()%17+1;
    }while(howManyColors>17);

    short int* numbers;
    numbers= new short int[(howManyColors+2)*4];

    short int i;
    for(i=0;i<howManyColors;i++){
        for(short int j=0;j<4;j++){
            numbers[i*4+j]=i+1;
        }
    }

    for(;i<howManyColors+2;i++){
        for(short int j=0;j<4;j++){
            numbers[i*4+j]=0;
        }
    }

    random_shuffle(numbers, numbers+(howManyColors+2)*4);

    vector<vector<short int> > random;
    vector<short int> temp;

    for(short int i=0;i<howManyColors+2;i++){

        for(short int j=0;j<4;j++){
            if(numbers[i*4+j]!=0){
                temp.push_back(numbers[i*4+j]);
            }
        }
        random.push_back(temp);
        temp.resize(0);
    }

    delete[] numbers;

    Game* game;
    Game* solution;
    game= new Game(random);

    Jar** jars= game->getJars();

    game->seeJars();

    solution=BFS(game);

    if(solution==nullptr){
        cout<<"There is not a solution"<<endl;
    }
    else{
        Jar** jars2= solution->getJars();
        solution->seeJars();
    }

    stack<Game*> help;
    while(solution){
        help.push(solution);
        solution=solution->getPrevious();
    }

    while(!help.empty()){
        cout<<help.top()->getActionName()<<endl;
        help.pop();
    }

    return 0;
}

