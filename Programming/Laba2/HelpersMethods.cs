namespace Lab2;

public static class HelperMethods
{
    private static double GetDoubleInput(string prompt)
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
    
    private static bool IsTriangleValid(double side1, double side2, double side3)
    {
        
        return side1 + side2 > side3 &&
               side1 + side3 > side2 &&
               side2 + side3 > side1;
    }

    public static void GetTriangleSides(out double side1, out double side2, out double side3)
    {
        while (true)
        {
            side1 = GetDoubleInput("Enter the first side: ");
            side2 = GetDoubleInput("Enter the second side: ");
            side3 = GetDoubleInput("Enter the third side: ");

            if (IsTriangleValid(side1, side2, side3) && side1 >= 0 && side2 >= 0 && side3 >= 0)
            {
                return;
            }
            Console.WriteLine("Is this really a triangle? Try again:");
        }
    }

    public static void GetPointCoordinates(out double x, out double y)
    {
        x = GetDoubleInput("Enter the x-coordinate: ");
        y = GetDoubleInput("Enter the y-coordinate: ");
    }
    
}