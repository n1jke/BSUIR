namespace Lab_5.HelperMethods;
using Lab_5.Users;
using Lab_5.Service;

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

    public static Guid GetGuidInput(string prompt)
    {
        while (true)
        {
            Console.Write(prompt);
            if (Guid.TryParse(Console.ReadLine(), out Guid guid))
            {
                return guid;
            }
            Console.WriteLine("Error: Please enter a valid Guid.");
        }
    }

    public static TypeService GetServiceTypeInput(string prompt)
    {
        while (true)
        {
            Console.Write(prompt);
            string input = Console.ReadLine();
            if (Enum.TryParse(input, true, out TypeService serviceType))
            {
                return serviceType;
            }
            Console.WriteLine("Error! Please enter: water, gas, heat, or electricity.");
        }
    }

    public static void ShowAllResidents(List<HouseResident> residents)
    {
        if (residents.Count == 0)
        {
            Console.WriteLine("No residents registered.");
            return;
        }

        Console.WriteLine("List of all residents:");
        foreach (var resident in residents)
        {
            Console.WriteLine($"- {resident.FullName}, with id: {resident.Id}");
        }
    }
}

