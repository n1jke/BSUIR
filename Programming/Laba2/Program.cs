using Lab2;

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
      Console.WriteLine("3 - Exit");
      Console.WriteLine("=====================");
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
          IsoscelesTriangle.CheckIsoscelesTriangle();
          break;
        case "2":
          Console.Clear();
          PointPosition.CheckPointPosition();
          break;
        case "3":
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