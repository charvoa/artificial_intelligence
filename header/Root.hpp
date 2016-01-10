//
// main.cpp for  in /home/nicolaschr/Work
//
// Made by Nicolas Charvoz
// Login   <nicolaschr@epitech.net>
//
// Started on  Fri Dec 25 20:14:14 2015 Nicolas Charvoz
// Last update Sun Jan 10 14:23:16 2016 Nicolas Charvoz
//

#include <iostream>
#include <string>
#include <map>
#include <list>
#include <sstream>
#include <random>
#include <iterator>

class Root {

  typedef void (Root::*Func)(void*);

private:

  std::string _name;
  std::string _nameOfUser;
  std::map<std::string, Func> _funcMap;
  bool _firstLaunch;
  std::vector<std::string> _responses;

public:

  Root(const std::string &name_) {
    _firstLaunch = true;
    _name = name_;
    _funcMap.insert(std::make_pair("Hello", &Root::helloFunc));
    _funcMap.insert(std::make_pair("ChangeMyName", &Root::changeMyName));
    _funcMap.insert(std::make_pair("FirstLaunch", &Root::firstLaunch));
    _funcMap.insert(std::make_pair("Calc", &Root::makeCalc));
    _funcMap.insert(std::make_pair("List", &Root::displayList));
    _funcMap.insert(std::make_pair("Goodbye", &Root::goodbyeFunc));
    try
      {
	this->initBrain();
      } catch (const std::exception) {
      std::cout << "Cannot initialize brain ... \n Will quit in 3\n2\n1..." << std::endl;
    }
    if (_firstLaunch)
      {
	Func fp = _funcMap["FirstLaunch"];
	(this->*fp)(NULL);
      }
  }

  ~Root() { std::cout << "You've destroyed me .. " << std::endl; }

  void initBrain() {
    _responses.push_back("Hello there ! ");
    _responses.push_back("Hi !");
  }

  template<typename Iter, typename RandomGenerator>
  Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
  }

  template<typename Iter>
  Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
  }

  void firstLaunch(void *data) {
    (void) data;
    std::string line;

    std::string helloStr = *select_randomly(_responses.begin(), _responses.end());
    std::cout << helloStr <<"My name is " << _name
	      << ". I am here to serve you. First of all, do you like my name ?"
	      << std::endl;
    std::getline(std::cin, line);
    this->analyze(line, _firstLaunch);
  }

  bool checkDumbName(const std::string &nameToCheck)
  {
    std::list<std::string> dumbnameList;

    dumbnameList.push_back("Dick");
    dumbnameList.push_back("Penis");
    dumbnameList.push_back("Fuck");
    for (std::list<std::string>::iterator it = dumbnameList.begin();
	 it != dumbnameList.end();
	 ++it) {
      if (nameToCheck == (*it))
	return true;
    }
    return false;
  }

  void goodbyeFunc(void *data)
  {
    (void) data;
    std::cout << "Goodbye " << _nameOfUser << std::endl;
    exit(0);
  }

  void helloFunc(void *data)
  {
    (void) data;
    std::cout << "Hi " << _nameOfUser << std::endl;
  }


  void displayList(void *data)
  {
    (void) data;
    std::cout << "Here is the list of the things I can do .. : "
	      << "(Examples after '>>')" << std::endl;
    std::cout << "Say hello >> 'Hello'" << std::endl;
    std::cout << "Make calcul >> 'What's 2 times 4 ?'" << std::endl;

  }

  std::pair<std::string, int> getPairForCalcul(int first, int sec,
					       const std::string &s)
  {
    std::pair<std::string, int> final;

    if (s == "times")
      final = std::make_pair(" x ", first*sec);
    else if (s == "plus")
      final = std::make_pair(" + ", first+sec);
    else if (s == "minus")
      final = std::make_pair(" - ", first-sec);

    return final;
  }

  void makeCalc(void *data)
  {
    std::string *tmp = static_cast<std::string*>(data);
    std::string sData = *tmp;
    delete tmp;
    std::stringstream ss(sData);
    if (sData.find("times") != std::string::npos
	|| sData.find("plus") != std::string::npos
	|| sData.find("minus") != std::string::npos) {
      std::string avoid;
      int first, sec;

      ss >> avoid >> first >> avoid >> sec;
      std::pair<std::string, int> calcPair = this->getPairForCalcul(first, sec,
								    avoid);
      std::cout << first << calcPair.first << sec << " = "
		<< calcPair.second << std::endl;
    }
    else if (sData.find("divided by") != std::string::npos) {
      std::string avoid;
      int first, sec;

      ss >> avoid >> first >> avoid >> avoid >> sec;
      std::cout << first << " / " << sec << " = " << first/sec << std::endl;
    }
  }

  void nameFunc(void *data)
  {
    (void) data;
    std::getline(std::cin, _nameOfUser);
    std::cout << "Nice to meet you " << _nameOfUser << " !"<< std::endl;
  }

  void changeMyName(void *data)
  {
    (void) data;
    std::cout << "You don't like my name ? Ok, give me another one ..." << std::endl;
    std::string newName;
    std::getline(std::cin, newName);
    if (!(this->checkDumbName(newName))) {
      _name = newName;
      std::cout << _name << " ? Yeah ! I like my new name ! What's yours ?"
		<< std::endl;
    }
    else
      std::cout << newName << " ? Ehm .. Let's keep my old name ! What's yours ?"
		<< std::endl;
    this->nameFunc(NULL);
  }

  void analyze(const std::string &phrase, bool firstLaunch_)
  {
    if (firstLaunch_) {
      if (phrase.find("No") != std::string::npos
	  || phrase.find("no") != std::string::npos) {
	Func fp = _funcMap["ChangeMyName"];
	(this->*fp)(NULL);
      }
      else {
	std::cout << "Oh great ! What's your name now ?" << std::endl;
	this->nameFunc(NULL);
      }
    }
    if (phrase.find("Hello") != std::string::npos
	|| phrase.find("hello") != std::string::npos) {
      Func fp = _funcMap["Hello"];
      (this->*fp)(NULL);
    }
    else if (phrase.find("list") != std::string::npos
	|| phrase.find("function") != std::string::npos) {
      Func fp = _funcMap["List"];
      (this->*fp)(NULL);
    }
    else if (phrase.find("goodbye") != std::string::npos
	|| phrase.find("Goodbye") != std::string::npos) {
      Func fp = _funcMap["Goodbye"];
      (this->*fp)(NULL);
    }
    else if (phrase.find("What's") != std::string::npos) {
      if (phrase.find("times") != std::string::npos
	  || phrase.find("divided by") != std::string::npos
	  || phrase.find("plus") != std::string::npos
	  || phrase.find("minus") != std::string::npos) {
	Func fp = _funcMap["Calc"];
	void *vp = static_cast<void*>(new std::string(phrase));
	(this->*fp)(vp);
      }
    }
  }

};
