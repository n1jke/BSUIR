class Program
{ 
  static void Main(string[] args)
  {
    Console.WriteLine("Введите первое число:");
    double x = Solution.InputDouble();
    
    Console.WriteLine("Введите второе число:");
    double y = Solution.InputDouble();

    double result = Solution.Solve(x, y);
    Console.WriteLine($"Результат деления {x} на {y} равен: {result}");
  }
}
