/*Rescrierea si adaptarea aplicatiei Web "AMR" pentru compilare si executare locala
Acest exercitiu are ca scop scoaterea in evidenta a utilizarii diferitelor structuri de date*/

#include <iostream>
#include <iomanip>      //completeaza <iostream> cu functii de formatare (i/o manipulation)
#include <vector>
#include <string>
#include <fstream>
#include <chrono>       //precizie mai buna pentru time, clock, etc

using namespace std;

//Structura unei intrari, ce reflecta campurile din WebApp-ul AMR
struct LeaveEntry {
    long long id;       // Timestamp ID
    string date;        // Format: AAAA-LL-ZZ
    string type;        // "obtinuta" sau "utilizata"
    string category;    // "liber", "exercitiu", "recompensa" or "n/a (tip: utilizata)"
    double amount;      // Numarul de zile
    string note;        // Detalii (optional)
};

vector<LeaveEntry> db;

// Generare timestamp ID local (avem nevoie de acuratetea <chrono> pt a "forta" unicitatea IDurilor)
long long generateTimestamp() {
    return chrono::duration_cast<chrono::milliseconds>(
        chrono::system_clock::now().time_since_epoch()
    ).count();
}

// 1. Vizionare intrari - simularea unui REST API "GET"
void handleGetEntries() {
    cout << "\n================================ ISTORIC ================================\n";
    if (db.empty()) {
        cout << " Nu exista inregistrari.\n";
        cout << "=================================================================================\n";
        return;
    }

    cout << left 
        << setw(15) << "ID" 
        << setw(12) << "Date" 
        << setw(10) << "Type" 
        << setw(15) << "Category" 
        << setw(10) << "Amount" 
        << "Note\n";
    cout << string(81, '-') << "\n";

    for (const auto& entry : db) {
        cout << left 
            << setw(15) << entry.id 
            << setw(12) << entry.date 
            << setw(10) << entry.type 
            << setw(15) << (entry.category.empty() ? "utilizata" : entry.category) 
            << setw(10) << entry.amount 
            << entry.note << "\n";
    }
    cout << "=================================================================================\n";
}

// 2. Adaugarea unei noi intrari - simularea unui REST API "POST"
void handlePostEntry() {
    LeaveEntry entry;
    entry.id = generateTimestamp();

    cout << "\n--- Intrare Noua ---\n";
    while (true) {
        cout << "Recuperare Obtinuta (o) / Utilizata (u): "; 
        cin >> entry.type;
        if (entry.type == "o" || entry.type == "u") break;
        cout << "Tip Recuperare introdus gresit. Incearca din nou.\n";
    }

    cout << "Data (AAAA-LL-ZZ): "; 
    cin >> entry.date;
    
    if (entry.type == "o") {
        cout << "Categorie ('liber' [2 days], 'exercitiu' [1 day], 'recompensa' [1 day]): ";
        cin >> entry.category;
        
        if (entry.category == "liber") entry.amount = 2.0;
        else if (entry.category == "exercitiu" || entry.category == "recompensa") entry.amount = 1.0;
        else { 
            cout << "Categorie inexistenta! Iesire...\n"; 
            return; 
        }
    } else {
        cout << "Introdu nr. zile utilizate: "; 
        cin >> entry.amount;
        entry.category = "n/a";
    }
    
    cin.ignore();   // Clear newline buffer
    cout << "Introdu detalii (optional): "; 
    getline(cin, entry.note);

    db.push_back(entry);
    cout << "\nIntrarea noua s-a adaugat cu succes!\n";
}

// 3. Calcul Sumar - zile libere (recuperari) disponibile
void handleGetBalance() {
    double balance = 0.0;
    for (const auto& entry : db) {
        if (entry.type == "o") balance += entry.amount;
        else balance -= entry.amount;
    }
    cout << "\n================================ SUMAR ================================\n";
    cout << " Zile libere (Recuperari) disponibile: " << balance << " zile\n";
    cout << "=======================================================================\n";
}

// 4. Functia de export
void handleExportToFile() {
    if (db.empty()) {
        cout << "\nNu sunt intrari. Nimic de exportat.\n";
        return;
    }

    string filename = "libere.csv";
    ofstream outFile(filename);

    if (!outFile) {
        cout << "\nNu am putut creea sau deschide fisierul.\n";
        return;
    }

    // Crearea CSV Header
    outFile << "ID,Data,Tip,Categorie,NrZile,Detalii\n";

    // Scriere randuri in CSV
    for (const auto& entry : db) {
        outFile << entry.id << ","
                << entry.date << ","
                << entry.type << ","
                << (entry.category.empty() ? "u" : entry.category) << ","
                << entry.amount << ","
                << "\"" << entry.note << "\"\n";
    }

    outFile.close();
    cout << "\nExport realizat cu succes catre fisierul: '" << filename << "'\n";
}

// TUI - Terminal User Interface
void displayMenu() {
    cout << "\n================ AMR - MENIU  ================\n";
    cout << "1. Vizualizare intrari     (GET /api/entries)\n";
    cout << "2. Adaugare intrare noua   (POST /api/entries)\n";
    cout << "3. Sumar                   (GET /api/balance)\n";
    cout << "4. Export catre fisier CSV\n";
    cout << "5. Iesire\n";
    cout << "==============================================\n";
    cout << "Alege o optiune: ";
}

int main() {
    int choice = 0;
    
    // Initializare db
    db.push_back({1716034000000, "2026-01-01", "o", "recompensa", 0.0, "Sistemul a pornit local cu succes."});

    do {
        displayMenu();
        if (!(cin >> choice)) {
            cout << "Input invalid. Introdu un numar: \n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: handleGetEntries(); break;
            case 2: handlePostEntry(); break;
            case 3: handleGetBalance(); break;
            case 4: handleExportToFile(); break;
            case 5: cout << "\nLa revedere!\n"; break;
            default: cout << "\n404 Error: Optiune invalida.\n";
        }
    } while (choice != 5);

    return 0;
}