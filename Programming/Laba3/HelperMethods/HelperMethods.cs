namespace Lab3.HelperMethods;

public static class HelperMethods
{
  public static double GetDoubleInput(string prompt)
  {
    while (true)
    {
      Console.Write(prompt);
      if (double.TryParse(Console.ReadLine(), out double number))
      {
        return number;
      }
      Console.WriteLine("Error: Please enter a valid number.");
    }
  }

  public static (int year, int month, int day) GetData()
  {
    int year = 0, month = 0, day = 0;
    
    while (true)
    {
      Console.WriteLine("Please enter a year:");
      if (int.TryParse(Console.ReadLine(), out year) && year >= 1 && year <= 9999)
      {
        break;
      }
      Console.WriteLine("Please try again)");
    }

    while (true)
    {
      Console.WriteLine("Please enter a month:");
      if (int.TryParse(Console.ReadLine(), out month) && month >= 1 && month <= 12)
      {
        break;
      } 
      Console.WriteLine("Please try again)");
    }

    while (true)
    {
      Console.WriteLine("Please enter a day:");
      if (int.TryParse(Console.ReadLine(), out day))
      {
        int maxDays = DateTime.DaysInMonth(year, month); // get max days in curr month
        if (day >= 1 && day <= maxDays)
        {
          break;
        }
        Console.WriteLine($"Invalid day, month has only {maxDays} days.");
      }
      else
      {
        Console.WriteLine("Please try again)");
      }
    }
    
    return (year, month, day);
  }
  
  public static string GetStringInput(string prompt)
  {
    (int year, int month, int day) = GetData();
    return $"{year:0000}.{month:00}.{day:00}";
  }
}
