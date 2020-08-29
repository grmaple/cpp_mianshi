## 复习complex类的实现过程

```cpp
//complex.h
#inndef __COMPLEX__
#define __COMPLEX__
#include <cmath>
//前置声明
class complex;
complex& __doapl (complex* ths, const complex& r);

//类声明
class complex 
{
public:
    complex (double r = 0, double i =0): re (r), im (i) {}
    complex& operator += (const complex&);
    double real () const {return re;}
    double imag () const {return im;}
private:
    double re, im;
    friend complex& __doapl (complex*, const complex&);    
};
//类定义
//+=
inline complex& 
__doapl (complex* ths, const complex& r){
    ths->re += r.re;
    ths->im += r.im;
    return *ths;
}
inline complex& 
complex::operator += (const complex& r){
    return __doapl(this, r);
}

inline double
imag(const complex& x){
    return x.imag();
}
inline double
real(const complex& x){
    return x.real();
}
//+
inline complex 
operator + (const complex& x, const complex& y){
    return complex(real(x) + real(y), 
                   imag(x) + imag(y));
}
inline complex 
operator + (const complex& x, double y){
    return complex(real(x) + y, imag(x));
}
inline complex 
operator + (double x, const complex& y) {
    return complex(x + real(y), imag(y));
}
//+ -
inline complex 
operator + (const complex& x){
    return x;
}
inline complex 
operator - (const complex& x){
    return complex(-real(x), -imag(x));
}
//==
inline bool 
operator == (const complex& x, const complex& y){
    return real(x) == real(y) && imag(x) == imag(y);
}
inline bool
operator == (const complex& x, double y){
    return real(x) == y && imag(x) == 0;
}
inline bool 
operator == (double x, const complex& y) {
    return x == real(y) && imag(y) == 0;
}
//!=
inline bool 
operator != (const complex& x, const complex& y){
    return real(x) != real(y) || imag(x) != imag(y);
}
inline bool
operator != (const complex& x, double y){
    return real(x) != y || imag(x) != 0;
}
inline bool 
operator != (double x, const complex& y) {
    return x != real(y) || imag(y) != 0;
}
//共轭
inline complex 
conj (const complex& x){
    return complex(real(x), -imag(x));
}
#endif
```

```cpp
//complex-test.cpp
#include <iostream>
#include "complex.h"
using namespace std;
//<<
ostream &
operator << (ostream& os, const complex& x){
    return os << '(' << real(x) << ',' << imag(x) <<')';
}

int main() {
    complex c1(2,1);
    complex c2;
    c2 += c1;
    cout << c2;//(2,1)
    cout << real(c1);//2
    cout << imag(c1);//1
    cout << +c1;//(2,1)
    cout << -c1;//(-2,-1)
    cout << (c1 == c2);//1
    cout << (c1 != 2);//1
    cout << conj(c1);//(2,-1)
    cout << c1 << endl;//(2,1)
    return 0;
}
```







