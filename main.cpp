#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <sstream>
#include "Matcher.h"
#include "MatchedStorage.h"
#include "Cargo.h"
#include "Freight.h"
#include "Storage.h"

// Create type aliases
using FreightStorage = Storage<Freight>;
using CargoStorage = Storage<Cargo>;


using namespace std;

// Helper: Validate 24-hour time input
time_t getValidatedTime() {
    string input;
    int time = 0;

    while (true) {
        cout << "Enter Time (e.g. 0900 for 9am): ";
        getline(cin, input);

        // Check for 4-digit numeric input
        if (input.length() != 4 || !all_of(input.begin(), input.end(), ::isdigit)) {
            cout << "Invalid input: Enter a 4-digit number only.\n";
            continue;
        }

        try {
            time = stoi(input);
            int hours = time / 100;
            int minutes = time % 100;

            if (hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60)
                return time;
            else
                cout << "Invalid time: Must be in 24-hour format (0000 to 2359).\n";
        }
        catch (...) {
            cout << "Error converting time.\n";
        }
    }
}

// Helper: Validate letters-only location
string capitalizeWords(const string& input) {
    stringstream ss(input);
    string word, result;

    while (ss >> word) {
        // Capitalize first letter, lowercase the rest
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        word[0] = toupper(word[0]);

        if (!result.empty())
            result += " ";
        result += word;
    }

    return result;
}

string getValidatedLocation() {
    string location;
    while (true) {
        cout << "Enter Location: ";
        getline(cin, location);

        // Check for non-empty string with only letters and spaces
        if (!location.empty() && all_of(location.begin(), location.end(), [](char c) {
            return isalpha(c) || isspace(c);
            })) {
            return capitalizeWords(location);
        }
        else {
            cout << "Invalid location: Letters and spaces only.\n";
        }
    }
}

