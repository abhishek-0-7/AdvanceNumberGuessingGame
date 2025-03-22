#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

// Function to display a loading animation
void loading_animation() {
    printf("\nLoading the game");
    for (int i = 0; i < 5; i++) {
        printf(".");
        fflush(stdout);
        _sleep(500); // Delay for 500 milliseconds (Windows)
        // For Linux/Unix systems, use usleep(500000);
    }
    printf("\n");
}

// Function to display a header
void display_header() {
    printf("\n======================================\n");
    printf("     🎮 Number Guessing Game 🎮       \n");
    printf("======================================\n");
}

// Function to calculate and display elapsed time
void display_timer(clock_t start_time, clock_t end_time) {
    double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("\n⏱ Time taken: %.2f seconds\n", elapsed_time);
}

// Enhanced hint system
void provide_hint(int guess, int random_guess) {
    if (random_guess % 2 == 0) {
        printf("Hint: The number is EVEN.\n");
    } else {
        printf("Hint: The number is ODD.\n");
    }

    if (random_guess % 3 == 0) {
        printf("Hint: The number is divisible by 3.\n");
    } else {
        printf("Hint: The number is NOT divisible by 3.\n");
    }

    if (abs(guess - random_guess) <= 10) {
        printf("Hint: You're VERY close! The difference is less than or equal to 10.\n");
    }
}

// Main function
int main() {
    int no_of_guess, random_guess, guess, range = 100;
    char play_again;

    srand(time(NULL)); // Seed the random number generator

    do {
        no_of_guess = 0;
        random_guess = rand() % range + 1;

        display_header();
        loading_animation();

        printf("Guess a number between 1 and %d.\n", range);
        clock_t start_time = clock(); // Start the timer

        while (1) {
            printf("\nEnter your guess: ");
            scanf("%d", &guess);

            // Validate input
            if (guess < 1 || guess > range) {
                printf("Invalid input! Please enter a number between 1 and %d.\n", range);
                continue;
            }

            no_of_guess++;

            if (guess < random_guess) {
                printf("Too low! Try a larger number.\n");
            } else if (guess > random_guess) {
                printf("Too high! Try a smaller number.\n");
            } else {
                printf("\n🎉 CONGRATULATIONS! 🎉\n");
                printf("You guessed the number %d in %d attempts!\n", random_guess, no_of_guess);
                break;
            }

            // Provide enhanced hints after every 3 incorrect guesses
            if (no_of_guess % 3 == 0) {
                provide_hint(guess, random_guess);
            }
        }

        clock_t end_time = clock(); // End the timer
        display_timer(start_time, end_time); // Show the elapsed time

        // Ask if the player wants to play again
        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &play_again);

    } while (tolower(play_again) == 'y');

    printf("\nThanks for playing! Goodbye.\n");
    return 0;
}