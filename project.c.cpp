#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define tab printf("\t\t\t\t\t")
#define RED_TEXT "\x1b[31m"
#define GREEN_TEXT "\x1b[32m"
#define YELLOW_TEXT "\x1b[33m"
#define BLUE_TEXT "\x1b[34m"
#define RESET_TEXT "\x1b[0m"

struct signin {
    char name[40];
    char username[40];
    char password[40];
    unsigned long long int number;
} l;

struct list {
    char name[40];
    char email[100];
    unsigned long long int number;
    char address[50];
} s, check;

void addcontact() {
    system("cls");
    char choice = 'y';
    FILE *p;
    p = fopen("contact.txt", "a+");
    if (p == NULL) {
        tab; printf(RED_TEXT "Error opening file\n" RESET_TEXT);
        return;
    }

    while (choice == 'y') {
        system("cls");

        tab; printf(BLUE_TEXT "-------------\n");
        tab; printf("NEW CONTACT\n");
        tab; printf("-------------\n" RESET_TEXT);
        tab; printf("enter name:");
        fflush(stdin);
        gets(s.name);
        tab; printf("enter email:");
        fflush(stdin);
        gets(s.email);

        while (1) {
            tab; printf("Enter a 10-digit number: ");
            fflush(stdin);
            scanf("%llu", &s.number);
            if (s.number >= 1000000000ULL && s.number <= 9999999999ULL) {
                break;
            } else {
                tab; printf(RED_TEXT "Invalid input. Please enter a 10-digit number.\n"RESET_TEXT);
            }
        }

        tab; printf("You entered: %llu\n", s.number);
        tab; printf("enter address:");
        fflush(stdin);
        gets(s.address);
        fwrite(&s, sizeof(struct list), 1, p);
        tab; printf(GREEN_TEXT "-----------\n");
        tab; printf("SUCCESSFUL.\n");
        tab; printf("-----------\n" RESET_TEXT);
        tab; printf("DO YOU WANT TO ADD ANOTHER RECORD (y/n):");
        fflush(stdin);
        choice = getchar();
    }
    fclose(p);
}

void editcontact() {
    system("cls");
    char choice = 'y';
    int a, f = 0;
    unsigned long long number;
    FILE *p;
    FILE *n;

    while (choice == 'y') {
        p = fopen("contact.txt", "r");
        if (p == NULL) {
            printf("Error opening file\n");
            return;
        }

        n = fopen("temp.txt", "w");
        if (n == NULL) {
            printf("Error opening temporary file\n");
            fclose(p);
            return;
        }

        tab;printf(BLUE_TEXT"-------------\n");
        tab;printf("EDIT CONTACT\n");
        tab;printf("-------------\n"RESET_TEXT);

        
        while (1) {
            tab;printf("Enter a 10-digit number: ");
            fflush(stdin); 
            scanf("%llu", &number);
            if (number >= 1000000000ULL && number <= 9999999999ULL) {
                break;
            } else {
                tab; printf("Invalid input. Please enter a 10-digit number.\n");
            }
        }

      
        while (fread(&s, sizeof(struct list), 1, p)) {
            if (s.number == number) {
                f = 1;
               tab; printf("-------------\n");
               tab; printf("EDIT CONTACT\n");
               tab; printf("-------------\n");
               tab; printf("What do you want to edit:\n");
               tab; printf("1. Name\n");
               tab; printf("2. Email\n");
               tab; printf("3. Number\n");
               tab; printf("4. Address\n");
               tab; printf("5. Exit\n");
               tab; printf("----------------\n");
               tab; printf("Enter your choice: ");
                scanf("%d", &a);

                switch (a) {
                    case 1:
                        tab;printf("Enter new name: ");
                        fflush(stdin);
                        gets(s.name);
                        break;
                    case 2:
                        tab;printf("Enter new email: ");
                        fflush(stdin);
                        gets(s.email);
                        break;
                    case 3:
                        while (1) {
                            tab;printf("Enter new number: ");
                            fflush(stdin);
                            scanf("%llu", &s.number);
                            if (s.number >= 1000000000ULL && s.number <= 9999999999ULL) {
                                break;
                            } else {
                                printf("Invalid input. Please enter a 10-digit number.\n");
                            }
                        }
                        break;
                    case 4:
                        tab;printf("Enter new address: ");
                        fflush(stdin);
                        gets(s.address);
                        break;
                    case 5:
                        fclose(p);
                        fclose(n);
                       return;
                        break;
                    default:
                        printf("Invalid choice\n");
                        break;
                }
            }
            fwrite(&s, sizeof(struct list), 1, n);
        }

        fclose(p);
        fclose(n);

        remove("contact.txt");
        rename("temp.txt", "contact.txt");

        if (f == 0) {
            printf("Contact not found\n\n");
        } else {
            printf("CONTACT EDITED SUCCESSFULLY.\n\n");
        }

        printf("DO YOU WANT TO EDIT ANOTHER CONTACT (y/n): ");
        fflush(stdin);
        choice = getchar();
    }
}


