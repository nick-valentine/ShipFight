#ifndef PAIR_HPP
#define PAIR_HPP

template<typename T1, typename T2>
class Pair
{
public:
  Pair();
  Pair(const Pair &other);
  ~Pair();
  Pair(T1 a, T2 b);

  Pair<T1,T2> &operator=(const Pair &other);
  bool operator==(const Pair &other);

  T1 &get_first();
  T2 &get_second();

  void set_first(T1 a);
  void set_second(T2 b);

private:
  T1 first;
  T2 second;
};

template<typename T1, typename T2>
Pair<T1,T2>::Pair()
{

}

template<typename T1, typename T2>
Pair<T1,T2>::Pair(const Pair<T1,T2> &other)
{
  this->first = other.first;
  this->second = other.second;
}

template<typename T1, typename T2>
Pair<T1,T2>::~Pair()
{

}

template<typename T1, typename T2>
Pair<T1,T2>::Pair(T1 a, T2 b)
{
  this->first = a;
  this->second = b;
}

template<typename T1, typename T2>
Pair<T1,T2> &Pair<T1,T2>::operator=(const Pair<T1,T2> &other)
{
  this->first = other.first;
  this->second = other.second;

  return *this;
}

template<typename T1, typename T2>
bool Pair<T1,T2>::operator==(const Pair<T1,T2> &other)
{
  return (this->first == other.first && this->second == other.second);
}

template<typename T1, typename T2>
T1 &Pair<T1,T2>::get_first()
{
  return this->first;
}

template<typename T1, typename T2>
T2 &Pair<T1,T2>::get_second()
{
  return this->second;
}

template<typename T1, typename T2>
void Pair<T1,T2>::set_first(T1 a)
{
  this->first = a;
}

template<typename T1, typename T2>
void Pair<T1,T2>::set_second(T2 b)
{
  this->second = b;
}

#endif //PAIR_HPP
