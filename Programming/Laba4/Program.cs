namespace Lab_4;
using  Lab_4.Services;
using Lab_4.HelperMethods;

class LrWork
{
  static void Main(string[] args)
  {
    Tariff tariff = Tariff.GetInstance();
    Service service = new("Gophers district", 9001486, 100, 95, tariff);
    
      while (true)
      {
        Console.WriteLine("====== Context Menu ======");
        Console.WriteLine("0 - Author");
        Console.WriteLine("1 - Change residents");
        Console.WriteLine("2 - Change paid residents");
        Console.WriteLine("3 - Change tariff");
        Console.WriteLine("4 - Pay debt");
        Console.WriteLine("5 - Show all information");
        Console.WriteLine("6 - Exit");
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
            int residents = HelperMethods.HelperMethods.GetIntegerInput("Change total residents: ");
            service.UpdateResidents(residents);
            break;
          case "2":
            Console.Clear();
            int paid = HelperMethods.HelperMethods.GetIntegerInput("Change paid residents: ");
            service.UpdatePaidResidents(paid);
            break;
          case "3":
            Console.Clear();
            decimal newTariff = HelperMethods.HelperMethods.GetDecimalInput("Enter new tariff: ");
            tariff.UpdateRate(newTariff);
            service.UpdatePaidResidents(service.PaidResidents);
            break;
          case "4":
            Console.Clear();
            decimal payDebt = HelperMethods.HelperMethods.GetDecimalInput("Enter how much you want to pay: ");
            service.PayDebt(payDebt);
            break;
          case "5":
            Console.Clear();
            Console.WriteLine($"Current residents: {service.TotalResidents}");
            Console.WriteLine($"Current paid: {service.PaidResidents}");
            Console.WriteLine($"Current debt: {service.Debt:C}");
            Console.WriteLine($"Current tariff: {tariff.CurrentRate:C}");
            break;
          case "6":
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