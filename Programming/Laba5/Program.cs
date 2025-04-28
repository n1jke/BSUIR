namespace Lab_5;

using Lab_5.HelperMethods;
using Lab_5.Users;
using Lab_5.Service;

class LrWork
{
  static void Main(string[] args)
  {
    HouseService houseService = new HouseService();
    
      while (true)
      {
        Console.WriteLine("====== House Service Menu ======");
        Console.WriteLine("0 - Author");
        Console.WriteLine("1 - Add house resident.");
        Console.WriteLine("2 - Set/update tariff.");
        Console.WriteLine("3 - Register house resident usings (full name).");
        Console.WriteLine("4 - Register house resident usings (Guid).");
        Console.WriteLine("5 - Get house resident info (full name).");
        Console.WriteLine("6 - Get house resident info (guid).");
        Console.WriteLine("7 - Get cost fo all house residents.");
        Console.WriteLine("8 - Show all Residents.");
        Console.WriteLine("9 - Exit");
        Console.Write("Select a menu item: ");

        string choice = Console.ReadLine();

        try
        {
        switch (choice)
        {
          case "0":
            Console.Clear();
            Console.WriteLine("Complete: Khadorik Matvey");
            
            break;
          
          case "1":
            Console.Clear();
            Console.Write("Enter resident full name: ");
            string fullName = Console.ReadLine();
            houseService.AddResident(fullName, true);
            Console.WriteLine("Resident added successfull!");
            
            break;
          
          case "2":
            Console.Clear();
            TypeService serviceType = HelperMethods.HelperMethods.GetServiceTypeInput("Enter service type(water, gas, electricity or heat): ");
            decimal price = HelperMethods.HelperMethods.GetDecimalInput("Enter tariff price per one unit: ");
            houseService.SetTariff(serviceType, price);
            Console.WriteLine("Tariff set/updated successfull!");
            
            break;
          
          case "3":
            Console.Clear();
            Console.Write("Enter resident full name: ");
            
            string nameResident = Console.ReadLine();
            TypeService typeServ = HelperMethods.HelperMethods.GetServiceTypeInput("Enter type of service: ");
            decimal units = HelperMethods.HelperMethods.GetDecimalInput("Enter number used units: ");
            
            houseService.RegisterUserService(nameResident, typeServ, units);
            Console.WriteLine("Service usage registered successfull!");
            
            break;
          
          case "4":
            Console.Clear();
           
            Guid guidResident = HelperMethods.HelperMethods.GetGuidInput("Enter guid of house resident: ");
            TypeService typeServGuid = HelperMethods.HelperMethods.GetServiceTypeInput("Enter type of service: ");
            decimal unitsGuid = HelperMethods.HelperMethods.GetDecimalInput("Enter number used units: ");
            
            houseService.RegisterUserService(guidResident, typeServGuid, unitsGuid);
            Console.WriteLine("Service usage registered successfull!");
            
            break;
          
          case "5":
            Console.Clear();
            
            Console.Write("Enter resident full name: ");
            string nameInfo = Console.ReadLine();
            decimal costName = houseService.GetResidentTotalCost(nameInfo);
            
            Console.WriteLine($"Sum cost for resident {nameInfo}: {costName:C} ");
            break;
          
          case "6":
            Console.Clear();
            
            Guid guidInfo = HelperMethods.HelperMethods.GetGuidInput("Enter guid of resident: ");
            decimal costGuid = houseService.GetResidentTotalCost(guidInfo);
            
            Console.WriteLine($"Sum cost for resident {guidInfo}: {costGuid:C} ");
            break;
          
          case "7":
            Console.Clear();

            decimal summaryCost = houseService.GetTotalServiceCost();
            Console.WriteLine($"Sum cost for all residents: {summaryCost:C} ");
            break;
          
          case "8":
            Console.Clear();

            HelperMethods.HelperMethods.ShowAllResidents(houseService.GetResidents());
            break;
          
          case "9":
            return;
          
          default:
            Console.Clear();
            Console.WriteLine("Invalid input.");
            break;
        }
      }catch (Exception ex)
        {
          Console.Clear();
          Console.WriteLine($"Errorrrrrrrr): {ex.Message}");
        }
    }
  } 
}