int main() {
    FreightStorage freightStorage;
    CargoStorage cargoStorage;
    MatchedStorage matchedStorage;
    vector<string> unmatchedFreights, unmatchedCargos;

    freightStorage.loadFromFile("Freight.txt");
    cargoStorage.loadFromFile("Cargo.txt");

    string command;
    int option;

    
    while (true) {
        cout << "\n========== MAIN MENU ==========\n"
            << "1. View Cargo and Freight\n"
            << "2. View Schedule\n"
            << "3. Add Cargo\n"
            << "4. Edit Cargo\n"
            << "5. Delete Cargo\n"
            << "6. Add Freight\n"
            << "7. Edit Freight\n"
            << "8. Delete Freight\n"
            << "9. Generate & View Schedule\n"
            << "10. Save Schedule to File\n"
            << "11. Exit\n"
            << "Select an option: ";

        getline(cin, command);

        try {
            option = stoi(command);
        }
        catch (...) {
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (option) {
        case 1:
            cargoStorage.printCargoTable(freightStorage);
            break;

        case 2:
            matchedStorage.displayScheduleFile("schedule.txt");
            break;

        case 3: {
            string id = cargoStorage.generateNextCargoId();
            cout << "Auto-generated Cargo ID: " << id << endl;


            string location = getValidatedLocation();
            time_t time = getValidatedTime();

            try {
                Cargo c(id, location, time);
                cargoStorage.addCargo(c); //addCargo to addItem?
            }
            catch (const exception& e) {
                cout << "Error adding cargo: " << e.what() << endl;
            }
            break;
        }

        case 4: {
            string id;

            while (true) {
                cout << "Enter Cargo ID to edit (blank = cancel): ";
                getline(cin, id);

                if (id.empty()) break;                    // leave loop then cancel
                if (cargoStorage.exists(id)) break;       // found then continue below

                cout << "Cargo not found. Try again.\n";
            }
            if (id.empty()) {                             // cancelled
                cout << "No ID entered - returning to main menu.\n";
                break;
            }

            string location = getValidatedLocation();
            time_t timeVal = getValidatedTime();

            if (cargoStorage.editCargo(id, location, timeVal))
                cout << "Cargo updated.\n";
            else
                cout << "Update failed (data invalid).\n";
            break;
        }


        case 5: {
            string id;

            while (true) {
                cout << "Enter Cargo ID to delete (blank = cancel): ";
                getline(cin, id);

                if (id.empty()) {
                    cout << "No ID entered - returning to main menu.\n";
                    break;                               //  back to menu
                }
                if (cargoStorage.exists(id))             // case-insensitive
                    break;

                cout << "Cargo not found. Try again.\n";
            }
            if (id.empty()) break;                       // user cancelled earlier

            /* --- confirmation loop --- */
            string yn;
            do {
                cout << "Delete Cargo " << id << "? (y/n): ";
                getline(cin, yn);
            } while (yn != "y" && yn != "Y" && yn != "n" && yn != "N");

            if (yn == "n" || yn == "N") {
                cout << "Deletion cancelled.\n";
                break;
            }

            if (cargoStorage.deleteCargo(id))
                cout << "Cargo deleted.\n";
            else
                cout << "Delete failed.\n";
            break;
        }

        case 6: {
            string id = freightStorage.generateNextFreightId();
            cout << "Auto-generated Freight ID: " << id << endl;

            string location = getValidatedLocation();
            time_t time = getValidatedTime();

            try {
                Freight f(id, location, time);
                freightStorage.addFreight(f); //addFreight to addItem?
            }
            catch (const exception& e) {
                cout << "Error adding freight: " << e.what() << endl;
            }
            break;
        }

        case 7: {
            string id;

            while (true) {
                cout << "Enter Freight ID to edit (blank = cancel): ";
                getline(cin, id);

                if (id.empty()) break;
                if (freightStorage.exists(id)) break;

                cout << "Freight not found. Try again.\n";
            }
            if (id.empty()) {
                cout << "No ID entered - returning to main menu.\n";
                break;
            }

            string location = getValidatedLocation();
            time_t timeVal = getValidatedTime();

            if (freightStorage.editFreight(id, location, timeVal))
                cout << "Freight updated.\n";
            else
                cout << "Update failed (data invalid).\n";
            break;
        }

        case 8: {
            string id;

            while (true) {
                cout << "Enter Freight ID to delete (blank = cancel): ";
                getline(cin, id);

                if (id.empty()) {
                    cout << "No ID entered - returning to main menu.\n";
                    break;
                }
                if (freightStorage.exists(id))
                    break;

                cout << "Freight not found. Try again.\n";
            }
            if (id.empty()) break;

            /* --- confirmation loop --- */
            string yn;
            do {
                cout << "Delete Freight " << id << "? (y/n): ";
                getline(cin, yn);
            } while (yn != "y" && yn != "Y" && yn != "n" && yn != "N");

            if (yn == "n" || yn == "N") {
                cout << "Deletion cancelled.\n";
                break;
            }

            if (freightStorage.deleteFreight(id))
                cout << "Freight deleted.\n";
            else
                cout << "Delete failed.\n";
            break;
        }

        case 9: {
            matchedStorage.generateMatches(freightStorage, cargoStorage, unmatchedFreights, unmatchedCargos);
            matchedStorage.displayAllMatches(unmatchedFreights, unmatchedCargos, freightStorage, cargoStorage);
            break;
        }

        case 10: {
            string filename;
            matchedStorage.saveMatches("schedule.txt", unmatchedFreights, unmatchedCargos);
            break;
        }

        case 11: {
            string choice;
            cout << "\nDo you want to save changes to Cargo.txt and Freight.txt? (Y/N): ";
            getline(cin, choice);

            if (choice == "Y" || choice == "y") {
                cargoStorage.saveCargoStorage("Cargo.txt");
                freightStorage.saveFreightStorage("Freight.txt");
                cout << "Changes saved.\n";
            }
            else {
                cout << "Changes not saved.\n";
            }

            cout << "Exiting...\n";
            return 0;
        }
        default:
            cout << "Invalid option. Try again.\n";
            break;
        }
    }
}
