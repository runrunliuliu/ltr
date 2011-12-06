// Copyright 2011 Yandex

#ifndef LTR_SCORERS_UTILITY_SCORER_UTILITY_H_
#define LTR_SCORERS_UTILITY_SCORER_UTILITY_H_

#include <boost/lexical_cast.hpp>

#include <string>

#include "ltr/scorers/scorer.h"
#include "ltr/data/data_set.h"

namespace ltr {
namespace utility {

template <class TElement>
void MarkDataSet(const DataSet<TElement>& elements, const Scorer& scorer);

template <class TElement>
void MarkElement(const TElement& element, const Scorer& scorer);

std::string GenerateLocalClassName(const Scorer& scorer, size_t index) {
  return "Local" + boost::lexical_cast<std::string>(index) +
      "_" + scorer.alias();
}
}
}

#endif  // LTR_SCORERS_UTILITY_SCORER_UTILITY_H_
