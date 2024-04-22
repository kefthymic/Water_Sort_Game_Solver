#include "Game.h"
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

/**
 * Κενός κατασκευαστής
 */
Game::Game(){
    previous=nullptr;
    actionName="";

}

/**
 * Αυτός ο κατασκευαστής δέχεται ένα vector, που περιέχει ένα σύνολο από vectors<short int>, όπου το κάθε ένα vector από αυτό το σύνολο αναπαριστά ένα δοχείο
 * Το πλήθος των χρωμάτων είναι ίσο με το πλήθος όλων των δοχείων μειωμένο κατά δύο
 */
Game::Game(vector< vector<short int> > random){
    jars= new Jar*[random.size()];

    for(short int i=0;i<random.size();i++){
        jars[i]= new Jar(random[i]);
    }

    colors= random.size()-2;

    actionName="";
    previous=nullptr;
}

Game::Game(short int colors, Jar** jars, Game* previous, string actionName){
    this->colors=colors;
    this->jars=jars;
    this->previous=previous;
    this->actionName=actionName;

}

void Game::setColors(short int colors){
    this->colors=colors;
}

void Game::setJars(Jar** jars){
    this->jars=jars;
}

void Game::setPrevious(Game* previous){
    this->previous=previous;
}

void Game::setActionName(string actionName){
    this->actionName=actionName;
}

/**
 * Για την δημιουργία του actionName χρησιμοποιείται αυτή η συνάρτηση
 * Δέχεται δύο παραμέτρους: @param from, που δείχνει από πιο δοχείο μεταφέρθηκε η κορυφή
                            @param to, που δείχνει σε πιο δοχείο μεταφέρθηκε
 */
void Game::setActionName(short int from, short int to){
    actionName="transfer the color from the top of the "+to_string(from+1)+" jar to the top of the "+to_string(to+1)+" jar";
}

short int Game::getColors(){
    return colors;
}

Jar** Game::getJars(){
    return jars;
}

Game* Game::getPrevious(){
    return previous;
}

string Game::getActionName(){
    return actionName;
}


/**
 * Μεταφέρει την κορυφή από το δοχείο που δείχνει η @param current, στο δοχείο που δείχνει η @param next
 * @param n, σε αυτή την μεταβλητή αποθηκεύεται αρχικά η παρούσα κατάσταση, έτσι ώστε η μεταφορά των κορυφών να γίνεται σε αυτή την παράμετρο
 */
bool Game:: transferToOther(short int current, short int next, Game& n){
    n=*this;

    if(n.jars[current]->transferTop(n.jars[next])){
        n.setPrevious(this);
        n.setActionName(current, next);

        return true;
    }

    return false;

}

/**
 * Η συνάρτηση χρησιμοποιείται, ώστε να αποθηκευτούν όλα τα παιδιά, που μπορούν να παραχθούν απο την παρούσα κατάσταση, σε ένα vector<Game*>
 * @return ένα vector<Game*> με όλα τα παιδιά της κατάστασης
 */
vector<Game*> Game::expand(){
    vector<Game*> children;
    Game* child;

    for(short int i=0;i<colors+2;i++){
        for(short int j=0;j<colors+2;j++){
            if(i!=j){
                child=new Game(*this);

                if(transferToOther(i, j, *child)){
                    children.push_back(child);
                }
                else{
                    delete child;
                }
            }
        }
    }

    return children;

}

/**
 * Ελέγχει αν η παρούσα κατάσταση είναι τελική και επιστρέφει ανάλογα μία λογική τιμή
 */
bool Game::gameOver(){
    short int temp;
    temp=0;

    for(short int i=0;i<colors+2;i++){
        if(jars[i]->isOneColor()){
            temp++;
        }
    }

    if(temp==colors){
        return true;
    }

    return false;
}

/**
 * Συνάρτηση που δημιουργεί ένα ξεχωριστό κλειδί για κάθε μία κατάσταση.
 *
 * Για την δημιουργία του κλειδιού, αρχικά δημιουργείται ένας πίνακας string* tempKey, με θέσεις όσες και το πλήθος των δοχείων που υπάρχουν στο παιχνίδι.
 * Η κάθε μία θέση αυτού του πίνακα, αναφέρεται στο αντίστοιχο δοχείο του παιχνιδιού.
 * Σε κάθε στοιχείο του πίνακα tempKey, αποθηκεύονται όλα τα χρώματα που υπάρχουν στο αντίστοιχο δοχείο(char) σε μία σειρά, με πρώτο το στοιχείο που βρίσκεται στον πάτο του δοχείου
 * Σε κάθε ένα χρώμα ξεχωριστά, προστίθεται ο αριθμός 96, έτσι ώστε το χρώμα με αριθμό 1, να συμβολίζεται με το γράμμα 'a' και αντίστοιχα τα υπόλοιπα.
 *                              Έτσι, κάθε ένα χρώμα αντιστοιχίζεται με ένα μόνο γράμμα του λατινικού αλφαβήτου.
 *                              Αν το δοχείο έχει κενές θέσεις, για κάθε μία κενή αποθηκεύεται το σύμβολο με αριθμό ascii: το 96
 *                              Με αυτό τον τρόπο δημιουργείται μία συμβολοσειρά για κάθε ένα δοχείο
 * Επειδή στο παιχνίδι δεν έχει σχέση σε πια θέση βρίσκεται ένα δοχείο, ταξινομείται σε αύξουσα σειρά ο tempKey με τις συναρτήσεις της mergeSort, έτσι ώστε τα παρόμοια στιγμιότυπα να έχουν ίδιο κλειδί
 *                              Αυτό έχει ως αποτέλεσμα, στον αλγόριθμο DFS, το μέτωπο αναζήτησης να μην μεγαλώνει άσκοπα
 * Στο τέλος, ενώνονται όλα τα στοιχεία του ταξινομημένου πίνακα tempKey, δημιουργώντας έτσι το κλειδί
 * @return το κλειδί της παρούσας κατάστασης
 */
