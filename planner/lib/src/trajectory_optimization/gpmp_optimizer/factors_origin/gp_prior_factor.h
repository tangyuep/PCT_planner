#pragma once

#include "gtsam/nonlinear/NonlinearFactor.h"
#include "trajectory_optimization/gpmp_optimizer/models/wnoa_origin.hpp"

class GPPriorFactorOrigin
    : public gtsam::NoiseModelFactor2<gtsam::Vector4, gtsam::Vector4> {
 public:
  GPPriorFactorOrigin(gtsam::Key key1, gtsam::Key key2, const double delta,
                      const double Qc)
      : NoiseModelFactor2(gtsam::noiseModel::Gaussian::Covariance(
                              calcQ(Qc * Eigen::Matrix2d::Identity(), delta)),
                          key1, key2),
        delta_(delta),
        phi_(calcPhi(2, delta)){};
  ~GPPriorFactorOrigin() = default;

  gtsam::Vector evaluateError(
      const gtsam::Vector4& x1, const gtsam::Vector4& x2,
      boost::optional<gtsam::Matrix&> H1 = boost::none,
      boost::optional<gtsam::Matrix&> H2 = boost::none) const override;

  void verbose() {}

 private:
  double delta_ = 0.0;
  gtsam::Matrix44 phi_;
};