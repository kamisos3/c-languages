// This is a simple game of guessing numbers using C#, to apply simple game creating syntax and creating a console with dotnet
using System;

class Game
{
    static void Main()
    {
        Console.WriteLine("<o>--------Number Guess Game--------<o>");

        Random random = new Random();
        int secretNumber = random.Next(1, 334); // Picks a number between 1 to 333
        int guess = 0;
        int attempts = 0;

        while (guess != secretNumber)
        {
            Console.Write("Guess between the numbers 1 to 333: ");
            guess = int.Parse(Console.ReadLine());
            attempts++; // Sums the attempts taking to guess the number

            if (guess < secretNumber)
                Console.WriteLine("Maybe a higher number?");
            else if (guess > secretNumber)
                Console.WriteLine("Try a smaller number...");
            else
                Console.WriteLine("YOU WIN!");
        }
    }
}