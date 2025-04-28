namespace Lab3.Data;
using static Lab3.HelperMethods.HelperMethods;

public class DateService
{
  public static void UsingService()
  {
    while (true)
    {
      Console.WriteLine("=== Context Menu for Data Service ===");
      Console.WriteLine("1 - GetDay");
      Console.WriteLine("2 - GetDaySpan");
      Console.WriteLine("3 - Exit");
      Console.WriteLine("=======================================");
      Console.Write("Select a menu item: ");

      string choice = Console.ReadLine();

      switch (choice)
      {
        case "1":
          Console.Clear();
          string date = GetStringInput("Enter the data to get day of week.");
          GetDay(date);
          break;
        case "2":
          Console.Clear();
          (int year, int month, int day) = GetData();
          GetDaySpan(year, month, day);
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
  
  private static void GetDay(string date)
  {
    DateTime parsedDate = DateTime.Parse(date);
    string dayName = parsedDate.ToString("dddd");
    dayName = char.ToUpper(dayName[0]) + dayName.Substring(1); // first letter tp upper
            
    Console.WriteLine($"Today {date} is {dayName}");
  }

  private static void GetDaySpan(int year, int month, int day)
  {
    DateTime currentDate = DateTime.Today;
    
    DateTime targetDate = new DateTime(year, month, day);
    
    TimeSpan difference = targetDate - currentDate;
    if (difference.Days > 0)
    {
      Console.WriteLine($"{targetDate.ToShortDateString()} is {difference.Days} days from now {currentDate.ToShortDateString()}.");
    }
    else if (difference.Days < 0)
    {
      Console.WriteLine($"{targetDate.ToShortDateString()} was {-difference.Days} days ago {currentDate.ToShortDateString()}.");
    }
    else
    {
      Console.WriteLine($"{targetDate.ToShortDateString()} today {currentDate.ToShortDateString()}.");
    }
  }
}