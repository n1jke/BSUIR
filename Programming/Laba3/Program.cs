namespace Lab3;
using Lab3.Compare;
using Lab3.Services;
using Lab3.Data;
class LrWork
{ 
  static void Main(string[] args)
  {
    while (true)
    {
      Console.WriteLine("=== Context Menu ===");
      Console.WriteLine("0 - Author");
      Console.WriteLine("1 - Task 1");
      Console.WriteLine("2 - Task 2");
      Console.WriteLine("3 - Task 3");
      Console.WriteLine("4 - Exit");
      Console.WriteLine("====================");
      Console.Write("Select a menu item: ");

      string choice = Console.ReadLine();

      switch (choice)
      {
        case "0":
          Console.Clear();
          Console.WriteLine("Complete: Khadorik Matvey");
          break;
        case "1":
          Console.Clear();
          CompareFuncResult.Compare();
          break;
        case "2":
          Console.Clear();
          ParametrFunctionResult.Find();
          break;
        case "3":
          Console.Clear();
          DateService.UsingService();
          break;
        case "4":
          Console.Clear();
          Console.WriteLine("Exiting the program...");
          return;
        default:
          Console.WriteLine("Invalid input. Please try again.");
          break;
      }
    }
  }
}