void searchcontact() {
    system("cls");
    int f = 0;
    FILE *p;
    p = fopen("contact.txt", "r");
    if (p == NULL) {
        tab; printf(RED_TEXT "Error opening file\n" RESET_TEXT);
        return;
    }
    tab; printf(BLUE_TEXT "-----------\n");
    tab; printf("SEARCH CONTACT\n");
    tab; printf("-----------\n" RESET_TEXT);
    tab; printf("Enter name: ");
    fflush(stdin);
    gets(check.name);
    while (fread(&s, sizeof(struct list), 1, p) == 1) {
        if (strcmp(check.name, s.name) == 0) {
            f = 1;
            tab; printf(BLUE_TEXT "---------------\n");
            tab; printf("Name: %s\n", s.name);
            tab; printf("Email: %s\n", s.email);
            tab; printf("Number: %llu\n", s.number);
            tab; printf("Address: %s\n", s.address);
            tab; printf("----------------\n" RESET_TEXT);
            break;
        }
    }

    fclose(p);
    if (f == 0) {
        tab; printf(RED_TEXT "Contact not found\n" RESET_TEXT);
    }
}

void listcontact() {
    system("cls");
    FILE *p;
    p = fopen("contact.txt", "r");
    if (p == NULL) {
        tab; printf(RED_TEXT "Error opening file\n" RESET_TEXT);
        return;
    }
    tab; printf(BLUE_TEXT "-----------\n");
    tab; printf("LIST CONTACTS\n");
    tab; printf("-----------\n" RESET_TEXT);
    tab; printf("%-20s %-30s %-20s %s\n", "NAME", "EMAIL", "NUMBER", "ADDRESS");
    while (fread(&s, sizeof(struct list), 1, p) == 1) {
        tab; printf("%-20s %-30s %-20llu %s\n", s.name, s.email, s.number, s.address);
    }
    fclose(p);
}

