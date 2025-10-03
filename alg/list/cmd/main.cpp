#include "../bigString.h"
#include "../linked_list_string.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

char*
recieveAndTreatString(const char* prompt){
  std::cout << prompt;
  const int BUFFER = 1024;
  char tempString[BUFFER];

  std::cin >> std::ws; // Fix for input bug
  std::cin.getline(tempString, BUFFER);
  char* optimized = (char*)malloc(std::strlen(tempString) + 1);
  if(optimized == nullptr) return nullptr;

  std::strcpy(optimized, tempString);
  return optimized;
}

bool
checkIfSingle(const char* text)
{
  return strchr(text, ' ') == nullptr;
}

char** 
split_string_c_style(char* str, int* wordCount) 
{
    const char* delimiter = " ";
    int capacity = 10; // Start with an initial capacity for 10 words
    
    char** words = (char**)malloc(capacity * sizeof(char*));
    if (!words) return nullptr; // Check if malloc failed
    
    *wordCount = 0;
    char* token = strtok(str, delimiter);

    while (token != nullptr) {
        // If we run out of space, double the capacity
        if (*wordCount >= capacity) {
            capacity *= 2;
            char** new_words = (char**)realloc(words, capacity * sizeof(char*));
            if (!new_words) { // Check if realloc failed
                // Free previously allocated memory before returning
                for (int i = 0; i < *wordCount; ++i) {
                    free(words[i]);
                }
                free(words);
                return nullptr;
            }
            words = new_words;
        }

        // Allocate memory for the specific token and copy it
        words[*wordCount] = (char*)malloc(strlen(token) + 1);
        if (!words[*wordCount]) { // Check malloc
            // Free previously allocated memory
            for (int i = 0; i < *wordCount; ++i) {
                free(words[i]);
            }
            free(words);
            return nullptr;
        }
        strcpy(words[*wordCount], token);

        (*wordCount)++;
        token = strtok(nullptr, delimiter);
    }
  return words;
}

int
main()
{
  bigString l1;

  unsigned int pos_to_opp;
  char choice;
  char* txt_to_add;

  while(true){
    std::cout << "\nwhat to do in linkedlist? \n";
    std::cout << "\n(i)nsert (r)emove (p)rint print-(s)um (g)et-char-by-index (q)uit print-(d)ata\n- ";
    std::cin >> choice;

    if( choice == 'q' || choice == 'Q'){
      break;
    } else if (choice == 'p' || choice == 'P'){
      l1.print();
      continue;
    } else if (choice == 'd') {
      l1.printData();
    } else if(choice == 'i' || choice == 'I'){
      txt_to_add = recieveAndTreatString("\ntype content to add to list node\n- ");
      if(txt_to_add) {
        if(checkIfSingle(txt_to_add)){
          std::cout << "\nposition for operation to be made\n- ";
          std::cin >> pos_to_opp;
          l1.insert(pos_to_opp, txt_to_add);
        } else {
          int wordCount = 0;
          char** words = split_string_c_style(txt_to_add, &wordCount);
          
          std::cout << "\nposition for operation to be made\n- ";
          std::cin >> pos_to_opp;

          if (words) {
            for (int i = 0; i < wordCount; i++) {
              l1.insert(pos_to_opp, words[i]);
              ++pos_to_opp;
            }

            for (int i = 0; i < wordCount; i++) {
                free(words[i]);
            }
            free(words);
          }
        }
        free(txt_to_add);
      }
    } else if (choice == 's' || choice == 'S') { 
      std::cout << l1.getSum() << '\n';

    }else if (choice == 'g' || choice == 'G') {
      std::cout << "\nindex to get\n- ";
      std::cin >> pos_to_opp;
      std::cout << '\n' << l1[pos_to_opp] << '\n';
    } else if(choice == 'r' || choice == 'R'){
      std::cout << "\nposition for operation to be made\n- ";
      std::cin >> pos_to_opp;
      l1.remove(pos_to_opp);
    } else {
      std::cout << "\nnot valid input, try again\n";
    }
  }
  return 0;
}
