#include "homework.h"
#include <iostream>
#include <cstring>
#include <limits>

static char* readAndAllocateOptimalString(const char* prompt) {
    std::cout << prompt;
    const int TEMP_BUFFER_SIZE = 1024;
    char temp_buffer[TEMP_BUFFER_SIZE];
    std::cin.getline(temp_buffer, TEMP_BUFFER_SIZE);

    size_t input_length = std::strlen(temp_buffer);
    char* optimal_buffer = (char*)malloc(input_length + 1);

    if (optimal_buffer == nullptr) {
        return nullptr;
    }

    std::strcpy(optimal_buffer, temp_buffer);
    return optimal_buffer;
}

int run_homework_cli() {
    SinglyLinked l1;
    DoublyLinked l2;
    CircularBuffer<char*> lc(5);

    while (true) {
        int listType;
        char opp;
        int pos_to_opp;
        char* txt_to_add;

        std::cout << "\nDigite o tipo de implementacao de lista: (1) Encadeada (2) Duplamente encadeada (3) Buffer circular (4) Sair - ";
        std::cin >> listType;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida." << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (listType == 4) {
            break;
        }

        if (listType == 1) {
            std::cout << "\nDigite (i)nserir ou (d)eletar - ";
            std::cin >> opp;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (opp == 'd' || opp == 'D') {
                std::cout << "\nInsert position to delete - ";
                std::cin >> pos_to_opp;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                l1.remove(pos_to_opp);
            } else if (opp == 'i' || opp == 'I') {
                std::cout << "\nInsert position to insert - ";
                std::cin >> pos_to_opp;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                txt_to_add = readAndAllocateOptimalString("Type the string to be inserted - ");
                if(txt_to_add) {
                    l1.insert(pos_to_opp, txt_to_add);
                    free(txt_to_add);
                }
            }
            l1.print();
        } else if (listType == 2) {
            std::cout << "\nDigite (i)nserir ou (d)eletar - ";
            std::cin >> opp;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (opp == 'd' || opp == 'D') {
                std::cout << "\nInsert position to delete - ";
                std::cin >> pos_to_opp;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                l2.remove(pos_to_opp);
            } else if (opp == 'i' || opp == 'I') {
                std::cout << "\nInsert position to insert - ";
                std::cin >> pos_to_opp;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                txt_to_add = readAndAllocateOptimalString("Type the string to be inserted - ");
                if(txt_to_add) {
                    l2.insert(pos_to_opp, txt_to_add);
                    free(txt_to_add);
                }
            }
            l2.print();
        } else if (listType == 3) {
            std::cout << "\nDigite (p)ush ou p(o)p - ";
            std::cin >> opp;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (opp == 'p' || opp == 'P') {
                txt_to_add = readAndAllocateOptimalString("Type the string to be pushed - ");
                if(txt_to_add) {
                    lc.push(txt_to_add);
                }
            } else if (opp == 'o' || opp == 'O') {
                if (!lc.empty()) {
                    char* popped = lc.pop();
                    std::cout << "Popped: " << popped << std::endl;
                    free(popped);
                } else {
                    std::cout << "Buffer is empty." << std::endl;
                }
            }
            lc.print();
        }
    }

    return 0;
}