void deletecontact() {
    system("cls");
    char choice = 'y';
    int f = 0;
    unsigned long long int number;
    FILE *p;
    FILE *n;

    while (choice == 'y') {
        p = fopen("contact.txt", "r");
        if (p == NULL) {
            tab; printf(RED_TEXT "Error opening file\n" RESET_TEXT);
            return;
        }
        n = fopen("temp.txt", "w");
        if (n == NULL) {
            tab; printf(RED_TEXT "Error opening temporary file\n" RESET_TEXT);
            fclose(p);
            return;
        }

        tab; printf(BLUE_TEXT "-------------\n");
        tab; printf("DELETE CONTACT\n");
        tab; printf("-------------\n" RESET_TEXT);

        while (1) {
            tab; printf("Enter a 10-digit number: ");
            fflush(stdin);
            scanf("%llu", &number);
            if (number >= 1000000000ULL && number <= 9999999999ULL) {
                break;
            } else {
                tab; printf(RED_TEXT "Invalid input. Please enter a 10-digit number.\n" RESET_TEXT);
            }
        }

        while (fread(&s, sizeof(struct list), 1, p) == 1) {
            if (s.number != number) {
                fwrite(&s, sizeof(struct list), 1, n);
            } else {
                f = 1;
            }
        }
        fclose(p);
        fclose(n);

        remove("contact.txt");
        rename("temp.txt", "contact.txt");

        if (f == 0) {
            tab; printf(RED_TEXT "Contact not found\n\n" RESET_TEXT);
        } else {
            tab; printf(GREEN_TEXT "CONTACT DELETED SUCCESSFULLY.\n\n" RESET_TEXT);
        }

        tab; printf("DO YOU WANT TO DELETE ANOTHER CONTACT (y/n): ");
        fflush(stdin);
        choice = getchar();
    }
}
void passwordhide(char *password) {
    char ch;
    int i = 0;

    while ((ch = getch()) != '\r') {
        if (ch == '\b') { // handle backspace
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
}


void loading() {
    int i;
    tab; printf(YELLOW_TEXT "LOADING");
    for (i = 0; i < 4; i++) {
        fflush(stdout);
        sleep(1);
        printf(".......");
    }
    printf("\n" RESET_TEXT);
}

int login() {
    system("cls");
    char cho = 'y';
    char ch;
    int i;
    char username[40],password[40];
    int j = 0;
    FILE *f = fopen("hello.txt", "r");
    if (f == NULL) {
        tab; printf(RED_TEXT "File not found\n" RESET_TEXT);
        exit(0);
    }

    while (cho == 'y' || cho == 'Y') {
        system("cls");
        tab; printf(BLUE_TEXT "---------------------------\n");
        tab; printf("WELCOME TO THE LOGIN PAGE\n");
        tab; printf("---------------------------\n" RESET_TEXT);
        fflush(stdin);
        tab; printf("Enter username: ");
        gets(username);
        fflush(stdin);
        tab; printf("Enter password:");
        passwordhide(password);
        printf("\n");

        rewind(f);
        j = 0;
        while (fread(&l, sizeof(struct signin), 1, f)) {
            if (strcmp(l.username, username) == 0 && strcmp(l.password, password) == 0) {
                j = 1;
                tab; printf(GREEN_TEXT "LOGIN SUCCESSFUL\n" RESET_TEXT);
                system("cls");
                break;
            }
        }

        if (j == 0) {
            tab; printf(RED_TEXT "USERNAME OR PASSWORD DOES NOT MATCH" RESET_TEXT);
            printf("\n");
            tab; printf("Do you want to re-enter the username and password? (Y/N): ");
            fflush(stdin);
            cho = getchar();
            fflush(stdin);
            if (cho != 'y' && cho != 'Y') {
                break;
            }
        } else {
            break;
        }
    }

    fclose(f);
    return j;
}


void signin() {
    system("cls");
    char ch;
    int i;
    FILE *f;
    f = fopen("hello.txt", "a");
    if (f == NULL) {
        tab; printf(RED_TEXT "File not found\n" RESET_TEXT);
        return;
    }
    tab; printf(BLUE_TEXT "---------------------------\n");
    tab; printf("WELCOME TO THE SIGN IN PAGE\n");
    tab; printf("---------------------------\n" RESET_TEXT);
    tab; printf("Enter name:");
    gets(l.name);
    fflush(stdin);
    tab; printf("Enter username:");
    gets(l.username);
    fflush(stdin);
    tab; printf("Enter password:");
    passwordhide(l.password);
    fflush(stdin);
    printf("\n");
    while (1) {
        tab; printf("Enter a 10-digit number: ");
        fflush(stdin);
        scanf("%llu", &l.number);
        if (l.number >= 1000000000ULL && l.number <= 9999999999ULL) {
            break;
        } else {
            tab; printf(RED_TEXT "Invalid input. Please enter a 10-digit number.\n" RESET_TEXT);
        }
    }

    fwrite(&l, sizeof(struct signin), 1, f);
    fclose(f);
    tab; printf(BLUE_TEXT "---------------------------\n");
    tab; printf("YOU HAVE BEEN REGISTERED\n");
    tab; printf("---------------------------\n" RESET_TEXT);
}

void forgetpassword(){
    system("cls");
    int i = 0;
    char newpassword[40];
    char confirm[40];
    unsigned long long int phone;
    FILE *f;
    FILE *n;
    f = fopen("hello.txt", "r");
    if (f == NULL) {
        tab; printf(RED_TEXT "Error opening file\n" RESET_TEXT);
        return;
    }
    n = fopen("new.txt", "w");
    if (n == NULL) {
        tab; printf(RED_TEXT "Error opening temporary file\n" RESET_TEXT);
        fclose(f);
        return;
    }
    tab; printf(BLUE_TEXT "-------------\n");
    tab; printf("CHANGE PASSWORD HERE\n");
    tab; printf("-------------\n" RESET_TEXT);

    while (1) {
        tab; printf("Enter your registered 10-digit number: ");
        fflush(stdin);
        scanf("%llu",&phone);
        if (phone >= 1000000000ULL && phone <= 9999999999ULL) {
            break;
        } else {
            tab; printf(RED_TEXT "Invalid input. Please enter a 10-digit number.\n" RESET_TEXT);
        }
    }

    while (fread(&l, sizeof(struct signin), 1, f)) {
        if (l.number == phone) {
            i = 1;
            tab; printf("Enter new password: ");
            fflush(stdin);
            passwordhide(newpassword);
            printf("\n");
            tab; printf("confirm new password");
            fflush(stdin);
            passwordhide(confirm);
            strcpy(l.password, newpassword);
            printf("\n");
            if (strcmp(newpassword,confirm) == 0) {
                strcpy(l.password,newpassword);
                tab;printf(GREEN_TEXT "PASSWORD CHANGED SUCCESSFULLY" RESET_TEXT);
                break;
            } else {
                printf(RED_TEXT "Password not changed.\n" RESET_TEXT);
                break;
            }
        }
        fwrite(&l, sizeof(struct signin), 1, n);
    }
    fclose(f);
    fclose(n);

    remove("hello.txt");
    rename("new.txt", "hello.txt");

    if (i == 0) {
        tab; printf(RED_TEXT "Phone number not found\n\n" RESET_TEXT);
    } 
}

void mainMenu() {
    int a;
    while (1) {
        su:
        tab; printf(BLUE_TEXT "-----------\n");
        tab; printf("MAIN MENU\n");
        tab; printf("-----------\n" RESET_TEXT);
        tab; printf("1. Create new contact.\n");
        tab; printf("2. Edit contact.\n");
        tab; printf("3. Search contact.\n");
        tab; printf("4. List contacts.\n");
        tab; printf("5. Delete contact.\n");
        tab; printf("6. Exit.\n");
        tab; printf("----------------\n");
        tab; printf("Enter your choice:");
        scanf("%d", &a);
        fflush(stdin);
        switch (a) {
            case 1:
                system("cls");
                addcontact();
                loading();
                system("cls");
                break;
            case 2:
                system("cls");
                editcontact();
                loading();
                system("cls");
                break;
            case 3:
                searchcontact();
                loading();
                system("cls");
                break;
            case 4:
                system("cls");
                listcontact();
                loading();
                system("cls");
                break;
            case 5:
                system("cls");
                deletecontact();
                loading();
                system("cls");
                break;
            case 6:
                system("cls");
                tab; printf(BLUE_TEXT "THANK YOU VISIT AGAIN\n" RESET_TEXT);
                exit(0);
                break;
            default:
                tab; printf(RED_TEXT "Invalid entry\n" RESET_TEXT);
                goto su;
                break;
        }
    }
}

int main() {
    int a;

    while (1) {
        system("cls");

        si:
        tab; printf(BLUE_TEXT "---------------------------\n");
        tab; printf("WELCOME TO THE LOGIN MENU\n");
        tab; printf("---------------------------\n" RESET_TEXT);
        tab; printf("1. Sign In\n");
        tab; printf("2. Login\n");
        tab; printf("3. Forget Password\n");
        tab; printf("Enter your choice:");
        scanf("%d", &a);
        fflush(stdin);
        switch (a) {
            case 1:
                signin();
                loading();
                system("cls");
                break;
            case 2:
                if (login() == 1) {
                    mainMenu();
                } else {
                    tab; printf(RED_TEXT "Login failed\n" RESET_TEXT);
                }
                break;
            case 3:
                forgetpassword();
                printf("\n");
                loading();
                system("cls");
                break;
            default:
                tab; printf(RED_TEXT "You have entered wrong choice\n" RESET_TEXT);
                goto si;
                break;
        }
    }
    return 0;
}
