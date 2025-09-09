````md
# Embedded Power Source Selection

This project demonstrates a **power source selection algorithm** for embedded systems, inspired by runoff election logic. The program selects the most suitable power source for a set of consumers based on their ranked preferences, iteratively eliminating less preferred or overloaded sources until a viable choice is determined.

---

## Features

- Supports up to 100 consumers and 9 power sources.
- Uses **ranked preferences** for each consumer to determine the best source.
- Handles conflicts by eliminating sources with the lowest selection count.
- Automatically resolves ties when all remaining sources are equally viable.
- Fully non-interactive; uses preset preference arrays suitable for embedded systems.

---

## How It Works

1. **Define Sources:** Each source has a name, a supply count (number of consumers currently assigned), and an eliminated flag.
2. **Preset Preferences:** Each consumer ranks the available sources in order of preference.
3. **Allocation Loop:**
   - Tabulate supply counts for non-eliminated sources.
   - Check if any source has majority support (more than half of consumers).
   - If no majority, eliminate sources with the minimum supply.
   - Repeat until a single source is selected or a tie occurs.
4. **Output:** Prints the selected power source(s) to the console.

---

## Example Setup

```c
// Define available sources
sources[0].name = "Battery";
sources[1].name = "Solar";
sources[2].name = "USB";

// Define consumer preferences (ranked fallback order)
int preset_preferences[5][3] = {
    {1, 0, 2},  // Consumer 0 prefers Solar -> Battery -> USB
    {0, 1, 2},  // Consumer 1 prefers Battery -> Solar -> USB
    {1, 2, 0},  // Consumer 2 prefers Solar -> USB -> Battery
    {0, 2, 1},  // Consumer 3 prefers Battery -> USB -> Solar
    {2, 0, 1}   // Consumer 4 prefers USB -> Battery -> Solar
};
````
---

## Benefits

* Ensures fair allocation of power sources based on consumer preferences.
* Resolves conflicts and overloaded sources dynamically.
* Adaptable to real embedded systems, such as IoT devices or robotics, where multiple power options are available.

---

## Usage

* Compile with a standard C compiler:

```bash
gcc -o power_selection power_selection.c
```

* Run:

```bash
./power_selection
```
---

The output will display the selected power source(s) based on the preset preferences.

---

## Notes

* The algorithm is inspired by runoff election logic but repurposed for resource allocation.
* Can be extended to handle dynamic preferences, real-time sensor input, or additional selection criteria.

```

This README is concise, professional, and explains the **purpose, logic, and usage** of your embedded power source selection script without unnecessary emojis.  

If you want, I can also add a **diagram showing the iterative elimination flow**, which is helpful for embedded system documentation. Do you want me to do that?
```
---