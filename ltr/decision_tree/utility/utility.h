// Copyright 2012 Yandex

#ifndef LTR_DECISION_TREE_UTILITY_UTILITY_H_
#define LTR_DECISION_TREE_UTILITY_UTILITY_H_

#include <vector>
#include <string>

#include "ltr/data/data_set.h"
#include "ltr/decision_tree/condition.h"

using std::string;

namespace ltr {
namespace decision_tree {

void split(DataSet<Object> data,
           vector<Condition::Ptr> conditions,
           vector<DataSet<Object> >* datas);

/** Function returns the string name of the given class
 */
template<class T> string ClassName();
}
}

#endif  // LTR_DECISION_TREE_UTILITY_UTILITY_H_
