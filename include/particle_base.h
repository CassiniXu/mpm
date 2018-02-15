#ifndef MPM_PARTICLEBASE_H_
#define MPM_PARTICLEBASE_H_

#include <array>
#include <iostream>
#include <limits>
#include <memory>
#include <vector>

#include "cell.h"
#include "serialize.h"

namespace mpm {

//! Global index type for the particleBase
using Index = unsigned long long;

//! ParticleBase class
//! \brief Base class that stores the information about particleBases
//! \details ParticleBase class: id_ and coordinates.
//! \tparam Tdim Dimension
template <unsigned Tdim>
class ParticleBase {
 public:
  //! Define a vector of size dimension
  using VectorDim = Eigen::Matrix<double, Tdim, 1>;

  ParticleBase(boost::archive::text_iarchive& archive) {
    std::cout << "Archive base: " << &archive << "\n";
  }

  //! Constructor with id and coordinates
  ParticleBase(Index id, const VectorDim& coord);

  //! Constructor with id, coordinates and status
  ParticleBase(Index id, const VectorDim& coord, bool status);

  //! Destructor
  virtual ~ParticleBase(){};

  //! Delete copy constructor
  ParticleBase(const ParticleBase<Tdim>&) = delete;

  //! Delete assignement operator
  ParticleBase& operator=(const ParticleBase<Tdim>&) = delete;

  //! Return id of the particleBase
  Index id() const { return id_; }

  //! Assign coordinates
  //! \param[in] coord Assign coord as coordinates of the particleBase
  void coordinates(const VectorDim& coord) { coordinates_ = coord; }

  //! Return coordinates
  //! \retval coordinates_ return coordinates of the particleBase
  VectorDim coordinates() const { return coordinates_; }

  //! Assign cell
  virtual bool assign_cell(const std::shared_ptr<Cell<Tdim>>& cellptr) = 0;

  //! Return cell id
  virtual Index cell_id() const = 0;

  //! Assign status
  void assign_status(bool status) { status_ = status; }

  //! Status
  bool status() const { return status_; }

  //! Initialise properties
  virtual void initialise() = 0;

  //! Assign mass
  virtual void assign_mass(unsigned nphase, double mass) = 0;

  //! Return mass
  virtual double mass(unsigned nphase) const = 0;

  //! Assign stress
  virtual void assign_stress(unsigned nphase,
                             const Eigen::VectorXd& stress) = 0;

  //! Return stress
  virtual Eigen::VectorXd stress(unsigned nphase) const = 0;

  //! Assign velocity
  virtual void assign_velocity(unsigned nphase,
                               const Eigen::VectorXd& velocity) = 0;

  //! Return velocity
  virtual Eigen::VectorXd velocity(unsigned nphase) const = 0;

  //! Assign momentum
  virtual void assign_momentum(unsigned nphase,
                               const Eigen::VectorXd& momentum) = 0;

  //! Return momentum
  virtual Eigen::VectorXd momentum(unsigned nphase) const = 0;

  //! Assign acceleration
  virtual void assign_acceleration(unsigned nphase,
                                   const Eigen::VectorXd& acceleration) = 0;

  //! Return acceleration
  virtual Eigen::VectorXd acceleration(unsigned nphase) const = 0;

 protected:
  //! particleBase id
  Index id_{std::numeric_limits<Index>::max()};

  //! coordinates
  VectorDim coordinates_;

  //! Cell id
  Index cell_id_{std::numeric_limits<Index>::max()};

  //! Status
  bool status_{true};
  
  //! Serialize
  friend class boost::serialization::access;
  template <class Archive>
  void save(Archive& ar, const unsigned int version) const {
    ar << id_;
    ar << coordinates_;
    std::cout << "Base\n";
  }

  friend class boost::serialization::access;
  template <class Archive>
  void serialize(Archive& ar, const unsigned int version) {
    std::cout << "Base\n";
  }

};  // ParticleBase class
}  // namespace mpm

#include "particle_base.tcc"

#endif  // MPM_PARTICLEBASE_H__
