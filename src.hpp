// Only allowed header
#include <vector>

// Do not add using namespace std;

template <typename T>
class Expect {
 private:
  T value;
  bool ok;
  bool negate;

  template <typename Predicate>
  Expect& apply(Predicate pred) {
    bool res = pred();
    if (negate) res = !res;
    ok = ok && res;
    // reset negate for subsequent calls
    negate = false;
    return *this;
  }

 public:
  explicit Expect(const T& v) : value(v), ok(true), negate(false) {}

  // logical negation flag for subsequent conditions
  Expect& Not() {
    negate = !negate;
    return *this;
  }

  // Equality x == y
  template <typename U>
  Expect& toBe(const U& y) {
    return apply([&]() { return value == y; });
  }

  // Membership: y is std::vector<TLike>
  template <typename U>
  Expect& toBeOneOf(const std::vector<U>& vec) {
    return apply([&]() {
      for (const auto& z : vec) {
        if (value == z) return true;
      }
      return false;
    });
  }

  // Comparators
  template <typename U>
  Expect& le(const U& y) {
    return apply([&]() { return !(y < value); }); // value <= y
  }

  template <typename U>
  Expect& ge(const U& y) {
    return apply([&]() { return !(value < y); }); // value >= y
  }

  template <typename U>
  Expect& lt(const U& y) {
    return apply([&]() { return value < y; });
  }

  template <typename U>
  Expect& gt(const U& y) {
    return apply([&]() { return y < value; }); // value > y
  }

  // Conversion to bool to finalize the chain
  operator bool() const { return ok; }
};

template <typename T>
Expect<T> expect(const T& v) { return Expect<T>(v); }

