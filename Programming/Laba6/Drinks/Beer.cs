namespace Lab_6.Models;

public class Beer : Alcohol
{
  // properties
  public double IBU { get; set; }  // (International Bitterness Unit == 'горечь')
  public bool IsCraft { get; set; } 

  // constructor (with init list for base class)
  public Beer(double ibu, double strength, double price, string name, string brand, bool isCraft)
    : base(strength, price, name, brand)
  {
    IBU = ibu;
    IsCraft = isCraft;
  }

  // overload method IncreasePrice
  public void IncreasePrice(double amount, string reason, out string operationDetails)
  {
    base.IncreasePrice(amount); // base class methods 
    operationDetails = $"Method overload. Up cost for {amount} because : {reason}";
  }

    // hide method MultiplyPrice 
  public new void MultiplyPrice(double multiplier, out string operationDetails)
  {
    double oldPrice = Price;
    base.MultiplyPrice(multiplier); //base class methods 
    operationDetails = $"Transform : from {oldPrice} -> to {Price} (x{multiplier})";
  }

  // override method
  public override double CalculateQualityRating()
  {
    // random formula
    double baseRating = 2.5 + (Strength / 10); // 2.5-5.5 
    double craftBonus = IsCraft ? 3 : 0;  // + craft bonus
    double ibuBonus = Math.Min(IBU / 20, 3); // 0 - 3
    return Math.Round(baseRating + craftBonus + ibuBonus, 1); 
  }

  // ferm. time in weeks
  public int GetFermentationTime() => IsCraft ? 14 : 7; 
}