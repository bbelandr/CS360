// Benjamin Belandres
// This program simulates a nuclear blast from certain coordinates taken in from the command line
    // Using this program
        // The command is formatted like ./nuke <blast strength> <attenuation> <blast x> <blast y>
        // AFterwards, the program begins reading in people at certain coordinates
            // <x> <y> <name>
        // The program then immediately calculates how many sieverts that person would recieve and prints it
        // This continues until the program no longer has names to read
            // This strategy avoids having to store all the people into memory, and we can just work with
            // what immediately is given to the program
    // The sieverts calculation
        // sieverts = blastStrength * (attenuation)^distance 
        // Distance
            // sqrt((x1 - x0)^2 + (y1 - y0)^2)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Point {  // Holds an x and y coordinate on the grid
    int x;
    int y;
};

struct Person {
    struct Point* location;
    char name[65];  // Takes a maximum of 64 characters plus the null character at the end
};

static double distance(const struct Point *p1, const struct Point *p2); // Calculates the distance from point1 to point2

int main(int argc, char *argv[]) {
    
    // Read in the command line arguments
    if (argc != 5) {
        printf("Usage: ./nuke <blast strength> <attenuation> <blast x> <blast y>\n");
        return 1;
    }

    // Read in bomb
    char* end;  // The position of the last character + 1 read in by strtod is stored in this
    double blastStrength = strtod(argv[1], &end);
    double attenuation = strtod(argv[2], &end);
    
    struct Point* blastLocation = malloc(sizeof(struct Point));
    blastLocation->x = (int)strtol(argv[3], &end, 10);
    blastLocation->y = (int)strtol(argv[4], &end, 10);

    // Read in person
    struct Person currentPerson;
    currentPerson.location = malloc(sizeof(struct Point));
    scanf("%d %d %64s", &currentPerson.location->x, &currentPerson.location->y, currentPerson.name);
    // currentPerson.location->x = 1;
    // currentPerson.location->y = 5;


    // Calculations
    double sieverts = pow(attenuation, distance(blastLocation, currentPerson.location)) * blastStrength;

    printf("%-16.16s:%9.4lf Sv.\n", currentPerson.name, sieverts);

    
    // while Read in a person formatted like:
        // x y name


    free(blastLocation);
    free(currentPerson.location);
    return 0;
}

static double distance(const struct Point *p1, const struct Point *p2) {
    
    return sqrt( pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2));
}
