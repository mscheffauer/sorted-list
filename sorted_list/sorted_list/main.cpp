// main.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>

#include "sorted_list.h"
using namespace std;

void handleResult(int v, pair<sorted_list<int>::iterator, bool> result)
{
    cout << "Insertion of value " << v << "...";

    string text = (result.second) ? ("insertion successful, iterator value: ") : ("insertion failed: following element prevented it: ");

    cout << text << *result.first << endl;
}
void handleResult(int v, pair<sorted_list<int, greater<>>::iterator, bool> resultRev)
{
    cout << "Insertion of value " << v << "...";

    string text = (resultRev.second) ? ("insertion successful, iterator value: " ) : ("insertion failed: following element prevented it: ");
    
    cout << text << *resultRev.first << endl;  

}
int main()
{
    sorted_list<int> myList;
    sorted_list<int, greater<>> myRevList;
    pair<sorted_list<int>::iterator, bool> result;
    pair<sorted_list<int,greater<>>::iterator, bool> resultRev;

  result = myList.insert(5);
  handleResult(5, result);
  result = myList.insert(5);
  handleResult(5, result);
  result = myList.insert(0);
  handleResult(0, result);
  result = myList.insert(1);
  handleResult(1, result);
  result = myList.insert(15);
  handleResult(15, result);
  result = myList.insert(4);
  handleResult(4, result);
  result = myList.insert(6);
  handleResult(6, result);
  result = myList.insert(7);
  handleResult(7, result);
  result = myList.insert(27);
  handleResult(27, result);
  result = myList.insert(30);
  handleResult(30, result);
  result = myList.insert(35);
  handleResult(35, result);
  result = myList.insert(35);
  handleResult(35, result);
  cout  << endl;

  sorted_list<int>::iterator it = myList.begin();
  cout << "Print out list with forward iterator:" << endl;
  for (it = myList.begin(); it != myList.end(); it++)
  {
      cout << *it << endl;
  }
  cout << endl;

  sorted_list<int> stlList;
  cout << "Create second list with all values doubled (std::transform) but only print them if they are greater 7 (std::remove_if):" << endl;
  ostream_iterator<int> out_it(std::cout, ", ");

  transform(remove_if(myList.begin(), myList.end(), [&](int i) { return i > 7; }), myList.end(), out_it, [&](int i) { return i *2; });
  cout << endl << endl;

  cout << "Now insert original list in another list containing of 99,100,101 (std::insert_iterator):" << endl;
  std::list<int> l{ 99,100,101 };
  std::copy(myList.begin(), myList.end(), // may be simplified with std::inserter
      std::insert_iterator<std::list<int>>(l, std::next(l.begin())));
  for (int n : l)
      std::cout << n << ' ';
  std::cout << '\n';

  cout << endl << "is item with value 15 in list?: " << myList.find(15) << endl;
  cout << endl << "delete item with value 15..."  << endl;
  myList.erase(15);
  cout << endl << "is item with value 15 in list?: " << myList.find(15) << endl;

  cout << endl << "Now erase first three items..." << endl;
  it = myList.begin();

  myList.erase(it, it+3);

  sorted_list<int>::reverse_iterator rit = myList.rbegin();
  cout << endl << "Print out list with reverse iterator:" << endl;

  for (rit = myList.rbegin(); rit != myList.rend(); rit++)
  {
      cout << *rit << endl;
  }
  cout << "get list size: " << myList.size() << endl;
  cout << "so is it empty?: " << myList.empty() << endl;

  cout << "get first item: " << myList.front() << endl;
  cout << "pop first item..." << endl;
  myList.pop_front();
  cout << "get last item: " << myList.back() << endl;
  cout << "pop last item..." << endl;
  myList.pop_back();
  cout << "Print list without first and last:" << endl;
  for (rit = myList.rbegin(); rit != myList.rend(); rit++)
  {
      cout << *rit << endl;
  }
  int myMaximum = 27;
  cout << "Now erase all elements greater or equal "<< myMaximum << "..." << endl;
  myList.erase_if([&](int i) { return i >= myMaximum; });

  cout << "Print list..." << endl;
  for (rit = myList.rbegin(); rit != myList.rend(); rit++)
  {
      cout << *rit << endl;
  }
  cout << "Now clear list..." << endl;
  myList.clear();
  cout << "so is it empty?: " << myList.empty() << endl << endl;

  cout << "Now fill in second list = from highest to lowest in forward order..." << endl;

  resultRev = myRevList.insert(5);
  handleResult(5, resultRev);
  resultRev = myRevList.insert(0);
  handleResult(0, resultRev);
  resultRev = myRevList.insert(1);
  handleResult(1, resultRev);
  resultRev = myRevList.insert(15);
  handleResult(15, resultRev);
  cout << endl;

  sorted_list<int,greater<>>::iterator Nit = myRevList.begin();

  cout << "Print out list with forward iterator:" << endl;
  for (Nit = myRevList.begin(); Nit != myRevList.end(); Nit++)
  {
      cout << *Nit << endl;
  }
 
}

