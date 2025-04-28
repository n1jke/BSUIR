using  Lab_6.Models;

class Demo
{
  static void Main()
  {
    Console.WriteLine("=== Class Beer ===");
    var beer = new Beer(ibu: 45, strength: 4.4, price: 4, name: "Пітнае", brand: "Аліварыя", isCraft: true); 
    Console.WriteLine($"new Beer: {beer.Name}, {beer.Brand}, {beer.Price} byn., IBU: {beer.IBU}, stenght: {beer.Strength}, is craft? {beer.IsCraft}");
    Console.WriteLine($"Рейтинг качества: {beer.CalculateQualityRating()}"); // abstract method
    
    Console.WriteLine($"Up cost, current :  {beer.Price}"); 
    beer.IncreasePrice(0.5, "up water price", out string increaseDetails); 
    Console.WriteLine(increaseDetails);

    //MultiplyPrice no hiding
    Console.WriteLine($"Base method for '*', without hiding, current : {beer.Price}");
    beer.MultiplyPrice(1.5);
    Console.WriteLine($"New price {beer.Price}");

    // hiding MultiplyPrice
    Console.WriteLine("Hide method");
    beer.MultiplyPrice(2, out string operationDetails);
    Console.WriteLine(operationDetails);

     // change brand form base
    Console.WriteLine($"Change brand, current : {beer.Brand}");
    beer.ChangeBrand("Рэчыцкае");
    Console.WriteLine($"New: {beer.Brand}");

    // ferm time
    Console.WriteLine($"Fermentation time: {beer.GetFermentationTime()} weeks");

    Console.WriteLine("\n=== Class Gin ===");
    var botanicals = new HashSet<string>
    {
      "Juniper", "Coriander", "Angelica", "Lemon peel", "Orris root", "Cardamom", "Cinnamon", "Ginger", "Nutmeg"
    };
    var gin = new Gin(strength: 42.0, price: 30, name: "Dry London", brand: "Beefeater", distillationTimes: 4, botanicals: botanicals);

    Console.WriteLine($"new Gin: {gin.Name}, {gin.Brand}, {gin.Price} byn., strenght: {gin.Strength}, dist times: {gin.DistillationTimes}");
    Console.WriteLine($"Botanicals: {string.Join(", ", gin.Botanicals)}");
    
    // abstract method
    Console.WriteLine($"Rating: {gin.CalculateQualityRating()}");  

    // override virtual
    Console.WriteLine($"Change brand, current: {gin.Brand}"); 
    gin.ChangeBrand("Bombay Sapphire");
    Console.WriteLine($"New brand: {gin.Brand}");

    // base method
    Console.WriteLine($"Up cost, current: {gin.Price}"); 
    gin.IncreasePrice(3);
    Console.WriteLine($"New price {gin.Price}");

    Console.WriteLine("Method '*' from base");
    Console.WriteLine($"Current price: {gin.Price}");
    gin.MultiplyPrice(2.5);
    Console.WriteLine($"New price: {gin.Price}");

    Console.WriteLine($"Influsion time : {gin.CalculateOptimalInfusionTime()} hours for good drink"); 
  }
}