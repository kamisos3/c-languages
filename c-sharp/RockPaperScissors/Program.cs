// Making a rock, paper, scissors game to work with C# object oriented programming
using System;

enum Choice { Rock, Paper, Scissors }

class Game
{
    private Random random = new Random();
    private int playerScore = 0;
    private int computerScore = 0;

    static void Main() => new Game().Play();

    void Play()
    {
        while (true)
        {
            Console.WriteLine($"\n[Player: {playerScore} | Computer: {computerScore}]");
            Console.WriteLine("1. Rock  2. Paper  3. Scissors  4. Quit");
            Console.Write("Choose: ");

            if (!int.TryParse(Console.ReadLine(), out int input) || input == 4)
                break;

            Choice player = (Choice)(input - 1);
            Choice computer = (Choice)random.Next(3);

            Console.WriteLine($"You: {player} | Computer: {computer}");
            DetermineWinner(player, computer);
        }

        Console.WriteLine($"\nFinal Score - You: {playerScore} | Computer: {computerScore}");
    }

    void DetermineWinner(Choice player, Choice computer)
    {
        if (player == computer)
            Console.WriteLine("Tie! Play again");
        else if ((player == Choice.Rock && computer == Choice.Scissors) ||
                 (player == Choice.Paper && computer == Choice.Rock) ||
                 (player == Choice.Scissors && computer == Choice.Paper))
        {
            Console.WriteLine("YOU WIN!");
            playerScore++;
        }
        else
        {
            Console.WriteLine("You loose...");
            computerScore++;
        }
    }
}
