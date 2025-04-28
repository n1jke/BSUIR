namespace Lab_5.Users;
using Lab_5.Service;

public class HouseResident
{
  public Guid Id { get;} // Guid - globaly unique identifier
  
  public string FullName { get;}
  
  private Dictionary<Service.TypeService, decimal> counter = new();

  public HouseResident(string fullName)
  {
    if (string.IsNullOrWhiteSpace(fullName))
    {
      throw new ArgumentException($"'{nameof(fullName)}' cannot be null or whitespace.", nameof(fullName));
    }
    FullName = fullName;
    Id = Guid.NewGuid();
  }

  public void AddUnits(Service.TypeService service, decimal units)
  {
    if (units < 0)
    {
      throw new ArgumentException($"'{nameof(units)}' cannot be negative.", nameof(units));
    }

    if (counter.ContainsKey(service))
    {
      counter[service] += units;
    }
    else
    {
      counter.Add(service, units);
    }
  }

  public decimal GetCost(Dictionary<Service.TypeService, Tariff> TariffWithCost)
  {
    decimal cost = 0;

    foreach (var entry in counter)
    {
      if (TariffWithCost.TryGetValue(entry.Key, out var tariff))
      {
        cost += entry.Value * tariff.PricePerOne;
      }
      else
      {
        throw new ArgumentException($"'{nameof(entry.Key)}' cannot be null or empty.", nameof(entry.Key));
      }
    }

    return cost;
  }
  
}