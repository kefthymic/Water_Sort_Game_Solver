#ifndef JAR_H
#define JAR_H

#include <stack>
#include <algorithm>

using namespace std;

/**
 * το struct details περιέχει τις πληροφορίες για την κορυφή του δοχείο.
 * @top αποθηκεύεται το χρώμα που βρίσκεται στην κορυφή (ένας ακέραιος αριθμός από το 1 μέχρι και το 17)
 * @ml αποθηκεύεται η ποσότητα σε ml που υπάρχει στην κορυφή από το ίδιο χρώμα
*/
struct details{
    short int top;
    short int ml;
};

/**
 * Η κλάση Jar αναπαριστά ένα δοχείο με τις ιδιότητές του.
*/
class Jar{

    private:
        stack<char> colors; //Το δοχείο αναπαριστάται από μία στοίβα με μέγιστη χωρητικότητα τα 4 ml
    public:
        Jar(){}
        Jar(vector<short int> );

        stack<char> getColors();//Επιστρέφει την στοίβα με τα χρώματα
        void setColors(stack<char>);

        bool isOneColor();//Επιστρέφει μία λογική τιμή, που δείχνει αν το δοχείο είναι γεμάτο με ένα μόνο χρώμα
        bool isFull();
        bool isEmpty();
        details* getTop();// Επιστρέφει τις πληροφορίες για την κορυφή του δοχείου
        short int addColor(details*);// Προσθέτει στην κορυφή του δοχείου νέο χρώμα
        bool removeTop();// Αφαιρεί όλα τα ml του ίδιου χρώματος της κορυφής του δοχείου
        bool removeTop(short int);// Αφαιρεί συγκεκριμένα ml από την κορυφή του δοχείου

        bool transferTop(Jar*);// Μεταφέρει την κορυφή ενός δοχείου στην κορυφή ενός άλλου δοχείου

        bool operator==(const Jar& ) const;

        Jar operator= (Jar );

        void seeJar();// Εμφανίζονται οι πληροφορίες του δοχείου
};



#endif // JAR_H
