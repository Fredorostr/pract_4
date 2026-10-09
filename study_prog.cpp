#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct student{
    std::string Name;
    std::string Group;
    std::vector<int> grades;
};

std::vector<student> studs;
std::vector<std::string> groups;

int searchingGr(const std::string& g){
    for (int i = 0; i < groups.size(); i++){
        if (groups[i] == g){
            return i;
        }
    }
    return -1;
}

void addGroup() {
    std::string g;
    std::cout<<"Новая группа ";
    std::cin.ignore();
    std::getline(std::cin, g);
    groups.push_back(g);
}

void delg(){
    std::string g;
    std::cout << "какую удалить ? ";
    std::cin.ignore();
    std::getline(std::cin, g);
    int ind = searchingGr(g);
    if (ind == -1) {
        std::cout << "такой группы нет, убили их\n";
        return;
    }
    for (const auto& s : studs) {
        if (s.Group == g) {
            std::cout << "в группе есть студенты, удалить нельзя, грустно \n";
            return;
        }
    }
    groups.erase(groups.begin() + ind);
}

void editgr (){
    std::string old;
    std::string nw;
    std::cout<<"какую изменить ?";
    std::cin.ignore();
    std::getline(std::cin, old);
       int inf = searchingGr(old);
    if (inf == -1) {
        std::cout << "такой группы нет\n";
        return;
    }
    int ind = searchingGr(old);
    std::cout<<"Введите новое название";
    std::getline(std::cin, nw);
    for (auto& s : studs){
        if (s.Group == old) s.Group = nw;
    }
    groups[ind] = nw;
    } 

int searching(const std::string& name){
    for (int i = 0; i < studs.size(); i++){
        if (studs[i].Name == name){
            return i;
        }
    }
    return -1;
}
    
void addingStud(std::vector<student> & Students) {
    student s;
    std::cout<< "введите фио ";
    std::cin.ignore();
    std::getline(std::cin, s.Name);
    std::cout<<"Введите группу";
    std::getline(std::cin, s.Group);
    if (searchingGr(s.Group) == -1) {
        std::cout << "такой группы нет\n";
        return;
    }
    int count;
    std::cout<<"Количество оценок ";
    std::cin>>count; 
    for(int i = 0; i < count; i++){
        int grade;
        std::cout<<"Оценка" << i+1 << ": ";
        std::cin>>grade;
        s.grades.push_back(grade);
    }
    Students.push_back (s);
}

void edit (){
    std::string name;
    std::cout<<"ФИО для изменения ";
    std::cin.ignore();
    std::getline(std::cin, name);
    int ind = searching(name);
    if(ind == -1){
        std::cout<<"нет такого, убили";
        return;
    }
    std::cout<<"новый студент";
    std::getline(std::cin,studs[ind].Name);
    std::cout<<"Новая группа";
    std::getline(std::cin, studs[ind].Group);
}

void delite(){
    std::string name;
    std::cout<<"ФИО для удаления";
    std::cin.ignore();
    std::getline(std::cin, name);
    
    int ind = searching(name);
    if(ind == -1){
        std::cout<<"нету такого, отравился";
        return;
    }

    studs.erase(studs.begin() + ind);
}

double averstud(const student& s){
    if(s.grades.empty()) return 0.0;
    double sum = 0;
    for (int g : s.grades) sum += g;
    return sum / s.grades.size();
}

double groupaver (std::string Group){
    double sum = 0;
    int count = 0;
    for(const auto& s: studs){
        if(s.Group == Group){
            for (int g : s.grades){
                sum+=g;
                count++;
            }
        }
    }
    return (count == 0) ? 0.0 : sum / count;
}

void addMark(){
    std::string name;
    std::cout<<"Введите ФИО";
    std::cin.ignore();
    std::getline(std::cin, name);
    int ind = searching(name);
    if (ind == -1) {
        std::cout << "нет такого, надеюсь умер супостат(супа хочу, надо поесть)\n";
        return;
    }
    int grade;
    std::cout << "Оценка: ";
    std::cin >> grade;
    if (grade < 2 || grade > 5) {
        std::cout << "оценка должна быть от 2 до 5\n";
        return;
    }
    studs[ind].grades.push_back(grade);
}

void stat() {
    std::string g;
    std::cout << "Группа: ";
    std::cin.ignore();
    std::getline(std::cin, g);
    if (searchingGr(g) == -1) {
        std::cout << "такой группы нет\n";
        return;
    }
    int five = 0, four = 0, three = 0, two = 0, idiot = 0;
    for (const auto& s : studs) {
        if (s.Group != g) continue;
        if (s.grades.empty()) {
            idiot++;
            continue;
        }
        int mn = s.grades[0];
        for (int x : s.grades) {
            if (x < mn) mn = x;
        }
        if (mn == 5) five++;
        else if (mn == 4) four++;
        else if (mn == 3) three++;
        else two++;
    }

    std::cout << "Отличников: " << five << "\n";
    std::cout << "Хорошистов: " << four << "\n";
    std::cout << "Троечников: " << three << "\n";
    std::cout << "Дебилы: " << two << "\n";
    std::cout << "Без оценок: " << idiot << "\n";
}


int main () {
    int answer = -1;
    while (answer != 0) {
        std::cout << "\n1. добавление студента\n2. изменение студента\n3. удаление студента\n"
                  << "4. добавление группы\n5. изменение группы\n6. удаление группы (не должно быть студентов)\n"
                  << "7. средний балл студента\n8. средний балл группы\n9. добавление оценки\n"
                  << "10. статистика по группе\n0. выход\nВыбор: ";
        std::cin >> answer;

        switch (answer) {
        case 1:  addingStud(studs); break;
        case 2:  edit();            break;
        case 3:  delite();          break;
        case 4:  addGroup();        break;
        case 5:  editgr();          break;
        case 6:  delg();            break;
        case 7: {
            std::string name;
            std::cout << "Введите ФИО: ";
            std::cin.ignore();
            std::getline(std::cin, name);
            int ind = searching(name);
            if (ind == -1) {
                std::cout << "нет такого студента\n";
                break;
            }
            if (studs[ind].grades.empty()) {
                std::cout << "у студента нет оценок\n";
                break;
            }
            std::cout << "Средний балл: " << averstud(studs[ind]) << "\n";
            break;
        }
        case 8: {
            std::string g;
            std::cout << "Введите группу: ";
            std::cin.ignore();
            std::getline(std::cin, g);
            if (searchingGr(g) == -1) {
                std::cout << "такой группы нет\n";
                break;
            }
            std::cout << "Средний балл группы: " << groupaver(g) << "\n";
            break;
        }
        case 9:  addMark();         break;
        case 10: stat();            break;
        case 0:  break;
        default: std::cout << "нет такого пункта\n"; break;
        }
    }
    return 0;
}