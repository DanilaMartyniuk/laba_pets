#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Pet {
    string owner, petType, petName;
    int age;
};

Pet* createAnimal(const string& owner, const string& animalType, const string& animalName, const string& age) {
    Pet* animal = new(Pet);
    animal->owner = owner;
    animal->petType = animalType;
    animal->petName = animalName;
    animal->age = stoi(age);
    return animal;
}

vector<Pet*> parser(const string& fileName) {
    ifstream input(fileName);
    int petNum;
    input >> petNum;
    input.ignore(1);
    string owner, petType, petName, age;
    vector<Pet*> result;
    for (int i = 0; i < petNum; i++) {
        getline(input, owner, ',');
        getline(input, petType, ',');
        getline(input, petName, ',');
        getline(input, age);
        result.push_back(createAnimal(owner, petType, petName, age));
    }
    input.close();
    return result;
}

void typesTotal(const vector<Pet*>& list) {
    map<string, set<string>> instrument;
    for (int i = 0; i < list.size(); i++) {
        instrument[list[i]->owner].insert(list[i]->petType);
    }
    for (auto it = instrument.begin(); it != instrument.end(); it++) {
        cout << it->first << " : " << it->second.size() << endl;
    }
}

void OwnersAndNamesByType(const vector<Pet*>& list) {
    string key;
    cout << "Enter pets type\n";
    cin >> key;
    map<string, set<pair<string, string>>> instrument;
    for (int i = 0; i < list.size(); i++) {
        instrument[list[i]->petType].insert({ list[i]->owner, list[i]->petName });
    }
    if (instrument[key].empty()) {
        cout << "No such pets\n";
        return;
    }
    for (auto i = instrument[key].begin(); i != instrument[key].end(); i++) {
        cout << "Owner: " << i->first << " Name: " << i->second << endl;
    }
}

void AmountOfTypesWithCurrentName(const vector<Pet*>& list) {
    string key;
    cout << "Enter pet's name\n";
    cin >> key;
    map<string, set<string>> instrument;
    for (int i = 0; i < list.size(); i++) {
        instrument[list[i]->petName].insert(list[i]->petType);
    }
    cout << "Types with current name :" << instrument[key].size() << endl;
}

void oldNyoung(const vector<Pet*>& list) {
    map<string, pair<Pet*, Pet*>> instrument;
    for (int i = 0; i < list.size(); i++) {
        if (instrument[list[i]->petType].first == nullptr) {
            instrument[list[i]->petType].first = list[i];
            instrument[list[i]->petType].second = list[i];
        }
        if (instrument[list[i]->petType].first->age < list[i]->age) {
            instrument[list[i]->petType].first = list[i];
        }
        if (instrument[list[i]->petType].second->age > list[i]->age) {
            instrument[list[i]->petType].second = list[i];
        }
    }
    for (auto i : instrument) {
        cout << i.first << " " << i.second.first->age << " " << i.second.first->owner << " " << i.second.first->petName
            << endl;
        cout << i.first << " " << i.second.second->age << " " << i.second.second->owner << " "
            << i.second.second->petName << endl;
    }
}

void deleteList(vector<Pet*>& list) {
    for (int i = 0; i < list.size(); ++i) {
        delete (list[i]);
    }
}

void callMenu() {
    cout << "           !!!CHOOSE YOUR DESTINY!!!\n";
    cout << "1 - Count pet types of all owners\n";
    cout << "2 - Find owners and names by pet type\n";
    cout << "3 - Count types, with needed name\n";
    cout << "4 - Search youngest and oldest pet of every type\n";
    cout << "0 - exit\n";
}

int main() {
    vector<Pet*> list = parser("input.txt");
    int option;
    callMenu();
    cin >> option;
    while (option) {
        switch (option) {
        case 1:typesTotal(list);
            cin >> option;
            break;
        case 2:OwnersAndNamesByType(list);
            cin >> option;
            break;
        case 3:AmountOfTypesWithCurrentName(list);
            cin >> option;
            break;
        case 4:oldNyoung(list);
            cin >> option;
            break;
        case 0:deleteList(list);
            return 0;
        default:
            cout << "invalid input\n";
            cin >> option;
            break;
        }
    }
}