#include <algorithm>
#include <iostream>
#include <map>

#include "testtype.hh"

extern std::map<std::string, std::vector<HanziString> > erbi;
extern StringVector vkey[4], ukey;

void TestType::display() const
{
  putRomanString(12, 62, "           ");
  putRomanString(12, 182, "           ");
  putRomanString(12, 302, "           ");
  for(PHVectorCIterator i = hanzi.begin(); i != hanzi.end(); ++i)
    putHanziString(i->x, i->y, i->hs, 4);
  putRomanString(12, 122, "           ");
  putRomanString(12, 242, "           ");
  putRomanString(12, 362, "           ");
}

void TestType::displayLastSolution()
{
  putString(236, 2, "上一个", 2);
  putRomanString(404, 2, last_sol, 2);
}

void TestType::displaySolution()
{
  putString(236, 2, "下一个", 2);
  putRomanString(404, 2, hanzi[next].sol, 2);
}

bool TestType::handleKey(char c, int &num, int &ok)
{
  if(!((c >= 'a' && c <= 'z') || c == '.' || c == ',' || c == '/' || c == ';'))
    return false;

  code += c;

  if(code.length() < hanzi[next].sol.length()) {
    putRomanString(12, 2, code, 1);
    return false;
  }

  std::vector<HanziString>::const_iterator i = erbi[code].begin();
  bool solved = false;
  while(i != erbi[code].end() && !solved)
    if((*i++)[0] == hanzi[next].hs[0])
      solved = true;

  if(solved) {
    ++ok;
    putCharacter(hanzi[next].x, hanzi[next].y + 60, hanzi[next].hs[0], 2);
  } else {
    bool one_hanzi = false;
    std::vector<HanziString>::const_iterator i;
    if(erbi.count(code) > 0) {
      for(i = erbi[code].begin(); i != erbi[code].end() && !one_hanzi; ++i)
	if(i->size() == 1)
	  one_hanzi = true;
    }
    if(one_hanzi)
      putCharacter(hanzi[next].x, hanzi[next].y + 60, (*(i-1))[0], 1);
    else
      putString(hanzi[next].x, hanzi[next].y + 60, "×", 1);
  }

  last_sol = hanzi[next].sol;
  ++num; ++next; code = "";
  putRomanString(12, 2, "           ");
  return true;
}

TestNKey::TestNKey(int nkey) : TestType(), n(nkey)
{
}

void TestNKey::generateTest()
{
  hanzi.clear();
  for(int i = 0; i < 33; ++i) {
    PositionedHanzi ph;
    ph.x = 12 + (i % 11) * 56;
    ph.y = 62 + (i / 11) * 120;
    ph.sol = vkey[n-1][random() % vkey[n-1].size()];
    std::vector<HanziString> tmp = erbi[ph.sol], tmp2;
    for(size_t i = 0; i < tmp.size(); ++i)
      if(tmp[i].size() == 1)
	tmp2.push_back(tmp[i]);
    ph.hs = tmp2[random() % tmp2.size()];
    hanzi.push_back(ph);
  }
  next = 0;
}

void TestUKey::generateTest()
{
  hanzi.clear();
  for(int i = 0; i < 33; ++i) {
    PositionedHanzi ph;
    ph.x = 12 + (i % 11) * 56;
    ph.y = 62 + (i / 11) * 120;
    ph.sol = ukey[random() % ukey.size()];
    std::vector<HanziString> tmp = erbi[ph.sol], tmp2;
    for(size_t i = 0; i < tmp.size(); ++i)
      if(tmp[i].size() == 1)
	tmp2.push_back(tmp[i]);
    ph.hs = tmp2[random() % tmp2.size()];
    hanzi.push_back(ph);
  }
  next = 0;
}

void TestAll::generateTest()
{
  hanzi.clear();
  for(int i = 0; i < 33; ++i) {
    PositionedHanzi ph;
    ph.x = 12 + (i % 11) * 56;
    ph.y = 62 + (i / 11) * 120;
    int type = random() % 5;
    if (type == 4)
      ph.sol = ukey[random() % ukey.size()];
    else
      ph.sol = vkey[type][random() % vkey[type].size()];
    std::vector<HanziString> tmp = erbi[ph.sol], tmp2;
    for(size_t i = 0; i < tmp.size(); ++i)
      if(tmp[i].size() == 1)
	tmp2.push_back(tmp[i]);
    ph.hs = tmp2[random() % tmp2.size()];
    hanzi.push_back(ph);
  }
  next = 0;
}