```cpp
#ifndef __MYCOMPLEX__
#define __MYCOMPLEX__

class complex; 
complex&
  __doapl (complex* ths, const complex& r);
complex&
  __doami (complex* ths, const complex& r);
complex&
  __doaml (complex* ths, const complex& r);


class complex
{
public:
  complex (double r = 0, double i = 0): re (r), im (i) { }
  complex& operator += (const complex&);
  complex& operator -= (const complex&);
  complex& operator *= (const complex&);
  double real () const { return re; }
  double imag () const { return im; }
private:
  double re, im;

  friend complex& __doapl (complex *, const complex&);
  friend complex& __doami (complex *, const complex&);
  friend complex& __doaml (complex *, const complex&);
};


inline complex&
__doapl (complex* ths, const complex& r)
{
  ths->re += r.re;
  ths->im += r.im;
  return *ths;
}
 
inline complex&
complex::operator += (const complex& r)
{
  return __doapl (this, r);
}

inline complex&
__doami (complex* ths, const complex& r)
{
  ths->re -= r.re;
  ths->im -= r.im;
  return *ths;
}
 
inline complex&
complex::operator -= (const complex& r)
{
  return __doami (this, r);
}
 
inline complex&
__doaml (complex* ths, const complex& r)
{
  double f = ths->re * r.re - ths->im * r.im;
  ths->im = ths->re * r.im + ths->im * r.re;
  ths->re = f;
  return *ths;
}

inline complex&
complex::operator *= (const complex& r)
{
  return __doaml (this, r);
}

inline double
imag (const complex& x)
{
  return x.imag ();
}

inline double
real (const complex& x)
{
  return x.real ();
}

inline complex
operator + (const complex& x, const complex& y)
{
  return complex (real (x) + real (y), imag (x) + imag (y));
}

inline complex
operator + (const complex& x, double y)
{
  return complex (real (x) + y, imag (x));
}

inline complex
operator + (double x, const complex& y)
{
  return complex (x + real (y), imag (y));
}

inline complex
operator - (const complex& x, const complex& y)
{
  return complex (real (x) - real (y), imag (x) - imag (y));
}

inline complex
operator - (const complex& x, double y)
{
  return complex (real (x) - y, imag (x));
}

inline complex
operator - (double x, const complex& y)
{
  return complex (x - real (y), - imag (y));
}

inline complex
operator * (const complex& x, const complex& y)
{
  return complex (real (x) * real (y) - imag (x) * imag (y),
			   real (x) * imag (y) + imag (x) * real (y));
}

inline complex
operator * (const complex& x, double y)
{
  return complex (real (x) * y, imag (x) * y);
}

inline complex
operator * (double x, const complex& y)
{
  return complex (x * real (y), x * imag (y));
}

complex
operator / (const complex& x, double y)
{
  return complex (real (x) / y, imag (x) / y);
}

inline complex
operator + (const complex& x)
{
  return x;
}

inline complex
operator - (const complex& x)
{
  return complex (-real (x), -imag (x));
}

inline bool
operator == (const complex& x, const complex& y)
{
  return real (x) == real (y) && imag (x) == imag (y);
}

inline bool
operator == (const complex& x, double y)
{
  return real (x) == y && imag (x) == 0;
}

inline bool
operator == (double x, const complex& y)
{
  return x == real (y) && imag (y) == 0;
}

inline bool
operator != (const complex& x, const complex& y)
{
  return real (x) != real (y) || imag (x) != imag (y);
}

inline bool
operator != (const complex& x, double y)
{
  return real (x) != y || imag (x) != 0;
}

inline bool
operator != (double x, const complex& y)
{
  return x != real (y) || imag (y) != 0;
}

#include <cmath>

inline complex
polar (double r, double t)
{
  return complex (r * cos (t), r * sin (t));
}

inline complex
conj (const complex& x) 
{
  return complex (real (x), -imag (x));
}

inline double
norm (const complex& x)
{
  return real (x) * real (x) + imag (x) * imag (x);
}

#endif   //__MYCOMPLEX__
```

```cpp
#include <iostream>
#include "complex.h"

using namespace std;

ostream&
operator << (ostream& os, const complex& x)
{
  return os << '(' << real (x) << ',' << imag (x) << ')';
}

int main()
{
  complex c1(2, 1);
  complex c2(4, 0);

  cout << c1 << endl;
  cout << c2 << endl;
  
  cout << c1+c2 << endl;
  cout << c1-c2 << endl;
  cout << c1*c2 << endl;
  cout << c1 / 2 << endl;
  
  cout << conj(c1) << endl;
  cout << norm(c1) << endl;
  cout << polar(10,4) << endl;
  
  cout << (c1 += c2) << endl;
  
  cout << (c1 == c2) << endl;
  cout << (c1 != c2) << endl;
  cout << +c2 << endl;
  cout << -c2 << endl;
  
  cout << (c2 - 2) << endl;
  cout << (5 + c2) << endl;
  
  return 0;
}
```