string Game:: getKey(){
    short int i, j;
    string* tempKey;
    string key;

    stack<char> help;

    Jar** jars= getJars();
    stack<char> temp;

    tempKey= new string[getColors()+2];

    for(i=0;i<getColors()+2;i++){
        temp=jars[i]->getColors();

        for(j=0;!temp.empty();j++){
            help.push(temp.top()+96);
            temp.pop();
        }

        while(!help.empty()){
            tempKey[i]+=help.top();
            help.pop();
        }

        for(;j<4;j++){
            tempKey[i]+=char(96);
        }
    }

    mergeSort(tempKey, 0, getColors()+2-1);

    key="";
    for(int i=0;i<getColors()+2;i++){
        key+=tempKey[i];
    }

    return key;
}


Game Game:: operator= (Game o){
    stack<char> temp;
    vector<short int> helpVector;
    short int* help;
    short int sizeTemp;

    colors=o.colors;
    jars=new Jar*[o.getColors()+2];

    for(short int i=0;i<o.getColors()+2;i++){
        temp=o.jars[i]->getColors();
        sizeTemp=temp.size();
        help=new short int[sizeTemp];

        for(short int j=sizeTemp-1;j>-1;j--){
            help[j]=temp.top();
            temp.pop();
        }

        for(short int j=0;j<sizeTemp;j++){
            helpVector.push_back(help[j]);
        }

        jars[i]= new Jar(helpVector);

        helpVector.resize(0);
        delete[] help;
    }

    previous=o.previous;
    actionName=o.actionName;

    return *this;
}

bool Game::operator==(const Game& o) const{
    Jar** temp1;
    Jar** temp2;

    temp1=jars;
    temp2=o.jars;

    if(colors!=o.colors){
        return false;
    }

    int howMany=0;
    for(int i=0;i<colors+2;i++){
        for(int j=0;j<o.colors+2;j++){
            if(temp1[i]==temp2[j]){
                howMany++;
            }
        }
    }

    if(howMany==colors+2){
        return true;
    }

    return false;


}

void Game::seeJars(){
    Jar** jars;
    jars= new Jar*[getColors()+2];

    for(int i=0;i<getColors()+2;i++){
        jars[i]= new Jar;
        jars[i]->setColors(this->jars[i]->getColors());
    }

    int* jarsSize; // δείχνει το μέγεθος κάθε δοχείου
    jarsSize= new int[getColors()+2];

    Jar** tempJars;
    tempJars= new Jar*[getColors()+2];

    for(int i=0;i<getColors()+2;i++){
        tempJars[i]= new Jar;
        tempJars[i]->setColors(this->jars[i]->getColors());
    }
    stack<char> temp;

    for(int i=0;i<getColors()+2; i++){
        jarsSize[i]=0;
        temp= tempJars[i]->getColors();
        while(!temp.empty()){
            jarsSize[i]++;
            temp.pop();
        }
        delete tempJars[i];
    }
    delete tempJars;

    for(short int i=0;i<4;i++){
        for(int j=0;j<getColors()+2;j++){
            cout<<"|";
            if(jars[j]->getTop()->top>=1 && jarsSize[j]==4){
                    if(jars[j]->getTop()->top<10){
                        cout<<" "<<jars[j]->getTop()->top<<" ";
                    }
                    else{
                        cout<<" "<<jars[j]->getTop()->top;
                    }
                jars[j]->removeTop(1);
            }
            else{
                jarsSize[j]++;
                cout<<"   ";
            }
            cout<<"|  ";

        }
        cout<<endl;
    }
}

void myMerge(string *arr, short start, short mid, short last){
    short i, j, k;

    short size1= mid-start+1;
    short size2= last-mid;

    string *temp1, *temp2;

    temp1= new string[size1];
    temp2= new string[size2];

    for(i=0;i<size1;i++){
        temp1[i]=arr[start+i];
    }
    for(i=0;i<size2;i++){
        temp2[i]=arr[mid+1+i];
    }

    i=0;
    j=0;
    k=start;

    while(i<size1 && j<size2){
        if(temp1[i]>=temp2[j]){
            arr[k]=temp1[i];
            i++;
        }
        else{
            arr[k]=temp2[j];
            j++;
        }
        k++;
    }

    while(i<size1){
        arr[k]=temp1[i];
        i++;
        k++;
    }
    while(j<size2){
        arr[k]=temp2[j];
        j++;
        k++;
    }

}

 void mergeSort(string *arr, short start, short last){
    short int mid;

    if(start>=last){
        return;
    }

    mid= (start+last)/2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid+1, last);
    myMerge(arr, start, mid, last);

 }


