namespace Lab_7;

public class Interval
{
  private double _left; 
  private double _right;

  public double Left
  {
    get => _left;
    set
    {
      if (value > _right) throw new ArgumentException("Left boundary must be less or equal than the right boundary.");
      _left = value;
    }
  }

  public double Right
  {
    get => _right;
    set
    {
      if (value < _left) throw new ArgumentException("Right boundary must be greater or equal than the left boundary.");
      _right = value;
    }
  }

  // indexator
  public double this[int index]
  {
    get => index switch
    {
      0 => Left,
      1 => Right,
      _ => throw new IndexOutOfRangeException()
    };
    set
    {
      if (index == 0) Left = value;
      else if (index == 1) Right = value;
      else throw new IndexOutOfRangeException();
    }
  }
  
  public double Length() => Right - Left;

  public Interval(double left, double right)
  {
    Right = right;
    Left = left;
  }
  
  //true && false 
  public static bool operator true(Interval temp)  => temp.Length() != 0;
  public static bool operator false(Interval temp) => temp.Length() == 0;
  
  // casts
  public static explicit operator double(Interval temp) => temp.Length();
  public static explicit operator Interval(double len) => new Interval(0, len); 
  
  // toString 
  public override string ToString() => $"({Left}, {Right})";
  
  // '+', '-', '*'
  public static Interval operator* (Interval first, Interval second)
  {
    double left = Math.Max(first.Left, second.Left);
    double right = Math.Min(first.Right, second.Right);
    if (left > right)
    {
      throw new InvalidOperationException($"Interval {first.ToString()} and {second.ToString()} do not overlap.");
    }
    return new Interval(left, right);
  }

  public static Interval operator+ (Interval first, Interval second)
  {
    var overlap = first * second;
    if (ReferenceEquals(overlap, null))
      throw new InvalidOperationException(
        $"Interval {first} and {second} do not overlap and cannot be merged)"
      );
    return new Interval(Math.Min(first.Left, second.Left), Math.Max(first.Right, second.Right)
    );
  }


  public static Interval operator- (Interval first, Interval second)
  {
    //not overlapped
    if ((first * second).Length() == 0)
    {
      return new Interval(first.Left, first.Right);
    }
    
    // full overlap
    if (second.Left <= first.Left && second.Right >= first.Right)
    {
      return new Interval(0, 0);
    } 
    
    // second in the left part
    if (second.Left <= first.Left && second.Right < first.Right)
    {
      return new Interval(second.Right, first.Right);
    }

    // second in the right part
    if (second.Left > first.Left && second.Right >= first.Right)
    {
      return new Interval(first.Left, second.Left);
    }
    
    throw new InvalidOperationException( $"Interval {second} divide {first} into two intervals.");
  }
  
  // increment and decrement
  public static Interval operator ++(Interval i) => new Interval(i.Left - 1, i.Right + 1);
  public static Interval operator --(Interval i)
  {
    if (i.Length() < 2) throw new InvalidOperationException("Error! Length < 0.");
    return new Interval(i.Left + 1, i.Right - 1);
  }
  
  //compare operators 
  public static bool operator <(Interval a, Interval b) => a.Length() < b.Length();
  public static bool operator >(Interval a, Interval b) => a.Length() > b.Length();
  public static bool operator ==(Interval a, Interval b) => (a.Length() - b.Length()) < double.Epsilon;
  public static bool operator !=(Interval a, Interval b) => !(a == b);
}