/*
 Namn: Fredrik Sellgren
 Datum: 2018-01-10
 Kurs: DT028G - Introduktion till programmering
 Labb: CowBull
 */


#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <unistd.h>
#include <vector>





using namespace std;

bool unique(int * arr, int len) // tittar så alla siffror är unika
{
    for(int i = 0; i < len; i++)
        for(int j = 0; j < len; j++)
            if(arr[i] == arr[j] && i != j )
            {
                return false;
            }
    return true;
}

vector<string> hidden_numbers() // Hämtar alla kombinationer av giltiga lösningar.
{
    vector<string> hidden;
    const int size = 4;
    for(int i = 1; i < 10; i++)
        for(int j = 0; j < 10; j++)
            for(int k = 0; k < 10; k++)
                for(int l = 0; l < 10; l++)
                {
                    int arr[] = {i, j, k, l};
                    if(unique(arr, size))
                    {
                        hidden.push_back((to_string(arr[0]))+(to_string(arr[1]))+(to_string(arr[2]))+(to_string(arr[3])));
                    }
                }
    return hidden;
}

string hidden_number() // Tar ett random tal ur de giltiga lösningarna
{
    vector<string> hidden;
    string hidden_answer = "";
    
    hidden = hidden_numbers();
    
    string s = "1234567890";
    random_shuffle(s.begin(), s.end());
    string g = s.substr(0,4);
    srand ((time(NULL))+(stoi(g)));
    hidden_answer = hidden[rand() % hidden.size()];
    return hidden_answer;
}

bool innehaller_samma(string samma) // Tittar så att alla siffror är unika.
{
    sort(samma.begin(), samma.end());// sorterar siffrorna så att siffror som är lika hamnar jämte varandra.
    return adjacent_find(samma.begin(), samma.end()) != samma.end();
}

bool guess_filter(string &guess, vector<string> &guesses) // Kollar så att nästa gissning är unik och att den inte upprepas.
{
    int arr[] = {stoi(guess)};
    
    return(guess.length() == 4 && unique(arr, 4) && find(guesses.begin(), guesses.end(), guess) != guesses.end());
}

bool removed = 0;    //Global variabel då den används i alla spel

string computer_guess(int &count, vector<string> &brain, int &t, int &k) // Generarar en gissning åt datorn.
{
    
    
    string comp_guess;
    if(t + k != 4)
    {
        if(count == 0 && !removed) // vill att datorn första rundan svarar detta
        {
            comp_guess = "1234";
        }
        else if(count == 1 && !removed)
        {
            
            comp_guess = "5678";
        }
        
        else
        {
            comp_guess = brain[rand() % brain.size()];
            
        }
        
    }
    else
    {
        comp_guess = brain[rand() % brain.size()];
        
        
    }
    return comp_guess;
}

vector <string> memory(vector<string> guesses) // Detta hjälper datorn att kom ihåg vilka svar denna kan ge.
{
    
    
    vector<string> mem;
    mem = hidden_numbers();
    for(int i = 0; i < mem.size(); i++)
    {
        for(int j=0; j<guesses.size(); j++)
        {
            if(mem[i]==guesses[j])
            {
                mem.erase(mem.begin()+i);
                --i;
                break;
            }
            
        }
    }
    return mem;
}

void not_right_spot(string &guess, vector<string> &guesses) // Hjälper datorn att sortera bort ogiltiga gissningar.
{
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            for(int k = 0; k < 10; k++)
                for(int l = 0; l < 10; l++)
                    if(i != l && i != j && i != k && i != l && j != k && j != l && l != k) // siffrorna måste vara unika.
                    {    // detta gör så att sifforna inte får ha samma position igen.
                        int arr[] = {i, j, k, l};
                        string cant_be = (to_string(arr[0]))+(to_string(arr[1]))+(to_string(arr[2]))+(to_string(arr[3]));
                        if(guess[0] == cant_be[0] || guess[1] == cant_be[1] || guess[2] == cant_be[2] || guess[3] == cant_be[3])
                        {
                            guesses.push_back(cant_be);
                        }
                        
                    }
}

