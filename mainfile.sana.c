/*
 * ------------------------- *
 * Application : SANA        *
 * Version : 3.1             *
 * By : Md. Salman Morshed   *
 * salmanmorshed@gmail.com   *
 * Date : 13-08-2012         *
 * ------------------------- *
 */


#include "header.sana.h"


char defaultBotID[17] = "821635401e34e889";
float sanaVersion = 3.1;


int main(int argc, char **argv) {
    int exitCoin = 0, runCycles = 0, totalCycles;
    char defaultCustID[17], input[300], output[300];
    strcpy(defaultCustID, GetCustomerID(defaultBotID));

    FILE *cycles;
    cycles = fopen("cycles.dat", "r");
    if (cycles == NULL) {
        totalCycles = 0;
    } else {
        char buf[8];
        fgets(buf, 8, cycles);
        totalCycles = atoi(buf);
        fclose(cycles);
    }
    if (argc == 3 && !strcmp(argv[1], "--botid")) {
        if (strlen(argv[2]) != 16) {
            puts("> Error: Bot ID should be 16-characters in length.");
            exit(4);
        } else {
            strcpy(defaultBotID, argv[2]);
            printf("~ Attention! This is not SANA anymore! \n  Bot ID has been changed to %s\n", defaultBotID);
        }

    } else {
        puts("SANA is an intelligent chatter bot.");
        puts("She is friendly and loves to talk!");
        puts("She learns from you and never forgets!");
        puts("--------------------------------");

        if (totalCycles < 5) {
            puts("Type \"!help\" to get the available options");
            puts("Type \"!exit\" to end the conversation and quit");
            puts("--------------------------------");
        }
    }

    while (!exitCoin) {
        printf("> ");
        gets(input);
        if (!strcmp(input, "!about")) {
            puts(": SANA is a chatterbot application");
            puts("  Version 3.1, Released 13-10-2012");
            puts("  Frontend designed in C language");
            puts("  Developed by Md. Salman Morshed");
            puts("  Mail: salmanmorshed@gmail.com");
            puts("  Based on ALICE by Dr. Richard Wallace");
            puts("--------------------------------");
            continue;
        }

        if (!strcmp(input, "!update")) {
            VersionCheck();
            puts("--------------------------------");
            continue;
        }

        if (!strcmp(input, "!help")) {
            puts(": Special commands:");
            puts("  !about \t Get software and developer information");
            puts("  !update \t Check and notify if newer version is available");
            puts("  !reset \t Reset user recognition and data");
            puts("  !help \t Display the help texts (duh!)");
            puts("  !exit \t Tell SANA goodbye and quit the program");
            puts("--------------------------------");
            continue;
        }
        if (strstr(input, "!reset")) {
            remove("./customer.dat");
            remove("./cycles.dat");
            puts("-- Customer data has been reset!");
            continue;
        }
        if (!strcmp(input, "!exit")) {
            exitCoin = 1;
        } else {
            runCycles++;
        }
        strcpy(output, FormatXMLReply(GetXMLReply(defaultBotID, defaultCustID, input), 'a'));
        printf(": ");
        puts(output);
    }
    cycles = fopen("cycles.dat", "w");
        totalCycles += runCycles;
        char buf[8];
        sprintf(buf, "%d", totalCycles);
        fputs(buf, cycles);
        fclose(cycles);

    if (runCycles >= 10) {
        puts("--------------------------------");
        puts("  System: Please hang on, this will take a second...");
        if (VersionCheck("silent")) getchar();
    }

    sleep(1);
    return 0;
}



/* *** Function to check new version availability *** */
int VersionCheck() {
    puts(": Looking for updates...");
    char *vbk, *defaultCustID;
    defaultCustID = GetCustomerID(defaultBotID);
    vbk = FormatXMLReply(GetXMLReply(defaultBotID, defaultCustID, "latestversionnumber"), 'a');
    float latest = atof(vbk);
    if (latest > sanaVersion) {
        puts(": New version of SANA is available!");
        printf("  Current: %1.1f, New: %1.1f\n", sanaVersion, latest);
        puts("  Run the \"sana-updater.exe\" tool from the installation folder!");
        return 1;
    } else {
        printf("  You are using the latest version! [%1.1f]\n", latest);
        return 0;
    }
}
