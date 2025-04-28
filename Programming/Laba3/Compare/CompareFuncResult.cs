namespace Lab3.Compare;
using static Lab3.HelperMethods.HelperMethods;

public class CompareFuncResult
{
  public static void Compare()
  {
    double firstVar = GetDoubleInput("Input first variable: ");
    double secondVar = GetDoubleInput("Input second variable: ");

    double firstResult = FindFunctionResult(firstVar);
    double secondResult = FindFunctionResult(secondVar);

    if (Math.Abs(firstResult - secondResult) <= Double.Epsilon)
    {
      Console.WriteLine($"Function result is equal between variables {firstResult} and {secondResult}.");
    } else if (firstResult > secondResult)
    {
      Console.WriteLine($"First function with result {firstResult} result is greater than the second {secondResult}.");
    }
    else
    {
      Console.WriteLine($"Second function with result {secondResult} result is greater than the first {firstResult}.");
    }
  }
  private static double FindFunctionResult(double arg)
  {
    double result = arg - Math.Sin(arg);
    return result;
  }
}