void correct_numbers(string &guess, vector<string> &guesses) // Hjälper datorn att sortera bort ogiltiga gissningar.
{
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            for(int k = 0; k < 10; k++)
                for(int l = 0; l < 10; l++)
                    if(i != l && i != j && i != k && j != k && j != l && l != k) // siffrorna måste vara unika.
                    {    //Detta gör så att alla gissningar som inte innehåller gissningens siffror stoppas in i guesses vector, detta pga att siffrorna i gissningen ingår i lösningen.
                        int arr[] = {i, j, k, l};
                        string cant_be = (to_string(arr[0]))+(to_string(arr[1]))+(to_string(arr[2]))+(to_string(arr[3]));
                        if(guess[0] != cant_be[0])
                            if(guess[0] != cant_be[1])
                                if(guess[0] != cant_be[2])
                                    if(guess[0] != cant_be[3])
                                        if(guess[1] != cant_be[0])
                                            if(guess[1] != cant_be[1])
                                                if(guess[1] != cant_be[2])
                                                    if(guess[1] != cant_be[3])
                                                        if(guess[2] != cant_be[0])
                                                            if(guess[2] != cant_be[1])
                                                                if(guess[2] != cant_be[2])
                                                                    if(guess[2] != cant_be[3])
                                                                        if(guess[3] != cant_be[0])
                                                                            if(guess[3] != cant_be[1])
                                                                                if(guess[3] != cant_be[2])
                                                                                    if(guess[3] != cant_be[3])
                                                                                    {
                                                                                        guesses.push_back(cant_be);
                                                                                    }
                        
                    }
}

void none_right(string &guess, vector<string> &guesses) //Här tas alla giltiga gissningar och kollas mot gissnigen, datorn gjort.
{
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++)
            for(int k = 0; k < 10; k++)
                for(int l = 0; l < 10; l++)
                    if(i != l && i != j && i != k && j != k && j != l && l != k) // siffrorna måste vara unika.
                    {    //Detta gör så att alla gissningar som innehåller gissningens siffror stoppas in i guesses vector, detta pga att siffrorna inte ingår i lösningen.
                        int arr[] = {i, j, k, l};
                        string cant_be = (to_string(arr[0]))+(to_string(arr[1]))+(to_string(arr[2]))+(to_string(arr[3]));
                        for(int m = 0; m < 4; m++)
                            for(int n = 0; n < 4; n++)
                                if(guess[m] == cant_be[n])
                                {
                                    guesses.push_back(cant_be);
                                }
                        
                        
                    }
    
}



int bull_check(int hidden_answer_length, string &guess, string &hidden_answer) // tittar om talet innhåller en tjur
{
    int tjur = 0;
    for(int i = 0; i != hidden_answer_length; ++i)
    {
        int pos = hidden_answer.find(guess[i]);
        if(pos == i)
        {
            ++tjur;
        }
    }
    return tjur;
}
int cow_check(int hidden_answer_length, string &guess, string hidden_answer) // tittar om talet innehåller en ko
{
    int kor = 0;
    for(int i = 0; i != hidden_answer_length; ++i)
    {
        int pos = hidden_answer.find(guess[i]);
        if (guess.find(hidden_answer) != pos && pos != i)
        {
            ++kor;
        }
    }
    return kor;
}

void solve(vector<string> &brain, int &t, int &k, string &comp_guess) // Hjälper datorn att ta bort ogiltiga gissningar.
{
    for(int i = 0; i < brain.size(); i++)
    {
        int new_t = bull_check(comp_guess.size(), comp_guess, brain[i]);
        int new_k = cow_check(comp_guess.size(), comp_guess, brain[i]);
        
        if(new_t != t || new_k != k)
        {
            brain.erase(brain.begin()+i);
            --i;
        }
    }
    
}

void computer_solver(string &comp_guess, vector<string> &guesses, int &tjur, int &kor) // Datorn tar bort gissningar som inte är gilltiga.
{
    if(kor + tjur == 0)
    {
        none_right(comp_guess, guesses);
    }
    
    if(kor + tjur == 4)
    {
        
        correct_numbers(comp_guess, guesses);
        removed = 1;
        
        
    }
    
    if(tjur == 0)
    {
        
        not_right_spot(comp_guess, guesses);
        
    }
    sort(guesses.begin(), guesses.end());
    guesses.erase(unique(guesses.begin(), guesses.end()), guesses.end());
    
}


