namespace Lab_7
{ 
  class Program
  { 
    static void Main()
    {
      // [1,5] && [3,7]
      Interval a = new Interval(1, 5);
      Interval b = new Interval(3, 7);
      Console.WriteLine($"a = {a}, b = {b}");
      
      Console.WriteLine($"a * b = {a * b}"); // [3,5]
      Console.WriteLine($"a + b = {a + b}"); // [1,7]
      
      // [1,5] – [4,6] -> [1,4]
      Interval c = new Interval(4, 6);
      Console.WriteLine($"\na = {a}, c = {c}");
      Console.WriteLine($"a - c = {a - c}"); // [1,4]
      
      //  [1,8] – [3,5] -> exception
      var d = new Interval(1, 8);
      var e = new Interval(3, 5);
      Console.WriteLine($"\nd = {d}, e = {e}");
      try
      {
        var diffDE = d - e;
        Console.WriteLine($"d - e = {diffDE}");
      }
      catch (InvalidOperationException ex)
      {
        Console.WriteLine($"Exception!!! d - e: {ex.Message}");
      }
      
      //  [10,12] && [0,3]
      Interval f = new Interval(10, 12);
      Interval g = new Interval(0, 3);
      Console.WriteLine($"\nf = {f}, g = {g}");
      
      Interval interFG;
      try
      {
        interFG = f * g;
      }
      catch (InvalidOperationException ex)
      {
        Console.WriteLine($"Exception!!! f * g: {ex.Message}");
        interFG = f; 
      }
      
      try
      {
        var unionFG = f + g;
        Console.WriteLine($"f + g = {unionFG}");
      }
      catch (InvalidOperationException ex)
      {
        Console.WriteLine($"\nException!!! f + g: {ex.Message}");
      }
    }
  }
}