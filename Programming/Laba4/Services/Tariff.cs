namespace Lab_4.Services;

public class Tariff
{
  private static Tariff _instance;
  private decimal _currentRate;
    
  public decimal CurrentRate
  {
    get => _currentRate;
    private set => _currentRate = value > 0 ? value : throw new ArgumentException("Rate must be greater than zero.");
  }
    
  private Tariff(decimal rate) => CurrentRate = rate;
    
  public static Tariff GetInstance()
  {
    _instance ??= new Tariff(50); // check is null for singleton pattern
    return _instance;
  }
    
  public void UpdateRate(decimal value) => CurrentRate = value;
}