void ManvsComp()
{
    cout << "Du ska här tänka på att fyrsiffrigt tal" << endl;
    cout << "Datorn ska sedan lista ut det " << endl;
    cout << "Tryck på valfri tangent för att starta " << endl;
    cin.get();
    
    string comp_guess;
    int count = 0;
    int t = 0;
    int k = 0;
    int tjur = 0;
    int kor = 0;
    vector<string> guesses;
    vector<string> brain;
    
    while(tjur != 4)
    {
        
        if(guesses.size() >= 5040 || (tjur == 3 && kor == 1)) // Kollar ifall spelaren fuskat eller skrivit fel.
        {
            cout << "Jag spelare inte med fuskare, om 4 sekunder återvänder jag till menyn" << endl;
            usleep(4000000);
            guesses.clear();
            brain.clear();
            return;
        }
        comp_guess = computer_guess(count, brain, t, k);
        while(guess_filter(comp_guess, guesses)) comp_guess = computer_guess(count, brain, t, k); // kollar så att det är en giltig gissning.
        
        count++;
        cout << "Dator 1 tänker "<< endl;
        usleep(2000000);
        cout << comp_guess << endl;
        guesses.push_back(comp_guess);
        
        cout << " Hur många tjurar ?" << endl;
        while((!(cin >> tjur)) || (tjur >= 5) || (!(to_string(tjur).size() == 1))) // Tittar så att spelaren enbart matar in en siffra mellan 0 & 4.
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enbart en siffra, hur många tjurar ? ";
        }
        
        
        cout <<" Hur många kor ?" << endl;
        while((!(cin >> kor)) || (kor >= 5) || (!(to_string(kor).size() == 1)) || (kor + tjur >= 5)) // // Tittar så att spelaren enbart matar in en siffra mellan 0 & 4.
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enbart siffror, hur många kor ?, kor + tjur > 4 ";
        }
        
        t = tjur;
        k = kor;
        brain = memory(guesses);
        computer_solver(comp_guess, guesses, t, k);
        solve(brain, t, k, comp_guess);
        
        
        
        
        cout << tjur << " tjurar, " << kor << " kor.\n";
        
        if (tjur == 4)
        {
            cout << " Rätt svar " << comp_guess << endl;
            cout << " Antal gissningar "<< count << endl;
            cout << "Grattis! Du har rätt!\n";
            usleep(4000);
            k = t = count = removed = 0;
            guesses.clear();
            brain.clear();
            return;
        }
    }
}

