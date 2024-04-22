#ifndef GAME_H
#define GAME_H

#include "Jar.h"
#include <stack>
#include <string>


using namespace std;

/**
 * Η κλάση Game, αναπαριστά το παιχνίδι.
 * Περιέχει: μια μεταβλητή colors, που δείχνει πόσα διαφορετικά χρώματα υπάρχουν συνολικά στο παιχνίδι
 *           έναν πίνακα Jar** jars, που περιέχει όλα τα δοχεία του παιχνιδιού
 *           έναν δείκτη Game* previous, που δείχνει την προηγούμενη κατάσταση από αυτήν
 *           μια συμβολοσειρά actionName, που αναφέρει την τελευταία ενέργεια που έγινε, ώστε να βρεθεί το παιχνίδι στην παρούσα κατάσταση
 */
class Game{
    private:
        short int colors;
        Jar** jars;
        Game* previous;
        string actionName;
    public:
        /**
         * Κατασκευαστές
         */
        Game();
        Game(vector<vector<short int> > );
        Game(short int, Jar**, Game*, string);

        /**
         * setters
         */
        void setColors(short int );
        void setJars(Jar** );
        void setPrevious(Game*);
        void setActionName(string);
        void setActionName(short int , short int );

        /**
         * getters
         */
        short int getColors();
        Jar** getJars();
        Game* getPrevious();
        string getActionName();

        vector<Game* > expand();//βρίσκει τα παιδιά, που μπορούν να παραχθούν από την παρούσα κατάσταση
        bool transferToOther(short int, short int ,Game& );// Μεταφέρει την κορυφή από ένα δοχείο σε ένα άλλο

        string getKey();//Παραγωγή κλειδιού, που χρησιμοποιείται στο DFS

        bool gameOver();//Συνάρτηση που εντοπίζει αν η παρούσα κατάσταση είναι η τελική του παιχνιδιού

        Game operator= (Game o);
        bool operator==(const Game& o) const;

        void seeJars();

};

/**
 * Βοηθητικές συναρτήσεις που χρησιμοποιούνται για την παραγωγή του κλειδιού
 */
void myMerge(string*, short, short, short);
void mergeSort(string*, short, short);


#endif // GAME_H
