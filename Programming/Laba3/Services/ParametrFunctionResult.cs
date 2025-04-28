namespace Lab3.Services;
using  Lab3.HelperMethods;

public class ParametrFunctionResult
{
  public static void Find()
  {
    double _argK = HelperMethods.GetDoubleInput("Input variable k: ");
    double _argZ = HelperMethods.GetDoubleInput("Input variable z: ");
    double _argX = FindParametrX(_argK, _argZ);

    double baseValue = Math.Log(1 + Math.Pow(_argX, 2)) + Math.Cos(_argX + 1);
    double exponentValue = Math.Exp(_argK * _argX); // e^(k*x)
    double result = Math.Pow(baseValue, exponentValue);


    Console.WriteLine($"Function result: {result}");
  }
  
  private static double FindParametrX(double argK, double argZ)
  {
    if (argK >= 1)
    {
      return Math.Pow(argZ, 2) + argZ;
    }
    else
    {
      return argK * Math.Pow(argZ, 3);
    }
  }
}
