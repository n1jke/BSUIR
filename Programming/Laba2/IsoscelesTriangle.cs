namespace Lab2;

public static class IsoscelesTriangle
{
  public static void CheckIsoscelesTriangle()
  {
    double side1, side2, side3;
    HelperMethods.GetTriangleSides(out side1, out side2, out side3);
        
    if (IsoscelesTriangle.IsTriangleIsosceles(side1, side2, side3))
    {
      Console.WriteLine($"The triangle with sides {side1}, {side2}, {side3} is isosceles!");
    }
    else
    {
      Console.WriteLine($"The triangle with sides {side1}, {side2}, {side3} is not isosceles.");
    }
  }
  
  public static bool IsTriangleIsosceles(double side1, double side2, double side3)
  {
    return side1 == side2 || side1 == side3 || side2 == side3;
  }
}