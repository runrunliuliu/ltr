// Copyright 2013 Yandex

#ifndef LTR_OPTIMIZATION_SETS_SET_H_
#define LTR_OPTIMIZATION_SETS_SET_H_

#include <string>
#include "ltr/utility/macros.h"
#include "ltr/utility/boost/shared_ptr.h"
#include "ltr/interfaces/aliaser.h"
#include "ltr/optimization/functions/function.h"

namespace optimization {
/** 
 * \brief Interface class for sets in \f$\mathbb{R}^n\f$.
 */
class Set : public ltr::Aliaser {
 public:
  typedef ltr::utility::shared_ptr<Set> Ptr;

  explicit Set(int dimension);
  virtual ~Set();

  /** 
   * Checks, whether given point is inside this set.
   */
  virtual bool isInside(const Point& point) const = 0;
  /** 
   * Projects given point on this set.
   */
  virtual void computeProjection(const Point& point,
                                 Point* projection) const = 0;
  /**
   * Give a cubic boundaries which contain this set.
   */
  virtual void getBoundaries(Point* top, Point* bottom) const = 0;
  /**
   * Get arbitrary point in given set.
   */
  virtual void sampleRandomPointInside(Point* random_point) const;
  /**
   * Get nmber of dimensions of this set.
   */
  GET(int, dimension);

  virtual string getDefaultAlias() const { return "Set"; }
 protected:
  /**
   * Get random point in boundaries of this set.
   */
  void getRandomPoint(Point* random_point) const;
 private:
  /**
   * Dimension of space which contains set.
   */
  int dimension_;
};
}

#endif  // LTR_OPTIMIZATION_SETS_SET_H_

