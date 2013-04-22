/*
 * ------------------------- *
 * Application : SANA        *
 * Version : 3.3             *
 * By : Md. Salman Morshed   *
 * salmanmorshed@gmail.com   *
 * Date : 10-10-2012         *
 * ------------------------- *
 */

#include "header.sana.h"

char defaultBotID[17] = "b9b96b247e34f4f2";

int main(int argc, char **argv) {
    int exitCoin = 0, runCycles = 0, totalCycles;
    char defaultCustID[17], input[300], output[300];
    strcpy(defaultCustID, GetCustomerID(defaultBotID));

    FILE *cycles;
    cycles = fopen("cycles.dat", "rb");
    if (cycles == NULL) {
        totalCycles = 0;
    } else {
        fscanf(cycles, "%d", &totalCycles);
        fclose(cycles);
    }
    if (argc == 3 && !strcmp(argv[1], "--botid")) {
        if (strlen(argv[2]) != 16) {
            puts("> Error: Bot ID should be 16-characters in length.");
            exit(4);
        } else {
            strcpy(defaultBotID, argv[2]);
            printf("Attention! This is not SANA anymore!\nAlien-bot loaded, ID: %s\n", defaultBotID);
            puts("--------------------------------");
        }

    } else {
        puts("SANA is an intelligent chatter bot");
        puts("She is friendly and loves to talk");
        puts("She learns from you and never forgets!");
        puts("--------------------------------");

        if (totalCycles < 5) {
            puts("Type \"!help\" to get the available options");
            puts("Type \"!exit\" to end the conversation");
            puts("--------------------------------");
        }
    }

    while (!exitCoin) {
        printf("> ");
        gets(input);
        if (!strcmp(input, "!about")) {
            puts(": SANA is a chatterbot application");
            puts("  Version 3.3, Released 10 October 2012");
            puts("  Frontend designed in C language");
            puts("  Developed by Md. Salman Morshed");
            puts("  Mail: salmanmorshed@gmail.com");
            puts("  Based on ALICE by Dr. Richard Wallace");
            puts("--------------------------------");
            continue;
        }

        if (!strcmp(input, "!update")) {
            VersionCheck(defaultBotID);
            puts("--------------------------------");
            continue;
        }

        if (!strcmp(input, "!help")) {
            puts(": In-chat commands:");
            puts("  !about \t Get software and developer information");
            puts("  !update \t Check and notify if newer version is available");
            puts("  !reset \t Reset the user and usage information");
            puts("  !help \t Display the help texts (duh!)");
            puts("  !exit \t Tell SANA goodbye and quit the program");
            puts("--------------------------------");
            continue;
        }
        if (strstr(input, "!reset")) {
            remove("./customer.dat");
            remove("./cycles.dat");
            puts("-- SANA has been reset!");
            goto lastpart;
            break;
        }
        if (!strcmp(input, "!exit")) {
            exitCoin = 1;
        } else {
            runCycles++;
        }
        strcpy(output, FormatXMLReply(GetXMLReply(defaultBotID, defaultCustID, input), 'a'));
        printf(": ");
        puts(StringReplace(output, "&quot;", "\""));
    }
    cycles = fopen("cycles.dat", "wb");
    totalCycles += runCycles;
    fprintf(cycles, "%d", totalCycles);
    fclose(cycles);

    if (runCycles >= 10) {
        puts("--------------------------------");
        puts(": Please wait, this will only take a second...");
        if (VersionCheck(defaultBotID)) getchar();
    }
lastpart:
    usleep(2000);
    return 0;
}