void CompvsMan()
{
    cout << "Datorn tänker på att fyrsiffrigt tal" << endl;
    cout << "Ditt jobb är att lista ut det " << endl;
    cout << "Tryck på valfri tangent för att starta " << endl;
    cin.get();
    int hidden_answer_length = 4;
    string hidden_answer = hidden_number();
    string guess;
    int count = 0;
    int tjur = 0;
    vector<string> guesses;
    
    while(tjur != 4)
    {
        cout << "Din gissning" << endl;
        while((!(cin >> guess)) || innehaller_samma((guess)) || ((guess.size() != 4)) || (!all_of(guess.begin(), guess.end(), ::isdigit))) // Tittar så att spelaren enbart matar in 4 unika siffror.
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Mata in enbart siffror, Även unika siffror, även fyra siffror ";
        }
        
        if(guess_filter(guess, guesses)) // kollar om gissningen är gilltig.
        {
            cout << "Svaret " << guess << " är inte en korrekt gissning! " << "talet ska vara "<< 4 << " siffror långt" << " Samt att du inte får göra samma gissning två gånger " << endl;
            continue;
        }
        guesses.push_back(guess); // stoppar in gissningen i en vector så att den inte får återkomma.
        count++;
        
        int tjur = bull_check(hidden_answer_length, guess, hidden_answer); // kollar efter bull
        int kor = cow_check(hidden_answer_length, guess, hidden_answer); // kollar efter kor
        
        cout << tjur << " tjurar, " << kor << " kor.\n";
        if (tjur == 4) // om tjur är 4 har man vunnit
        {
            cout << "Grattis! Du har rätt!\n";
            cout << " Antal gissningar "<< count << endl;
            usleep(4000000);
            guesses.clear();
            return;
        }
    }
}
void CompvsComp()
{
    int hidden_answer_length = 4;
    string hidden_answer = hidden_number();
    string comp_guess;
    vector<string> guesses;
    int count = 0;
    int tjur = 0;
    int t = 0;
    int k = 0;
    vector<string> brain;
    while(tjur != 4)
    {
        
        
        
        if(guesses.size() >= 5040 ) // om vectorn guesses är 5040 finns det inte någon gissning kvar. alltså har man fuskat.
        {
            cout << "JJag spelare inte med fuskare, om 4 sekunder återvänder jag till menyn" << endl;
            usleep(4000000);
            guesses.clear();
            brain.clear();
            return;
        }
        string comp_guess = computer_guess(count, brain, t, k); // Datorn hämtar en gissning
        while(guess_filter(comp_guess, guesses)) comp_guess = computer_guess(count, brain, t, k);
        
        count++;
        cout << "Dator 1 tänker "<< endl;
        usleep(1000000);
        brain = memory(guesses);
        cout << "Datorn svarar: " << comp_guess << endl;
        usleep(1000000);
        guesses.push_back(comp_guess); // stoppar in gissningen så den inte kan användas igen.
        cout << "Dator 2 kontrollerar " << endl;
        usleep(1000000);
        int tjur = bull_check(hidden_answer_length, comp_guess, hidden_answer); // Kollar om gissningen innehåller en tjur
        int kor = cow_check(hidden_answer_length, comp_guess, hidden_answer); // Kollar om gissningen innehåller en ko
        
        t = tjur;
        k = kor;
        computer_solver(comp_guess, guesses, t, k);
        solve(brain, t, k, comp_guess);
        
        usleep(1000000);
        cout << tjur << " tjurar, " << kor << " kor.\n";
        usleep(1000000);
        if (tjur == 4)
        {
            cout << " Antal gissningar "<< count << endl;
            cout << "Grattis! Du har rätt!\n";
            usleep(4000000);
            k = t = count = removed = 0;
            guesses.clear();
            brain.clear();
            return;
        }
    }
}
void Benchmark() // exakt samma som Dator mot dator, alla cout är borttagna.
{
    
    int hidden_answer_length = 4;
    string hidden_answer = hidden_number();
    string comp_guess;
    vector<string> guesses;
    int count = 0;
    int tjur = 0;
    int t = 0;
    int k = 0;
    vector<string> brain;
    
    while(tjur != 4)
    {
        
        if(guesses.size() >= 5040 )
        {
            cout << "Jag spelare inte med fuskare, om 4 sekunder återvänder jag till menyn" << endl;
            usleep(4000000);
            guesses.clear();
            brain.clear();
            return;
        }
        string comp_guess = computer_guess(count, brain, t, k);
        while(guess_filter(comp_guess, guesses)) comp_guess = computer_guess(count, brain, t, k);
        
        count++;
        guesses.push_back(comp_guess);
        
        int tjur = bull_check(hidden_answer_length, comp_guess, hidden_answer);
        int kor = cow_check(hidden_answer_length, comp_guess, hidden_answer);
        t = tjur;
        k = kor;
        brain = memory(guesses);
        computer_solver(comp_guess, guesses, t, k);
        solve(brain, t, k, comp_guess);
        if (tjur == 4)
        {
            
            ofstream score("score",std::ios_base::app);
            score << count << " ";
            
            k = t = count = removed = 0;
            guesses.clear();
            brain.clear();
            return;
        }
    }
}

int main()
{
    while(true)
    {
        int input;
        system("clear");
        cout << "    MENY    \n";
        cout<<"1. Människa Mot Datorn \n";
        cout<<"2. Datorn Mot Människan \n";
        cout<<"3. Dator Mot Dator\n";
        cout <<"4. Exit \n";
        cout <<"5. Benchmark mode \n";
        cout<<": Välj ett spel\n";
        cin>> input;
        
        switch ( input )
        {
            case 1:
                
                cin.ignore();
                system("clear");
                ManvsComp();
                cout << "\n";
                break;
                
            case 2:
                
                cin.ignore();
                system("clear");
                CompvsMan();
                cout << "\n";
                break;
                
            case 3:
                
                cin.ignore();
                system("clear");
                CompvsComp();
                cout << "\n";
                break;
                
            case 4:
                
                cout <<"Tack för att du spelade \n";
                return 0;
                break;
                
            case 5:
                
                for(int i = 0; i < 5000000; i++)
                {
                    Benchmark();
                    cout << i << endl;
                }
                break;
                
            default:
                cout<<"Något gick fel! Restarting... \n";
                return 0;
        }
    }
}

