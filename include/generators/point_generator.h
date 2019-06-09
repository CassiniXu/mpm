#ifndef MPM_POINT_GENERATOR_H_
#define MPM_POINT_GENERATOR_H_

#include "mesh.h"

// JSON
using Json = nlohmann::json;

namespace mpm {
//! PointGenerator class
//! \brief Base class that defines generation of material points
//! \tparam Tdim Dimension
template <unsigned Tdim>
class PointGenerator {
 public:
  //! Constructor with mesh pointer and generator properties
  PointGenerator(const std::shared_ptr<mpm::Mesh<Tdim>>& mesh,
                 const std::shared_ptr<mpm::IO>& io, const Json& generator)
      : mesh_{mesh}, io_{io}, generator_{generator} {}

  //! Generate material points
  virtual std::vector<Eigen::Matrix<double, Tdim, 1>> generate_points() = 0;

 protected:
  //! Mesh
  std::shared_ptr<mpm::Mesh<Tdim>> mesh_;
  //! IO
  std::shared_ptr<mpm::IO> io_;
  //! JSON generator properties
  Json generator_;

};  // PointGenerator class
}  // namespace mpm
#endif  // MPM_POINTGENERATOR_H_
