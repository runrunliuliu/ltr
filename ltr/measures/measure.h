// Copyright 2011 Yandex

#ifndef LTR_MEASURES_MEASURE_H_
#define LTR_MEASURES_MEASURE_H_

#include <boost/shared_ptr.hpp>
#include <stdexcept>
#include <string>

#include "ltr/data/object.h"
#include "ltr/data/object_list.h"
#include "ltr/data/object_pair.h"
#include "ltr/data/data_set.h"
#include "ltr/interfaces/aliaser.h"
#include "ltr/interfaces/parameterized.h"
#include "ltr/parameters_container/parameters_container.h"

using std::string;
using std::logic_error;

namespace ltr {
/**
 * @section DESCRIPTION
 * This class allows to calculate most famous Measures on the ranking lists, pairs or single objects.
 * To learn more about these Measures visit http://romip.ru/romip2010/20_appendix_a_metrics.pdf (Russian) or
 * http://en.wikipedia.org/wiki/Learning_to_rank#Evaluation_measures (English)
 */
template <class TElement>
class Measure : public Aliaser, public Parameterized {
  public:
  typedef boost::shared_ptr<Measure> Ptr;
  typedef boost::shared_ptr<Measure> BasePtr;

  explicit Measure(const string& alias) : Aliaser(alias) {}

  /**
   * Value of measure(quality of algorithm)
   * @param element - element(single object, pair or list) for counting measure on
   */
  double operator()(const TElement& element) const;

  /**
   * Gets average measure value of all elements (as if all elements have equal weights)
   * @param set - input dataset of objects, to count average measure on
   */
  double average(const DataSet<TElement>& set) const;

  /**
   * Gets average measure value of all elements (using for counting average weights from dataset)
   * @param set - input dataset of objects, to count average measure on
   */
  double weightedAverage(const DataSet<TElement>& set) const;
  /**
   * Returns if expected better value of measure is really better than expected worse one.
   * There are two types of measures: when bigger measure is better (e.g. accuracy)
   * and when smaller measure is better (e.g. abs error)
   */
  virtual bool better(double expected_better, double expected_worse) const = 0;

  private:
  /**
   * Implementation. Returns value of measure(quality of algorithm)
   * @param element - element(single object, pair or list) for counting measure on
   */
  virtual double get_measure(const TElement& element) const = 0;
};

/**
 * Type of measure when smaller result is better (e.g. abs error)
 */
template <class TElement>
class LessIsBetterMeasure : public Measure<TElement> {
 public:
  explicit LessIsBetterMeasure(const string& alias)
    : Measure<TElement>(alias) {}

  bool better(double expected_better, double expected_worse) const {
    return expected_better < expected_worse;
  }
};
/**
 * Type of measure when bigger result is better (e.g. accuracy)
 */
template <class TElement>
class MoreIsBetterMeasure : public Measure<TElement> {
 public:
  explicit MoreIsBetterMeasure(const string& alias)
    : Measure<TElement>(alias) {}

  bool better(double expected_better, double expected_worse) const {
    return expected_better > expected_worse;
  }
};

typedef Measure<Object> PointwiseMeasure;
typedef Measure<ObjectPair> PairwiseMeasure;
typedef Measure<ObjectList> ListwiseMeasure;

template< class TElement>
double Measure<TElement>::operator()(const TElement& element) const {
  if (element.size() == 0) {
    throw logic_error(alias() + " gained empty list");
  }
  double measure = get_measure(element);
  return measure;
};

template< class TElement>
double Measure<TElement>::average(const DataSet<TElement>& set) const {
  if (set.size() == 0) {
    throw logic_error(alias() + " gained empty set");
  }

  double sum = 0.0;
  int query_proceed = 0;

  for (size_t i = 0; i < set.size(); ++i) {
    query_proceed += 1;
    double val;
    val = this->operator()(set[i]);
    sum += val;
  }

  sum /= query_proceed;
  return sum;
}

template< class TElement>
double Measure<TElement>::weightedAverage(
    const DataSet<TElement>& set) const {
  if (set.size() == 0) {
    throw logic_error(alias() + " gained empty set");
  }

  double sum = 0.0;
  double weights = 0.0;

  for (size_t i = 0; i < set.size(); ++i) {
    double w = set.getWeight(i);
    double val;
    val = w * this->operator()(set[i]);
    weights += w;
    sum += val;
  }
  return sum / weights;
}
};

#endif  // LTR_MEASURES_MEASURE_H_
