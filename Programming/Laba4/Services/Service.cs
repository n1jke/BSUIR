using Lab_4.Services;

namespace Lab_4.Services;

public class Service
{
  public string District { get; set; }
  
  public int OfficeNumber { get; set; }
  
  public int TotalResidents { get; private set; }
  
  public int PaidResidents { get; private set; }
  
  public decimal Debt { get; private set; }
  
  private readonly Tariff _tariff;

  public Tariff Tariff => _tariff;

  public void UpdateResidents(int total)
  {
    if (total < 0)
    {
      throw new ArgumentException("Total residents must be positive");
    }
    
    TotalResidents = total;

    if (PaidResidents > TotalResidents)
    {
      PaidResidents = TotalResidents;
    }
    
    UpdateDebt();
  }
  

  public void UpdatePaidResidents( int paidResidents)
  {
    if (PaidResidents < 0 || paidResidents > TotalResidents)
    {
      throw new ArgumentException("Paid residents must be positive and greater than total residents");
    }
    
    PaidResidents = Math.Clamp(paidResidents, 0, TotalResidents);
    UpdateDebt();
  }
  
  private void UpdateDebt() => Debt += (TotalResidents - PaidResidents) * _tariff.CurrentRate;

  public void PayDebt(decimal value)
  {
    if (value < 0)
    {
      throw new ArgumentException("Debt payments must be positive");
    }
    
    Debt = value > Debt 
                       ? 0 
                       : Debt - value;
  }
  
  public Service(string district, int officeNumber, int totalResidents, int paidResidents, Tariff tariff)
  {
    if (string.IsNullOrWhiteSpace(district))
    {
      throw new ArgumentException("District cannot be empty");
    }
    if (officeNumber <= 0)
    {
      throw new ArgumentException("Office number must be positive");
    }
    if (totalResidents < 0)
    {
      throw new ArgumentException("Total residents must be positive");
    }
    if (paidResidents < 0 || paidResidents > totalResidents)
    {
      throw new ArgumentException("Paid residents must be positive and not greater than total residents");
    }
    
    _tariff = tariff ?? throw new ArgumentNullException(nameof(tariff), "Tariff cannot be null");
    
    District = district;
    OfficeNumber = officeNumber;
    TotalResidents = totalResidents;
    PaidResidents = paidResidents;
    UpdateDebt();
  }
}