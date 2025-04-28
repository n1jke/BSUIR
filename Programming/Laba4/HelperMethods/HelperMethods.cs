namespace Lab_4.HelperMethods;

public static class HelperMethods
{
  public static decimal GetDecimalInput(string prompt)
  {
    while (true)
    {
      Console.Write(prompt);
      if (decimal.TryParse(Console.ReadLine(), out decimal number))
      {
        return number;
      }
      Console.WriteLine("Error: Please enter a valid number.");
    }
  }
  
  public static int GetIntegerInput(string prompt)
  {
    while (true)
    {
      Console.Write(prompt);
      if (int.TryParse(Console.ReadLine(), out int number))
      {
        return number;
      }
      Console.WriteLine("Error: Please enter a valid number.");
    }
  }


}
