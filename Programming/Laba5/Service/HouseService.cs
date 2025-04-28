namespace Lab_5.Service;
using Lab_5.Users;
using Lab_5.Service;

public class HouseService
{
    private List<HouseResident> residents = new();
    private Dictionary<TypeService, Tariff> tariffs = new();

    public List<HouseResident> GetResidents() => residents;
    
    public void SetTariff(TypeService service, decimal pricePerOne)
    {
        if (tariffs.ContainsKey(service))
        {
            tariffs[service].UpdatePrice(pricePerOne);
        }
        else
        {
            tariffs[service] = new Tariff(service, pricePerOne);
        }
    }
    
    public void AddResident(string fullName, bool allowDuplicate = false) // can change allowDuplicate to make 2 users with same fallName
    {
        foreach (var resident in residents)
        {
            if (resident.FullName.Equals(fullName, StringComparison.OrdinalIgnoreCase))
            {
                if (!allowDuplicate)
                {
                    throw new InvalidOperationException("Resident with the same name already exists. " +
                                                        "To add a duplicate, set allowDuplicate = true.");
                }
                break;
            }
        }
        
        residents.Add(new HouseResident(fullName));
    }
    
    public void RegisterUserService(string fullName, TypeService service, decimal units)
    {
        HouseResident foundResident = null;
        int count = 0;

        foreach (var resident in residents)
        {
            if (resident.FullName.Equals(fullName, StringComparison.OrdinalIgnoreCase))
            {
                foundResident = resident;
                count++;
            }
        }

        if (count == 0)
        {
            throw new ArgumentException("Resident not found.");
        }

        if (count > 1)
        {
            throw new InvalidOperationException("Multiple residents with the same name exist. " +
                                                "Use RegisterUser with guid instead.");
        }

        foundResident.AddUnits(service, units);
    }
    
    public void RegisterUserService(Guid residentId, TypeService service, decimal units)
    {
        foreach (var resident in residents)
        {
            if (resident.Id == residentId)
            {
                resident.AddUnits(service, units);
                return;
            }
        }
        
        throw new ArgumentException("Resident not found.");
    }
    
    public decimal GetResidentTotalCost(string fullName)
    {
        var matches = residents.Where(r => r.FullName.Equals(fullName, StringComparison.OrdinalIgnoreCase)).ToList();
        if (matches.Count == 0)
        {
            throw new ArgumentException("Resident not found.");
        }
        if (matches.Count > 1)
        {
            throw new InvalidOperationException("Multiple residents with the same name exist. " +
                                                "Please use GetResidentTotalCost(Guid id) to correct cost.");
        }

        return matches[0].GetCost(tariffs);
    }
    
    public decimal GetResidentTotalCost(Guid residentId)
    {
        var resident = residents.FirstOrDefault(r => r.Id == residentId);
        if (resident == null)
            throw new ArgumentException("Resident not found.");
        return resident.GetCost(tariffs);
    }
    
    public decimal GetTotalServiceCost()
    { 
        decimal totalCost = 0;

        foreach (var resident in residents)
        {
            totalCost += resident.GetCost(tariffs);
        } 
        return totalCost;
    }
}