#ifndef TESTTYPE_HH
#define TESTTYPE_HH

#include <cstdlib>
#include <ctime>

#include "erbi.hh"

struct PositionedHanzi
{
  int x;
  int y;
  HanziString hs;
  std::string sol;
};
typedef std::vector<PositionedHanzi> PHVector;
typedef PHVector::const_iterator PHVectorCIterator;

class TestType
{
public:
  TestType() : last_sol("    "), code("") { next = 0; srandom(time(NULL)); }
  virtual ~TestType() { }
  bool noNext() const { return (next >= hanzi.size()); }
  virtual void generateTest() = 0;
  void display() const;
  void displayLastSolution();
  void displaySolution();
  bool handleKey(char c, int &num, int &ok);
protected:
  size_t next;
  std::string last_sol, code;
  PHVector hanzi;
};

class TestNKey : public TestType
{
public:
  TestNKey(int nkey);
  void generateTest();
private:
  int n;
};

class TestUKey: public TestType
{
public:
  TestUKey() { }
  void generateTest();
};

class TestAll: public TestType
{
public:
  TestAll() { }
  void generateTest();
};

#endif // TESTTYPE_HH
