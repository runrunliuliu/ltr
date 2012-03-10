// Copyright 2011 Yandex

#include "ltr/scorers/scorer.h"

namespace ltr {

double Scorer::score(const ltr::Object& obj) const {
  Object sourceObject = obj.deepCopy();
  Object convertedObject;
  for (size_t featureConverterIdx = 0;
      featureConverterIdx < feature_converters_.size();
      ++featureConverterIdx) {
    (*feature_converters_[featureConverterIdx]).apply(sourceObject,
        &convertedObject);
    sourceObject = convertedObject;
  }
  return scoreImpl(sourceObject);
}
}
