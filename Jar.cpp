#include <iostream>
#include "Jar.h"

using namespace std;

/**
 * κατασκευαστής του δοχείου
 * @param random, ένα vector με αριθμούς που αναπαριστούν τα χρώματα που θα έχει αρχικά το δοχείο.
 *                Στη συνέχεια, κάθε χρώμα εισάγεται στην στοίβα του δοχείου
 */
Jar::Jar(vector<short int> random){
    for(short int i=0;i<random.size();i++){
        colors.push(random[i]);
    }

    random.clear();
}

/**
 * Επιστρέφει την στοίβα με τα χρώματα
*/
stack<char> Jar:: getColors(){
    return colors;
}

/**
 * setter για την στοίβα με τα χρώματα
 * @param colors, μία στοίβα με τα χρώματα που θα έχει το δοχείο
 */
void Jar::setColors(stack<char> colors){
    this->colors=colors;
}

/**
 * Η συνάρτηση δείχνει αν το δοχείο είναι γεμάτο
 * @return true, αν είναι γεμάτο το δοχείο
           false, σε άλλη περίπτωση
 */
bool Jar::isFull(){
    return (colors.size()==4);

}

/**
 * Η συνάρτηση δείχνει αν το δοχείο είναι άδειο
 * @return true, αν είναι άδειο
           false, σε άλλη περίπτωση
 */
bool Jar::isEmpty(){

    return colors.empty();
}


/**
 * Η συνάρτηση εντοπίζει το χρώμα που βρίσκεται στην κορυφή καθώς και τα ml που υπάρχουν στην κορυφή από το ίδιο χρώμα
 * @return τις πληροφορίες με την βοήθεια του struct details
 */
details* Jar::getTop(){
    short int i;
    details* temp;
    temp= new details;

    if(isEmpty()){
        temp->top=-1;
        temp->ml=0;
        return temp;
    }

    stack<char> help= colors;
    bool flag=false;

    temp->top=help.top();

    for(i=0;!flag;i++){
        help.pop();
        if(help.empty() || (temp->top != help.top())){
            flag=true;
        }
    }

    temp->ml=i;

    return temp;
}

/**
 * Η συνάρτηση εντοπίζει αν το δοχείο είναι γεμάτο (4ml) με ένα μόνο χρώμα και επιστρέφει ανάλογα μία λογική τιμή
 */
bool Jar::isOneColor(){

    if(!isFull()){
        return false;
    }

    char* temp;
    temp= new char[colors.size()];

    stack<char> help= colors;

    for(short int i=0;!help.empty();i++){
        temp[i]=help.top();

        help.pop();
    }

    for(short int i=1;i<colors.size();i++){
        if(temp[i]!=temp[i-1]){
            return false;
        }
    }

    return true;
}

/**
 * Η συνάρτηση προσθέτει το νέο χρώμα που δείνει η μεταβλητή newColor->top, στην κορυφή του δοχείου σε ποσότητα ίση με newColor->ml
 * Αν η κορυφή του δοχείου είναι διαφορετική από την μεταβλητή newColor->top, τότε δεν τοποθετείται το νέο χρώμα
 * Σε άλλη περίπτωση, τοποθετείται το νέο χρώμα στην κορυφή σε ποσότητα ίση με newColor->ml.
 * Αν το δοχείο είναι γεμάτο, τότε σταματάει η εισαγωγή του χρώματος ακόμα και αν δεν έχουν τοποθετήθεί όλα τα ml από το νέο χρώμα
 * @return Την ποσότητα σε ml, που δεν μπόρεσαν να εισαχθούν στο δοχείο
 */
short int Jar::addColor(details* newColor){

    if(!isEmpty() && (colors.top()!= newColor->top)){
        return newColor->ml;
    }

    for(;!isFull() && newColor->ml>0;){
        colors.push(newColor->top);
        newColor->ml--;
    }

    return newColor->ml;
}

/**
 * Αφαιρεί την κορυφή με όλα τα ml της
 * @return false, αν το δοχείο ήταν άδειο, οπότε δεν έχει κορυφή η στοίβα
           true, σε άλλη περίπτωση
 */
bool Jar::removeTop(){

    if(isEmpty()){
        return false;
    }

    details* temp=getTop();

    for(short int i=0;i<temp->ml;i++){
        colors.pop();
    }

    return true;

}

/**
 * Αφαιρεί την κορυφή σε ml ίσα με την @param ml
 * @return false, αν το δοχείο ήταν άδειο, οπότε δεν έχει κορυφή η στοίβα
           true, σε άλλη περίπτωση
 */
bool Jar::removeTop(short int ml){
    if(isEmpty() || ml>getTop()->ml){
        return false;
    }

    details* temp=getTop();

    for(short int i=0;i<ml;i++){
        colors.pop();
    }

    return true;

}

/**
 * Μεταφέρει την κορυφή του δοχείου, στην κορυφή του δοχείου @param other
 * @return true, αν η μεταφορά έγινε με επιτυχία
           false, αν δεν μπόρεσε να μεταφερθεί η κορυφή
 */
bool Jar::transferTop(Jar* other){
    short int left, ml;

    details* temp= getTop();

    ml= temp->ml;
    left=other->addColor(temp);

    if(left==ml){
        return false;
    }

    return removeTop(ml-left);

}

bool Jar::operator==(const Jar& o) const{

    if(colors.size()!=o.colors.size()){
        return false;
    }

    stack<char> temp1;
    stack<char> temp2;

    temp1=colors;
    temp2=o.colors;

    while(!temp1.empty()){
        if(temp1.top()!=temp2.top()){
            return false;
        }
        temp1.pop();
        temp2.pop();
    }

    return true;

}

Jar Jar:: operator= (Jar o){
    this->colors=o.colors;

    return *this;
}

void Jar::seeJar(){
    stack<char> help= colors;

    if(help.size()<4){
        short int i;
        for(i=0;i+help.size()<4;i++){
            cout<<"|   |"<<endl;
        }
    }

    for(;!help.empty();){
        cout<<"| "<<int(help.top())<<" |"<<endl;
        help.pop();
    }

    cout<<"- - -"<<endl;

}

