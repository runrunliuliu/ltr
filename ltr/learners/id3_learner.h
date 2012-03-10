// Copyright 2011 Yandex

#ifndef LTR_LEARNERS_ID3_LEARNER_H_
#define LTR_LEARNERS_ID3_LEARNER_H_

#include "ltr/learners/decision_tree_learner.h"
#include "ltr/learners/utility/id3_splitter.h"
#include "ltr/learners/utility/sqr_error_quality.h"

using ltr::decision_tree::DecisionTreeLearner;
using ltr::decision_tree::SqrErrorQuality;
using ltr::decision_tree::ID3_Splitter;

using ltr::decision_tree::ConditionsLearner;
using ltr::decision_tree::SplittingQuality;

namespace ltr {
class ID3_Learner : public DecisionTreeLearner {
  public:
    explicit ID3_Learner(
      const ParametersContainer& parameters = ParametersContainer())
      : DecisionTreeLearner(parameters.getGroup("")) {
      this->setConditionsLearner(
        ConditionsLearner::Ptr(
          new ID3_Splitter(
            parameters.getGroup("conditions learner"))));
      this->setSplittingQuality(
        SplittingQuality::Ptr(
          new SqrErrorQuality(
            parameters.getGroup("splitting quality"))));
      copyParameters(parameters);
    }
};
}

#endif  // LTR_LEARNERS_ID3_LEARNER_H_
