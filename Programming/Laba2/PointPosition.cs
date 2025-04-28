namespace Lab2;

public static class PointPosition
{
  public static void CheckPointPosition()
  {
    double pointX, pointY;
    HelperMethods.GetPointCoordinates(out pointX, out pointY);
    int result = PointPosition.DeterminePointLocation(pointX, pointY);

    switch (result)
    {
      case 0:
        Console.WriteLine($"The point with coordinates ({pointX}, {pointY}) is outside the defined area.");
        break;
      case 1:
        Console.WriteLine($"The point with coordinates ({pointX}, {pointY}) is on the boundary of the defined area.");
        break;
      case 2:
        Console.WriteLine($"The point with coordinates ({pointX}, {pointY}) is inside the defined area.");
        break;
    }
  }

  public static int DeterminePointLocation(double x, double y)
  {
    const double OuterRadius = 8.0;
    const double InnerRadius = 3.0;
    const double Precision = 1e-6;

    double distanceSquared = x * x + y * y;
    double outerRadiusSquared = OuterRadius * OuterRadius;
    double innerRadiusSquared = InnerRadius * InnerRadius;

    if ((Math.Abs(distanceSquared - outerRadiusSquared) < Precision && x < 0) ||
        (Math.Abs(distanceSquared - innerRadiusSquared) < Precision  && x < 0)||
        (Math.Abs(x) < Precision && Math.Abs(y) >= InnerRadius && Math.Abs(y) <= OuterRadius))
    {
      return 1; // On the boundary
    }
    else if (distanceSquared <= outerRadiusSquared &&
             distanceSquared >= innerRadiusSquared &&
             x < 0)
    {
      return 2; // Inside the area
    }
    else
    {
      return 0; // Outside the area
    }
  }
}
