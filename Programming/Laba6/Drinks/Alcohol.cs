namespace Lab_6.Models;

public abstract class Alcohol
{
  protected double _strength;
  protected double _price;
  protected string _name;
  protected string _brand;

  //public  properties
  public string Brand
  {
    get => _brand;
    protected set => _brand = value;
  }

  public double Strength
  {
    get => _strength;
    protected set => _strength = value;
  }

  public string Name
  {
    get => _name;
    protected set => _name = value;
  }

  public double Price
  {
    get => _price;
    protected set => _price = value;
  }

  // base constructor
  protected Alcohol(double strength, double price, string name, string brand)
  { 
    _strength = strength;
    _price = price; 
    _name = name;
    _brand = brand;
  }

  // overload in 'Beer' stay in gin
  public virtual void IncreasePrice(double amount) 
  {
    _price += amount;
  }

  // override virtual method in 'Gin'
  public virtual void ChangeBrand(string newBrand)
  {
    _brand = newBrand;
  }

  // abstract method
  public abstract double CalculateQualityRating();

  // hiding(with new) method
  public void MultiplyPrice(double multiplier)
  {
    _price *= multiplier;
  }

}