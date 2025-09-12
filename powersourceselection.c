#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Max consumers and sources
#define MAX_CONSUMERS 100
#define MAX_SOURCES 9

// preferences[i][j] is jth preference for consumer i
int preferences[MAX_CONSUMERS][MAX_SOURCES];

// Sources have name, supply count, eliminated status
typedef struct
{
    char* name;
    int supply;
    bool eliminated;
} source;

// Array of sources
source sources[MAX_SOURCES];

// Numbers of consumers and sources
int consumer_count;
int source_count;

// Function prototypes
bool request(int consumer, int rank, char* name);
void allocate(void);
bool print_selected(void);
int find_min(void);
bool is_conflict(int min);
void eliminate(int min);

int main(void)
{
    // Define available sources (like battery, solar, USB)
    source_count = 3;  
    sources[0].name = "Battery";
    sources[1].name = "Solar";
    sources[2].name = "USB";

    for (int i = 0; i < source_count; i++)
    {
        sources[i].supply = 0;
        sources[i].eliminated = false;
    }

    // Define number of consumers
    consumer_count = 5;  

    // Preset preferences (ranked fallback order for each consumer)
    // eg- consumer 0 prefers Solar -> Battery -> USB
    int preset_preferences[5][3] = {
        {1, 0, 2},  // consumer 0
        {0, 1, 2},  // consumer 1
        {1, 2, 0},  // consumer 2
        {0, 2, 1},  // consumer 3
        {2, 0, 1}   // consumer 4
    };

    // Copy preset preferences into global preferences array
    for (int i = 0; i < consumer_count; i++)
    {
        for (int j = 0; j < source_count; j++)
        {
            preferences[i][j] = preset_preferences[i][j];
        }
    }

    // Keep reallocating until viable source exists, not really recursively because that might get messy without malloc
    while (true)
    {
        // Calculate supply, given remaining sources
        allocate();

        // Check if a source has been selected
        bool selected = print_selected();
        if (selected)
        {
            break;
        }

        // Eliminate weakest sources
        int min = find_min();
        bool conflict = is_conflict(min);

        // If conflict, all remaining sources are viable
        if (conflict)
        {
            for (int i = 0; i < source_count; i++)
            {
                if (!sources[i].eliminated)
                {
                    printf("%s\n", sources[i].name);
                }
            }
            break;
        }

        // Eliminate any source with minimum supply
        eliminate(min);

        // Reset supply counts back to zero
        for (int i = 0; i < source_count; i++)
        {
            sources[i].supply = 0;
        }
    }
    return 0;
}

// Tabulate supply for non-eliminated sources
void allocate(void)
{
    // update supply count for eliminated sources
    for (int i = 0; i < consumer_count; i++)
    {
        for (int j = 0; j < source_count; j++)
        {
            if (sources[preferences[i][j]].eliminated == false)
            {
                sources[preferences[i][j]].supply++;
                break;
            }
        }
    }
    return;
}

// Print the selected source, if there is one
bool print_selected(void)
{
    // if any source has more than half of consumers, return true, if none selected, return false
    for (int i = 0; i < source_count; i++)
    {
        if (sources[i].supply > consumer_count / 2)
        {
            printf("%s\n", sources[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum consumers any remaining source has
int find_min(void)
{
    // keep track of what eliminated and make sure to return true if eliminated AND have min supply. check find_min def
    int min = consumer_count;
    for (int i = 0; i < source_count; i++)
    {
        if (sources[i].supply < min && sources[i].eliminated == false)
        {
            min = sources[i].supply;
        }

    }
    return min;
}

// Return true if selection is tied between all sources, false otherwise
bool is_conflict(int min)
{
    // takes arg - "min" || should return true if every source in the system has the same no of consumers, else return false
    for (int i = 0; i < source_count; i++)
    {
        if (!sources[i].eliminated && sources[i].supply != min)
        {
            return false;
        }
    }
    return true;
}

// Eliminate the source (or sources) in last place, ie, least desirable
void eliminate(int min)
{
    // eliminate any source still in the system who has "min" no of consumers
    for (int i = 0; i < source_count; i++)
    {
        if (sources[i].supply == min)
        {
            sources[i].eliminated = true;
        }
    }
    return;
}