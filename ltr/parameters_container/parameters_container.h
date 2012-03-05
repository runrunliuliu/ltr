// Copyright 2011 Yandex

#ifndef LTR_PARAMETERS_CONTAINER_PARAMETERS_CONTAINER_H_
#define LTR_PARAMETERS_CONTAINER_PARAMETERS_CONTAINER_H_

#include <boost/variant.hpp>

#include <map>
#include <string>
#include <vector>
#include <stdexcept>

// I don't need it. It is for Hook!!!
#include <algorithm>

using std::string;
using std::vector;
using std::map;

namespace ltr {
  typedef vector<int> List;
  /**
   * ParametersContainer holds parameters of types int, double and bool
   * with their names
   */
  class ParametersContainer {
  public:
    typedef map<string,
                boost::variant<int, double, bool, List> > TGroup;

    typedef map<string, TGroup> TMap;

    ParametersContainer() {
      params[""] = TGroup();
    }
    explicit ParametersContainer(TMap parameters) : params(parameters) {}

    void setDouble(const string& name, double value, const string& group="");
    void setInt(const string& name, int value, const string& group="");
    void setBool(const string& name, bool value, const string& group="");
    void setList(const string& name, const List& value, const string& group="");

    template<class T>
    bool has(const string& name, const string& group="") const;

    template<class T> T get(const string& name, const string& group="") const;
    double getDouble(const string& name, const string& group="") const;
    int getInt(const string& name, const string& group="") const;
    bool getBool(const string& name, const string& group="") const;
    List getList(const string& name, const string& group="") const;

    string toString() const;

    void copy(const ParametersContainer& parameters);
    ParametersContainer getGroup(const string& group) const;

    void clear();

  protected:
    TMap params;
  };

  // Template realization
  template <class T>
  bool ParametersContainer::has(const string& name,
                                const string& group) const {
    if (params.find(group) == params.end())
      return 0;
    const TGroup& group_ = params.find(group)->second;

    if (group_.find(name) == group_.end())
      return 0;
    try {
      boost::get<T>(group_.find(name)->second);
      return 1;
    } catch(...) {
      return 0;
    }
  }

  template <class T>
  T ParametersContainer::get(const string& name,
                             const string& group) const {
    if (params.find(group) == params.end()) {
      throw std::logic_error("no such group: " + group);
    }
    const TGroup& group_ = params.find(group)->second;
    if (group_.find(name) == group_.end()) {
      throw std::logic_error("no such parameter: " + name);
    }
    try {
      return boost::get<T>(group_.find(name)->second);
    } catch(...) {
      throw std::logic_error("parameter " + name + " has another type");
    }
  }
}
#endif  // LTR_PARAMETERS_CONTAINER_PARAMETERS_CONTAINER_H_
