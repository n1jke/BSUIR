namespace Lab_6.Models
{
  sealed class Gin : Alcohol
  {
    // set for uniq
    private HashSet<string> _botanicals = new HashSet<string>();

    // properties
    public HashSet<string> Botanicals
    {
      get => _botanicals;
      set => _botanicals = value ?? new HashSet<string>();  // check for null and create new set
    }

    public int DistillationTimes { get; set; } 

    // constructor with init list for base class
    public Gin(double strength, double price, string name, string brand, int distillationTimes, HashSet<string> botanicals)
      : base(strength, price, name, brand)
    {
      DistillationTimes = distillationTimes;
      _botanicals = botanicals ?? new HashSet<string>();
    }

    // override method ChangeBrand
    public override void ChangeBrand(string newBrand)
    {
      Brand = newBrand; 
    }

    // override method CalculateQualityRating 
    public override double CalculateQualityRating()
    {
      // base rating
      double baseRating = 5.0 + (Strength / 15) + Math.Min(DistillationTimes * 0.5, 3);

      // count of votanical
      double botanicalImpact = _botanicals.Count switch
      {
        < 5 => -1.0,  // low
        < 8 => 1.0,   // average
        _ => 2.0      // nice
      };

      return Math.Round(baseRating + botanicalImpact, 1);
    }

    // optimal time
    public int CalculateOptimalInfusionTime()
      => Convert.ToInt32(DistillationTimes * 1.6791); // random nums xd)()
  }
}
