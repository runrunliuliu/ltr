// Copyright 2012 Yandex

#ifndef LTR_FEATURE_CONVERTERS_FAKE_FEATURE_CONVERTER_H_
#define LTR_FEATURE_CONVERTERS_FAKE_FEATURE_CONVERTER_H_

#include <string>

#include "ltr/data/object.h"
#include "ltr/data/feature_info.h"
#include "ltr/data/data_set.h"

#include "ltr/feature_converters/feature_converter.h"

#include "ltr/utility/boost/shared_ptr.h"
#include "ltr/utility/boost/lexical_cast.hpp"

using std::string;

namespace ltr {
/**
 * Fake feature converter. Does nothing with input object
 */
class FakeFeatureConverter : public FeatureConverter {
  ALLOW_SHARED_PTR_ONLY_CREATION(FakeFeatureConverter)
 public:
  explicit FakeFeatureConverter(const ParametersContainer& parameters) {
  }

  FakeFeatureConverter(const FeatureInfo& feature_info = FeatureInfo())
    : FeatureConverter(feature_info) {}

  virtual FeatureInfo convertFeatureInfo() const;

  virtual string generateCppCode(const string& function_name) const;

  virtual string toString() const;
 private:
  virtual void applyImpl(const Object& input,
                               Object* output) const;

  virtual string getDefaultAlias() const;
};
};
#endif  // LTR_FEATURE_CONVERTERS_FAKE_FEATURE_CONVERTER_H_
